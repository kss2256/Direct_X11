#include "ksBoss_Ent.h"
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
#include "ksEnt_Poison.h"
#include "ksEnt_Sphere.h"
#include "ksCamera.h"
#include "ksStage1_1.h"
#include "ksAudioClip.h"
#include "ksGoldBox.h"

#include "ksMonsterMissile.h"

#define PI 3.1415926535f

#include "ksInput.h"


namespace ks
{

	Boss_Ent::Boss_Ent()
		: mPhase(Phase::None)
		, mTrapCount(0)
		, m_bSoundCheak(false)
		, m_bSoundDeathCheak(false)
		, mEntSoundCheak(false)
		, mEntCheak(false)
	{


		mTransform = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>();



		mStateInfo.direction = eDirection::None;
		mStateInfo.situation = eSituation::None;

		mStatus = AddComponent<Status>();
		mStatus->SetStateInfo(mStateInfo);

		mAttackCool = true;

		loadAnimation();
		loadSound();

		mHp = 200;

		SpriteRenderer* sr = AddComponent<SpriteRenderer>();

		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"SpriteMaterial");
		sr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);

		srand((unsigned int)time(nullptr));
		int a = rand();

		mAnimator->Play(L"Idle", true);

	}

	Boss_Ent::~Boss_Ent()
	{
	}

	void Boss_Ent::Initalize()
	{

		GameObject::Initalize();
	}

	void Boss_Ent::Update()
	{

		if (mDetection)
		{

			if (mPlayer != nullptr)
				mTargetPos = mPlayer->GetComponent<Transform>()->GetPosition();

			//mMonsterPos = mTransform->GetPosition();
			Vec3 pos = mTransform->GetPosition();

			if (mStateInfo.situation == eSituation::Death)
			{
				m_fTime += Time::DeltaTime();
				if (!m_bSoundDeathCheak)
				{
					soundClear();
					m_bSoundDeathCheak = true;
				}
				if (m_fTime >= 1.5f && !mEntSoundCheak)
				{
					soundDeath();
					mEntSoundCheak = true;
				}
				if (m_fTime >= 3.0f)
				{
					if (!mEntCheak)
					{
						createBox();
						mEntCheak = true;
					}
					Stage1_1* stage = nullptr;
					stage->KeyCount_Up();
					mPhase = Phase::None;

					mDetection = false;
					mTransform->SetPosition(Vec3::Zero);
					//this->Death();
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
							if (mPhase == Phase::Phase_1)
								mAnimator->Play(L"Phase_Idle", true);
							else
								mAnimator->Play(L"Idle", true);
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
					AngleDirection();
					if (mStep == eStep::None)
					{

						//int a = rand() % 3;		//0 ~ 9 까지 랜덤의 수인데 거기에 +1 을 해서					
						//mRnadomAttack = a;

						//if (mPrevRnadom != mRnadomAttack)
						//{
						//	mStep = eStep::Step_1;						
						//	mPrevRnadom = mRnadomAttack;
						//}

						if (mRnadomAttack >= 3)
							mRnadomAttack = 0;
						else
						{
							++mRnadomAttack;
						}

						m_bSoundCheak = true;
						mStep = eStep::Step_1;						
					}
					if (mRnadomAttack == 0)	//가시 공격
					{
						mTime += Time::DeltaTime();
						directionAnimation(L"Attack_Direction", false);
						if (mStep == eStep::Step_1)
						{
							if (mTime >= 0.6f)
							{
								for (size_t i = 0; i < 1; i++)
								{
									trapAttack();
								}
								mTime = 0.f;
								++mTrapCount;
								if (mTrapCount >= 6)
								{
									mStep = eStep::Step_2;
									mTrapCount = 0;
								}
							}
						}
						if (mStep == eStep::Step_2)
						{
							mStateInfo.situation = eSituation::None;
							mStep = eStep::None;
							mAttackCool = true;
							mCheak = false;
							mTime = 0.f;
						}


					}
					else if (mRnadomAttack == 1)	//독 뿌리기 공격 (왼쪽, 오른쪽 방향으로 + Phase는 둘다)
					{
						mTime += Time::DeltaTime();
						if (mStep == eStep::Step_1)
						{
							poisonAttackSound();
							int a = rand() % 2;		//0 ~ 9 까지 랜덤의 수인데 거기에 +1 을 해서					
							mPoisonRnadom = a;
							mStep = eStep::Step_2;
						}



						if (mStep == eStep::Step_2)
						{
							if (mPoisonRnadom == 0)
							{
								if (mPhase == Phase::None)
									mAnimator->Play(L"Attack_Direction_Left", false);
								else if (mPhase == Phase::Phase_1)
									mAnimator->Play(L"Phase_Attack_Direction_Left", false);
							}
							if (mPoisonRnadom == 1)
							{
								if (mPhase == Phase::None)
									mAnimator->Play(L"Attack_Direction_Right", false);
								else if (mPhase == Phase::Phase_1)
									mAnimator->Play(L"Phase_Attack_Direction_Right", false);
							}

							mStep = eStep::Step_3;
						}

						if (mStep == eStep::Step_3)
						{
							if (mTime >= 0.2)
							{
								for (size_t i = 1; i < 2; i++)
								{
									poisonAttack(mTrapCount, mPoisonRnadom);
									if (mPhase == Phase::Phase_1)
									{
										if (mPoisonRnadom == 0)
											poisonAttack(mTrapCount, 1);
										else if (mPoisonRnadom == 1)
											poisonAttack(mTrapCount, 0);
									}
								}
								mTime = 0.f;
								++mTrapCount;
								if (mTrapCount == 20)
								{
									mStep = eStep::Step_4;
									mTrapCount = 0;
								}
							}
						}
						if (mStep == eStep::Step_4)
						{

							mStateInfo.situation = eSituation::None;
							mStep = eStep::None;
							mAttackCool = true;
							mCheak = false;
							mTime = 0.f;
						}

					}
					else if (mRnadomAttack == 2)	//하늘색 구체 미사일
					{
						directionAnimation(L"Attack_Direction", false);
						mTime += Time::DeltaTime();
						if (mStep == eStep::Step_1)
						{
							mMonsterPos = mTransform->GetPosition();
							missileAttackSound();
							mStep = eStep::Step_2;
							mTime = 0.f;
						}
						if (mStep == eStep::Step_2)
						{
							if (mTime >= 0.3)
							{
								if (mPhase == Phase::Phase_1)
								{
									for (size_t i = 1; i < 2; i++)
									{
										sphereAttack_Phase(mTrapCount);
									}

								}
								else
								{
									for (size_t i = 1; i < 2; i++)
									{
										targetDir();
										sphereAttack();
									}
								}
								mTime = 0.f;
								++mTrapCount;
								if (mTrapCount == 15)
								{
									mStep = eStep::Step_3;
									mTrapCount = 0;
								}

							}
						}
						if (mStep == eStep::Step_3)
						{
							mStateInfo.situation = eSituation::None;

							mStep = eStep::None;
							mAttackCool = true;
							mCheak = false;
							mTime = 0.f;
						}

					}


					else if (mRnadomAttack == 3)	//화면 흔들리면서 범위 공격
					{
						directionAnimation(L"Attack_Direction", false);
						mTime += Time::DeltaTime();
						if (m_bSoundCheak)
						{
							earthquakeAttackSound();
							m_bSoundCheak = false;
						}

						if (mStep == eStep::Step_1)
						{
							earthquakeAttack();
							mainCamera->SetShock(true);
							mainCamera->SetShockDuration(2.0f);
							
							mStep = eStep::Step_2;
							mTime = 0.f;
						}

						if (mStep == eStep::Step_2)
						{

							if (mPhase == Phase::Phase_1)
							{
								if (mTime >= 1.5f)
								{
									if (mEartquake == 2)
									{

										mStep = eStep::Step_3;
										mTime = 0.f;
										mEartquake = 0;
									}
									else
									{
										mStep = eStep::Step_1;
										mTime = 0.f;
										++mEartquake;
									}
								}
							}
							else
							{
								mStep = eStep::Step_3;
								mTime = 0.f;
							}

						}

						if (mStep == eStep::Step_3)
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

			if (mHp <= 120 && mPhase == Phase::None && !(mStateInfo.situation == eSituation::Death))
			{
				if (mStateInfo.situation == eSituation::Attack)
				{
					if (mRnadomAttack == 1)
					{
						poisonAttackSoundStop();
					}
					else if (mRnadomAttack == 2)
					{
						missileAttackSoundStop();
					}
					else if (mRnadomAttack == 3)
					{
						earthquakeAttackSoundStop();
					}
				}

				mPhase = Phase::Phase_1;
				mStateInfo.situation = eSituation::Connect;
				mStep = eStep::None;
				mAttackCool = true;
				m_bSoundCheak = true;
				mCheak = false;
				mTime = 0.f;

			}

			if (mBossHit)
			{
				//boss_hit(0.1f, 0.2f, 50.f);
				boss_hit(0.1f, 0.01f, 25.f);
			}


			if (mStateInfo.situation == eSituation::Connect)
			{
				mTime += Time::DeltaTime();
				if (mStep == eStep::None)
				{
					mAnimator->Play(L"Phase", false);
					mStep = eStep::Step_1;
				}
				if (mStep == eStep::Step_1)
				{
					if (mTime >= 2.2f)
					{
						if (m_bSoundCheak)
						{
							earthquakeAttackSound();
							m_bSoundCheak = false;
						}
						mainCamera->SetShock(true);
						mainCamera->SetShockDuration(2.5f);
						mAnimator->Play(L"Phase_Attack_Start", true);
						mStep = eStep::Step_2;
						mTime = 0.f;
					}
				}

				if (mStep == eStep::Step_2)
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


		GameObject::Update();
	}

	void Boss_Ent::FixedUpdate()
	{

		GameObject::FixedUpdate();
	}

	void Boss_Ent::Render()
	{

		GameObject::Render();
	}



	void Boss_Ent::SetEntAnimation(const std::wstring& name)
	{
		mAnimator->Play(name, false);
	}

	void Boss_Ent::loadAnimation()
	{
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"BossEnt", L"Monster\\BossEnt.png");

		mNumbers.push_back(0);
		mNumbers.push_back(1);
		mNumbers.push_back(2);
		CreateAnimation(L"Roar1", texture, mAnimator, Vector2(322.0f, 350.0f), Vec2::Zero, mNumbers, 0.1f);
		mNumbers.clear();

		mNumbers.push_back(3);
		mNumbers.push_back(4);
		mNumbers.push_back(5);
		CreateAnimation(L"Roar2", texture, mAnimator, Vector2(322.0f, 350.0f), Vec2::Zero, mNumbers, 0.1f);
		mNumbers.clear();


		mNumbers.push_back(6);
		mNumbers.push_back(7);
		mNumbers.push_back(8);
		CreateAnimation(L"Attack_Start", texture, mAnimator, Vector2(322.0f, 350.0f), Vec2::Zero, mNumbers, 0.1f);
		mNumbers.clear();


		mNumbers.push_back(9);
		mNumbers.push_back(10);
		mNumbers.push_back(11);
		mNumbers.push_back(12);
		mNumbers.push_back(13);
		CreateAnimation(L"Attack_Direction_Right", texture, mAnimator, Vector2(322.0f, 350.0f), Vec2::Zero, mNumbers, 0.8f);
		mNumbers.clear();


		mNumbers.push_back(13);
		mNumbers.push_back(12);
		mNumbers.push_back(11);
		mNumbers.push_back(10);
		mNumbers.push_back(9);
		CreateAnimation(L"Attack_Direction_Left", texture, mAnimator, Vector2(322.0f, 350.0f), Vec2::Zero, mNumbers, 0.8f);
		mNumbers.clear();

		mNumbers.push_back(13);
		CreateAnimation(L"Attack_Direction_0", texture, mAnimator, Vector2(322.0f, 350.0f), Vec2::Zero, mNumbers, 0.1f);
		mNumbers.clear();

		mNumbers.push_back(12);
		CreateAnimation(L"Attack_Direction_45", texture, mAnimator, Vector2(322.0f, 350.0f), Vec2::Zero, mNumbers, 0.1f);
		mNumbers.clear();

		mNumbers.push_back(11);
		CreateAnimation(L"Attack_Direction_90", texture, mAnimator, Vector2(322.0f, 350.0f), Vec2::Zero, mNumbers, 0.1f);
		mNumbers.clear();

		mNumbers.push_back(10);
		CreateAnimation(L"Attack_Direction_135", texture, mAnimator, Vector2(322.0f, 350.0f), Vec2::Zero, mNumbers, 0.1f);
		mNumbers.clear();

		mNumbers.push_back(9);
		CreateAnimation(L"Attack_Direction_180", texture, mAnimator, Vector2(322.0f, 350.0f), Vec2::Zero, mNumbers, 0.1f);
		mNumbers.clear();

		mNumbers.push_back(15);
		mNumbers.push_back(16);
		mNumbers.push_back(17);
		mNumbers.push_back(18);
		mNumbers.push_back(19);
		mNumbers.push_back(20);
		mNumbers.push_back(21);
		mNumbers.push_back(22);
		mNumbers.push_back(23);
		mNumbers.push_back(24);
		mNumbers.push_back(25);

		CreateAnimation(L"Phase", texture, mAnimator, Vector2(322.0f, 350.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();






		mNumbers.push_back(26);
		CreateAnimation(L"Phase_Attack_Start", texture, mAnimator, Vector2(322.0f, 350.0f), Vec2::Zero, mNumbers, 0.1f);
		mNumbers.clear();


		mNumbers.push_back(27);
		mNumbers.push_back(28);
		mNumbers.push_back(29);
		mNumbers.push_back(30);
		mNumbers.push_back(31);
		CreateAnimation(L"Phase_Attack_Direction_Right", texture, mAnimator, Vector2(322.0f, 350.0f), Vec2::Zero, mNumbers, 0.8f);
		mNumbers.clear();


		mNumbers.push_back(31);
		mNumbers.push_back(30);
		mNumbers.push_back(29);
		mNumbers.push_back(28);
		mNumbers.push_back(27);
		CreateAnimation(L"Phase_Attack_Direction_Left", texture, mAnimator, Vector2(322.0f, 350.0f), Vec2::Zero, mNumbers, 0.8f);
		mNumbers.clear();

		mNumbers.push_back(31);
		CreateAnimation(L"Phase_Attack_Direction_0", texture, mAnimator, Vector2(322.0f, 350.0f), Vec2::Zero, mNumbers, 0.1f);
		mNumbers.clear();

		mNumbers.push_back(30);
		CreateAnimation(L"Phase_Attack_Direction_45", texture, mAnimator, Vector2(322.0f, 350.0f), Vec2::Zero, mNumbers, 0.1f);
		mNumbers.clear();

		mNumbers.push_back(29);
		CreateAnimation(L"Phase_Attack_Direction_90", texture, mAnimator, Vector2(322.0f, 350.0f), Vec2::Zero, mNumbers, 0.1f);
		mNumbers.clear();


		mNumbers.push_back(28);
		CreateAnimation(L"Phase_Attack_Direction_135", texture, mAnimator, Vector2(322.0f, 350.0f), Vec2::Zero, mNumbers, 0.1f);
		mNumbers.clear();

		mNumbers.push_back(27);
		CreateAnimation(L"Phase_Attack_Direction_180", texture, mAnimator, Vector2(322.0f, 350.0f), Vec2::Zero, mNumbers, 0.1f);
		mNumbers.clear();
		

		mNumbers.push_back(3);
		mNumbers.push_back(4);
		mNumbers.push_back(5);
		CreateAnimation(L"Idle", texture, mAnimator, Vector2(322.0f, 350.0f), Vec2::Zero, mNumbers, 0.3f);
		mNumbers.clear();

		mNumbers.push_back(21);
		mNumbers.push_back(22);
		mNumbers.push_back(23);
		CreateAnimation(L"Phase_Idle", texture, mAnimator, Vector2(322.0f, 350.0f), Vec2::Zero, mNumbers, 0.3f);
		mNumbers.clear();

	}

	void Boss_Ent::directionAnimation(const std::wstring& name, bool loop)
	{
		std::wstring aniname;

		

		switch (mStateInfo.direction)
		{
		case ks::eDirection::Left:
		{
			aniname = name + L"_180";
			if (mPhase == Phase::Phase_1)
			{
				aniname = L"Phase_" + aniname;
			}
			mAnimator->Play(aniname, loop);
		}
		break;
		case ks::eDirection::Right:
		{
			aniname = name + L"_0";
			if (mPhase == Phase::Phase_1)
			{
				aniname = L"Phase_" + aniname;
			}
			mAnimator->Play(aniname, loop);
		}
		break;		
		case ks::eDirection::Down:
		{
			aniname = name + L"_90";
			if (mPhase == Phase::Phase_1)
			{
				aniname = L"Phase_" + aniname;
			}
			mAnimator->Play(aniname, loop);
		}
		break;		
		case ks::eDirection::DownLeft:
		{
			aniname = name + L"_135";
			if (mPhase == Phase::Phase_1)
			{
				aniname = L"Phase_" + aniname;
			}
			mAnimator->Play(aniname, loop);
		}
		break;
		case ks::eDirection::DownRight:
		{
			aniname = name + L"_45";
			if (mPhase == Phase::Phase_1)
			{
				aniname = L"Phase_" + aniname;
			}
			mAnimator->Play(aniname, loop);
		}
		break;

		}
	}


	void Boss_Ent::trapAttack()
	{

		Monster_Trap_Line* trap = object::Instantiate<Monster_Trap_Line>(eLayerType::Monster_Attack);		
		trap->SetMonsterLine(Monster_Line::Ent_Trap);
		Transform* tr = trap->GetComponent<Transform>();


		tr->SetPosition(mPlayer->GetComponent<Transform>()->GetPosition());
		tr->SetScale(Vec3(1.3f, 1.3f, 2.0f));

		Flime_Missile* missile = object::Instantiate<Flime_Missile>(eLayerType::Monster_Attack);
		missile->SetStep(Flime_Step::Step_5);
		Transform* missiletr = missile->GetComponent<Transform>();
		missile->AddComponent<Collider2D>();
		missiletr->SetPosition(mPlayer->GetComponent<Transform>()->GetPosition());
		missiletr->SetScale(Vec3(0.0f, 0.0f, 2.0f));


	}

	void Boss_Ent::poisonAttack(UINT dir, UINT random)
	{

		if(random == 0)
		{
			for (size_t i = 0; i < 1; i++)
			{
				Ent_Poison* poison = object::Instantiate<Ent_Poison>(eLayerType::Monster_Attack);

				poison->SetDegree(((float)dir * 9));
				Transform* tr = poison->GetComponent<Transform>();

				Vec3 Pos = mTransform->GetPosition();
				poison->AddComponent<Collider2D>();

				tr->SetPosition(Vec3(Pos.x, Pos.y - 4.2f, Pos.z));
				tr->SetScale(Vec3(6.5f, 6.5f, 2.0f));
			}
		}
		if (random == 1)
		{
			for (size_t i = 0; i < 1; i++)
			{
				Ent_Poison* poison = object::Instantiate<Ent_Poison>(eLayerType::Monster_Attack);

				poison->SetDegree(180.f - (dir * 9));
				Transform* tr = poison->GetComponent<Transform>();

				Vec3 Pos = mTransform->GetPosition();
				poison->AddComponent<Collider2D>();

				tr->SetPosition(Vec3(Pos.x, Pos.y - 4.2f, Pos.z));
				tr->SetScale(Vec3(6.5f, 6.5f, 2.0f));
			}
		}

	}

	void Boss_Ent::sphereAttack()
	{

		for (UINT i = 0; i < 3; i++)
		{
			Ent_Sphere* sphere = object::Instantiate<Ent_Sphere>(eLayerType::Monster_Attack);
			Transform* tr = sphere->GetComponent<Transform>();
			//sphere->SetDegree(mTargetDir + i * 10);
			sphere->SetTargetPos(Vec3(mSphereMovePos.x - i * 0.25f, mSphereMovePos.y, mSphereMovePos.z));
			sphere->SetSphereType(Sphere_Type::Direction_3);
			Vec3 Pos = mTransform->GetPosition();
			sphere->AddComponent<Collider2D>();
			

			tr->SetPosition(Vec3(Pos.x, Pos.y - 4.2f, Pos.z));
			tr->SetScale(Vec3(10.0f, 10.0f, 2.0f));
		}
		



	}

	void Boss_Ent::targetDir()
	{		
			//mMonsterPos = mTransform->GetPosition();

			mSphereFixPos = mPlayer->GetComponent<Transform>()->GetPosition();
			mSphereMovePos = mSphereFixPos - mMonsterPos;
			mSphereMovePos.Normalize();
	}

	void Boss_Ent::sphereAttack_Phase(UINT dir)
	{

		for (UINT i = 0; i < 8; i++)
		{
			Ent_Sphere* sphere = object::Instantiate<Ent_Sphere>(eLayerType::Monster_Attack);
			Transform* tr = sphere->GetComponent<Transform>();
			sphere->SetDegree((12 * dir) + ((float)i * 45));
			sphere->SetSphereType(Sphere_Type::Direction_8);
			Vec3 Pos = mTransform->GetPosition();
			sphere->AddComponent<Collider2D>();


			tr->SetPosition(Vec3(Pos.x, Pos.y - 4.2f, Pos.z));
			tr->SetScale(Vec3(10.0f, 10.0f, 2.0f));
		}

	}

	void Boss_Ent::earthquakeAttack()
	{

		Monster_Trap_Line* trap = object::Instantiate<Monster_Trap_Line>(eLayerType::Monster_Attack);
		trap->SetMonsterLine(Monster_Line::Ent_Earthquake);
		Transform* tr = trap->GetComponent<Transform>();


		tr->SetPosition(mPlayer->GetComponent<Transform>()->GetPosition());
		tr->SetScale(Vec3(13.0f, 13.0f, 2.0f));

		Flime_Missile* missile = object::Instantiate<Flime_Missile>(eLayerType::Monster_Attack);
		missile->SetStep(Flime_Step::Step_7);
		Transform* missiletr = missile->GetComponent<Transform>();
		missile->AddComponent<Collider2D>();
		missiletr->SetPosition(mPlayer->GetComponent<Transform>()->GetPosition());
		missiletr->SetScale(Vec3(0.0f, 0.0f, 2.0f));


	}

	void Boss_Ent::loadSound()
	{
		std::shared_ptr<AudioClip> attack1= Resources::Load<AudioClip>
			(L"Ent_Attack_Poison", L"..\\Resources\\Sound\\Ent_Attack_Poison.ogg");

		std::shared_ptr<AudioClip> attack2= Resources::Load<AudioClip>
			(L"Ent_Attack_Missile", L"..\\Resources\\Sound\\Ent_Attack_Missile.ogg");

		std::shared_ptr<AudioClip> attack3= Resources::Load<AudioClip>
			(L"Ent_Attack_Earthquake", L"..\\Resources\\Sound\\Ent_Attack_Earthquake.ogg");

		std::shared_ptr<AudioClip> Ent_Death = Resources::Load<AudioClip>
			(L"Boss_Death", L"..\\Resources\\Sound\\Boss_Death.ogg");

		std::shared_ptr<AudioClip> Ent_Clear = Resources::Load<AudioClip>
			(L"Boss_Clear", L"..\\Resources\\Sound\\Boss_Clear.ogg");
	}

	void Boss_Ent::poisonAttackSound()
	{
		std::shared_ptr<AudioClip> booksound = Resources::Find<AudioClip>(L"Ent_Attack_Poison");
		booksound->SetLoop(false);
		booksound->Play();
	}

	void Boss_Ent::missileAttackSound()
	{
		std::shared_ptr<AudioClip> booksound = Resources::Find<AudioClip>(L"Ent_Attack_Missile");
		booksound->SetLoop(false);
		booksound->Play();
	}

	void Boss_Ent::poisonAttackSoundStop()
	{
		std::shared_ptr<AudioClip> booksound = Resources::Find<AudioClip>(L"Ent_Attack_Poison");
		booksound->Stop();
	}

	void Boss_Ent::missileAttackSoundStop()
	{
		std::shared_ptr<AudioClip> booksound = Resources::Find<AudioClip>(L"Ent_Attack_Missile");
		booksound->Stop();
	}

	void Boss_Ent::earthquakeAttackSoundStop()
	{
		std::shared_ptr<AudioClip> booksound = Resources::Find<AudioClip>(L"Ent_Attack_Earthquake");
		booksound->Stop();
	}

	void Boss_Ent::soundClear()
	{
		std::shared_ptr<AudioClip> sound = Resources::Find<AudioClip>(L"Boss_Clear");
		sound->SetLoop(false);
		sound->Play();
	}

	void Boss_Ent::soundDeath()
	{
		std::shared_ptr<AudioClip> sound = Resources::Find<AudioClip>(L"Boss_Death");
		sound->SetLoop(false);
		sound->Play();
	}

	void Boss_Ent::createBox()
	{
		GoldBox* goldbox = object::Instantiate<GoldBox>(eLayerType::Shop_Item);
		goldbox->SetName(L"Platinum_Box");
		goldbox->SetTarget(mPlayer);
		goldbox->SetBoxType(e_BoxType::Platinum);



		Collider2D* collider = goldbox->AddComponent<Collider2D>();
		collider->SetType(eColliderType::Rect);
		collider->SetSize(Vector2(0.14f, 0.09f));


		Transform* tr = goldbox->GetComponent<Transform>();
		Vec3 pos = mTransform->GetPosition();
		pos.y -= 4.0f;
		tr->SetPosition(pos);
		tr->SetScale(Vector3(11.0f, 11.0f, 1.0f));
		goldbox->Initalize();

	}

	void Boss_Ent::earthquakeAttackSound()
	{
		std::shared_ptr<AudioClip> booksound = Resources::Find<AudioClip>(L"Ent_Attack_Earthquake");
		booksound->SetLoop(false);
		booksound->Play();
	}

}