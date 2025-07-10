#include "ECS/Actor.h"

Actor::Actor(const std::string& actorName) {
  //Setup actor name
  m_name = actorName;

  //Setup shape
  EngineUtilities::TSharedPointer<CShape> shape = EngineUtilities::MakeShared<CShape>();
  addComponent(shape);

  //Setup transform
  EngineUtilities::TSharedPointer<Transform> transform = EngineUtilities::MakeShared<Transform>();
  addComponent(transform);
}

void 
Actor::update(float deltaTime) {
  auto transform = getComponent<TRANSFORM>(); 
  auto shape = getComponent<CShape>();
  
  if (transform && shape) {
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
}