#pragma once

#include "../Prerequisites.h"

class
	Window;

/**
 * @enum ComponentType
 * @brief Enumerates the possible types of components
 * that can be attached to entities or actors.
 */
enum
	ComponentType {
	/** No type specified. */
	NONE = 0,

	/** Transform component (position, rotation, scale). */
	TRANSFORM = 1,

	/** Sprite component for 2D graphics. */
	SPRITE = 2,

	/** Renderer component responsible for drawing. */
	RENDERER = 3,

	/** Physics component for collision or movement. */
	PHYSICS = 4,

	/** Audio source component for sound playback. */
	AUDIOSOURCE = 5,

	/** Shape component (e.g., bounding box, collider shape). */
	SHAPE = 6,

	/** Texture component for applying images to surfaces. */
	TEXTURE = 7
};

/**
 * @class Component
 * @brief Abstract base class for all components in the engine.
 *
 * Components define behavior and data that can be attached to entities or actors.
 * Each component has a type and implements basic lifecycle methods.
 */
class
	Component {
public:
	/**
	 * @brief Default constructor.
	 */
	Component() = default;

	/**
	 * @brief Constructs a component with a specific type.
	 * @param type The type of the component (from ComponentType enum).
	 */
	Component(const ComponentType type) : m_type(type) {}

	/**
	 * @brief Virtual default destructor.
	 */
	virtual
		~Component() = default;

	/**
	 * @brief Called when the component is initialized.
	 *
	 * This method should be overridden by derived classes
	 * to implement custom startup logic.
	 */
	virtual void
		start() = 0;

	/**
	 * @brief Called once per frame to update the component.
	 * @param deltaTime Time elapsed since the last frame (in seconds).
	 */
	virtual void
		update(float deltaTime) = 0;

	/**
	 * @brief Called to render the component.
	 * @param window Shared pointer to the window or rendering context.
	 */
	virtual void
		render(const EngineUtilities::TSharedPointer<Window>& window) = 0;

	/**
	 * @brief Called when the component is being destroyed.
	 *
	 * This is where you release resources or perform clean-up logic.
	 */
	virtual void
		destroy() = 0;

	/**
	 * @brief Retrieves the type of the component.
	 * @return The ComponentType of this component.
	 */
	ComponentType
		getType() const { return m_type; }

protected:
	/**
	 * @brief The type of this component.
	 */
	ComponentType m_type = ComponentType::NONE;
};