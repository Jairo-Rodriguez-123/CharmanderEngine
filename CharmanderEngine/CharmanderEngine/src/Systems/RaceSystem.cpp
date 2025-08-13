// Systems/RaceSystem.cpp
#include "Systems/RaceSystem.h"
#include "Utilities/EngineMath.h"
#include <algorithm>
#include <limits>

// Constructor: initializes race state, lap data, and progress tracking
RaceSystem::RaceSystem(const RaceConfig& inCfg)
  : cfg(inCfg) {

  buildCircuitMeter();

  const size_t N = cfg.actors.size();
  laps.resize(N);
  progress.assign(N, 0.f);
  elapsed.assign(N, 0.f);
  lastS.assign(N, 0.f);

  // HUD player anti-bounce timer
  lapCooldown = lapDebounceSec;
  lapArmed = false;

  // Wrap counts for ranking
  wraps.assign(N, -1);
  wrapCooldown.assign(N, 0.f);

  // Timing variables
  timingActive = false;
  playerLapTime = 0.f;
  playerBestLap = 0.f;
  bestLapValid = false;

  // Initialize per-actor lap and progress
  if (cfg.waypoints && !cfg.waypoints->empty()) {
    const auto& W = *cfg.waypoints;
    for (size_t i = 0; i < N; ++i) {
      auto& a = cfg.actors[i];

      LapComponent lc{};
      lc.lap = 0;
      lc.checkpoint = 0;

      if (!a.isNull()) {
        EngineMathLib::CVector2 p = getActorPos(a);

        // Find nearest waypoint
        float best = std::numeric_limits<float>::max();
        size_t bestIdx = 0;
        for (size_t k = 0; k < W.size(); ++k) {
          EngineMathLib::CVector2 wk{ W[k].x, W[k].y };
          float d = distC(p, wk);
          if (d < best) { best = d; bestIdx = k; }
        }
        lc.checkpoint = static_cast<int>(bestIdx);

        // Init progress along path
        float s0 = sAlongPath(p);
        lastS[i] = s0;
        progress[i] = s0;
      }

      elapsed[i] = 0.f;
      laps[i] = lc;
    }
  }
}

// Main update: progress, lap timing, wrap detection
void
RaceSystem::update(float dt) {
  if (!cfg.waypoints || cfg.waypoints->size() < 2) return;
  const auto& W = *cfg.waypoints;
  const size_t Nw = W.size();
  const size_t Na = cfg.actors.size();
  if (Nw < 2 || Na == 0) return;

  // Decrease cooldowns
  if (lapCooldown > 0.f) {
    lapCooldown -= dt;
    if (lapCooldown < 0.f) lapCooldown = 0.f;
  }
  for (size_t i = 0; i < Na; ++i) {
    if (wrapCooldown[i] > 0.f) {
      wrapCooldown[i] -= dt;
      if (wrapCooldown[i] < 0.f) wrapCooldown[i] = 0.f;
    }
  }

  // Player lap timer
  if (timingActive) playerLapTime += dt;

  for (size_t i = 0; i < Na; ++i) {
    auto& a = cfg.actors[i];
    if (a.isNull()) continue;

    elapsed[i] += dt;
    EngineMathLib::CVector2 p = getActorPos(a);

    // Advance checkpoint if near and forward
    int idx = (laps[i].checkpoint < 0) ? 0 : laps[i].checkpoint;
    int next = (idx + 1) % static_cast<int>(Nw);

    EngineMathLib::CVector2 wp = toC(W[static_cast<size_t>(idx)]);
    EngineMathLib::CVector2 wpN = toC(W[static_cast<size_t>(next)]);

    float d = distC(p, wp);
    bool near = (d <= cfg.checkpointRadius);

    EngineMathLib::CVector2 seg = wpN - wp;
    EngineMathLib::CVector2 rel = p - wp;
    bool forward = (seg.x * rel.x + seg.y * rel.y) > 0.f;

    if (near && forward) laps[i].checkpoint = next;

    // Wrap and lap detection
    float sNow = sAlongPath(p);
    float sPrev = lastS[i];

    if (totalLen > 0.f) {
      float ds = sNow - sPrev;

      // Wraps for race ranking
      if (ds < -0.5f * totalLen && wrapCooldown[i] <= 0.f) {
        wraps[i] += 1;
        wrapCooldown[i] = wrapDebounceSec;
      }

      // Player lap tracking
      if (i == static_cast<size_t>(lapOwnerIndex)) {
        if (ds < -0.5f * totalLen && lapCooldown <= 0.f) {
          if (!lapArmed) {
            lapArmed = true;
            lapCooldown = lapDebounceSec;
            playerLapTime = 0.f;
          }
          else {
            laps[i].lap += 1;
            if (timingActive) {
              float thisLap = playerLapTime;
              if (thisLap > 0.f) {
                if (!bestLapValid || thisLap < playerBestLap) {
                  playerBestLap = thisLap;
                  bestLapValid = true;
                }
              }
              playerLapTime = 0.f;
            }
            lapCooldown = lapDebounceSec;
          }
        }
      }
    }

    lastS[i] = sNow;
    progress[i] = static_cast<float>(wraps[i]) * totalLen + sNow;
  }
}

