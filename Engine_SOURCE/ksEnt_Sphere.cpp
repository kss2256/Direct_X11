#include "ksEnt_Sphere.h"
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

#define PI 3.1415926535f

namespace ks
{

	Ent_Sphere::Ent_Sphere()
		: mSpeed(3.0f)
		, mSphereStep(Step::Step_1)
	{
		mTransform = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>();
		
		
		loadAnimation();

		SpriteRenderer* sr = AddComponent<SpriteRenderer>();


		std::shared_ptr<Material> mr = Resources::Find<Material>(L"MonsterMaterial");
		sr->SetMaterial(mr);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);

		mAnimator->Play(L"Sphere", true);

	}

	Ent_Sphere::~Ent_Sphere()
	{
	}

	void Ent_Sphere::Initalize()
	{

		GameObject::Initalize();
	}

	void Ent_Sphere::Update()
	{



		switch (mSphereType)
		{
		case ks::Sphere_Type::Direction_3:
		{
			if(mSphereStep == Step::Step_1)
			{
				mCollider = GetComponent<Collider2D>();
				mCollider->SetType(eColliderType::Rect);
				mCollider->SetSize(Vec2(0.08f, 0.08f));
				Initalize();
				mSphereStep = Step::Step_2;
			}
			if (mSphereStep == Step::Step_2)
			{
				Vec3 pos = mTransform->GetPosition();
				pos += mTargetPos * 3.5f * Time::DeltaTime();

				mTransform->SetPosition(pos);
			}
		}
			break;
		case ks::Sphere_Type::Direction_8:
		{
			if (mSphereStep == Step::Step_1)
			{
				mCollider = GetComponent<Collider2D>();
				mCollider->SetType(eColliderType::Rect);
				mCollider->SetSize(Vec2(0.08f, 0.08f));
				Initalize();
				mSphereStep = Step::Step_2;
			}
			if (mSphereStep == Step::Step_2)
			{
				Vec3 pos = mTransform->GetPosition();

				float fRadian = (mDegree * PI) / 180.f;

				pos.x += mSpeed * cosf(fRadian) * Time::DeltaTime();
				pos.y -= mSpeed * sinf(fRadian) * Time::DeltaTime();

				mTransform->SetPosition(pos);
			}
		}
			break;		
		}

		




		mCooldownTime += Time::DeltaTime();
		if (mCooldownTime >= 15.0f)
		{

			this->Death();
			mCooldownTime = 0.f;
		}	

		GameObject::Update();
	}

	void Ent_Sphere::FixedUpdate()
	{

		GameObject::FixedUpdate();
	}

	void Ent_Sphere::Render()
	{

		GameObject::Render();
	}

	void Ent_Sphere::loadAnimation()
	{

		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"skill_ent3@[10-15]", L"Attack\\skill_ent3@[10-15].png");

		mNumbers.push_back(0);
		mNumbers.push_back(1);
		mNumbers.push_back(2);
		mNumbers.push_back(3);
		mNumbers.push_back(4);
		mNumbers.push_back(5);
		mNumbers.push_back(6);
		mNumbers.push_back(7);
		mNumbers.push_back(8);
		CreateAnimation(L"Sphere", texture, mAnimator, Vector2(60.0f, 60.0f), Vec2::Zero, mNumbers, 0.3f);
		mNumbers.clear();



	}

}