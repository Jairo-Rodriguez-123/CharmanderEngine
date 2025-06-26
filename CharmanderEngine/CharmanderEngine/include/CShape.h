#pragma once
#include "Prerequisites.h"
#include "ECS/Component.h"

/**
 * @class Window
 * @brief Encapsulates an SFML RenderWindow for rendering and window management.
 * The Window class is a forward declaration for the main application window
 */
class Window;

/**
* @class CShape
* @brief Encapsulates an SFML shape and provides an interface for shape manipulation and rendering.
* The CShape class manages an internal SFML shape object, allowing for creation, transformation,
* color modification, and rendering of various shape types. It supports updating the shape's state,
* setting its position, rotation, scale, and fill color, and rendering it to a custom Window class.
* The class also provides access to the underlying SFML shape pointer for advanced operations.
*
* @note The class supports dynamic shape creation and may also manage a vertex array for custom line rendering.
*/
class
  CShape : public Component {
public:
  /**
  * @brief Default constructor for the CShape class.
  * Constructs a CShape object with default values.
  */
  CShape() = default;

  /**
  * @brief Constructs a CShape object with a specified shape type.
  * Initializes the CShape instance, setting the internal shape pointer to nullptr
  * and the shape type to ShapeType::EMPTY.
  *
  * @param shapeType The type of shape to initialize.
  */
  CShape(ShapeType shapeType) : m_shapePtr(nullptr),
    m_shapeType(ShapeType::EMPTY),
    Component(ComponentType::SHAPE) {
  }

  /**
  * @brief Default destructor for the CShape class.
  * Destroys the CShape object and releases any associated resources.
  */
  virtual
    ~CShape() = default;

  /**
  * @brief Creates an SFML shape based on the specified shape type.
  * This function instantiates and returns a pointer to an sf::Shape object
  * corresponding to the provided ShapeType.
  *
  * @param shapeType The type of shape to create.
  * @return A pointer to the created sf::Shape object.
  */
  void
    createShape(ShapeType shapeType);

  /**
  * @brief Updates the shape's state.
  * This function updates the internal state of the shape, such as animations or transformations,
  * based on the elapsed time since the last update.
  *
  * @param deltaTime The time elapsed since the last update, in seconds.
  */
  void
    update(float deltaTime);

  /**
  * @brief Renders the shape to the specified window.
  * This function draws the shape onto the given window.
  *
  * @param window Reference to the Window object where the shape will be rendered.
  */
  void
    render(const EngineUtilities::TSharedPointer<Window>& window);

  /**
  * @brief Sets the position of the shape.
  * This function sets the position of the shape using the specified x and y coordinates.
  *
  * @param x The x-coordinate of the new position.
  * @param y The y-coordinate of the new position.
  */
  void
    setPosition(float x, float y);

  /**
  * @brief Sets the position of the shape.
  * This function sets the position of the shape using a 2D vector.
  *
  * @param position The new position as an sf::Vector2f.
  */
  void
    setPosition(const sf::Vector2f& position);

  /**
  * @brief Sets the fill color of the shape.
  * This function changes the fill color of the shape to the specified color.
  *
  * @param color The new fill color as an sf::Color.
  */
  void
    setFillColor(const sf::Color& color);

  /**
  * @brief Sets the rotation angle of the shape.
  * This function sets the rotation of the shape to the specified angle in degrees.
  *
  * @param angle The rotation angle in degrees.
  */
  void
    setRotation(float angle);

  /**
  * @brief Sets the scale of the shape.
  * This function sets the scale of the shape using a 2D vector.
  *
  * @param scl The new scale as an sf::Vector2f.
  */
  void
    setScale(const sf::Vector2f& scl);

  /**
  * @brief Gets the internal SFML shape pointer.
  * This function returns a pointer to the underlying sf::Shape object managed by this CShape instance.
  * The returned pointer can be used to access or modify the properties of the shape directly.
  *
  * @return A pointer to the internal sf::Shape object, or nullptr if no shape is currently set.
  */
  /*
  sf::Shape*
  getShape() {
    return m_shape;
  }*/

private:
  /**
  * @brief Pointer to the internal SFML shape object.
  * This member holds a pointer to the dynamically allocated sf::Shape instance
  * managed by this CShape object. It represents the graphical shape rendered
  * and manipulated by the class. The pointer may be nullptr if no shape is set.
  */
  //sf::Shape* m_shape;
  EngineUtilities::TSharedPointer<sf::Shape> m_shapePtr;

  /**
  * @brief The type of the shape.
  * This member stores the type of shape currently represented by this CShape instance.
  * It is used to determine the specific kind of shape (e.g., circle, rectangle, etc.)
  * and to manage shape-specific logic.
  */
  ShapeType m_shapeType;

  /**
  * @brief Pointer to the internal SFML vertex array for line rendering.
  * This member holds a pointer to an sf::VertexArray used for rendering lines or
  * custom shapes that require direct vertex manipulation. It may be nullptr if
  * not used for the current shape type.
  */
  sf::VertexArray* m_line;
};