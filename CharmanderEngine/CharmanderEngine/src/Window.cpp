#include "Window.h"

Window::Window(int width, int height, const std::string& title) {
  //Inicializar la ventana
  m_windowPtr = EngineUtilities::MakeUnique<sf::RenderWindow>(sf::VideoMode(width, height), title);
  //m_window = new sf::RenderWindow(sf::VideoMode(width, height), title);

  if (!m_windowPtr.isNull()) {
      m_windowPtr->setFramerateLimit(60); //Limitar a 60 fps
      MESSAGE("Window", "Window", "Window created succesfully");
  }
  else {
      ERROR("Window", "Window," "Failed to create window");
  }
}

Window::~Window() {
  m_windowPtr.release();
  //SAFE_PTR_RELASE(m_window);
}

void
Window::handleEvents() {
    sf::Event event;
    while (m_windowPtr->pollEvent(event)) {
        //Cerrar la ventana si el usuario lo indica
        if (event.type == sf::Event::Closed) {
         m_windowPtr->close();

        }
    }
}

bool 
Window::isOpen() const {
   //check that window is not null
  if (!m_windowPtr.isNull()) {
    return m_windowPtr->isOpen();
   }
    else {
        ERROR("Window", "isOpen", "Window is null");
        return false;
    }
}

void
Window::clear(const sf::Color& color) {
  if(!m_windowPtr.isNull()) {
    m_windowPtr->clear(color);

  } else {
    ERROR("Window", "isOpen", "Window is null");
  }
}

void 
Window::draw(const sf::Drawable& drawable, const sf::RenderStates& states){
  if (!m_windowPtr.isNull()) {
    m_windowPtr->draw(drawable, states);

   } else {
     ERROR("Window", "isOpen", "Window is null");
   }
}

void
Window::display() {
  if (!m_windowPtr.isNull()) {
    m_windowPtr->display();

  } else {
    ERROR("Window", "isOpen", "Window is null");
  }
}

void Window::destroy() {
  //SAFE_PTR_RELEASE(m_windowPtr);

}


