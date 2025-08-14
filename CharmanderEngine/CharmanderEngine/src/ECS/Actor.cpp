#include "ECS/Actor.h"

Actor::Actor(const std::string& actorName) {
  //Setup actor name
  m_name = actorName;

  //Setup shape
  EngineUtilities::TSharedPointer<CShape>
    shape = EngineUtilities::MakeShared<CShape>();
  addComponent(shape);

  //Setup transform
  EngineUtilities::TSharedPointer<Transform>
    transform = EngineUtilities::MakeShared<Transform>();
  addComponent(transform);
}

void
Actor::start() {

}

void
Actor::update(float deltaTime) {
  auto transform = getComponent<Transform>();
  auto shape = getComponent<CShape>();

  if (transform && shape) {
    // Update the position of the shape based on the transform
    shape->setPosition(transform->getPosition());
    shape->setRotation(transform->getRotation().x);
    shape->setScale(transform->getScale());
  }
}

void
Actor::render(const EngineUtilities::TSharedPointer<Window>& window) {
  for (unsigned int i = 0; i < components.size(); i++) {
    auto component = components[i];
    if (component) {
      component->render(window);
    }
  }
}

void
Actor::destroy() {

}

void
Actor::setTexture(const EngineUtilities::TSharedPointer<Texture>& texture) {
  auto shape = getComponent<CShape>();
  if (shape) {
    if (!texture.isNull()) {
      shape->setTexture(texture);
      addComponent(texture);
    }
  }
}

/*void
Actor::update(float deltaTime) {
  auto transform = getComponent<Transform>();
  auto shape = getComponent<CShape>();

  if(transform && shape) {
    // Update the position of the shape based on the transform
    shape->setPosition(transform->getPosition());
    shape->setRotation(transform->getRotation().x);
    shape->setScale(transform->getScale());
  }
}

void
Actor::render(const EngineUtilities::TSharedPointer<Window>& window) {
  for (unsigned int i = 0; i < components.size(); i++) {
    auto shape = components[i].dynamic_pointer_cast<CShape>();
    if (shape) {
      shape->render(window);
    }
  }
}*/