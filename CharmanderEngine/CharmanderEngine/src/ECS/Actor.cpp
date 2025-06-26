#include "ECS/Actor.h"

Actor::Actor(const std::string& actorName) {
  //Setup actor name
  m_name = actorName;

  //Setup shape
  EngineUtilities::TSharedPointer<CShape> shape = EngineUtilities::MakeShared<CShape>();
  addComponent(shape);

  //Setup transform
  //EngineUtilities::TSharedPointer<Transform> transform = EngineUtilities::MakeShared<Transform>();
  //addComponent(transform);
}

void
Actor::render(const EngineUtilities::TSharedPointer<Window>& window) {

}