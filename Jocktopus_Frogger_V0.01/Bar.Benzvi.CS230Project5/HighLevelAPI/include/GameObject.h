//------------------------------------------------------------------------------
//
// File Name:	GameObject.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include <BetaObject.h>
#include "Serializable.h"


//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

class Component;
class Space;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.
class GameObject : public BetaObject, public Serializable
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Create a new game object.
	// Params:
	//	 name = The name of the game object being created.
	GameObject(const std::string& name);

	// Clone a game object from another game object.
	// Params:
	//	 other = A reference to the object being cloned.
	GameObject(const GameObject& other);

	// Free the memory associated with a game object.
	~GameObject();

	// Initialize this object's components and set it to active.
	void Initialize() override;

	// Update any components attached to the game object.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void Update(float dt) override;

	// Updates components using a fixed timestep (usually just physics)
	// Params:
	//	 dt = A fixed change in time, usually 1/60th of a second.
	void FixedUpdate(float dt) override;

	// Draw any visible components attached to the game object.
	void Draw() override;
	
	// Adds a component to the object.
	void AddComponent(Component* component);

	Component* GetComponent(const std::string& name_) const;

	// Retrieves the component with the given type if it exists.
	// Template params:
	//  ComponentType = The type of component to retrieve.
	// Returns:
	//  A pointer to the component if it exists, nullptr otherwise.
	template<class ComponentType> 
	ComponentType* GetComponent()
	{
		for (auto it = components.cbegin(); it < components.cend(); ++it)
		{
			if (typeid(**it) == typeid(ComponentType) || dynamic_cast<ComponentType*>(*it) != nullptr)
			{
				return static_cast<ComponentType*>((*it));
			}
		}

		return nullptr;
	}
	
	// Mark an object for destruction.
	void Destroy();
	
	// Whether the object has been marked for destruction.
	// Returns:
	//		True if the object will be destroyed, false otherwise.
	bool IsDestroyed() const;

	// Get the space that contains this object.
	Space* GetSpace() const;

	// Loads object data from a file.
	virtual void Deserialize(Parser& parser);
	// Saves object data to a file.
	virtual void Serialize(Parser& parser) const;

private:
	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// Components
	std::vector<Component*> components;

	// Whether the object has been marked for destruction.
	bool isDestroyed;
};

//------------------------------------------------------------------------------
