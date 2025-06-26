#pragma once
#include "../Prerequisites.h"
#include "Component.h"

class Window;

class Entity {
public:

	virtual
		~Entity() = default;

	virtual void
		start() = 0;

	virtual void
		update(float deltaTime) = 0;

	virtual void
		render(const EngineUtilities::TSharedPointer<Window>& window) = 0;

	virtual void
		destroy() = 0;

	template<typename T>
	void
		addComponent(EngineUtilities::TSharedPointer<T> component) {
		static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
		components.push_back(component.template dynamic_pointer_cast<Component>());
	}

	template<typename T>
	EngineUtilities::TSharedPointer<T>
		getComponent() {
		for (auto& component : components) {
			Engine::Utilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T>();
			if (specificComponent) {
				return specificComponent;
			}
		}
		return EngineUtilities::TSharedPointer<T>();
	}

protected:
	bool isActive;
	uint32_t id;
	std::vector<EngineUtilities::TSharedPointer<Component>> components;
};