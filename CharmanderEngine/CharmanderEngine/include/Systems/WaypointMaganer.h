#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>

/**
 * @class WaypointManager
 * @brief Stores and provides access to a list of waypoints.
 *
 * @details
 * This class holds a sequence of 2D points (sf::Vector2f) that can be used
 * for AI navigation, track definition, or path-following logic.
 */
class
  WaypointManager {

public:
  /**
   * @brief Replace the current waypoint list.
   * @param pts New list of 2D waypoints.
   */
  void
    setWaypoints(const std::vector<sf::Vector2f>& pts) {
    waypoints_ = pts;
  }

  /**
   * @brief Get the current list of waypoints.
   * @return Const reference to the internal vector of waypoints.
   */
  const std::vector<sf::Vector2f>&
    waypoints() const { return waypoints_; }

private:
  /** Sequence of waypoints in world coordinates. */
  std::vector<sf::Vector2f> waypoints_;
};
