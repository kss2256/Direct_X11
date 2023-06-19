#include "ksSlime_Green.h"
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
#include "ksAudioClip.h"

#include "ksInput.h"



namespace ks
{

	Slime_Green::Slime_Green()
		: m_bSoundOneCheak(false)
		, m_bSoundCheak(false)
	{
		mTransform = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>();



		mStateInfo.direction = eDirection::Down;
		mStateInfo.situation = eSituation::Patrol;

		mStatus = AddComponent<Status>();
		mStatus->SetStateInfo(mStateInfo);

		mHp = 15;

		loadAnimation();
		loadSound();


		SpriteRenderer* sr = AddComponent<SpriteRenderer>();

		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"SpriteMaterial");

		sr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);

		srand((unsigned int)time(nullptr));
		int a = rand();

		mAnimator->Play(L"Idle_Down", true);

	}

	Slime_Green::~Slime_Green()
	{


	}

	void Slime_Green::Initalize()
	{

		GameObject::Initalize();
	}

	void Slime_Green::Update()
	{


		mHp;

		if(mDetection)
		{

			if (mPlayer != nullptr)
				mTargetPos = mPlayer->GetComponent<Transform>()->GetPosition();

			mMonsterPos = mTransform->GetPosition();
			Vec3 pos = mTransform->GetPosition();

			if (mStateInfo.situation == eSituation::Death)
			{
				mTime += Time::DeltaTime();
				mAnimator->Play(L"Death", false);
				if(!m_bSoundDeathCheak)
				{
					soundDeath();
					m_bSoundDeathCheak = true;
				}

				createCoin(mTransform->GetPosition());

				if (mTime >= 1.0f)
				{
					//this->Death();
					
					mTransform->SetPosition(Vec3(0.0f, 20.0f, 1.0f));
					mDetection = false;
					m_bWalkStop = false;
					m_bSoundDeathCheak = false;
					Stage1_1* stage = nullptr;
					stage->KeyCount_Up();
					mTime = 0.f;
				}

			}

			else
			{
				if (m_bWalkStop)
					return;
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
								AngleDirection();
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
						int a = rand() % 2;		//0 ~ 9 까지 랜덤의 수인데 거기에 +1 을 해서

						mRnadomAttack = (float)a;

						mStep = eStep::Step_1;

					}
					if (mRnadomAttack == 0)
					{

						if (mStep == eStep::Step_1)
						{

							mFixPos = mPlayer->GetComponent<Transform>()->GetPosition();
							mStep = eStep::Step_2;
							mOneDirection = mStateInfo.direction;
						}

						if (mStep == eStep::Step_2)
						{
							oneDirectionAnimation(L"Attack_Triple", mOneDirection, false);
							mStep = eStep::Step_3;
						}

						if (mStep == eStep::Step_3)
						{
							mTime += Time::DeltaTime();
							if (!mCheak)
							{
								if (mTime >= 0.6f)
								{
									soundtripleAttack();
									tripleAttack();
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
					else if (mRnadomAttack == 1)
					{
						if (mStep == eStep::Step_1)
						{
							mFixPos = mPlayer->GetComponent<Transform>()->GetPosition();
							mStep = eStep::Step_2;
							mOneDirection = mStateInfo.direction;
						}

						if (mStep == eStep::Step_2)
						{
							oneDirectionAnimation(L"Attack_Multiple", mOneDirection, false);
							mStep = eStep::Step_3;
						}

						if (mStep == eStep::Step_3)
						{
							mTime += Time::DeltaTime();
							if (!mCheak)
							{
								if (mTime >= 0.3f && m_bSoundCheak == false)
								{
									soundMultipleJump();
									m_bSoundCheak = true;
								}

								if (mTime >= 0.6f && m_bSoundOneCheak == false)
								{
									soundMultipleJump();
									m_bSoundOneCheak = true;
								}


								if (mTime >= 1.2f)
								{
									soundMultipleAttack();
									multipleAttack();
									mCheak = true;
								}
							}
							if (mTime >= 1.4f)
							{
								directionAnimation(L"Idle", true);
								mAttackCool = true;
								mCheak = false;
								m_bSoundOneCheak = false;
								m_bSoundCheak = false;
								mStep = eStep::None;
								mStateInfo.situation = eSituation::None;
								mTime = 0.f;
							}
						}
					}



				}

				if (mStateInfo.situation == eSituation::Hit)
				{
					hit(0.1f, 0.2f, 50.f);
					directionAnimation(L"Idle", true);
				}
				if (mStateInfo.situation == eSituation::Skil_Hit)
				{					
					//directionAnimation(L"Idle", true);
				}


			}
		}

		Monster::Update();
	}

	void Slime_Green::FixedUpdate()
	{

		GameObject::FixedUpdate();
	}

	void Slime_Green::Render()
	{

		GameObject::Render();
	}


	void Slime_Green::loadAnimation()
	{

		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Slime_Green", L"Monster\\Slime_Green.png");



		mNumbers.push_back(0);
		mNumbers.push_back(2);
		CreateAnimation(L"Move_Down", texture, mAnimator, Vector2(96.0f, 96.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();

		mNumbers.push_back(3);
		mNumbers.push_back(5);
		CreateAnimation(L"Move_Left", texture, mAnimator, Vector2(96.0f, 96.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();

		mNumbers.push_back(6);
		mNumbers.push_back(8);
		CreateAnimation(L"Move_Right", texture, mAnimator, Vector2(96.0f, 96.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();

		mNumbers.push_back(9);
		mNumbers.push_back(11);
		CreateAnimation(L"Move_Up", texture, mAnimator, Vector2(96.0f, 96.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();



		mNumbers.push_back(12);
		mNumbers.push_back(13);
		mNumbers.push_back(14);
		mNumbers.push_back(24);
		mNumbers.push_back(25);
		mNumbers.push_back(26);
		CreateAnimation(L"Attack_Multiple_Down", texture, mAnimator, Vector2(96.0f, 96.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();

		mNumbers.push_back(15);
		mNumbers.push_back(16);
		mNumbers.push_back(17);
		mNumbers.push_back(27);
		mNumbers.push_back(28);
		mNumbers.push_back(29);
		CreateAnimation(L"Attack_Multiple_Left", texture, mAnimator, Vector2(96.0f, 96.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();

		mNumbers.push_back(18);
		mNumbers.push_back(19);
		mNumbers.push_back(20);
		mNumbers.push_back(30);
		mNumbers.push_back(31);
		mNumbers.push_back(32);
		CreateAnimation(L"Attack_Multiple_Right", texture, mAnimator, Vector2(96.0f, 96.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();



		mNumbers.push_back(21);
		mNumbers.push_back(22);
		mNumbers.push_back(23);
		mNumbers.push_back(33);
		mNumbers.push_back(34);
		mNumbers.push_back(35);
		CreateAnimation(L"Attack_Multiple_Up", texture, mAnimator, Vector2(96.0f, 96.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();




		mNumbers.push_back(36);
		mNumbers.push_back(37);
		mNumbers.push_back(38);
		CreateAnimation(L"Attack_Triple_Down", texture, mAnimator, Vector2(96.0f, 96.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();

		mNumbers.push_back(51);
		mNumbers.push_back(52);
		mNumbers.push_back(53);
		CreateAnimation(L"Attack_Triple_Left", texture, mAnimator, Vector2(96.0f, 96.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();

		mNumbers.push_back(54);
		mNumbers.push_back(55);
		mNumbers.push_back(56);
		CreateAnimation(L"Attack_Triple_Right", texture, mAnimator, Vector2(96.0f, 96.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();

		mNumbers.push_back(57);
		mNumbers.push_back(58);
		mNumbers.push_back(59);
		CreateAnimation(L"Attack_Triple_Up", texture, mAnimator, Vector2(96.0f, 96.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();


		mNumbers.push_back(60);
		mNumbers.push_back(61);
		mNumbers.push_back(62);
		CreateAnimation(L"Death", texture, mAnimator, Vector2(96.0f, 96.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();


		mNumbers.push_back(39);
		CreateAnimation(L"Hit_Down", texture, mAnimator, Vector2(96.0f, 96.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();

		mNumbers.push_back(42);
		CreateAnimation(L"Hit_Left", texture, mAnimator, Vector2(96.0f, 96.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();

		mNumbers.push_back(45);
		CreateAnimation(L"Hit_Right", texture, mAnimator, Vector2(96.0f, 96.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();

		mNumbers.push_back(48);
		CreateAnimation(L"Hit_Up", texture, mAnimator, Vector2(96.0f, 96.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();



		mNumbers.push_back(1);
		CreateAnimation(L"Idle_Down", texture, mAnimator, Vector2(96.0f, 96.0f), Vec2::Zero, mNumbers, 0.1f);
		mNumbers.clear();

		mNumbers.push_back(4);
		CreateAnimation(L"Idle_Left", texture, mAnimator, Vector2(96.0f, 96.0f), Vec2::Zero, mNumbers, 0.1f);
		mNumbers.clear();

		mNumbers.push_back(7);
		CreateAnimation(L"Idle_Right", texture, mAnimator, Vector2(96.0f, 96.0f), Vec2::Zero, mNumbers, 0.1f);
		mNumbers.clear();

		mNumbers.push_back(10);
		CreateAnimation(L"Idle_Up", texture, mAnimator, Vector2(96.0f, 96.0f), Vec2::Zero, mNumbers, 0.1f);
		mNumbers.clear();
	}

	void Slime_Green::loadSound()
	{

		std::shared_ptr<AudioClip> slime_death = Resources::Load<AudioClip>
			(L"slime_death", L"D:\\50\\Resources\\Sound\\slime_death.ogg");

		std::shared_ptr<AudioClip> slime_Triple_Attack = Resources::Load<AudioClip>
			(L"slime_Triple_Attack", L"D:\\50\\Resources\\Sound\\slime_Triple_Attack.ogg");

		std::shared_ptr<AudioClip> slime_jump = Resources::Load<AudioClip>
			(L"slime_jump", L"D:\\50\\Resources\\Sound\\slime_jump.ogg");

		std::shared_ptr<AudioClip> slime_jump_Attack = Resources::Load<AudioClip>
			(L"slime_jump_Attack", L"D:\\50\\Resources\\Sound\\slime_jump_Attack.ogg");

	}

	void Slime_Green::tripleAttack()
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
			Vec3 pos = mTransform->GetPosition();
			
			tr->SetPosition(Vec3(pos.x, pos.y - 0.4f, pos.z));
			tr->SetScale(Vec3(0.7f, 0.7f, 2.0f));

			missile->Initalize();
		}


	}

	void Slime_Green::multipleAttack()
	{

		for (size_t i = 0; i < 8; i++)
		{
			MonsterMissile* missile = object::Instantiate<MonsterMissile>(eLayerType::Monster_Attack);
			missile->SetDegree((i * 45.f));
			missile->SetSpeed(6.0f);


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

	void Slime_Green::soundDeath()
	{
		std::shared_ptr<AudioClip> sound = Resources::Find<AudioClip>(L"slime_death");
		sound->SetLoop(false);
		sound->Play();

	}

	void Slime_Green::soundtripleAttack()
	{
		std::shared_ptr<AudioClip> sound = Resources::Find<AudioClip>(L"slime_Triple_Attack");
		sound->SetLoop(false);
		sound->Play();
	}

	void Slime_Green::soundMultipleJump()
	{
		std::shared_ptr<AudioClip> sound = Resources::Find<AudioClip>(L"slime_jump");
		sound->SetLoop(false);
		sound->Play();
	}

	void Slime_Green::soundMultipleAttack()
	{
		std::shared_ptr<AudioClip> sound = Resources::Find<AudioClip>(L"slime_jump_Attack");
		sound->SetLoop(false);
		sound->Play(3.0f);
	}

	void Slime_Green::resurrection()
	{
		mStateInfo.direction = eDirection::Down;
		mStateInfo.situation = eSituation::Patrol;
		m_bCoin = false;
		mStatus->SetStateInfo(mStateInfo);

		mHp = 15;

		mAnimator->Play(L"Idle_Down", true);

	}


}