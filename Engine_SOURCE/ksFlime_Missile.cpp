#include "ksFlime_Missile.h"
#include "ksTransform.h"
#include "ksSpriteRenderer.h"
#include "ksResources.h"
#include "ksTexture.h"
#include "ksMaterial.h"
#include "ksMesh.h"
#include "ksAnimator.h"
#include "ksTime.h"
#include "ksCollider2D.h"

#include "ksScene.h"
#include "ksSceneManager.h"

#include "ksInput.h"
#include <time.h>


#define PI 3.1415926535f

namespace ks
{

	Flime_Missile::Flime_Missile()
		: mSpeed(6.0f)
	{

		mTransform = GetComponent<Transform>();


		std::shared_ptr<Texture> bow1 = Resources::Load<Texture>(L"FlimeLine", L"Attack\\FlimeLine.png");



		SpriteRenderer* sr = AddComponent<SpriteRenderer>();


		std::shared_ptr<Material> mr = Resources::Find<Material>(L"FlimeMaterial");
		mr->SetTexture(bow1);
		sr->SetMaterial(mr);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);

		srand((unsigned int)time(nullptr));
		int a = rand();
	}

	Flime_Missile::~Flime_Missile()
	{
	}

	void Flime_Missile::Initalize()
	{

		GameObject::Initalize();
	}

	void Flime_Missile::Update()
	{

		if (Input::GetKeyDown(eKeyCode::N_1))
		{



		}

		switch (mStep)
		{
		case ks::Flime_Step::None:
		{
			mTime += Time::DeltaTime();
			mScale.x += Time::DeltaTime();
			mScale.y += Time::DeltaTime();
			if (mTime >= 0.9f)
			{
				mTime = 0.f;
				mScale = Vec3::Zero;
				if (mMissile)
					mStep = Flime_Step::Step_1;
				else
					mStep = Flime_Step::Step_4;
			}
			mTransform->SetScale(mScale);
		}
		break;
		case ks::Flime_Step::Step_1:
		{
			mTime += Time::DeltaTime();
			if (mTime >= 2.5f)
			{
				std::shared_ptr<Texture> bow1 = Resources::Load<Texture>(L"Monster_Tan", L"Attack\\Monster_Tan.png");
				std::shared_ptr<Material> mr = Resources::Find<Material>(L"FlimeMaterial");
				mr->SetTexture(bow1);

				Collider2D* collider = GetComponent<Collider2D>();
				collider->SetType(eColliderType::Rect);
				collider->SetSize(Vec2(0.6f, 0.6f));
				int rnadom = rand() % 361 + 1;		//0 ~ 9 까지 랜덤의 수인데 거기에 +1 을 해서	
				mDegree = (float)rnadom;

				Initalize();

				mStep = Flime_Step::Step_2;
				mTransform->SetScale(Vec3(0.6f, 0.6f, 2.0f));
				mTime = 0.f;
			}
		}
		break;
		case ks::Flime_Step::Step_2:
		{

			Vec3 pos = mTransform->GetPosition();

			float fRadian = (mDegree * PI) / 180.f;

			pos.x += mSpeed * cosf(fRadian) * Time::DeltaTime();
			pos.y -= mSpeed * sinf(fRadian) * Time::DeltaTime();

			mTransform->SetPosition(pos);
			mTime += Time::DeltaTime();
			if (mTime >= 5.0f)
			{
				mStep = Flime_Step::Step_3;
				mTime = 0.f;
			}

		}
		break;
		case ks::Flime_Step::Step_3:
		{
			this->Death();
			mTime = 0.f;
		}
		break;
		case ks::Flime_Step::Step_4:
		{
			mTime += Time::DeltaTime();
			if (mTime >= 2.0f)
			{
				this->Death();
				mTime = 0.f;
			}
		}
		break;

		case ks::Flime_Step::Step_5:
		{
			mTime += Time::DeltaTime();
			mScale.x += Time::DeltaTime();
			mScale.y += Time::DeltaTime();
			if (mTime >= 1.2f)
			{
				mTime = 0.f;
				mScale = Vec3::Zero;
				mStep = Flime_Step::Step_6;
			}
			mTransform->SetScale(mScale);
		}
		break;
		case ks::Flime_Step::Step_6:
		{
			mTime += Time::DeltaTime();
			if (mTime >= 2.0f)
			{
				this->Death();
				mTime = 0.f;
			}
		}
		break;
		case ks::Flime_Step::Step_7:
		{
			mTime += Time::DeltaTime();
			mScale.x += 6.5f * Time::DeltaTime();
			mScale.y += 6.5f * Time::DeltaTime();
			if (mTime >= 2.0f)
			{
				mTime = 0.f;
				mScale = Vec3::Zero;
				mStep = Flime_Step::Step_6;
			}
			mTransform->SetScale(mScale);
		}
		break;
		case ks::Flime_Step::Step_8:
		{
			mTime += Time::DeltaTime();
			if (mTime >= 2.0f)
			{
				this->Death();
				mTime = 0.f;
			}
		}
		break;
		}




		GameObject::Update();
	}

	void Flime_Missile::FixedUpdate()
	{

		GameObject::FixedUpdate();
	}

	void Flime_Missile::Render()
	{

		GameObject::Render();
	}

	void Flime_Missile::Lineinterval(float interval)
	{
		Vec3 pos = mTransform->GetPosition();

		float fRadian = (mDegree * PI) / 180.f;



		pos.x = mTransform->GetPosition().x - 0.1f + interval * cosf(fRadian);
		pos.y = mTransform->GetPosition().y - 0.7f - interval * sinf(fRadian);



		mTransform->SetPosition(pos);


	}

}