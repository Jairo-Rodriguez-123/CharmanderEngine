#pragma once
#include "Prerequisites.h"
#include "SFML/System/Vector2.hpp"
#include "ECS/Component.h"
class Window;

class
  Transform : public Component {
public:
  Transform() = position(0.0f, 0.0f),
                rotation(0.0f, 0.0f),
                scale(1.0f, 1.0f),
                Component(ComponentType::Transform) {}
}

  virtual
    ~Transform() = default;

  //Component
  void
    start() override;

  void
    update(float deltaTime) override;

  void
    render(const EngineUtilities::TSharedPointer<Window>& window) override;

  void
    destroy() {}

  void
  seek(const sf::Vector2f& targetPosition,
       float speed,
       float deltaTime,
       float range) {
    sf::Vector2f direction = targetPosition - m_position;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length > range) {
      direction /= length; // Normalize the direction vector
      m_position += direction * speed * deltaTime; // Move towards the target
    }
  }





  // Getters
  void
    getPosition(sf::Vector2f& position) const { position = m_position; }

  void
    getRotation(sf::Vector2f& rotation) const { rotation = m_rotation; }

  void
    getScale(sf::Vector2f& scale) const { scale = m_scale; }

  // Setters
  void
    setPosition(const sf::Vector2f& position) { m_position = position; }

  void
    setRotation(const sf::Vector2f& rotation) { m_rotation = rotation; }

  void
    setScale(const sf::Vector2f& scale) { m_scale = scale; }

private:
  sf::Vector2f m_position;
  sf::Vector2f m_rotation;
  sf::Vector2f m_scale;
};
