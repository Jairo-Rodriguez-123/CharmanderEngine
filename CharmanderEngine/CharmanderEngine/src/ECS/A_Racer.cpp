#include "ECS/A_Racer.h"
#include "ECS/Transform.h"

// Constructor: passes the name to the base Actor.
A_Racer::A_Racer(const std::string& name)
  : Actor(name) {
}

// Update: copies the logical position to the Transform and updates components.
void
A_Racer::update(float deltaTime) {
  if (auto tr = getComponent<Transform>()) {
    tr->setPosition(sf::Vector2f(logicPosition.x, logicPosition.y));
  }
  Actor::update(deltaTime);
}