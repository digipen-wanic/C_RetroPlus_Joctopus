//------------------------------------------------------------------------------
//
// File Name:	GameObject.cpp
// Author(s):	Bar Ben-zvi
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "stdafx.h"

#include "GameObject.h"
#include "Component.h"
#include "Space.h"
#include "Parser.h"
#include "GameObjectFactory.h"

GameObject::GameObject(const std::string& name)
	: BetaObject(name), isDestroyed(false)
{
}

GameObject::GameObject(const GameObject& other)
	: BetaObject(other.GetName())
{
	for (auto it = other.components.cbegin(); it != other.components.cend(); ++it)
	{
		AddComponent((*it)->Clone());
	}

	isDestroyed = other.isDestroyed;


}

GameObject::~GameObject()
{
	for (auto it = components.cbegin(); it != components.cend(); ++it)
	{
		delete *it;
	}

	components.clear();
}

void GameObject::Initialize()
{
	for (auto it = components.cbegin(); it != components.cend(); ++it)
	{
		(*it)->Initialize();
	}
}

void GameObject::Update(float dt)
{
	for (auto it = components.cbegin(); it != components.cend(); ++it)
	{
		(*it)->Update(dt);
	}
}

void GameObject::FixedUpdate(float dt)
{
	for (auto it = components.cbegin(); it != components.cend(); ++it)
	{
		(*it)->FixedUpdate(dt);
	}
}

void GameObject::Draw()
{
	for (auto it = components.cbegin(); it != components.cend(); ++it)
	{
		(*it)->Draw();
	}
}

void GameObject::AddComponent(Component* component_)
{
	component_->SetParent(this);
	components.push_back(component_);
}

Component* GameObject::GetComponent(const std::string& name_) const
{
	for (auto it = components.cbegin(); it != components.cend(); ++it)
	{
		if ((*it)->GetName() == name_)
		{
			return *it;
		}
	}

	return nullptr;
}

void GameObject::Destroy()
{
	isDestroyed = true;
}

bool GameObject::IsDestroyed() const
{
	return isDestroyed;
}

Space* GameObject::GetSpace() const
{
	return static_cast<Space*>(GetParent());
}

// Loads object data from a file.
void GameObject::Deserialize(Parser& parser)
{
	int componentCount;
	parser.ReadSkip(GetName());
	parser.ReadSkip('{');
	parser.ReadVariable("numComponents", componentCount);

	for (int i = 0; i < componentCount; ++i)
	{
		std::string compName;
		parser.ReadValue(compName);
		Component* component = GameObjectFactory::GetInstance().CreateComponent(compName);

		if (component == nullptr)
		{
			throw ParseException(compName, "Given component could not be found");
		}

		AddComponent(component);

		parser.ReadSkip('{');

		component->Deserialize(parser);

		parser.ReadSkip('}');
		
	}
	parser.ReadSkip('}');
}
// Saves object data to a file.
void GameObject::Serialize(Parser& parser) const
{
	parser.WriteValue(GetName());
	parser.BeginScope();
	parser.WriteVariable("numComponents", components.size());
	for (auto it = components.cbegin(); it != components.cend(); ++it)
	{
		parser.WriteValue(std::string(typeid(**it).name()).substr(6));
		parser.BeginScope();
		(*it)->Serialize(parser);
		parser.EndScope();
	}

	parser.EndScope();
}