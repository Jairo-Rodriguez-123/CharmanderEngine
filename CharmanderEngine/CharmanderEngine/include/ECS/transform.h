#pragma once
#include "Prerequisites.h"
#include "SFML/System/Vector2.hpp"
#include "ECS/Component.h"
class Window;

class
  Transform : public Component {
public:
  Transform() = default;

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
    destroy() override;

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
