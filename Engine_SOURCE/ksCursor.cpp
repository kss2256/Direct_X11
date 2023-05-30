#include "ksCursor.h"
#include "ksTransform.h"
#include "ksInput.h"
#include "ksApplication.h"
#include "ksGameObject.h"
#include "ksCamera.h"

extern ks::Application application;



namespace ks
{

	Vector3		Cursor::mMousePos = Vector3::Zero;
	Transform*	Cursor::mTransform = nullptr;
	GameObject* Cursor::mTarget = nullptr;

	Cursor::Cursor()
		: Script()
	{
	}

	Cursor::~Cursor()
	{
	}

	void Cursor::Initalize()
	{

	
		mTransform = GetOwner()->GetComponent<Transform>();

		mTarget = GetTarget();

		
		

		//���콺 Ŀ�� �Ⱥ��̰� �ϴ°� �ٸ������� �Ѿ�� �� true�� �ٲ�����ϰ� ȣ�� �Ҷ����� ���۷��� ������..?
		ShowCursor(false);		
		

	}

	void Cursor::Update()
	{
		// �ȵ�??
		//CONSOLE_CURSOR_INFO cursorInfo = { 0, };
		//cursorInfo.dwSize = 1; //Ŀ�� ���� (1 ~ 100)
		//cursorInfo.bVisible = FALSE; //Ŀ�� Visible TRUE(����) FALSE(����)
		//SetConsoleCursorInfo(application.GetHwnd(), &cursorInfo);

		

		//RECT winRect = {};
		//GetClientRect(application.GetHwnd(), &winRect);

		//Vector2 winCenter = {};
		//winCenter.x = ((float)winRect.right - (float)winRect.left) / 2.0f;
		//winCenter.y = ((float)winRect.bottom - (float)winRect.top) / 2.0f;


		//mMousePos = Vector3(Input::GetMousPosition().x, Input::GetMousPosition().y, 1.0f);

		//mMousePos.x = ((float)mMousePos.x - winCenter.x);
		//mMousePos.y = -((float)mMousePos.y - winCenter.y);
		//mMousePos.z = 1.0f;


		//mMousePos = (mMousePos / 100.f) + Vector3(1.f, 1.f, 0.f);

		//

		//mMousePos = Vector3(Input::GetMousPosition().x, Input::GetMousPosition().y, 1.0f);


		mMousePos = Input::GetMousWorldPosition();

		mTransform->SetPosition(mMousePos);

		//mTransform->SetPosition(Camera::CalRealPos(mMousePos));


		



	}





	void Cursor::FixedUpdate()
	{
		
		Transform * tr = mTarget->GetComponent<Transform>();

		Vector3 distance = Vector3(mMousePos.x - tr->GetPosition().x, mMousePos.y - tr->GetPosition().y, 1.0f);



		float dir = atan2(distance.y, distance.x);

		float angle = (float)((dir * 180) / 3.14159265);

		tr->SetAngle(angle);
		tr->SetDirection(Vector3(distance.x, distance.y, 1.0f));


		//mouse = Camera.main.ScreenToWorldPoint(Input.mousePosition);
		//angle = Mathf.Atan2(mouse.y - target.y, mouse.x - target.x) * Mathf.Rad2Deg;
		//this.transform.rotation = Quaternion.AngleAxis(angle - 90, Vector3.forward);




	}

	void Cursor::Render()
	{

	}

}
