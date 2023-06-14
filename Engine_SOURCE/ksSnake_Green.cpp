#include "ksSnake_Green.h"
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

#include "ksAudioClip.h"


namespace ks
{

	Snake_Green::Snake_Green()
		: m_bSoundDeathCheak(false)
	{
		mTransform = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>();

		

		mStateInfo.direction = eDirection::Down;
		mStateInfo.situation = eSituation::Patrol;
		
		mStatus = AddComponent<Status>();
		mStatus->SetStateInfo(mStateInfo);

		
		mHp = 10;


		loadAnimation();
		loadSound();

		SpriteRenderer* sr = AddComponent<SpriteRenderer>();

		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"SpriteMaterial");
		sr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);

		mAnimator->Play(L"Idle_Down", true);

	}

	Snake_Green::~Snake_Green()
	{
	}

	void Snake_Green::Initalize()
	{


		GameObject::Initalize();
	}

	void Snake_Green::Update()
	{


		mHp;

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
				if (!m_bSoundDeathCheak)
				{
					soundDeath();
					m_bSoundDeathCheak = true;
				}
				createCoin(mTransform->GetPosition());

				if (mTime >= 1.0f)
				{
					//this->Death();

					mTransform->SetPosition(Vec3(0.0f, 0.0f, 1.0f));
					mDetection = false;
					m_bSoundDeathCheak = false;
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

					pos += mMovePos * 2.0f * Time::DeltaTime();


					if (mStep == eStep::None)
					{
						soundAttack1();
						mFixPos = mPlayer->GetComponent<Transform>()->GetPosition();
						mMovePos = mFixPos - mMonsterPos;
					
						mMovePos.Normalize();
						mStep = eStep::Step_1;
						mOneDirection = mStateInfo.direction;
					}

					if (mStep == eStep::Step_1)
					{

						oneDirectionAnimation(L"Attack", mOneDirection, false);
						soundAttack2();
						tripleAttack();
						mStep = eStep::Step_2;
					}

					if (mStep == eStep::Step_2)
					{
						mTime += Time::DeltaTime();
						if (!mCheak)
						{
							if (mTime >= 0.8f)
							{
								oneDirectionAnimation(L"Move", mOneDirection, true);
								mCheak = true;
							}
						}

						if (mTime >= 1.5f)
						{
							oneDirectionAnimation(L"Attack", mOneDirection, false);

							doubleAttack();
							mStep = eStep::Step_3;
							mCheak = false;
							mTime = 0.f;
						}
					}
					if (mStep == eStep::Step_3)
					{
						mTime += Time::DeltaTime();
						if (!mCheak)
						{
							if (mTime >= 0.8f)
							{
								oneDirectionAnimation(L"Move", mOneDirection, true);
								mCheak = true;
							}
						}

						if (mTime >= 1.5f)
						{
							oneDirectionAnimation(L"Attack", mOneDirection, false);
							soundAttack2();
							tripleAttack();
							mStep = eStep::Step_4;
							mCheak = false;
							mTime = 0.f;
						}
					}

					if (mStep == eStep::Step_4)
					{
						mTime += Time::DeltaTime();
						if (!mCheak)
						{
							if (mTime >= 0.8f)
							{
								oneDirectionAnimation(L"Move", mOneDirection, true);
								mCheak = true;
							}
						}
						if (mTime >= 1.5f)
						{
							oneDirectionAnimation(L"Attack_Wait", mOneDirection, true);
							mAttackCool = true;
							mCheak = false;
							mStep = eStep::None;
							mStateInfo.situation = eSituation::None;
							mTime = 0.f;
						}
					}



					mTransform->SetPosition(pos);
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

	void Snake_Green::FixedUpdate()
	{		

		GameObject::FixedUpdate();
	}

	void Snake_Green::Render()
	{
		GameObject::Render();
	}



	void Snake_Green::loadAnimation()
	{


		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Snake_Green", L"Monster\\Snake_Green.png");



		mNumbers.push_back(0);
		mNumbers.push_back(2);
		CreateAnimation(L"Move_Down", texture, mAnimator, Vector2(48.0f, 48.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();

		mNumbers.push_back(3);
		mNumbers.push_back(5);
		CreateAnimation(L"Move_Left", texture, mAnimator, Vector2(48.0f, 48.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();

		mNumbers.push_back(6);
		mNumbers.push_back(8);
		CreateAnimation(L"Move_Right", texture, mAnimator, Vector2(48.0f, 48.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();

		mNumbers.push_back(9);
		mNumbers.push_back(11);
		CreateAnimation(L"Move_Up", texture, mAnimator, Vector2(48.0f, 48.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();


		mNumbers.push_back(12);
		mNumbers.push_back(13);
		mNumbers.push_back(14);
		CreateAnimation(L"Attack_Down", texture, mAnimator, Vector2(48.0f, 48.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();

		mNumbers.push_back(15);
		mNumbers.push_back(16);
		mNumbers.push_back(17);
		CreateAnimation(L"Attack_Left", texture, mAnimator, Vector2(48.0f, 48.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();

		mNumbers.push_back(18);
		mNumbers.push_back(19);
		mNumbers.push_back(20);
		CreateAnimation(L"Attack_Right", texture, mAnimator, Vector2(48.0f, 48.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();

		mNumbers.push_back(21);
		mNumbers.push_back(22);
		mNumbers.push_back(23);
		CreateAnimation(L"Attack_Up", texture, mAnimator, Vector2(48.0f, 48.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();


		mNumbers.push_back(24);
		mNumbers.push_back(25);
		CreateAnimation(L"Attack_Wait_Down", texture, mAnimator, Vector2(48.0f, 48.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();

		mNumbers.push_back(27);
		mNumbers.push_back(28);
		CreateAnimation(L"Attack_Wait_Left", texture, mAnimator, Vector2(48.0f, 48.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();

		mNumbers.push_back(30);
		mNumbers.push_back(31);
		CreateAnimation(L"Attack_Wait_Right", texture, mAnimator, Vector2(48.0f, 48.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();

		mNumbers.push_back(33);
		mNumbers.push_back(34);
		CreateAnimation(L"Attack_Wait_Up", texture, mAnimator, Vector2(48.0f, 48.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();

		mNumbers.push_back(36);
		CreateAnimation(L"Death", texture, mAnimator, Vector2(48.0f, 48.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();


		mNumbers.push_back(1);
		CreateAnimation(L"Idle_Down", texture, mAnimator, Vector2(48.0f, 48.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();

		mNumbers.push_back(4);
		CreateAnimation(L"Idle_Left", texture, mAnimator, Vector2(48.0f, 48.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();

		mNumbers.push_back(7);
		CreateAnimation(L"Idle_Right", texture, mAnimator, Vector2(48.0f, 48.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();

		mNumbers.push_back(10);
		CreateAnimation(L"Idle_Up", texture, mAnimator, Vector2(48.0f, 48.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();

	}

	void Snake_Green::doubleAttack()
	{


		float Dir = 0.f;
		if (mOneDirection == eDirection::Down)
			Dir = 75.0f;
		else if (mOneDirection == eDirection::Left)
			Dir = 165.0f;
		else if (mOneDirection == eDirection::Up)
			Dir = 255.0f;
		else if (mOneDirection == eDirection::Right)
			Dir = 345.0f;
		else if (mOneDirection == eDirection::DownLeft)
			Dir = 120.f;
		else if (mOneDirection == eDirection::DownRight)
			Dir = 30.f;
		else if (mOneDirection == eDirection::UpRight)
			Dir = 300.f;
		else if (mOneDirection == eDirection::UpLeft)
			Dir = 210.f;

		for (size_t i = 0; i < 2; i++)
		{
			MonsterMissile* missile = object::Instantiate<MonsterMissile>(eLayerType::Monster_Attack);
			missile->SetDegree(Dir + (i * 25));
			missile->SetSpeed(6.0f);

			missile->AddComponent<Collider2D>();
			Collider2D* collider = missile->GetComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			collider->SetSize(Vec2(0.6f, 0.6f));

			Transform* tr = missile->GetComponent<Transform>();
			tr->SetPosition(mTransform->GetPosition());
			tr->SetScale(Vec3(0.7f, 0.7f, 2.0f));
			missile->Initalize();

		}
	}

	void Snake_Green::tripleAttack()
	{
		
		float Dir = 0.f;
		if (mOneDirection == eDirection::Down)
			Dir = 60.0f;
		else if (mOneDirection == eDirection::Left)
			Dir = 150.0f;
		else if (mOneDirection == eDirection::Up)
			Dir = 240.0f;
		else if (mOneDirection == eDirection::Right)
			Dir = 330.0f;
		else if (mOneDirection == eDirection::DownLeft)
			Dir = 120.f;
		else if (mOneDirection == eDirection::DownRight)
			Dir = 15.f;
		else if (mOneDirection == eDirection::UpRight)
			Dir = 300.f;
		else if (mOneDirection == eDirection::UpLeft)
			Dir = 210.f;


		for (size_t i = 0; i < 3; i++)
		{
			MonsterMissile* missile = object::Instantiate<MonsterMissile>(eLayerType::Monster_Attack);
			missile->SetDegree(Dir + (i * 30));
			missile->SetSpeed(6.0f);


			missile->AddComponent<Collider2D>();
			Collider2D* collider = missile->GetComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			collider->SetSize(Vec2(0.6f, 0.6f));

			Transform* tr = missile->GetComponent<Transform>();
			tr->SetPosition(mTransform->GetPosition());
			tr->SetScale(Vec3(0.7f, 0.7f, 2.0f));

			missile->Initalize();
		}



	}

	void Snake_Green::loadSound()
	{

		std::shared_ptr<AudioClip> Snake_death = Resources::Load<AudioClip>
			(L"Snake_death", L"D:\\50\\Resources\\Sound\\Snake_death.ogg");

		std::shared_ptr<AudioClip> Snake_Attack1 = Resources::Load<AudioClip>
			(L"Snake_Attack1", L"D:\\50\\Resources\\Sound\\Snake_Attack1.ogg");

		std::shared_ptr<AudioClip> Snake_Attack2 = Resources::Load<AudioClip>
			(L"Snake_Attack2", L"D:\\50\\Resources\\Sound\\Snake_Attack2.ogg");

		


	}

	void Snake_Green::soundDeath()
	{
		std::shared_ptr<AudioClip> sound = Resources::Find<AudioClip>(L"Snake_death");
		sound->SetLoop(false);
		sound->Play();
	}

	void Snake_Green::soundAttack1()
	{
		std::shared_ptr<AudioClip> sound = Resources::Find<AudioClip>(L"Snake_Attack1");
		sound->SetLoop(false);
		sound->Play();

	}

	void Snake_Green::soundAttack2()
	{
		std::shared_ptr<AudioClip> sound = Resources::Find<AudioClip>(L"Snake_Attack2");
		sound->SetLoop(false);
		sound->Play();
	}

	void Snake_Green::resurrection()
	{

		mStateInfo.direction = eDirection::Down;
		mStateInfo.situation = eSituation::Patrol;
		m_bCoin = false;
		mHp = 10;

		mStatus->SetStateInfo(mStateInfo);

	
	
		mAnimator->Play(L"Idle_Down", true);
	}
}