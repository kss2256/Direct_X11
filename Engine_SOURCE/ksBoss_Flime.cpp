#include "ksBoss_Flime.h"
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
#include "ksMonster_Trap_Line.h"
#include "ksFlime_Missile.h"
#include "ksStage1_1.h"



#define PI 3.1415926535f

#include "ksInput.h"

namespace ks
{


	Boss_Flime::Boss_Flime()
		: mTrapCount(1)
		, mInterval(1.3f)
		, mMaxTrapCount(7)
		
	{

		mTransform = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>();



		mStateInfo.direction = eDirection::None;
		mStateInfo.situation = eSituation::None;

		mStatus = AddComponent<Status>();
		mStatus->SetStateInfo(mStateInfo);

		mAttackCool = true;


		mHp = 100;

		loadAnimation();



		SpriteRenderer* sr = AddComponent<SpriteRenderer>();

		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"SpriteMaterial");
		sr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);

		srand((unsigned int)time(nullptr));
		int a = rand();

		mAnimator->Play(L"Idle_Down", true);

	}

	Boss_Flime::~Boss_Flime()
	{
	}

	void Boss_Flime::Initalize()
	{


		GameObject::Initalize();

	}

	void Boss_Flime::Update()
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

					Stage1_1* stage = nullptr;
					stage->KeyCount_Up();

					this->Death();
					mTime = 0.f;
				}

			}

			else
			{
				

				if (mStateInfo.situation == eSituation::None)
				{
					mTime += Time::DeltaTime();

					if (mAttackCool)
					{
						AngleDirection();
						if (!mDirectionCheak)
						{
							mCheak = false;
						}
						if (!mCheak)
						{
							directionAnimation(L"Idle", true);
							mCheak = true;
						}

						if (mTime >= 3.0f)
						{
							mStateInfo.situation = eSituation::Attack;

							mCheak = false;
							mAttackCool = false;
							mTime = 0.f;
						}
					}

				}

				if (mStateInfo.situation == eSituation::Attack)
				{

					if (mStep == eStep::None)
					{

						int a = rand() % 3;		//0 ~ 9 까지 랜덤의 수인데 거기에 +1 을 해서					
						mRnadomAttack = a;

						if (mPrevRnadom != mRnadomAttack)
						{
							mStep = eStep::Step_1;
							AngleDirection();
							mPrevRnadom = mRnadomAttack;
						}
						//mRnadomAttack = 1;
					}

					if (mRnadomAttack == 0)
					{
						mTime += Time::DeltaTime();


						if (mStep == eStep::Step_1)
						{
							directionAnimation(L"Attack_Direction", false);
							multipleAttack(18.f, 20);
							mStep = eStep::Step_2;
							mTime = 0.f;
						}
						if (mStep == eStep::Step_2)
						{
							if (mTime >= 0.7f)
							{
								//directionAnimation(L"Idle", true);
								multipleAttack(14.4f, 25);
								mStep = eStep::Step_3;
								mTime = 0.f;
							}
						}
						if (mStep == eStep::Step_3)
						{
							if (mTime >= 0.7f)
							{
								multipleAttack(18.f, 20);
								mStep = eStep::Step_4;
								mTime = 0.f;
							}
						}

						if (mStep == eStep::Step_4)
						{
							if (mTime >= 0.7f)
							{
								mStateInfo.situation = eSituation::None;
								mStep = eStep::None;
								mAttackCool = true;
								mCheak = false;
								mTime = 0.f;
							}
						}

					}
					else if (mRnadomAttack == 1)
					{
						mTime += Time::DeltaTime();

						if (mStep == eStep::Step_1)
						{
							directionAnimation(L"Attack_Thorn", false);
							mStep = eStep::Step_2;
							mTime = 0.f;
						}
						if (mStep == eStep::Step_2)
						{
							if (mTime >= 0.7f)
							{
								mStep = eStep::Step_3;
								mTime = 0.f;
							}
						}


						if (mStep == eStep::Step_3)
						{
							if (mTime >= 0.25)
							{
								for (size_t i = 1; i < mMaxTrapCount; i++)
								{
									if (mTrapCount == i)
										directionTrap(8, i * mInterval, true);
								}
								mTime = 0.f;
								++mTrapCount;
							}

							if (mTrapCount == 7)
							{
								mStep = eStep::Step_4;
								mTrapCount = 0;
								mTime = 0.f;
							}

						}

						if (mStep == eStep::Step_4)
						{
							if (mTime >= 2.5f)
							{
								mStateInfo.situation = eSituation::None;
								mStep = eStep::None;
								mAttackCool = true;
								mCheak = false;
								mTime = 0.f;
							}
						}

					}
					else if (mRnadomAttack == 2)
					{
						mTime += Time::DeltaTime();

						if (mStep == eStep::Step_1)
						{
							directionAnimation(L"Attack_Thorn", false);
							mStep = eStep::Step_2;
							mTime = 0.f;
						}

						if (mStep == eStep::Step_2)
						{
							if (mTime >= 0.7f)
							{
								mStep = eStep::Step_3;
								mTime = 0.f;
							}
						}

						// 트랩 갯수 정리 1. 가운데 1개 둘러싸기 20개 
						// 2. 캐릭 둘러싼거 10개 , 그다음 둘러싸기 20개
						//3. 1가운데 20개 20개 
						if (mStep == eStep::Step_3)
						{
							TrapAttack(1, 0.f, false);
							TrapAttack(20, 2.5f, false);

							mStep = eStep::Step_4;
							mTime = 0.f;

						}
						if (mStep == eStep::Step_4)
						{
							if (mTime >= 3.0f)
							{
								TrapAttack(10, 1.5f, false);
								TrapAttack(20, 3.7f, false);

								mStep = eStep::Step_5;
								mTime = 0.f;
							}
						}
						if (mStep == eStep::Step_5)
						{
							if (mTime >= 3.0f)
							{
								TrapAttack(1, 0.f, false);
								TrapAttack(20, 2.5f, false);
								TrapAttack(20, 4.5f, false);

								mStep = eStep::Step_6;
								mTime = 0.f;
							}

						}

						if (mStep == eStep::Step_6)
						{
							if (mTime >= 2.5f)
							{
								mStateInfo.situation = eSituation::None;
								mStep = eStep::None;
								mAttackCool = true;
								mCheak = false;
								mTime = 0.f;
							}
						}

					}
				}

			}


			if (mBossHit)
				boss_hit(0.2f, 0.2f, 50.f);

			/*if (mStateInfo.situation == eSituation::Hit)
			{
				hit(0.1f, 0.2f, 50.f);
				directionAnimation(L"Idle", true);
			}*/



		}



		GameObject::Update();
	}

	void Boss_Flime::FixedUpdate()
	{

		GameObject::FixedUpdate();
	}

	void Boss_Flime::Render()
	{

		GameObject::Render();
	}

	void Boss_Flime::loadAnimation()
	{

		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"BossFlime", L"Monster\\BossFlime.png");


		mNumbers.push_back(0);
		CreateAnimation(L"Attack_Direction_Down", texture, mAnimator, Vector2(250.0f, 190.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();

		mNumbers.push_back(3);
		CreateAnimation(L"Attack_Direction_Left", texture, mAnimator, Vector2(250.0f, 190.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();

		mNumbers.push_back(6);
		CreateAnimation(L"Attack_Direction_Right", texture, mAnimator, Vector2(250.0f, 190.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();

		mNumbers.push_back(9);
		CreateAnimation(L"Attack_Direction_Up", texture, mAnimator, Vector2(250.0f, 190.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();


		mNumbers.push_back(1);
		mNumbers.push_back(2);
		CreateAnimation(L"Idle_Down", texture, mAnimator, Vector2(250.0f, 190.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();

		mNumbers.push_back(4);
		mNumbers.push_back(5);
		CreateAnimation(L"Idle_Left", texture, mAnimator, Vector2(250.0f, 190.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();

		mNumbers.push_back(7);
		mNumbers.push_back(8);
		CreateAnimation(L"Idle_Right", texture, mAnimator, Vector2(250.0f, 190.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();

		mNumbers.push_back(10);
		mNumbers.push_back(11);
		CreateAnimation(L"Idle_Up", texture, mAnimator, Vector2(250.0f, 190.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();


		mNumbers.push_back(12);
		mNumbers.push_back(13);
		mNumbers.push_back(14);
		CreateAnimation(L"Attack_Thorn_Down", texture, mAnimator, Vector2(250.0f, 190.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();

		mNumbers.push_back(15);
		mNumbers.push_back(16);
		mNumbers.push_back(17);
		CreateAnimation(L"Attack_Thorn_Left", texture, mAnimator, Vector2(250.0f, 190.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();

		mNumbers.push_back(18);
		mNumbers.push_back(19);
		mNumbers.push_back(20);
		CreateAnimation(L"Attack_Thorn_Right", texture, mAnimator, Vector2(250.0f, 190.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();

		mNumbers.push_back(21);
		mNumbers.push_back(22);
		mNumbers.push_back(23);
		CreateAnimation(L"Attack_Thorn_Up", texture, mAnimator, Vector2(250.0f, 190.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();

		mNumbers.push_back(24);
		CreateAnimation(L"Death", texture, mAnimator, Vector2(250.0f, 190.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();

	}

	void Boss_Flime::multipleAttack(float dir, UINT count)
	{


		for (size_t i = 0; i < count; i++)
		{
			MonsterMissile* missile = object::Instantiate<MonsterMissile>(eLayerType::Monster_Attack);
			missile->SetDegree((i * dir));
			missile->SetSpeed(4.0f);


			missile->AddComponent<Collider2D>();
			Collider2D* collider = missile->GetComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			collider->SetSize(Vec2(0.6f, 0.6f));

			Transform* tr = missile->GetComponent<Transform>();
			Vec3 pos = mTransform->GetPosition();

			tr->SetPosition(Vec3(pos.x, pos.y - 0.4f, pos.z));
			tr->SetScale(Vec3(0.7f, 0.7f, 2.0f));

			missile->Initalize();
		}

	}

	void Boss_Flime::directionTrap(UINT count, float interval, bool missil)
	{
		float dir = 360.f / (float)count;
		for (size_t i = 0; i < count; i++)
		{
			Monster_Trap_Line* trap = object::Instantiate<Monster_Trap_Line>(eLayerType::Monster_Attack);

			trap->SetDegree((i * dir));
			trap->SetMonsterLine(Monster_Line::Flime_Missile);
			Transform* tr = trap->GetComponent<Transform>();

			tr->SetPosition(mTransform->GetPosition());
			tr->SetScale(Vec3(0.8f, 0.8f, 2.0f));
			trap->Lineinterval(interval);


			Flime_Missile* missile = object::Instantiate<Flime_Missile>(eLayerType::Monster_Attack);
			missile->SetDegree((i * dir));
			missile->SetMissile(missil);
			Transform* missiletr = missile->GetComponent<Transform>();
			missile->AddComponent<Collider2D>();
			missiletr->SetPosition(mTransform->GetPosition());
			missiletr->SetScale(Vec3(0.0f, 0.0f, 2.0f));
			missile->Lineinterval(interval);
		}


	}

	void Boss_Flime::TrapAttack(UINT count, float interval, bool missil)
	{
		float dir = 360.f / (float)count;
		for (size_t i = 0; i < count; i++)
		{
			Monster_Trap_Line* trap = object::Instantiate<Monster_Trap_Line>(eLayerType::Monster_Attack);
			trap->SetDegree((i * dir));
			trap->SetMonsterLine(Monster_Line::Flime_Trap);
			Transform* tr = trap->GetComponent<Transform>();		
			

			tr->SetPosition(mPlayer->GetComponent<Transform>()->GetPosition());
			tr->SetScale(Vec3(0.8f, 0.8f, 2.0f));
			trap->Lineinterval(interval);

			Flime_Missile* missile = object::Instantiate<Flime_Missile>(eLayerType::Monster_Attack);
			missile->SetDegree((i * dir));
			missile->SetMissile(missil);
			Transform* missiletr = missile->GetComponent<Transform>();
			missile->AddComponent<Collider2D>();
			missiletr->SetPosition(mPlayer->GetComponent<Transform>()->GetPosition());
			missiletr->SetScale(Vec3(0.0f, 0.0f, 2.0f));
			missile->Lineinterval(interval);
		}

	}


}