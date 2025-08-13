#include "ECS/Actor.h"

// Constructor: sets name, creates default Shape and Transform components.
Actor::Actor(const std::string& actorName) {
  m_name = actorName;

  EngineUtilities::TSharedPointer<CShape> shape =
    EngineUtilities::MakeShared<CShape>();
  addComponent(shape);

  EngineUtilities::TSharedPointer<Transform> transform =
    EngineUtilities::MakeShared<Transform>();
  addComponent(transform);
}

// Render: calls render() on all components.
void
Actor::render(const EngineUtilities::TSharedPointer<Window>& window) {
  for (unsigned int i = 0; i < components.size(); i++) {
    auto component = components[i];
    if (component) {
      component->render(window);
    }
  }
}

// Start: currently does nothing.
void
Actor::start() {}

// Update: syncs shape with transform.
void
Actor::update(float deltaTime) {
  auto transform = getComponent<Transform>();
  auto shape = getComponent<CShape>();

  if (transform && shape) {
    shape->setPosition(transform->getPosition());
    shape->setRotation(transform->getRotation().x);
    shape->setScale(transform->getScale());
  }
}

// Destroy: currently does nothing.
void
Actor::destroy() {}

// Set texture: assigns texture to the shape and adds it as a component.
void
Actor::setTexture(const EngineUtilities::TSharedPointer<Texture>& texture) {
  auto shape = getComponent<CShape>();
  if (shape && !texture.isNull()) {
    shape->setTexture(texture);
    addComponent(texture);
  }
}