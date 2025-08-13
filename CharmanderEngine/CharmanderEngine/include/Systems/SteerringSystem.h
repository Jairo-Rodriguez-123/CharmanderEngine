#pragma once
#include "Prerequisites.h"
#include "ECS/A_Racer.h"
#include "ECS/Transform.h"

/**
 * @struct SteeringConfig
 * @brief Configuration for moving racers via steering behaviors.
 *
 * @details
 * Contains a list of racers (NPCs and optionally the player if in TargetSeek
 * mode) and a seek range threshold used by Transform::seek to decide when to
 * stop moving toward a target.
 */
struct
  SteeringConfig {
  /** List of racers controlled by this system. */
  std::vector<EngineUtilities::TSharedPointer<A_Racer>> racers;

  /** Distance threshold to stop seeking toward a target. */
  float seekRange = 10.f; // Stop threshold for Transform::seek
};

/**
 * @class SteeringSystem
 * @brief Applies steering logic to racers each frame.
 *
 * @details
 * Updates the position and velocity of racers according to their configured
 * SteeringMode. Supports Arrive and Pursuit modes, using helper methods to
 * compute desired movement vectors in engine coordinates.
 */
class
  SteeringSystem {

public:
  /**
   * @brief Construct the system with a configuration.
   * @param cfg Racers and steering parameters.
   */
  SteeringSystem(const SteeringConfig& cfg) : cfg(cfg) {}

  /**
   * @brief Virtual destructor (default).
   */
  ~SteeringSystem() = default;

  /**
   * @brief Per-frame update for all configured racers.
   * @param dt Seconds elapsed since last frame.
   */
  void
    update(float dt);

private:
  /** Immutable configuration containing racers and steering params. */
  SteeringConfig cfg;

  /**
   * @brief Compute Arrive steering vector.
   * @param pos Current position of the racer.
   * @param target Target position to approach.
   * @param speed Current speed of the racer.
   * @param arriveRadius Radius at which to begin slowing down.
   * @return Desired velocity vector toward the target.
   */
  EngineMathLib::CVector2
    arrive_L(const EngineMathLib::CVector2& pos,
      const EngineMathLib::CVector2& target,
      float speed,
      float arriveRadius);

  /**
   * @brief Compute Pursuit steering vector toward a moving target.
   * @param self Racer performing the pursuit.
   * @param target Target racer to intercept.
   * @param speed Current speed of the pursuer.
   * @param maxPrediction Max time ahead to predict target position.
   * @return Desired velocity vector to intercept the target.
   */
  EngineMathLib::CVector2
    pursuit_L(const A_Racer& self,
      const A_Racer& target,
      float speed,
      float maxPrediction);

  /**
   * @brief Convert engine vector to SFML vector.
   * @param v Input CVector2.
   * @return Equivalent sf::Vector2f.
   */
  static sf::Vector2f
    toSF(const EngineMathLib::CVector2& v) { return { v.x, v.y }; }

  /**
   * @brief Convert SFML vector to engine vector.
   * @param v Input sf::Vector2f.
   * @return Equivalent CVector2.
   */
  static
    EngineMathLib::CVector2 toC(const sf::Vector2f& v) { return { v.x, v.y }; }
};
