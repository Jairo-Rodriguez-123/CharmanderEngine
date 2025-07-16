#include <BaseApp.h>

BaseApp::~BaseApp() {
}

int
BaseApp::run() {
  if (!init()) {
    ERROR("BaseApp",
      "run",
      "Initializes result on a false statement, check method validations");
  }
  while (m_windowPtr->isOpen()) {
    m_windowPtr->handleEvents();
    update();
    render();
  }
  destroy();
  return 0;
}

bool
BaseApp::init() {
  m_windowPtr = EngineUtilities::MakeShared<Window>(1920, 1080, "Graphos");
  if (!m_windowPtr) {
    ERROR("BaseApp",
      "init",
      "Failed to create window pointer, check memory allocation");
    return false;
  }

  void 
    BaseApp::update() {
    if (!m_ACircle.isNull()) {
      //m_ACircle->update(0);
      
      //obtener el componente de transform del actor
      auto transform = m_ACircle->getComponent<TransformComponent>();
      if (transform.isNull)() {
        return;
      }

      //Posicion actual del destino (Punto recorrido)
      sf::Vector2f currentPosition = transform->getPosition();

      //Llamar al seek del transform
      transform->seek(currentPosition, 200.0f, deltaTime,10.0f);
    }
  }




  //m_window = new Window(1920, 1080, "Graphos");
  //m_circle = new sf::CircleShape(100.0f);
  //m_circle->setFillColor(sf::Color::Green);
  //m_circle->setPosition(200.f, 150.f);
  m_shapePtr = EngineUtilities::MakeShared<Shape>();
  if (m_shapePtr) {
    m_shapePtr->createShape(ShapeType::CIRCLE);
    m_shapePtr->setFillColor(sf::Color::Green);
    m_shapePtr->setPosition(200.f, 150.f);
  }
  return true;
}

void
BaseApp::update() {
  if (!m_windowPtr.isNull()) {
    m_windowPtr->update();
  }
  //Update actors
  if (!m_ACirlce.isNull()) {
    m_ACirlce->update(m_windowPtr->m_deltaTime.asSeconds());

    //Posicion del destino (Punto recorrido)
    sf::Vector2f targetPos(1200.f, 150.f);

    //llamar al seek del transform
    m_ACirlce->getComponent<Transform>()->seek(targetPos, 200.0f, m_windowPtr->m_deltaTime.asSeconds(), 10.0f);

    void
      BaseApp::render() {

      if (!m_windowPtr) {
        return;
      }
      m_windowPtr->clear();
      if (m_shapePtr) {
        m_shapePtr->render(m_windowPtr);
      }
      m_windowPtr->display();
    }

    void
      BaseApp::destroy() {
      //delete m_circle;
      //m_window->destroy();
    }
  }