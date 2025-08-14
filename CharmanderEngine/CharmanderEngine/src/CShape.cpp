#include "CShape.h"
#include "Window.h"
#include "ECS/Texture.h"

void
CShape::createShape(ShapeType type) {
  m_shapeType = type;
  switch (type) {
  case ShapeType::CIRCLE: {
    //sf::CircleShape* circle = new sf::CircleShape(10.f); //Example radius
    auto circleSP = EngineUtilities::MakeShared<sf::CircleShape>(10.f); // Example radius
    circleSP->setFillColor(sf::Color::White);
    m_shapePtr = circleSP.dynamic_pointer_cast<sf::Shape>();
    break;
  }
  case ShapeType::RECTANGLE: {
    //sf::RectangleShape* rectangle = new sf::RectangleShape(sf::Vector2f(100.f, 50.f)); // Example size
    auto rectSP = EngineUtilities::MakeShared<sf::RectangleShape>(sf::Vector2f(100.f, 50.f)); // Example size
    rectSP->setFillColor(sf::Color::White);
    m_shapePtr = rectSP.dynamic_pointer_cast<sf::Shape>();
    break;
  }
  case ShapeType::TRIANGLE: {
    //sf::ConvexShape* triangle = new sf::ConvexShape(3);
    auto triSP = EngineUtilities::MakeShared<sf::ConvexShape>(3);
    triSP->setPoint(0, { 0,0 });
    triSP->setPoint(1, { 50,100 });
    triSP->setPoint(2, { 100,0 });
    triSP->setFillColor(sf::Color::White);
    m_shapePtr = triSP.dynamic_pointer_cast<sf::Shape>();
    break;
  }
  case ShapeType::POLYGON: {
    //sf::ConvexShape* polygon = new sf::ConvexShape(5); // Example with 5 points
    auto polySP = EngineUtilities::MakeShared<sf::ConvexShape>(5); // Example with 5 points
    polySP->setPoint(0, { 0,0 });
    polySP->setPoint(1, { 50,100 });
    polySP->setPoint(2, { 100,0 });
    polySP->setPoint(3, { 75,-50 });
    polySP->setPoint(4, { -25,-50 });
    polySP->setFillColor(sf::Color::White);
    m_shapePtr = polySP.dynamic_pointer_cast<sf::Shape>();
    break;
  }
  default:
    m_shapePtr.reset();
    ERROR("CShape", "createShape", "Unknown shape type");
    return;
  }
}

void
CShape::start() {

}

void
CShape::update(float deltaTime) {
  // Update logic for the shape can be added here if needed
}

void
CShape::render(const EngineUtilities::TSharedPointer<Window>& window) {
  if (m_shapePtr) {
    window->draw(*m_shapePtr);
  }
}

void
CShape::destroy() {
  //m_shapePtr.reset(); // Reset the shared pointer to release the shape
}

void
CShape::setPosition(float x, float y) {
  if (m_shapePtr) {
    m_shapePtr->setPosition({ x, y });
  }
  else {
    ERROR("CShape", "setPosition", "Shape is not initialized");
  }
}

void
CShape::setPosition(const sf::Vector2f& position) {
  if (m_shapePtr) {
    m_shapePtr->setPosition(position);
  }
  else {
    ERROR("CShape", "setPosition", "Shape is not initialized");
  }
}

/*
void
CShape::setPosition(const sf::Vector2f& position) {
  if (m_shape) {
    m_shape->setPosition(position);
  }
  else {
    ERROR("CShape", "setPosition", "Shape is not initialized");
  }
}
*/

void
CShape::setFillColor(const sf::Color& color) {
  if (m_shapePtr) {
    m_shapePtr->setFillColor(color);
  }
  else {
    ERROR("CShape", "setFillColor", "Shape is not initialized");
  }
}

void
CShape::setRotation(float angle) {
  if (m_shapePtr) {
    m_shapePtr->setRotation(sf::degrees(angle));
  }
  else {
    ERROR("CShape", "setRotation", "Shape is not initialized");
  }
}

void
CShape::setScale(const sf::Vector2f& scl) {
  if (m_shapePtr) {
    m_shapePtr->setScale(scl);
  }
  else {
    ERROR("CShape", "setScale", "Shape is not initialized");
  }
}

void
CShape::setTexture(const EngineUtilities::TSharedPointer<Texture>& texture) {
  if (!texture.isNull()) {
    m_shapePtr->setTexture(&texture->getTexture());
  }
}