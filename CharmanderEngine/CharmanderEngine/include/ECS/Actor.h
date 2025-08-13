#pragma once

#include "../Prerequisites.h"
#include "Entity.h"
#include "Cshape.h"
#include "../ECS/Transform.h"

/**
 * @class Actor
 * @brief Represents an actor in the game or engine, derived from Entity.
 *
 * The Actor class encapsulates basic functionality and lifecycle events
 * for any in-game object or entity, including component management.
 */
class
	Actor : Entity {

public:
	/**
	 * @brief Default constructor.
	 */
	Actor() = default;

	/**
	 * @brief Constructs an Actor with a given name.
	 * @param actorName Name of the actor.
	 */
	Actor(const std::string& actorName);

	/**
	 * @brief Virtual default destructor.
	 */
	virtual
		~Actor() = default;

	/**
	 * @brief Called when the actor is initialized in the game or engine.
	 *
	 * Override of the base Entity::start method. Intended to be customized
	 * by derived classes to perform setup logic at the beginning of the actor's
	 * lifecycle.
	 */
	void
		start() override;

	/**
	 * @brief Called every frame to update the actor's behavior.
	 * @param deltaTime Time elapsed since the last frame (in seconds).
	 *
	 * Override of the base Entity::update method. Typically used to implement
	 * frame-dependent logic such as movement, AI, or animations.
	 */
	void
		update(float deltaTime) override;

	/**
	 * @brief Called to render the actor to the screen.
	 * @param window Shared pointer to the rendering window.
	 *
	 * Override of the base Entity::render method. This function is responsible
	 * for drawing the actor using the provided render context.
	 */
	void
		render(const EngineUtilities::TSharedPointer<Window>& window) override;

	/**
	 * @brief Called when the actor is being destroyed.
	 *
	 * Override of the base Entity::destroy method. Clean-up logic should be
	 * placed here.
	 */
	void
		destroy() override;

	void
		setTexture(const EngineUtilities::TSharedPointer<Texture>& texture);

	const std::string&
		getName() const { return m_name; }


	/**
	 * @brief Retrieves the first component of type T attached to the actor.
	 *
	 * This function iterates over the list of components and attempts to
	 * dynamically cast each one to the requested type T. If a component
	 * of the desired type is found, it is returned as a shared pointer.
	 *
	 * @tparam T The type of component to search for.
	 * @return EngineUtilities::TSharedPointer<T> A shared pointer to the component
	 *         of type T if found; otherwise, an empty shared pointer.
	 */
	template <typename T>
	EngineUtilities::TSharedPointer<T> getComponent();

private:
	/**
	 * @brief The name of the actor.
	 */
	std::string m_name = "Actor";

	// NOTE: It is assumed that the base Entity class provides:
	// std::vector<EngineUtilities::TSharedPointer<Component>> components;
};

// -------- Template implementation --------

/**
 * @brief Retrieves the first component of type T attached to the actor.
 *
 * This method searches through all components currently associated with actor.
 * It uses dynamic_pointer_cast to determine if the component can be converted
 * to type T.
 *
 * @tparam T The type of component to retrieve.
 * @return EngineUtilities::TSharedPointer<T> A shared pointer
 * to the component  of type T if found, otherwise an empty shared pointer.
 */
template<typename T>
inline EngineUtilities::TSharedPointer<T> Actor::getComponent() {
	for (auto& component : components) {
		// Attempt to dynamically cast the component to the requested type T
		EngineUtilities::TSharedPointer<T> specificComponent
			= component.template dynamic_pointer_cast<T>();

		// If the cast is successful, return this component
		if (specificComponent) {
			return specificComponent;
		}
	}

	// Return an empty shared pointer if no matching component is found
	return EngineUtilities::TSharedPointer<T>();
}