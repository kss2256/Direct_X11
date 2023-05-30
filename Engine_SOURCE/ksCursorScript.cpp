#include "ksCursorScript.h"
#include "ksCursor.h"
#include "ksApplication.h"
#include "ksTransform.h"
#include "ksGameObject.h"
#include "ksInput.h"
#include "ksTime.h"



extern ks::Application application;


namespace ks
{
	CursorScript::CursorScript()
	{
	}

	CursorScript::~CursorScript()
	{
	}

	void CursorScript::Initalize()
	{


	}

	void CursorScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector3 mousepos = Input::GetMousPosition();
		Vector2 window = Vector2((float)application.GetWidth(), (float)application.GetHeight());

		//mMousePos.x = (float)(mousepos.x - (float)window.x / 2.0) * (float)((1.0 / (float)(window.x / 2.0)));
		//mMousePos.y = -(float)(mousepos.y - (float)window.y / 2.0) * (float)((1.0 / (float)(window.y / 2.0)));

		mMousePos.x = (float)(mousepos.x / 2) * (float)((1.0 / (float)(window.x)));
		mMousePos.y = -(float)(mousepos.y / 2) * (float)((1.0 / (float)(window.y)));



		tr->SetPosition(Vector3(mMousePos.x, mMousePos.y, 1.0f));

		//Transform* tr = GetOwner()->GetComponent<Transform>();

		//if (Input::GetKey(eKeyCode::RIGHT))
		//{
		//	Vector3 pos = tr->GetPosition();
		//	pos.x += 3.0f * Time::DeltaTime();
		//	tr->SetPosition(pos);
		//}

		//if (Input::GetKey(eKeyCode::LEFT))
		//{
		//	Vector3 pos = tr->GetPosition();
		//	pos.x -= 3.0f * Time::DeltaTime();
		//	tr->SetPosition(pos);
		//}


	}

	void CursorScript::Render()
	{


	}

	void CursorScript::OnCollisionEnter(Collider2D* collider)
	{
	}

	void CursorScript::OnCollisionStay(Collider2D* collider)
	{
	}

	void CursorScript::OnCollisionExit(Collider2D* collider)
	{
	}

}