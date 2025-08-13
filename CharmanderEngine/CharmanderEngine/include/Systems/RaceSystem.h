// Systems/RaceSystem.h
#pragma once
#include "Prerequisites.h"
#include "ECS/Actor.h"
#include "ECS/Transform.h"
#include <vector>
#include "Vectors/CVector2.h"

/**
 * @struct RaceConfig
 * @brief Configuration data for RaceSystem setup.
 *
 * @details
 * Holds the set of racers (player at index 0, then NPCs), a closed-path list
 * of waypoints that defines the circuit, and a checkpoint radius used to
 * validate waypoint passes for lap progression.
 */
struct
  RaceConfig {
  /** All race actors. Convention: index 0 is the player. */
  std::vector<EngineUtilities::TSharedPointer<Actor>> actors; /* Player + NPCs */

  /** Pointer to circuit waypoints (assumed closed loop). */
  const std::vector<sf::Vector2f>* waypoints = nullptr;       /* closed circuit */

  /** Radius to consider a checkpoint reached. */
  float checkpointRadius = 12.f;
};

/**
 * @class RaceSystem
 * @brief Computes lap progress, standings, and timing over a waypoint circuit.
 *
 * @details
 * Tracks per-actor lap data, parametric path progress, wrap counts (virtual
 * laps), and debounced lap timing for the player HUD. Standings are derived
 * from total parametric distance traveled along the path (wraps + s).
 */
class
  RaceSystem {

public:
  /**
   * @brief Construct a race system with configuration.
   * @param cfg Actors, waypoints, and checkpoint radius.
   */
  RaceSystem(const RaceConfig& cfg);

  /**
   * @brief Default virtual destructor.
   */
  ~RaceSystem() = default;

  /**
   * @brief Per-frame update of lap state, standings, and timers.
   * @param dt Seconds since last frame.
   */
  void
    update(float dt);

  /**
   * @brief Compute standings by descending progress.
   * @return Indices into cfg.actors sorted by progress (best first).
   */
  std::vector<int>
    getStandings() const;

  // ---------------- Accessors ----------------

  /**
   * @brief Read-only access to per-actor lap component.
   * @param i Actor index in cfg.actors.
   * @return Const reference to LapComponent.
   */
  const LapComponent&
    getLapData(size_t i) const { return laps[i]; }

  /**
   * @brief Get the NPC total virtual laps (wraps) for ranking.
   * @param i Actor index in cfg.actors.
   * @return Wrap count or 0 if out of range.
   */
  int
    getNpcLaps(size_t i) const { return (i < wraps.size() ? wraps[i] : 0); }

  // ---------------- Player timing ----------------

  /**
   * @brief Enable or disable player lap timing accumulation.
   * @param b True to enable timing, false to pause.
   */
  void
    setTimingActive(bool b) { timingActive = b; }

  /**
   * @brief Current lap time for the player (seconds).
   * @return Elapsed time of the active lap.
   */
  float
    getPlayerCurrentLapTime() const { return playerLapTime; }

  /**
   * @brief Best lap time for the player, if available.
   * @return Best lap or -1.f if not recorded yet.
   */
  float
    getPlayerBestLapTime() const { return (bestLapValid ? playerBestLap : -1.f); }

  /**
   * @brief Whether a valid best lap exists.
   * @return True if best lap has been set.
   */
  bool
    hasBestLap() const { return bestLapValid; }

private:
  /** Immutable configuration used by the system. */
  RaceConfig cfg;

  // ---------------- Per-actor state ----------------

  /** Per-actor lap data. Index 0 used for player HUD; NPCs for bookkeeping. */
  std::vector<LapComponent> laps;

  /** Continuous progress metric: wraps * totalLen + s (param length). */
  std::vector<float> progress;

  /** Elapsed runtime per actor (can feed AI or telemetry). */
  std::vector<float> elapsed;

  /** Previous local path parameter s, to detect forward wraps. */
  std::vector<float> lastS;

  // ---------------- Virtual laps (true ranking) ----------------

  /** Wrap count increments on each start/finish crossing for all actors. */
  std::vector<int>   wraps;

  /** Per-actor cooldown to debounce wrap detection. */
  std::vector<float> wrapCooldown;

  /** Global wrap debounce time (seconds). */
  float wrapDebounceSec = 0.35f;

  // ---------------- Player HUD lap management ----------------

  /** Actor index owning the HUD lap (usually 0 = player). */
  int   lapOwnerIndex = 0;

  /** Debounce time for lap completion (seconds). */
  float lapDebounceSec = 0.35f;

  /** Current cooldown for lap debounce. */
  float lapCooldown = 0.f;

  /** Armed when conditions to commit a lap are met. */
  bool  lapArmed = false;

  // ---------------- Player timing ----------------

  /** If true, accumulate player lap time. */
  bool  timingActive = false;

  /** Player current lap time (seconds). */
  float playerLapTime = 0.f;

  /** Best lap time recorded for player (seconds). */
  float playerBestLap = 0.f;

  /** True when playerBestLap contains a valid result. */
  bool  bestLapValid = false;

  // ---------------- Parametrized path ----------------

  /** Prefix sums of segment lengths to map positions onto the path. */
  std::vector<float> prefix;

  /** Total circuit length (sum of segments). */
  float totalLen = 0.f;

  /** True if path connects last to first waypoint. */
  bool  closedLoop = true;

  // ---------------- Helpers ----------------

  /**
   * @brief Get 2D position of an actor using its Transform.
   * @param a Shared pointer to the actor.
   * @return 2D position as EngineMathLib::CVector2.
   */
  static EngineMathLib::CVector2
    getActorPos(const EngineUtilities::TSharedPointer<Actor>& a);

  /**
   * @brief Convert an sf::Vector2f to EngineMathLib::CVector2.
   * @param v Input vector.
   * @return Converted vector.
   */
  static EngineMathLib::CVector2
    toC(const sf::Vector2f& v) { return { v.x, v.y }; }

  /**
   * @brief Project point p onto segment ab and get local progress [0..1].
   * @param p Query point.
   * @param a Segment start.
   * @param b Segment end.
   * @return Scalar progress along ab in [0,1].
   */
  float
    segProgress(const EngineMathLib::CVector2& p,
      const EngineMathLib::CVector2& a,
      const EngineMathLib::CVector2& b) const;

  /**
   * @brief Compute parametric length s along the whole path for point p.
   * @param p Query point.
   * @return Distance along path in [0,totalLen).
   */
  float
    sAlongPath(const EngineMathLib::CVector2& p) const;

  /**
   * @brief Precompute prefix sums and total length for the circuit path.
   */
  void
    buildCircuitMeter();

  /**
   * @brief Euclidean distance between two SFML vectors.
   * @param A First point.
   * @param B Second point.
   * @return Distance scalar.
   */
  static float
    dist(const sf::Vector2f& A, const sf::Vector2f& B) {
    float dx = B.x - A.x, dy = B.y - A.y;
    return EngineMathLib::sqrt(dx * dx + dy * dy);
  }

  /**
   * @brief Euclidean distance between two engine vectors.
   * @param A First point.
   * @param B Second point.
   * @return Distance scalar.
   */
  static float
    distC(const EngineMathLib::CVector2& A,
      const EngineMathLib::CVector2& B) {
    float dx = B.x - A.x, dy = B.y - A.y;
    return EngineMathLib::sqrt(dx * dx + dy * dy);
  }
};