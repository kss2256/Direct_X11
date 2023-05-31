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
		Vec3 Scale = GetComponent<Transform>()->GetScale();
		Vec3 MousePos = Input::GetMousWorldPosition();

		if (mCmrAfctd)
		{
			MousePos = Camera::GetMovePos();
		}

		if (Pos.x <= MousePos.x && MousePos.x <= Pos.x + Scale.x
			&& Pos.y <= MousePos.y && MousePos.y <= Pos.y + Scale.y)
		{
			mMouseOn = true;
		}
		else
		{
			mMouseOn = false;
		}


		

	}

}
