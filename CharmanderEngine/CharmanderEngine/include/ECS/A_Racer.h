#pragma once
#include "Prerequisites.h"
#include "ECS/Actor.h"
#include "ECS/Transform.h"
#include "Vectors/CVector2.h"

/**
 * @enum PlayerControlMode
 * @brief Selects how the player is driven by the game logic.
 *
 * @details
 * - Direct: Input-driven (e.g., WASD), uses accel, friction, and max speed.
 * - TargetSeek: Seeks a stored target; steering is handled by external code.
 */
enum class
  PlayerControlMode {
  Direct, TargetSeek
};

/**
 * @class A_Player
 * @brief Player-controlled actor with direct and target-seeking modes.
 *
 * @details
 * Position authority lives in the attached Transform. This class stores
 * velocity and direct-control params, plus a target used by steering code.
 */
class
  A_Player : public Actor {
public:

  /**
   * @brief Construct a player actor with an engine-visible name.
   * @param name Unique identifier used for debug and lookups.
   */
  A_Player(const std::string& name) : Actor(name) {}

  // ------------- Control mode -------------

  /**
   * @brief Set how the player is controlled.
   * @param m One of PlayerControlMode (Direct or TargetSeek).
   */
  void
    setControlMode(PlayerControlMode m) { controlMode = m; }

  /**
   * @brief Get the current control mode.
   * @return The active PlayerControlMode.
   */
  PlayerControlMode
    getControlMode() const { return controlMode; }

  // ----- Direct control parameters (WASD) -----

  /**
   * @brief Set linear acceleration for Direct mode (px/s^2).
   * @param a Acceleration magnitude.
   */
  void
    setAcceleration(float a) { acceleration = a; }

  /**
   * @brief Get linear acceleration (px/s^2).
   * @return Current acceleration.
   */
  float
    getAcceleration() const { return acceleration; }

  /**
   * @brief Set friction/damping factor (unitless).
   * @param f Coefficient; higher means stronger slow down.
   */
  void
    setFriction(float f) { friction = f; }

  /**
   * @brief Get friction/damping factor (unitless).
   * @return Current friction coefficient.
   */
  float
    getFriction() const { return friction; }

  /**
   * @brief Set maximum speed clamp (px/s).
   * @param s Speed cap applied to velocity magnitude.
   */
  void
    setMaxSpeed(float s) { maxSpeed = s; }

  /**
   * @brief Get maximum speed (px/s).
   * @return Current speed cap.
   */
  float
    getMaxSpeed() const { return maxSpeed; }

  /**
   * @brief Override current velocity vector (px/s).
   * @param v New velocity; caller may clamp to max speed if needed.
   */
  void
    setVelocity(const EngineMathLib::CVector2& v) { velocity = v; }

  /**
   * @brief Get current velocity (px/s).
   * @return Velocity vector.
   */
  EngineMathLib::CVector2
    getVelocity() const { return velocity; }

  // ----- Position/target via Transform as source of truth -----

  /**
   * @brief Read world position from Transform, or {0,0} if missing.
   * @return Current 2D position.
   */
  EngineMathLib::CVector2
    getPosition() {
    auto tr = getComponent<Transform>();
    if (tr) return { tr->getPosition().x, tr->getPosition().y };
    return { 0.f, 0.f };
  }

  /**
   * @brief Write world position into Transform (no-op if missing).
   * @param p Desired 2D position.
   */
  void
    setPosition(const EngineMathLib::CVector2& p) {
    if (auto tr = getComponent<Transform>()) tr->setPosition({ p.x, p.y });
  }

  /**
   * @brief Set target used by TargetSeek logic.
   * @param t World-space destination.
   */
  void
    setTarget(const EngineMathLib::CVector2& t) { target = t; }

  /**
   * @brief Get current target for seeking.
   * @return World-space 2D target.
   */
  EngineMathLib::CVector2
    getTarget() const { return target; }

private:
  /** Current control mode (defaults to Direct). */
  PlayerControlMode controlMode = PlayerControlMode::Direct;

  /** Current velocity of the player in px/s. */
  EngineMathLib::CVector2 velocity{ 0.f, 0.f };

  /** Acceleration for Direct mode (px/s^2). */
  float acceleration = 600.f;

  /** Damping factor applied by Direct mode (unitless). */
  float friction = 6.f;

  /** Maximum allowed linear speed in px/s. */
  float  maxSpeed = 250.f;

  /** Target position used by TargetSeek behavior. */
  EngineMathLib::CVector2 target{ 0.f, 0.f };
};