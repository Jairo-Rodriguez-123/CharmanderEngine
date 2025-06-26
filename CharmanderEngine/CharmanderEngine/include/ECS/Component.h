#pragma once
#include "../Prerequisites.h"
class Window;

/**
* @enum ComponentType
* @brief Tipos de componentes disponibles en el juego.
*/
enum
  ComponentType {
  NONE = 0,
  TRANSFORM = 1,
  SPRITE = 2,
  RENDERER = 3,
  PHYSICS = 4,
  AUDIOSOURCE = 5,
  SHAPE = 6,
  TEXTURE = 7
};

/**
* @class Component
* @brief Clase base abstracta para todos los componentes del sistema ECS (Entity Component System).
*
* La clase Component define la interfaz b?sica que deben implementar todos los componentes del sistema ECS.
* permitiendo actualizar y renderizar el componente, as? como obtener su tipo
*/
class Component {
public:
  Component() = default;

  Component(const ComponentType type) : m_type(type) {}

  virtual
    ~Component() = default;

  virtual void
    start() = 0;

  virtual void
    update(float deltaTime) = 0;

  virtual void
    render(const EngineUtilities::TSharedPointer<Window>& window) = 0;

  virtual void
    destroy() = 0;

  ComponentType
    getType() const { return m_type; }

protected:
  ComponentType m_type; //Tipo de componente
};
