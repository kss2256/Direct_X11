#include "ksDiary.h"
#include "ksResources.h"
#include "ksTransform.h"
#include "ksSpriteRenderer.h"
#include "ksMaterial.h"
#include "ksMesh.h"
#include "ksPlayer.h"
#include "ksAnimator.h"
#include "ksCollider2D.h"
#include "ksInput.h"
#include "ksTime.h"
#include "ksFadeEffect.h"



namespace ks
{

	//bool Diary::mCheak = false;


	Diary::Diary()
		: mCheak(false)
	{
		
		

		mAnimator = AddComponent<Animator>();

		mCollider = AddComponent<Collider2D>();

		mCollider->SetType(eColliderType::Rect);
		mCollider->SetSize(Vec2(0.04f, 0.04f));

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vec3(12.0f, 12.0f, 1.0f));
		tr->SetPosition(Vec3(350.f, 0.0f, 1.0f));

		SpriteRenderer* sr = AddComponent<SpriteRenderer>();

		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"SpriteMaterial");
		sr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);

		loadanimation();

		mAnimator->Play(L"Idle", true);
		
	
		


	}

	Diary::~Diary()
	{
	}

	void Diary::Initalize()
	{


		GameObject::Initalize();
	}

	void Diary::Update()
	{

		if (mCheak)
		{
			mTime += Time::DeltaTime();

			if (mDiaryStep == eStep::None)
			{
				mAnimator->Play(L"Move", false);
				mDiaryStep = eStep::Step_1;
			}
			if (mDiaryStep == eStep::Step_1)
			{
				if (mTime >= 1.0f)
				{
					mAnimator->Play(L"Move_1", true);					
					mDiaryStep = eStep::Step_2;					
					mTime = 0.f;				
				}
			}
			if (mDiaryStep == eStep::Step_2)
			{
				if (mTime >= 2.0f)
				{					
					//Transform* tr = GetComponent<Transform>();
					//tr->SetScale(Vec3(40.0f, 40.0f, 1.0f));
					//AddComponent<FadeEffect>();
					//GetComponent<FadeEffect>()->Initalize();
					//GetComponent<FadeEffect>()->Fade_Out();
					mDiaryStep = eStep::Step_3;
					mTime = 0.f;
				}
			}


			if (mDiaryStep == eStep::Step_3)
			{			
				if (mTime >= 1.5f)
				{
					//GetComponent<FadeEffect>()->Fade_In();
					//mPlayer->SetGroundStage(eGroundStage::Ground1);
					//
					//Transform* player = mPlayer->GetComponent<Transform>();
					//player->SetPosition(Vec3(35.0f, 0.0f, 1.0f));
					//
					//Transform* tr = GetComponent<Transform>();
					//tr->SetScale(Vec3(12.0f, 12.0f, 1.0f));
					//tr->SetPosition(Vec3(350.f, 0.0f, 1.0f));

					mDiaryStep = eStep::None;
					mCheak = false;
			
				}
			}



		}



		GameObject::Update();
	}

	void Diary::FixedUpdate()
	{

		GameObject::FixedUpdate();
	}

	void Diary::Render()
	{

		GameObject::Render();
	}

	void Diary::loadanimation()
	{

		std::shared_ptr<Texture> diary = Resources::Load<Texture>(L"Diary", L"Map\\Diary.png");

		mAnimator->Create(L"Idle", diary, Vector2(0.0f, 0.0f), Vector2(48.0f, 36.0f), Vector2::Zero, 1, 0.1f);

		
		mNumbers.push_back(0);
		mNumbers.push_back(3);
		mNumbers.push_back(6);
		mNumbers.push_back(9);

		CreateAnimation(L"Move", diary, mAnimator, Vector2(48.0f, 36.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();


		mNumbers.push_back(10);
		mNumbers.push_back(7);
		mNumbers.push_back(4);
		mNumbers.push_back(1);
		CreateAnimation(L"Move_1", diary, mAnimator, Vector2(48.0f, 36.0f), Vec2::Zero, mNumbers, 0.3f);
		mNumbers.clear();


	}

	



}