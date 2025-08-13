#pragma once

#include "../Prerequisites.h"
#include "Component.h"

class
	Window;

/**
 * @class Entity
 * @brief Abstract base class representing an entity in the engine.
 *
 * Entities are core objects in the engine which can hold multiple components.
 * Each entity supports a standard lifecycle (start, update, render, destroy),
 * and provides methods to manage components.
 */
class
	Entity {
public:
	/**
	 * @brief Virtual default destructor.
	 */
	virtual
		~Entity() = default;

	/**
	 * @brief Called when the entity is initialized.
	 *
	 * This method is meant to be overridden to define startup logic
	 * such as component initialization.
	 */
	virtual void
		start() = 0;

	/**
	 * @brief Called every frame to update the entity.
	 * @param deltaTime Time elapsed since the last frame (in seconds).
	 *
	 * Override this to define per-frame behavior.
	 */
	virtual void
		update(float deltaTime) = 0;

	/**
	 * @brief Called to render the entity.
	 * @param window Shared pointer to the render window.
	 *
	 * Override this to define how the entity should be drawn.
	 */
	virtual void
		render(const EngineUtilities::TSharedPointer<Window>& window) = 0;

	/**
	 * @brief Called before the entity is destroyed to release resources.
	 *
	 * Use this to clean up any allocated resources or detach components.
	 */
	virtual void
		destroy() = 0;

	/**
	 * @brief Adds a component of type T to the entity.
	 *
	 * The component must inherit from the base Component class.
	 * Internally, it's cast to the base type to be stored in the component list.
	 *
	 * @tparam T The type of the component (must derive from Component).
	 * @param component Shared pointer to the component instance.
	 */
	template<typename T>
	void
		addComponent(EngineUtilities::TSharedPointer<T> component) {
		static_assert
			(std::is_base_of<Component, T>::value, "T must be derived from Component");

		// Cast component to base type and add to internal list
		components.push_back(component.template dynamic_pointer_cast<Component>());
	}

	/**
	 * @brief Retrieves the first component of type T attached to the entity.
	 *
	 * Iterates through the list of components and attempts to cast each one
	 * to the requested type. Returns the first successful match.
	 *
	 * @tparam T The type of component to retrieve.
	 * @return Shared pointer to the component if found; empty pointer otherwise.
	 */
	template<typename T>
	EngineUtilities::TSharedPointer<T> getComponent() {
		for (auto& component : components) {
			// Attempt dynamic cast from base component to specific type T
			EngineUtilities::TSharedPointer<T> specificComponent =
				component.template dynamic_pointer_cast<T>();

			if (specificComponent) {
				return specificComponent;
			}
		}

		// No matching component found
		return EngineUtilities::TSharedPointer<T>();
	}

protected:
	/**
	 * @brief Flag indicating whether the entity is currently active.
	 */
	bool isActive = true;

	/**
	 * @brief Unique identifier assigned to the entity.
	 */
	uint32_t id = 0;

	/**
	 * @brief List of components attached to this entity.
	 */
	std::vector<EngineUtilities::TSharedPointer<Component>> components;
};