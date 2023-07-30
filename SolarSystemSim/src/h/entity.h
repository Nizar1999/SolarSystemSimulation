#pragma once
#include <unordered_map>
#include <string>
#include <memory>

#include "component.h"
class Entity
{
private:
	std::unordered_map<std::string, std::unique_ptr<Component>> components;

public:
	template<typename T, typename... Args>
	void addComponent(Args&&... args)
	{
		auto component = std::make_unique<T>(std::forward<Args>(args)...);
		components[typeid(T).name()] = std::move(component);
	}

	template<typename T>
	T* getComponent()
	{
		auto it = components.find(typeid(T).name());
		if (it != components.end())
		{
			// Check if the stored Component is of the correct type
			if (auto* desiredComponent = dynamic_cast<T*>(it->second.get()))
			{
				return desiredComponent;
			}
		}
		return nullptr; // If component not found or incorrect type
	}

	virtual void update(float deltaTime) = 0;
};

