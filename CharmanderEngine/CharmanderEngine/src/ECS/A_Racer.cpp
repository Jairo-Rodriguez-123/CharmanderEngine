#include "ECS/A_Racer.h"
#include "ECS/Transform.h"
#include <algorithm>
#include <random>

A_Racer::A_Racer(const std::string& name, int initialPos)
  : Actor(name) {
}

void
A_Racer::update(float deltaTime) {
  Actor::update(deltaTime);

  if (!m_waypoints.empty()) {
    seekToWaypoint(deltaTime);
  }
}

void
A_Racer::setSpeed(float speed) {
  m_speed = speed;
}

void
A_Racer::setWayPoints(const std::vector<sf::Vector2f>& waypoints) {
  m_waypoints = waypoints;
  resetPos();
}

void
A_Racer::resetPos() {
  if (!m_waypoints.empty()) {
    m_currentWaypointIndex = m_initialPosIndex;
    getComponent<Transform>()->setPosition(m_waypoints[m_currentWaypointIndex]);
  }
}

void
A_Racer::seekToWaypoint(float deltaTime) {
  auto transform = getComponent<Transform>();
  if (!transform || m_waypoints.empty()) return;

  sf::Vector2f pos = transform->getPosition();
  sf::Vector2f targetPos = m_waypoints[m_currentWaypointIndex];
  sf::Vector2f direction = targetPos - pos;
  float dist = std::sqrt(direction.x * direction.x + direction.y * direction.y);

  
  constexpr float epsilon = 1e-6f;


  if (dist <= m_arrivalThreshold * 2.0f && dist > m_arrivalThreshold) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_real_distribution<float>
      approachSpeedDist(m_minApproachSpeed, m_maxApproachSpeed);

    m_speed = approachSpeedDist(gen);
  }

  
  if (dist <= m_arrivalThreshold) {
    int prevWaypoint = m_currentWaypointIndex;
    m_currentWaypointIndex = (m_currentWaypointIndex + 1) % m_waypoints.size();

   
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_real_distribution<float>
      waypointSpeedDist(m_minWaypointSpeed, m_maxWaypointSpeed);

    m_speed = waypointSpeedDist(gen);

    
    if (m_currentWaypointIndex == 0 &&
      prevWaypoint == static_cast<int>(m_waypoints.size()) - 1) {
      if (m_hasStartedLap) {
        m_laps++;
        m_hasStartedLap = false;
        if (m_laps >= m_totalLaps) {
          m_speed = 0.f;
        }
      }
    }
    else if (m_currentWaypointIndex != 0) {
      m_hasStartedLap = true;
    }
  }

 
  if (dist > epsilon) {
    direction /= dist;
    sf::Vector2f velocity = direction * m_speed * deltaTime;
    transform->setPosition(pos + velocity);
  }
}