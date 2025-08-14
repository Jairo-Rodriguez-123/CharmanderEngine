#pragma once
#include "ECS/Actor.h"

/**
 * @class A_Player
 * @brief Represents a player actor in the ECS system, with additional logic for podium, laps, and control.
 */
class
  A_Player : public Actor {
public:
  /**
   * @brief Constructs a player actor with a given name and initial position.
   * @param name The name of the player.
   * @param initialPos The initial position index of the player.
   */
  A_Player(const std::string& name, int initialPos);

  /**
   * @brief Updates the player actor with the given delta time.
   * @param deltaTime Time elapsed since last update.
   */
  void
    update(float deltaTime) override;

  /**
   * @brief Gets the total time accumulated by the player.
   * @return The total time as a float.
   */
  float
    getTotalTime() const;

  /**
   * @brief Gets the index of the last waypoint passed by the player.
   * @return The index of the last waypoint.
   */
  int
    getLastWaypointPassed() const;

  /**
   * @brief Gets the distance to the next waypoint for the player.
   * @return The distance to the next waypoint as a float.
   */
  float
    getDistToNextWaypoint() const;

  /**
   * @brief Checks if the player is currently frozen.
   * @return True if the player is frozen, false otherwise.
   */
  bool
    isFrozen() const;

  /**
   * @brief Freezes the player, preventing further updates or movement.
   */
  void
    freeze();

private:
  /**
   * @brief The movement speed of the player in units per second.
   */
  float moveSpeed = 200.0f; // Units per second

  /**
   * @brief Handles input for the player, updating state based on input and delta time.
   * @param deltaTime Time elapsed since last update.
   */
  void HandleInput(float deltaTime);

  /**
   * @brief The index of the last waypoint passed by the player.
   */
  int m_lastWaypointPassed = 0;

  /**
   * @brief The total time accumulated by the player.
   */
  float m_totalTime = 0.f;

  /**
   * @brief Indicates whether the player is currently frozen.
   */
  bool m_frozen = false;
};