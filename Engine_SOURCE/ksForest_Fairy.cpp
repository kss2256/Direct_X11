#include "ksForest_Fairy.h"
#include "ksPlayer.h"
#include "ksPlayerAttack.h"
#include "ksTransform.h"
#include "ksTime.h"
#include "ksAnimator.h"
#include "ksResources.h"
#include "ksMaterial.h"
#include "ksMesh.h"
#include "ksSpriteRenderer.h"
#include "ksMonsterMissile.h"
#include "ksStage1_1.h"

#include "ksInput.h"

namespace ks
{
	Forest_Fairy::Forest_Fairy()
	{

		mTransform = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>();



		mStateInfo.direction = eDirection::Down;
		mStateInfo.situation = eSituation::Patrol;

		mStatus = AddComponent<Status>();
		mStatus->SetStateInfo(mStateInfo);

		mHp = 20;

		loadAnimation();


		SpriteRenderer* sr = AddComponent<SpriteRenderer>();

		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"SpriteMaterial");
		sr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);

		mAnimator->Play(L"Idle_Down", true);

	}

	Forest_Fairy::~Forest_Fairy()
	{
	}

	void Forest_Fairy::Initalize()
	{


		GameObject::Initalize();
	}

	void Forest_Fairy::Update()
	{

		if (mDetection)
		{

			if (mPlayer != nullptr)
				mTargetPos = mPlayer->GetComponent<Transform>()->GetPosition();

			mMonsterPos = mTransform->GetPosition();
			Vec3 pos = mTransform->GetPosition();

			if (mStateInfo.situation == eSituation::Death)
			{
				mTime += Time::DeltaTime();
				mAnimator->Play(L"Death", false);

				if (mTime >= 1.0f)
				{
					//this->Death();

					mTransform->SetPosition(Vec3(0.0f, 0.0f, 1.0f));
					mDetection = false;


					Stage1_1* stage = nullptr;
					stage->KeyCount_Up();
					mTime = 0.f;
				}

			}

			else
			{
				AngleDirection();
				if (mStateInfo.situation == eSituation::None)
				{
					mTime += Time::DeltaTime();

					if (mAttackCool)
					{
						if (!mCheak)
						{
							if (mTime >= 1.0f)
							{
								directionAnimation(L"Idle", true);
								mCheak = true;
							}
						}

						if (mTime >= 3.0f)
						{
							if (!Range())
							{
								directionAnimation(L"Move", true);
								mStateInfo.situation = eSituation::Patrol;
							}
							else
							{
								mStateInfo.situation = eSituation::Attack;
							}

							mCheak = false;
							mAttackCool = false;
							mTime = 0.f;
						}
					}

				}

				else
				{
					//멀리 떨어져 있으면 가까이 다가옴 탐색 중일 때만 플레이어에게 이동 
					Patrol();
				}


				if (mStateInfo.situation == eSituation::Attack)
				{

					if (mStep == eStep::None)
					{
						mFixPos = mPlayer->GetComponent<Transform>()->GetPosition();
						mStep = eStep::Step_1;
						mOneDirection = mStateInfo.direction;
					}

					if (mStep == eStep::Step_1)
					{
						oneDirectionAnimation(L"Attack", mOneDirection, false);
						mStep = eStep::Step_2;
					}

					if (mStep == eStep::Step_2)
					{
						mTime += Time::DeltaTime();
						if (!mCheak)
						{
							if (mTime >= 0.6f)
							{
								std::vector<UINT> count;
								count.push_back(11);
								count.push_back(5);
								count.push_back(3);
								std::vector<float> dir;
								dir.push_back(50.f);
								dir.push_back(35.f);
								dir.push_back(15.f);

								multipleAttack(count, dir);
								mCheak = true;
							}
						}
						if (mTime >= 0.8f)
						{
							mAttackCool = true;
							mCheak = false;
							mStep = eStep::None;
							mStateInfo.situation = eSituation::None;
							mTime = 0.f;
						}
					}


				}



				if (mStateInfo.situation == eSituation::Hit)
				{
					hit(0.1f, 0.2f, 50.f);
					directionAnimation(L"Idle", true);
				}



			}

		}

		GameObject::Update();
	}

	void Forest_Fairy::FixedUpdate()
	{

		GameObject::FixedUpdate();
	}

	void Forest_Fairy::Render()
	{

		GameObject::Render();
	}



	void Forest_Fairy::loadAnimation()
	{
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Forest_Fairy", L"Monster\\Forest_Fairy.png");



		mNumbers.push_back(0);
		mNumbers.push_back(2);
		CreateAnimation(L"Move_Down", texture, mAnimator, Vector2(56.0f, 93.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();

		mNumbers.push_back(3);
		mNumbers.push_back(5);
		CreateAnimation(L"Move_Left", texture, mAnimator, Vector2(56.0f, 93.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();

		mNumbers.push_back(6);
		mNumbers.push_back(8);
		CreateAnimation(L"Move_Right", texture, mAnimator, Vector2(56.0f, 93.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();

		mNumbers.push_back(9);
		mNumbers.push_back(11);
		CreateAnimation(L"Move_Up", texture, mAnimator, Vector2(56.0f, 93.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();



		mNumbers.push_back(12);
		mNumbers.push_back(13);
		mNumbers.push_back(14);
		CreateAnimation(L"Attack_Down", texture, mAnimator, Vector2(56.0f, 93.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();

		mNumbers.push_back(15);
		mNumbers.push_back(16);
		mNumbers.push_back(17);
		CreateAnimation(L"Attack_Left", texture, mAnimator, Vector2(56.0f, 93.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();

		mNumbers.push_back(18);
		mNumbers.push_back(19);
		mNumbers.push_back(20);
		CreateAnimation(L"Attack_Right", texture, mAnimator, Vector2(56.0f, 93.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();

		mNumbers.push_back(21);
		mNumbers.push_back(22);
		mNumbers.push_back(23);
		CreateAnimation(L"Attack_Up", texture, mAnimator, Vector2(56.0f, 93.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();



		mNumbers.push_back(24);
		CreateAnimation(L"Death", texture, mAnimator, Vector2(56.0f, 93.0f), Vec2::Zero, mNumbers, 0.1f);
		mNumbers.clear();



		mNumbers.push_back(25);
		CreateAnimation(L"Hit_Down", texture, mAnimator, Vector2(56.0f, 93.0f), Vec2::Zero, mNumbers, 0.1f);
		mNumbers.clear();

		mNumbers.push_back(26);
		CreateAnimation(L"Hit_Left", texture, mAnimator, Vector2(56.0f, 93.0f), Vec2::Zero, mNumbers, 0.1f);
		mNumbers.clear();

		mNumbers.push_back(27);
		CreateAnimation(L"Hit_Right", texture, mAnimator, Vector2(56.0f, 93.0f), Vec2::Zero, mNumbers, 0.1f);
		mNumbers.clear();

		mNumbers.push_back(28);
		CreateAnimation(L"Hit_Up", texture, mAnimator, Vector2(56.0f, 93.0f), Vec2::Zero, mNumbers, 0.1f);
		mNumbers.clear();


		mNumbers.push_back(1);
		CreateAnimation(L"Idle_Down", texture, mAnimator, Vector2(56.0f, 93.0f), Vec2::Zero, mNumbers, 0.1f);
		mNumbers.clear();

		mNumbers.push_back(4);
		CreateAnimation(L"Idle_Left", texture, mAnimator, Vector2(56.0f, 93.0f), Vec2::Zero, mNumbers, 0.1f);
		mNumbers.clear();

		mNumbers.push_back(7);
		CreateAnimation(L"Idle_Right", texture, mAnimator, Vector2(56.0f, 93.0f), Vec2::Zero, mNumbers, 0.1f);
		mNumbers.clear();

		mNumbers.push_back(10);
		CreateAnimation(L"Idle_Up", texture, mAnimator, Vector2(56.0f, 93.0f), Vec2::Zero, mNumbers, 0.1f);
		mNumbers.clear();

	}

	void Forest_Fairy::multipleAttack(std::vector<UINT> missileCounts, std::vector<float> missileAngle)
	{
		float Dir = 0.f;
		if (mOneDirection == eDirection::Down)
			Dir = 90.0f;
		else if (mOneDirection == eDirection::Left)
			Dir = 180.0f;
		else if (mOneDirection == eDirection::Up)
			Dir = 270.0f;
		else if (mOneDirection == eDirection::Right)
			Dir = 360.0f;
		else if (mOneDirection == eDirection::DownLeft)
			Dir = 135.f;
		else if (mOneDirection == eDirection::DownRight)
			Dir = 45.f;
		else if (mOneDirection == eDirection::UpRight)
			Dir = 315.f;
		else if (mOneDirection == eDirection::UpLeft)
			Dir = 225.f;

		
		
		
		for (size_t i = 0; i < missileCounts.size(); i++)
		{
			UINT missileCount = missileCounts[i];
			
			float angleUnit = missileAngle[i] / (missileCount - 1);	//미사일 당 이동 해야하는 각도

			float missileOffset = -1.0f + i * 0.5f;
			for (size_t j = 0; j < missileCount; j++)
			{
				MonsterMissile* missile = object::Instantiate<MonsterMissile>(eLayerType::Monster_Attack);
				missile->SetDegree(Dir + (angleUnit * j) - (missileAngle[i] / 2.0f));
				missile->SetSpeed(7.5f);

				missile->AddComponent<Collider2D>();
				Collider2D* collider = missile->GetComponent<Collider2D>();
				collider->SetType(eColliderType::Rect);
				collider->SetSize(Vec2(0.6f, 0.6f));

				Transform* tr = missile->GetComponent<Transform>();
				Vec3 pos = mTransform->GetPosition();
				if (mOneDirection == eDirection::Down || mOneDirection == eDirection::DownLeft || mOneDirection == eDirection::DownRight)
					tr->SetPosition(Vec3(pos.x + 0.2f - j * 0.1f, pos.y + missileOffset, pos.z));
				else if (mOneDirection == eDirection::Left)
					tr->SetPosition(Vec3(pos.x + missileOffset, pos.y - 0.3f + j * 0.1f, pos.z));
				else if (mOneDirection == eDirection::Up || mOneDirection == eDirection::UpRight || mOneDirection == eDirection::UpLeft)
					tr->SetPosition(Vec3(pos.x - 0.1f + j * 0.1f, pos.y - missileOffset, pos.z));
				else if (mOneDirection == eDirection::Right)
					tr->SetPosition(Vec3(pos.x - missileOffset, pos.y - j * 0.1f, pos.z));

				tr->SetScale(Vec3(0.7f, 0.7f, 2.0f));
				missile->Initalize();
			}
		}
		

		//UINT missileCount = 20;		// 미사일 개수
		//float missileAngle = 60.0f;	// 미사일 각도
		//float angleUnit = missileAngle / (missileCount - 1);	//미사일 당 이동 해야하는 각도

		//for (size_t i = 0; i < 5; i++)
		//{
		//	float missileOffset = -1.0f + i * 0.5f;
		//	for (size_t j = 0; j < missileCount; j++)
		//	{	
		//		MonsterMissile* missile = object::Instantiate<MonsterMissile>(eLayerType::Monster_Attack);
		//		missile->SetDegree(Dir + (angleUnit * j) - (missileAngle / 2.0f));
		//		missile->SetSpeed(6.0f);

		//		missile->AddComponent<Collider2D>();
		//		Collider2D* collider = missile->GetComponent<Collider2D>();
		//		collider->SetType(eColliderType::Rect);
		//		collider->SetSize(Vec2(0.6f, 0.6f));

		//		Transform* tr = missile->GetComponent<Transform>();
		//		Vec3 pos = mTransform->GetPosition();
		//		if (mOneDirection == eDirection::Down || mOneDirection == eDirection::DownLeft || mOneDirection == eDirection::DownRight)
		//			tr->SetPosition(Vec3(pos.x - j * 0.1f, pos.y - missileOffset, pos.z));
		//		else if (mOneDirection == eDirection::Left)
		//			tr->SetPosition(Vec3(pos.x - missileOffset, pos.y + j * 0.1f, pos.z));
		//		else if (mOneDirection == eDirection::Up || mOneDirection == eDirection::UpRight || mOneDirection == eDirection::UpLeft)
		//			tr->SetPosition(Vec3(pos.x + j * 0.1f, pos.y - missileOffset, pos.z));
		//		else if (mOneDirection == eDirection::Right)
		//			tr->SetPosition(Vec3(pos.x - missileOffset, pos.y - j * 0.1f, pos.z));

		//		tr->SetScale(Vec3(0.7f, 0.7f, 2.0f));
		//		missile->Initalize();
		//	}
		//}


	}
	
	void Forest_Fairy::resurrection()
	{

		mStateInfo.direction = eDirection::Down;
		mStateInfo.situation = eSituation::Patrol;

		mStatus->SetStateInfo(mStateInfo);

		mHp = 20;

		mAnimator->Play(L"Idle_Down", true);

	}


}