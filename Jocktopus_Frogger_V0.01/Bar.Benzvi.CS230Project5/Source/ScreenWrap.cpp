#include "stdafx.h"
#include "GameObject.h"
#include "Transform.h"
#include "Physics.h"
#include "Graphics.h"
#include "ScreenWrap.h"

namespace Behaviors
{
	ScreenWrap::ScreenWrap()
		: Component("ScreenWrap")
	{
	}

	Component* ScreenWrap::Clone() const
	{
		return new ScreenWrap();
	}

	void ScreenWrap::Initialize()
	{
		transform = static_cast<Transform*>(GetOwner()->GetComponent("Transform"));
		physics = static_cast<Physics*>(GetOwner()->GetComponent("Physics"));
	}

	void ScreenWrap::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);

		BoundingRectangle dimensions = Graphics::GetInstance().GetScreenWorldDimensions();

		if (transform->GetTranslation().y > dimensions.top + (transform->GetScale().y / 2) && physics->GetVelocity().y > 0)
		{
			transform->SetTranslation(Vector2D(transform->GetTranslation().x, dimensions.bottom - (transform->GetScale().y / 2)));
		}
		else if (transform->GetTranslation().y < dimensions.bottom - (transform->GetScale().y / 2) && physics->GetVelocity().y < 0)
		{
			transform->SetTranslation(Vector2D(transform->GetTranslation().x, dimensions.top + (transform->GetScale().y / 2)));
		}
		else if (transform->GetTranslation().x < dimensions.left - (transform->GetScale().x / 2) && physics->GetVelocity().x < 0)
		{
			transform->SetTranslation(Vector2D(dimensions.right + (transform->GetScale().x / 2), transform->GetTranslation().y));
		}
		else if (transform->GetTranslation().x > dimensions.right + (transform->GetScale().x / 2) && physics->GetVelocity().x > 0)
		{
			transform->SetTranslation(Vector2D(dimensions.left - (transform->GetScale().x / 2), transform->GetTranslation().y));
		}

	}
}