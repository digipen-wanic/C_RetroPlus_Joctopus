#include "stdafx.h"
#include "GameObject.h"
#include "Transform.h"
#include "Physics.h"
#include "Graphics.h"
#include "ScreenWrap.h"
#include "Math.h"

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
		if (transform->GetTranslation().y > dimensions.top + (abs(transform->GetScale().y) * 1.5f) && physics->GetVelocity().y >= 0)
		{
			transform->SetTranslation(Vector2D(transform->GetTranslation().x, dimensions.bottom - (abs(transform->GetScale().y) * 1.5f)));
		}
		else if (transform->GetTranslation().y < dimensions.bottom - (abs(transform->GetScale().y) * 1.5f) && physics->GetVelocity().y <= 0)
		{
			transform->SetTranslation(Vector2D(transform->GetTranslation().x, dimensions.top + (abs(transform->GetScale().y) * 1.5f)));
		}
		else if (transform->GetTranslation().x < dimensions.left - (abs(transform->GetScale().x) * 1.5f) && physics->GetVelocity().x <= 0)
		{
			transform->SetTranslation(Vector2D(dimensions.right + (abs(transform->GetScale().x) * 1.5f), transform->GetTranslation().y));
		}
		else if (transform->GetTranslation().x > dimensions.right + (abs(transform->GetScale().x) * 1.5f) && physics->GetVelocity().x >= 0)
		{
			transform->SetTranslation(Vector2D(dimensions.left - (abs(transform->GetScale().x) * 1.5f), transform->GetTranslation().y));
		}

	}
}