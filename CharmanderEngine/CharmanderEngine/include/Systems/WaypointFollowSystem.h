#pragma once
#include <vector>
#include <limits>
#include <random>
#include "Prerequisites.h"
#include "ECS/A_Racer.h"

/**
 * @struct WaypointFollowConfig
 * @brief Configuration for AI racers to follow a waypoint circuit.
 *
 * @details
 * Stores racer list, waypoint list, parameters for when to advance to the
 * next waypoint, and "humanization" settings to make AI movement less
 * robotic. Also contains constraints to keep racers on track and slow them
 * in tight corners.
 */
struct
  WaypointFollowConfig {
  /** Racers to control via waypoint following logic. */
  std::vector<EngineUtilities::TSharedPointer<A_Racer>> racers;

  /** Pointer to ordered list of waypoints defining the track. */
  const std::vector<sf::Vector2f>* waypoints = nullptr;

  /** Distance threshold to advance to the next waypoint. */
  float arriveRadiusForAdvance = 12.f;

  // ----- Humanization knobs -----

  /** Delay before reacting to a new waypoint index (seconds). */
  float reactionDelay = 0.50f;

  /** Random offset radius applied to waypoint target (pixels). */
  float waypointNoiseRadius = 10.f;

  /** Look-ahead waypoints (0�2) beyond the next to aim toward. */
  int   lookAhead = 2;

  /** Chance to briefly pick a neighbor waypoint as target. */
  float mistakeProb = 0.5f;

  /** Minimum seconds between mistakes. */
  float mistakeCooldown = 5.0f;

  // ----- Track constraints -----

  /** Max lateral distance from segment to allow advancing. */
  float corridorWidth = 80.f;

  // ----- Corner speed limiter -----

  /** Enable slowdown on sharp turns for NPCs. */
  bool  cornerSlowdownEnabled = true;

  /** No slowdown for angles below this (degrees). */
  float cornerMinAngleDeg = 25.f;

  /** Full slowdown for angles at or above this (degrees). */
  float cornerMaxAngleDeg = 95.f;

  /** Minimum speed factor to apply on sharpest corners. */
  float cornerMinFactor = 0.82f;
};

/**
 * @class WaypointFollowSystem
 * @brief Assigns and updates waypoint targets for AI racers each frame.
 *
 * @details
 * Controls AI racers by steering them toward sequential waypoints. Includes
 * logic to advance indices when near or past a waypoint, add random noise to
 * avoid robotic movement, occasionally introduce mistakes, and slow down on
 * sharp corners. Keeps racers within a corridor to prevent cutting the track.
 */
class
  WaypointFollowSystem {

public:
  /**
   * @brief Construct system with config and initialize state.
   * @param cfg Configuration for waypoint following behavior.
   */
  WaypointFollowSystem(const WaypointFollowConfig& cfg)
    : cfg(cfg),
    indices(cfg.racers.size(), 0),
    reactTimers(cfg.racers.size(), 0.f),
    mistakeTimers(cfg.racers.size(), 0.f),
    rng(std::random_device{}()),
    uni(-1.f, 1.f),
    uni01(0.f, 1.f) {
  }

  /**
   * @brief Virtual destructor (default).
   */
  ~WaypointFollowSystem() = default;

  /**
   * @brief Initialize waypoint indices based on current positions.
   *
   * @details
   * Picks the nearest waypoint to each racer as its starting target. This
   * avoids "teleport" jumps when the race starts and ensures smooth entry
   * into the AI path.
   */
  void
    primeFromPositions();

  /**
   * @brief Update AI racer targets once per frame.
   *
   * @details
   * Advances target index when the racer is near it, near the actual target,
   * or has moved far enough along the segment within a corridor. Applies
   * corner speed limiting for NPCs and random target noise/mistakes for
   * humanization.
   *
   * @param dt Seconds since last frame.
   */
  void
    update(float dt);

private:
  /** Config parameters for waypoint following. */
  WaypointFollowConfig cfg;

  /** Current waypoint index for each racer. */
  std::vector<size_t> indices;

  /** Per-racer delay timers before reacting to new waypoints. */
  std::vector<float>  reactTimers;

  /** Per-racer timers controlling mistake frequency. */
  std::vector<float>  mistakeTimers;

  /** Random number generator. */
  std::mt19937 rng;

  /** Distribution for random noise in range [-1, 1]. */
  std::uniform_real_distribution<float> uni;

  /** Distribution for random chance in range [0, 1]. */
  std::uniform_real_distribution<float> uni01;
};