// Get actor indices sorted by progress
std::vector<int>
RaceSystem::getStandings() const {
  std::vector<int> order;
  order.reserve(progress.size());
  for (size_t i = 0; i < progress.size(); ++i)
    order.push_back(static_cast<int>(i));

  std::sort(order.begin(), order.end(),
    [&](int L, int R) {
      return progress[static_cast<size_t>(L)] > progress[static_cast<size_t>(R)];
    });
  return order;
}

// Helper: get actor's position from Transform
EngineMathLib::CVector2
RaceSystem::getActorPos(const EngineUtilities::TSharedPointer<Actor>& a) {
  auto tr = a->getComponent<Transform>();
  if (tr) return EngineMathLib::CVector2::sfToCVector2(tr->getPosition());
  return EngineMathLib::CVector2{ 0.f, 0.f };
}

// Helper: progress ratio along segment
float
RaceSystem::segProgress(const EngineMathLib::CVector2& p,
  const EngineMathLib::CVector2& a,
  const EngineMathLib::CVector2& b) const {
  EngineMathLib::CVector2 ab = b - a;
  EngineMathLib::CVector2 ap = p - a;
  float ab2 = ab.x * ab.x + ab.y * ab.y;
  if (ab2 <= 1e-6f) return 0.f;
  float t = (ap.x * ab.x + ap.y * ab.y) / ab2;
  if (t < 0.f) t = 0.f;
  if (t > 1.f) t = 1.f;
  return t;
}

// Helper: distance along the path from start
float
RaceSystem::sAlongPath(const EngineMathLib::CVector2& p) const {
  if (!cfg.waypoints || cfg.waypoints->size() < 2) return 0.f;
  const auto& W = *cfg.waypoints;
  const size_t N = W.size();

  float bestD2 = std::numeric_limits<float>::max();
  float bestS = 0.f;

  for (size_t i = 0; i < N; ++i) {
    size_t j = (i + 1) % N;
    if (!closedLoop && j == 0) break;

    EngineMathLib::CVector2 A = toC(W[i]);
    EngineMathLib::CVector2 B = toC(W[j]);
    float t = segProgress(p, A, B);

    EngineMathLib::CVector2 proj{ A.x + (B.x - A.x) * t,
                                  A.y + (B.y - A.y) * t };
    float dx = proj.x - p.x, dy = proj.y - p.y;
    float d2 = dx * dx + dy * dy;
    if (d2 < bestD2) {
      bestD2 = d2;
      float base = (i < prefix.size() ? prefix[i] : 0.f);
      float segLen = EngineMathLib::sqrt((B.x - A.x) * (B.x - A.x) +
        (B.y - A.y) * (B.y - A.y));
      bestS = base + t * segLen;
    }
  }

  if (totalLen > 0.f) {
    if (bestS >= totalLen) bestS = EngineMathLib::mod(bestS, totalLen);
    if (bestS < 0.f)       bestS += totalLen;
  }
  return bestS;
}

// Helper: precomputes prefix lengths for path segments
void
RaceSystem::buildCircuitMeter() {
  prefix.clear();
  totalLen = 0.f;
  closedLoop = true;

  if (!cfg.waypoints || cfg.waypoints->size() < 2) return;
  const auto& W = *cfg.waypoints;
  const size_t N = W.size();

  prefix.resize(N, 0.f);
  for (size_t i = 1; i < N; ++i) {
    float seg = dist(W[i - 1], W[i]);
    totalLen += seg;
    prefix[i] = totalLen;
  }
  if (closedLoop) totalLen += dist(W[N - 1], W[0]);
}