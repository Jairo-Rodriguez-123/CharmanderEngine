#include "ECS/A_Racer.h"
#include "ECS/Transform.h"


A_Racer::A_Racer(const std::string& name)
  : Actor(name) {
}

void
A_Racer::update(float deltaTime) {
  if (auto tr = getComponent<Transform>()) {
    tr->setPosition(sf::Vector2f(logicPosition.x, logicPosition.y));
  }
  Actor::update(deltaTime);
}