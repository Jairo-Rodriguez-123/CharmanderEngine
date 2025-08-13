#pragma once
#include "Prerequisites.h"
#include "ECS/Component.h"
#include "ECS/Texture.h"

class
	Window;

/**
 * @class CShape
 * @brief Derived component representing a graphical shape.
 *
 * This component encapsulates a drawable SFML shape, providing methods to
 * create, position, transform, and render it. It supports different shape types
 * defined by the ShapeType enum.
 */
class
	CShape : public Component {

public:
	/**
	 * @brief Default constructor.
	 */
	CShape() = default;

	/**
	 * @brief Constructor with shape type initialization.
	 * @param shapeType Type of the shape to create.
	 */
	CShape(ShapeType shapeType) :
		m_shapePtr(nullptr),
		m_shapeType(ShapeType::EMPTY),
		Component(ComponentType::SHAPE) {
	}

	/**
	 * @brief Destructor.
	 */
	virtual
		~CShape() = default;

	/**
	 * @brief Creates the shape of the specified type.
	 * @param shapeType Shape type enum value.
	 */
	void
		createShape(ShapeType shapeType);

	/**
	 * @brief Component lifecycle start method.
	 *
	 * Called when the component is initialized in the system.
	 */
	void
		start() override;

	/**
	 * @brief Updates the shape state.
	 * @param deltaTime Time elapsed since last update.
	 *
	 * Can be used to animate or adjust the shape's properties dynamically.
	 */
	void
		update(float deltaTime) override;

	/**
	 * @brief Renders the shape to the provided window.
	 * @param window Shared pointer to the target window.
	 */
	void
		render(const EngineUtilities::TSharedPointer<Window>& window) override;

	/**
	 * @brief Cleans up resources.
	 */
	void
		destroy() override;

	/**
	 * @brief Sets the position of the shape.
	 * @param x X coordinate.
	 * @param y Y coordinate.
	 */
	void
		setPosition(float x, float y);

	/**
	 * @brief Sets the position of the shape using a vector.
	 * @param position 2D position vector.
	 */
	void
		setPosition(const sf::Vector2f& position);

	/**
	 * @brief Sets the fill color of the shape.
	 * @param color SFML color object.
	 */
	void
		setFillColor(const sf::Color& color);

	/**
	 * @brief Sets the rotation angle of the shape in degrees.
	 * @param angle Rotation angle.
	 */
	void
		setRotation(float angle);

	/**
	 * @brief Sets the scale of the shape.
	 * @param scl 2D scale vector.
	 */
	void
		setScale(const sf::Vector2f& scl);

	void
		setTexture(const EngineUtilities::TSharedPointer<Texture>& texture);

	EngineUtilities::TSharedPointer<sf::Shape> getShapePtr() { return m_shapePtr; }

private:
	EngineUtilities::TSharedPointer<sf::Shape>
		m_shapePtr; ///< Shared pointer to the SFML shape instance.

	ShapeType
		m_shapeType; ///< Enum representing the current shape type.

	sf::VertexArray*
		m_line; ///< Pointer for line rendering (optional).



};