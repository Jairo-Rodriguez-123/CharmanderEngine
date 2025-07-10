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
}

void
BaseApp::render() {
  // Limpiar, dibujar y mostrar
  //m_windowPtr->clear();
  //m_windowPtr->draw(*m_circle);
  //m_windowPtr->display();

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
