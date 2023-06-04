#include "ksUIBase.h"
#include "ksTransform.h"
#include "ksInput.h"
#include "ksCamera.h"

namespace ks
{
	UIBase::UIBase()
	{
	}

	UIBase::~UIBase()
	{
	}
	void UIBase::Update()
	{

		MouseOnCheak();

		GameObject::Update();
	}


	void UIBase::MouseOnCheak()
	{

		Vec3 Pos = GetComponent<Transform>()->GetPosition();
		Vec3 Scale = GetComponent<Transform>()->GetScale() * 0.5f;
		Vec3 MousePos = Input::GetMousWorldPosition();


		if (MousePos.x <= Pos.x + Scale.x && MousePos.x >= Pos.x - Scale.x
			&& MousePos.y <= Pos.y + Scale.y && MousePos.y >= Pos.y - Scale.y )
		{
			mMouseOn = true;
		}
		else
		{
			mMouseOn = false;
		}
		

	}

}
