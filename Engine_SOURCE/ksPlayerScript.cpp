#include "ksPlayerScript.h"
#include "ksTransform.h"
#include "ksGameObject.h"
#include "ksObject.h"
#include "ksInput.h"
#include "ksTime.h"
#include "ksAnimator.h"
#include "ksTexture.h"
#include "ksResources.h"
#include "ksScene.h"
#include "ksSceneManager.h"
#include "ksPlayerAttack.h"
#include "ksPlayerEffect.h"
#include "ksPlayerMissile.h"
#include "ksAfterimage.h"
#include "ksFadeEffect.h"
#include "ksCamera.h"
#include "ksForest_Fairy.h"
#include "ksSlime_Green.h"
#include "ksSnake_Green.h"
#include "ksStage1_1Move.h"
#include "ksConstantBuffer.h"
#include "ksMonsterMissile.h"
#include "ksDiary.h"
#include "ksStage1_1.h"
#include "ksInventory.h"
#include "ksPlayerItem.h"
#include "ksCCoin.h"
#include "ksAudioClip.h"
#include "ksAudioListener.h"
#include "ksGoldBox.h"
#include "ksSkil_IceFairy.h"
#include "ksSkilUi.h"
#include "ksSkil_Dark.h"
#include "ksSkil_Barrier.h"
#include "ksSkil_Lighting.h"
#include "ksCollider2D.h"
#include "ksOptionUi.h"
#include "ksFlime_Missile.h"
#include "ksEnt_Poison.h"
#include "ksPlayScene.h"

#include <time.h>



#define MIN_TIME 0.5f
#define MAX_TIME 3.0f

//#define BASIC_SCALE 3.7f								//기본 크기
//#define MAX_SCALE 11.1f									//최대 크기
#define BASIC_SCALE 7.4f								//기본 크기
#define MAX_SCALE 22.2f									//최대 크기
#define INCREMENT (MAX_SCALE - BASIC_SCALE)				//크기 증가량
#define TIME_SCALE (INCREMENT / MAX_TIME)				//초당 크기 증가량  

namespace ks
{
	bool PlayerScript::mbRunning = false;
	bool PlayerScript::mbAttackWalk = false;
	bool PlayerScript::mCarge = false;
	bool PlayerScript::mCargeSound = false;
	bool PlayerScript::mCargeFinsh = false;
	bool PlayerScript::mCargeEffect = false;
	bool PlayerScript::mPlayerStop = false;
	bool PlayerScript::mAttackStop = false;
	bool PlayerScript::m_sbPlayerPower = false;
	bool PlayerScript::m_sbPlayerHit = false;
	UINT PlayerScript::miRef = 0;
	float PlayerScript::mfStaff = 0.f;
	float PlayerScript::m_sfPlayerHit = 0.f;
	float PlayerScript::m_sfPlayerHitTime = 1.f;
	//float PlayerScript::mCheakTime = 0.f;
	//float PlayerScript::mDelayTime = 0.f;
	//float PlayerScript::mTime = 0.f;
	

	PlayerScript::PlayerScript()
		: Script()
		, mAnimator(nullptr)
		, mStatus(nullptr)
		, mTransform(nullptr)
		, mPlayer(nullptr)
		, mState{}
		, mCheak(false)
		, mCheakTime(0.f)
		, mDelayTime(0.f)
		, mTime(0.f)
		, mStaffStnmina(false)
		, mOnceCheak(false)
		, mStaffAttack(false)
		, mInventory(nullptr)
		, m_fPlayerHitTime(0.f)
	{		
		srand((unsigned int)time(nullptr));
		int a = rand();

	}

	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initalize()
	{
		if (GetOwner() != nullptr)
		{
			mTransform = GetOwner()->GetComponent<Transform>();
			mStatus = GetOwner()->GetComponent<Status>();
			mAnimator = GetOwner()->GetComponent<Animator>();
			mPlayer = (Player*)GetOwner();
			mStatus->GetStateInfo();
			GetOwner()->AddComponent<FadeEffect>();

			mAnimator = GetOwner()->GetComponent<Animator>();
			
			mStatus->GetStateInfo();



			mState.situation = eSituation::None;
			mState.direction = eDirection::Up;
			mStatus->SetStateInfo(mState);

			Collider2D* collider = mPlayer->GetComponent<Collider2D>();
	

			loadSound();

		

		}
		//mAnimator* animator = GetOwner()->GetComponent<Animator>();
		//mAnimator->GetStartEvent(L"MoveDown") = std::bind(&PlayerScript::Start, this);
		//mAnimator->GetCompleteEvent(L"Idle") = std::bind(&PlayerScript::Action, this);
		//mAnimator->GetEndEvent(L"Idle") = std::bind(&PlayerScript::End, this);
		//mAnimator->GetEvent(L"Idle", 1) = std::bind(&PlayerScript::End, this);
	}

	void PlayerScript::Update()
	{

		
		//Vector3 rot = tr->GetRotation();
		//rot.z += 10.0f * Time::DeltaTime();
		//tr->SetRotation(rot);
		if(mPlayer->GetPlayerHp() > 0.f)
		{
			if (nullptr != mStatus)
				mState = mStatus->GetStateInfo();

			mTransform->GetPosition();
			mPlayerState = mPlayer->GetPlayerInfo();
			mPlayerState.item;

			if (!(mState.situation == eSituation::Run))
			{
				playerRunSoundStop();
			}
			playerHitColor();

			if (!mPlayerStop)
			{

#pragma region None -> Idle 로 변경, Idle 에서 휴식(Sit) 애니메이션으로 전환

				if (mState.situation == eSituation::Idle || mState.situation == eSituation::None
					|| mState.situation == eSituation::Sit || mState.situation == eSituation::Run)
				{
					if (!mPlayer->StaminaFull() && !mStaffStnminaRecovery)
					{
						float stanima = mPlayer->GetStamina();

						stanima += 10 * Time::DeltaTime();
						mPlayer->RestoreStamina(stanima);
					}
				}



				//행동 끝나고 전부 None 상태로 변경 None 상태에서는 Idle로 변경 후 Default 애니메이션으로 변경
				if (mState.situation == eSituation::None && (mbAttackWalk == false))
				{
					mCheakTime = 0.f;
					mState.situation = eSituation::Idle;
					mStatus->SetStateInfo(mState);
					directionAnimation(L"Idle", false);
				}
				//Idle 상태 3초 이상 지속 되면 Sit 상태로 변경 후 휴식 애니메이션 랜덤으루 재생
				if (mState.situation == eSituation::Idle && (mbAttackWalk == false))
				{

					if (Input::GetKey(eKeyCode::A))
					{
						mState.direction = eDirection::Left;
						mState.situation = eSituation::Run;
						mStatus->SetStateInfo(mState);
						if (mbRunning)
							directionAnimation(L"Run", true);
						else
							directionAnimation(L"Move", true);

					}
					if (Input::GetKey(eKeyCode::S))
					{
						mState.direction = eDirection::Down;
						mState.situation = eSituation::Run;
						mStatus->SetStateInfo(mState);
						if (mbRunning)

							directionAnimation(L"Run", true);
						else
							directionAnimation(L"Move", true);

					}
					if (Input::GetKey(eKeyCode::D))
					{
						mState.direction = eDirection::Right;
						mState.situation = eSituation::Run;
						mStatus->SetStateInfo(mState);
						if (mbRunning)

							directionAnimation(L"Run", true);
						else
							directionAnimation(L"Move", true);

					}
					if (Input::GetKey(eKeyCode::W))
					{
						mState.direction = eDirection::Up;
						mState.situation = eSituation::Run;
						mStatus->SetStateInfo(mState);
						if (mbRunning)

							directionAnimation(L"Run", true);
						else
							directionAnimation(L"Move", true);

					}

					mCheakTime += Time::DeltaTime();
					if (mCheakTime >= 5.0f)
					{
						mState.situation = eSituation::Sit;
						mStatus->SetStateInfo(mState);
						int a = rand() % 2;
						if (a == 1)
							mAnimator->Play(L"Sit_Pray", true);
						if (a == 0)
							mAnimator->Play(L"Sit_Down", false);

						mCheakTime = 0.f;
					}

				}

#pragma endregion



#pragma region 기본 무기 공격 후 딜레이 설정 (None, Sword, Bow, Staff)

				if (mState.situation == eSituation::Attack || mState.situation == eSituation::Continue || mState.situation == eSituation::Connect)
				{
					mCheakTime += Time::DeltaTime();
					mPlayerState = mPlayer->GetPlayerInfo();

					switch (mPlayerState.weapon)
					{
					case ks::eWeapon::None:
					{
						if (mCheakTime >= 0.45f)
						{
							mState.situation = eSituation::None;
							mStatus->SetStateInfo(mState);
							mCheakTime = 0.f;
						}
					}
					break;
					case ks::eWeapon::Sword:
					{

						if (miRef < 5)
						{
							if (mCheakTime >= 0.2f && mCheakTime < 0.25f)
							{
								if (mState.situation == eSituation::Continue)
								{
									mState.situation = eSituation::Connect;
									mStatus->SetStateInfo(mState);
									mCheakTime = 0.f;
								}
							}
							else if (mCheakTime >= 0.35f)
							{
								mState.situation = eSituation::None;
								mStatus->SetStateInfo(mState);
								mCheakTime = 0.f;
								miRef = 0;
							}
						}

						else if (miRef == 5)
						{
							if (mCheakTime >= 0.3f)
							{
								directionAnimation(L"Attack4_Sword", false);
								attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_3, 0.4f);
								mState.situation = eSituation::Continue;
								mStatus->SetStateInfo(mState);
								mCheakTime = 0.f;
								++miRef;
							}
						}

						else if (miRef > 5)
						{
							if (mCheakTime >= 0.4f)
							{
								mState.situation = eSituation::None;
								mStatus->SetStateInfo(mState);
								miRef = 0;
								mCheakTime = 0.f;
							}

						}
					}
					break;
					case ks::eWeapon::Bow:
					{
						if (mState.situation == eSituation::Auto)
						{
							if (mCheakTime >= 0.2f)
							{

								mCheakTime = 0.f;
							}
						}

						else
						{
							if (mCheakTime >= 0.45f)
							{

								mState.situation = eSituation::None;
								mStatus->SetStateInfo(mState);
								mCheakTime = 0.f;
							}
						}
					}
					break;
					case ks::eWeapon::Staff:
					{

						if (mCargeFinsh)
						{
							if (mCheakTime >= 0.8f)
							{
								mState.situation = eSituation::None;
								mStatus->SetStateInfo(mState);
								mCheakTime = 0.f;
								mCargeFinsh = false;
							}
						}
						else
						{
							if (mCheakTime >= 0.45f)
							{
								mState.situation = eSituation::None;
								mStatus->SetStateInfo(mState);
								mCheakTime = 0.f;
							}
						}
					}
					break;

					case ks::eWeapon::Legend_Sword:
					{

						if (miRef < 5)
						{
							if (mCheakTime >= 0.2f && mCheakTime < 0.25f)
							{
								if (mState.situation == eSituation::Continue)
								{
									mState.situation = eSituation::Connect;
									mStatus->SetStateInfo(mState);
									mCheakTime = 0.f;
								}
							}
							else if (mCheakTime >= 0.35f)
							{
								mState.situation = eSituation::None;
								mStatus->SetStateInfo(mState);
								mCheakTime = 0.f;
								miRef = 0;
							}
						}

						else if (miRef == 5)
						{
							if (mCheakTime >= 0.3f)
							{
								directionAnimation(L"Attack4_Sword", false);
								attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_3, 0.4f);
								mState.situation = eSituation::Continue;
								mStatus->SetStateInfo(mState);
								mCheakTime = 0.f;
								++miRef;
							}
						}

						else if (miRef > 5)
						{
							if (mCheakTime >= 0.4f)
							{
								mState.situation = eSituation::None;
								mStatus->SetStateInfo(mState);
								miRef = 0;
								mCheakTime = 0.f;
							}

						}
					}
					break;
					case ks::eWeapon::Legend_Bow:
					{
						if (mState.situation == eSituation::Auto)
						{
							if (mCheakTime >= 0.2f)
							{

								mCheakTime = 0.f;
							}
						}

						else
						{
							if (mCheakTime >= 0.45f)
							{

								mState.situation = eSituation::None;
								mStatus->SetStateInfo(mState);
								mCheakTime = 0.f;
							}
						}
					}
					break;
					case ks::eWeapon::Legend_Staff:
					{

						if (mCargeFinsh)
						{
							if (mCheakTime >= 0.8f)
							{
								mState.situation = eSituation::None;
								mStatus->SetStateInfo(mState);
								mCheakTime = 0.f;
								mCargeFinsh = false;
							}
						}
						else
						{
							if (mCheakTime >= 0.45f)
							{
								mState.situation = eSituation::None;
								mStatus->SetStateInfo(mState);
								mCheakTime = 0.f;
							}
						}
					}
					break;

					}

				}

#pragma endregion



#pragma region 플레이어 스킬 후 딜레이 설정 (Evade, )



				if (mState.situation == eSituation::Skil)
				{
					mCheakTime += Time::DeltaTime();

					mPlayerState = mPlayer->GetPlayerInfo();

					switch (mPlayerState.skil)
					{
					case ks::eSkil::Evade:
					{
						if (mCheakTime > 0.5f)
						{
							mPlayerState.skil = eSkil::None;
							mPlayer->SetPlayerInfo(mPlayerState);
							mState.situation = eSituation::None;
							mStatus->SetStateInfo(mState);
							mAnimator->ClearSpriteSheet();
							mCheakTime = 0.f;
						}
						else
						{
							Vector3 pos = mTransform->GetPosition();
							mPrevPos = mTransform->GetPosition();
							switch (mState.direction)
							{
							case ks::eDirection::Left:
								pos.x -= 6.0f * Time::DeltaTime();
								break;
							case ks::eDirection::Right:
								pos.x += 6.0f * Time::DeltaTime();
								break;
							case ks::eDirection::Up:
								pos.y += 6.0f * Time::DeltaTime();
								break;
							case ks::eDirection::Down:
								pos.y -= 6.0f * Time::DeltaTime();
								break;
							case ks::eDirection::UpLeft:
								pos.x -= 4.0f * Time::DeltaTime();
								pos.y += 4.0f * Time::DeltaTime();
								break;
							case ks::eDirection::UpRight:
								pos.x += 4.0f * Time::DeltaTime();
								pos.y += 4.0f * Time::DeltaTime();
								break;
							case ks::eDirection::DownLeft:
								pos.x -= 4.0f * Time::DeltaTime();
								pos.y -= 4.0f * Time::DeltaTime();
								break;
							case ks::eDirection::DownRight:
								pos.x += 4.0f * Time::DeltaTime();
								pos.y -= 4.0f * Time::DeltaTime();
								break;
							}
							mTransform->SetPosition(pos);
							if (mCheakTime < 0.45f)
							{
								mDelayTime += Time::DeltaTime();
								if (mDelayTime > 0.05f)
								{
									mAfterimage = object::Instantiate<Afterimage>(eLayerType::Player_Afterimage);
									mAfterimage->SetTarget(mPlayer);
									mAfterimage->PlayAfterimage(mAnimator->GetSpriteSheet(), mPrevPos);
									mDelayTime = 0.f;
								}

							}

						}

					}
					break;
					case ks::eSkil::Magic:
					{
						m_fSkilTime += Time::DeltaTime();
						if (mPlayer->GetSkilUiTarget()->GetActiveSkil() == eItem::Lighting)
						{
							if (m_bLightingOneCheak)
							{
								Collider2D* collider = mPlayer->GetComponent<Collider2D>();
								collider->SetSize(Vector2(1.2f, 0.8f));
								m_bLightingOneCheak = true;
							}
							Vec3 pos = mTransform->GetPosition();
							pos += m_vLightingPos * 9.5f * Time::DeltaTime();;

							mTransform->SetPosition(pos);

							if (m_fSkilTime > 0.6f)
							{

								targetLighting();
								Collider2D* collider = mPlayer->GetComponent<Collider2D>();
								collider->SetSize(Vector2(0.08f, 0.12f));
								m_bLightingAttack = false;
								mPlayerState.skil = eSkil::None;
								mPlayer->SetPlayerInfo(mPlayerState);
								mState.situation = eSituation::None;
								mStatus->SetStateInfo(mState);
								m_vectorLightingTargetPos.clear();
								m_fSkilTime = 0.f;
							}
						}
						else
						{

							if (m_fSkilTime > 0.5f)
							{
								mPlayerState.skil = eSkil::None;
								mPlayer->SetPlayerInfo(mPlayerState);
								mState.situation = eSituation::None;
								mStatus->SetStateInfo(mState);
								m_fSkilTime = 0.f;
							}
						}
					}
					break;
					}
				}

#pragma endregion









				if (Input::GetKeyState(eKeyCode::Q) == eKeyState::PRESSED)
				{


				}

				if (Input::GetKeyState(eKeyCode::R) == eKeyState::PRESSED)
				{


				}


#pragma	region 이동 로직 ASDW Idle, Run, Sit 상태에서만 이동 반응 + 무기 활일떄도 이동 가능 + 무기 스태프 충전 중일때도 가능


				if (Input::GetKey(eKeyCode::D))
				{
					if (mState.situation == eSituation::Idle || mState.situation == eSituation::Run
						|| mState.situation == eSituation::Sit || mbAttackWalk == true)
					{
						Vector3 pos = mTransform->GetPosition();
						if (mbAttackWalk && mPlayerState.weapon == eWeapon::Bow || mbAttackWalk && mPlayerState.weapon == eWeapon::Legend_Bow)
						{
							if (mState.direction == eDirection::UpRight || mState.direction == eDirection::DownRight)
								pos.x += 2.5f * 0.75f * Time::DeltaTime();
							else
								pos.x += 2.5f * Time::DeltaTime();

							mTransform->SetPosition(pos);
						}
						else
						{
							if (mState.direction == eDirection::UpRight || mState.direction == eDirection::DownRight)
							{
								if (mbRunning)
									pos.x += 5.5f * 0.75f * Time::DeltaTime();
								else
									pos.x += 2.5f * 0.75f * Time::DeltaTime();
							}
							else if (mState.direction == eDirection::Right)
							{
								if (mbRunning)
									pos.x += 5.5f * Time::DeltaTime();
								else
									pos.x += 2.5f * Time::DeltaTime();
							}
							mTransform->SetPosition(pos);
						}
					}
					//mCheakTime = 0.f;
				}



				if (Input::GetKey(eKeyCode::A))
				{
					if (mState.situation == eSituation::Idle || mState.situation == eSituation::Run
						|| mState.situation == eSituation::Sit || mbAttackWalk == true)
					{
						Vector3 pos = mTransform->GetPosition();
						if (mbAttackWalk && mPlayerState.weapon == eWeapon::Bow || mbAttackWalk && mPlayerState.weapon == eWeapon::Legend_Bow)
						{
							if (mState.direction == eDirection::UpLeft || mState.direction == eDirection::DownLeft)
								pos.x -= 2.5f * 0.75f * Time::DeltaTime();
							else
								pos.x -= 2.5f * Time::DeltaTime();

							mTransform->SetPosition(pos);
						}
						else
						{
							if (mState.direction == eDirection::UpLeft || mState.direction == eDirection::DownLeft)
							{
								if (mbRunning)
									pos.x -= 5.5f * 0.75f * Time::DeltaTime();
								else
									pos.x -= 2.5f * 0.75f * Time::DeltaTime();
							}
							else if (mState.direction == eDirection::Left)
							{
								if (mbRunning)
									pos.x -= 5.5f * Time::DeltaTime();
								else
									pos.x -= 2.5f * Time::DeltaTime();
							}
							mTransform->SetPosition(pos);
						}
					}
					//mCheakTime = 0.f;
				}


				if (Input::GetKey(eKeyCode::W))
				{
					if (mState.situation == eSituation::Idle || mState.situation == eSituation::Run
						|| mState.situation == eSituation::Sit || mbAttackWalk == true)
					{
						Vector3 pos = mTransform->GetPosition();
						if (mbAttackWalk && mPlayerState.weapon == eWeapon::Bow || mbAttackWalk && mPlayerState.weapon == eWeapon::Legend_Bow)
						{
							if (mState.direction == eDirection::UpLeft || mState.direction == eDirection::UpRight)
								pos.y += 2.5f * 0.75f * Time::DeltaTime();
							else
								pos.y += 2.5f * Time::DeltaTime();

							mTransform->SetPosition(pos);
						}
						else
						{
							if (mState.direction == eDirection::UpLeft || mState.direction == eDirection::UpRight)
							{
								if (mbRunning)
									pos.y += 5.5f * 0.75f * Time::DeltaTime();
								else
									pos.y += 2.5f * 0.75f * Time::DeltaTime();
							}
							else if (mState.direction == eDirection::Up)
							{
								if (mbRunning)
									pos.y += 5.5f * Time::DeltaTime();
								else
									pos.y += 2.5f * Time::DeltaTime();
							}
							mTransform->SetPosition(pos);
						}
					}
					//mCheakTime = 0.f;
				}


				if (Input::GetKey(eKeyCode::S))
				{
					if (mState.situation == eSituation::Idle || mState.situation == eSituation::Run
						|| mState.situation == eSituation::Sit || mbAttackWalk == true)
					{
						Vector3 pos = mTransform->GetPosition();
						if (mbAttackWalk && mPlayerState.weapon == eWeapon::Bow || mbAttackWalk && mPlayerState.weapon == eWeapon::Legend_Bow)
						{
							if (mState.direction == eDirection::DownLeft || mState.direction == eDirection::DownRight)
								pos.y -= 2.5f * 0.75f * Time::DeltaTime();
							else
								pos.y -= 2.5f * Time::DeltaTime();

							mTransform->SetPosition(pos);
						}
						else
						{
							if (mState.direction == eDirection::DownLeft || mState.direction == eDirection::DownRight)
							{
								if (mbRunning)
									pos.y -= 5.5f * 0.75f * Time::DeltaTime();
								else
									pos.y -= 2.5f * 0.75f * Time::DeltaTime();
							}
							else if (mState.direction == eDirection::Down)
							{
								if (mbRunning)
									pos.y -= 5.5f * Time::DeltaTime();
								else
									pos.y -= 2.5f * Time::DeltaTime();
							}
							mTransform->SetPosition(pos);
						}
					}
					//mCheakTime = 0.f;
				}

#pragma endregion


#pragma region 키 눌렀을때 ( (None, Idle, Sit), Run 상태에서만 반응 )
				//Animation Start
				if (Input::GetKeyDown(eKeyCode::D))
				{
					if (mState.situation == eSituation::None || mState.situation == eSituation::Idle
						|| mState.situation == eSituation::Sit)
					{

						mState.direction = eDirection::Right;
						mState.situation = eSituation::Run;
						if (mbRunning)
						{
							playerRunSound();
							directionAnimation(L"Run", true);
						}
						else
						{
							playerRunSound();
							directionAnimation(L"Move", true);
						}

					}
					else if (mState.situation == eSituation::Run)
					{
						switch (mState.direction)
						{

						case ks::eDirection::Left:
						{
							mState.direction = eDirection::BothX;
							mAnimator->Play(L"Idle_Left");
							playerRunSoundStop();
						}
						break;
						case ks::eDirection::Up:
						{
							mState.direction = eDirection::UpRight;
							if (mbRunning)
							{
								directionAnimation(L"Run", true);
							}
							else
							{
								directionAnimation(L"Move", true);
							}

						}
						break;
						case ks::eDirection::Down:
						{
							mState.direction = eDirection::DownRight;
							if (mbRunning)
							{
								directionAnimation(L"Run", true);
							}
							else
							{
								directionAnimation(L"Move", true);
							}
						}
						break;

						case ks::eDirection::BothY:
						{
							mState.direction = eDirection::Right;
							mState.situation = eSituation::Run;

							if (mbRunning)
							{
								playerRunSound();
								directionAnimation(L"Run", true);
							}
							else
							{
								playerRunSound();
								directionAnimation(L"Move", true);
							}
						}
						break;
						}
					}


					mStatus->SetStateInfo(mState);

				}
				if (Input::GetKeyDown(eKeyCode::A))
				{
					if (mState.situation == eSituation::None || mState.situation == eSituation::Idle
						|| mState.situation == eSituation::Sit)
					{
						mState.direction = eDirection::Left;
						mState.situation = eSituation::Run;

						if (mbRunning)
						{
							playerRunSound();
							directionAnimation(L"Run", true);
						}
						else
						{
							playerRunSound();
							directionAnimation(L"Move", true);
						}
					}
					else if (mState.situation == eSituation::Run)
					{
						switch (mState.direction)
						{
						case ks::eDirection::Right:
						{
							playerRunSoundStop();
							mState.direction = eDirection::BothX;
							mAnimator->Play(L"Idle_Right");
						}

						break;
						case ks::eDirection::Up:
						{
							mState.direction = eDirection::UpLeft;
							if (mbRunning)
								directionAnimation(L"Run", true);
							else
								directionAnimation(L"Move", true);
						}

						break;
						case ks::eDirection::Down:
						{
							mState.direction = eDirection::DownLeft;
							if (mbRunning)
								directionAnimation(L"Run", true);
							else
								directionAnimation(L"Move", true);
						}
						break;
						case ks::eDirection::BothY:
						{
							mState.direction = eDirection::Left;
							mState.situation = eSituation::Run;
							if (mbRunning)
							{
								playerRunSound();
								directionAnimation(L"Run", true);
							}
							else
							{
								playerRunSound();
								directionAnimation(L"Move", true);
							}
						}
						break;
						}
					}
					mStatus->SetStateInfo(mState);
				}

				if (Input::GetKeyDown(eKeyCode::S))
				{

					if (mState.situation == eSituation::None || mState.situation == eSituation::Idle
						|| mState.situation == eSituation::Sit)
					{
						mState.direction = eDirection::Down;
						mState.situation = eSituation::Run;

						if (mbRunning)
						{
							playerRunSound();
							directionAnimation(L"Run", true);
						}
						else
						{
							playerRunSound();
							directionAnimation(L"Move", true);
						}
					}
					else if (mState.situation == eSituation::Run)
					{
						switch (mState.direction)
						{
						case ks::eDirection::Right:
						{
							mState.direction = eDirection::DownRight;
							if (mbRunning)
								directionAnimation(L"Run", true);
							else
								directionAnimation(L"Move", true);
						}
						break;
						case ks::eDirection::Left:
						{
							mState.direction = eDirection::DownLeft;

							if (mbRunning)
								directionAnimation(L"Run", true);
							else
								directionAnimation(L"Move", true);
						}
						break;
						case ks::eDirection::Up:
						{
							playerRunSoundStop();
							mState.direction = eDirection::BothY;
							mAnimator->Play(L"Idle_Up");
						}
						break;
						case ks::eDirection::BothX:
						{
							mState.direction = eDirection::Down;
							mState.situation = eSituation::Run;

							if (mbRunning)
							{
								playerRunSound();
								directionAnimation(L"Run", true);
							}
							else
							{
								playerRunSound();
								directionAnimation(L"Move", true);
							}
						}
						break;
						}
					}
					mStatus->SetStateInfo(mState);
				}


				if (Input::GetKeyDown(eKeyCode::W))
				{

					if (mState.situation == eSituation::None || mState.situation == eSituation::Idle
						|| mState.situation == eSituation::Sit)
					{
						mState.direction = eDirection::Up;
						mState.situation = eSituation::Run;


						if (mbRunning)
						{
							playerRunSound();
							directionAnimation(L"Run", true);
						}
						else
						{
							playerRunSound();
							directionAnimation(L"Move", true);
						}
					}
					else if (mState.situation == eSituation::Run)
					{
						switch (mState.direction)
						{
						case ks::eDirection::Right:
						{
							mState.direction = eDirection::UpRight;


							if (mbRunning)
								directionAnimation(L"Run", true);
							else
								directionAnimation(L"Move", true);
						}
						break;
						case ks::eDirection::Left:
						{
							mState.direction = eDirection::UpLeft;
							if (mbRunning)
								directionAnimation(L"Run", true);
							else
								directionAnimation(L"Move", true);
						}
						break;
						case ks::eDirection::Down:
						{
							playerRunSoundStop();
							mState.direction = eDirection::BothY;
							mAnimator->Play(L"Idle_Down");
						}
						break;

						case ks::eDirection::BothX:
						{
							mState.direction = eDirection::Up;
							mState.situation = eSituation::Run;


							if (mbRunning)
							{
								playerRunSound();
								directionAnimation(L"Run", true);
							}
							else
							{
								playerRunSound();
								directionAnimation(L"Move", true);
							}
						}
						break;
						}
					}
					mStatus->SetStateInfo(mState);
				}
#pragma endregion



#pragma region 키 눌렀다 올라올때  (None, Idle, Sit, Run 상태에서만 반응)
				if (Input::GetKeyUp(eKeyCode::D))
				{
					if (mState.situation == eSituation::None || mState.situation == eSituation::Idle
						|| mState.situation == eSituation::Sit || mState.situation == eSituation::Run)
					{
						switch (mState.direction)
						{
						case ks::eDirection::Right:
							mState.situation = eSituation::None;
							mStatus->SetStateInfo(mState);
							playerRunSoundStop();
							break;
						case ks::eDirection::UpRight:
						{
							mState.direction = eDirection::Up;
							mStatus->SetStateInfo(mState);
							if (mbRunning)
							{

								directionAnimation(L"Run", true);
							}
							else
							{

								directionAnimation(L"Move", true);
							}
						}
						break;
						case ks::eDirection::DownRight:
						{
							mState.direction = eDirection::Down;
							mStatus->SetStateInfo(mState);
							if (mbRunning)
							{

								directionAnimation(L"Run", true);
							}
							else
							{

								directionAnimation(L"Move", true);
							}
						}
						break;
						case ks::eDirection::BothX:
						{
							mState.direction = eDirection::Left;
							mStatus->SetStateInfo(mState);
							if (mbRunning)
							{
								playerRunSound();
								directionAnimation(L"Run", true);
							}
							else
							{
								playerRunSound();
								directionAnimation(L"Move", true);
							}
						}
						break;
						case ks::eDirection::BothY:
						{
							mState.direction = eDirection::Right;
							mStatus->SetStateInfo(mState);
							playerRunSoundStop();
							mAnimator->Play(L"Idle_Right");
						}
						break;
						}
					}
				}

				if (Input::GetKeyUp(eKeyCode::A))
				{

					if (mState.situation == eSituation::None || mState.situation == eSituation::Idle
						|| mState.situation == eSituation::Sit || mState.situation == eSituation::Run)
					{
						switch (mState.direction)
						{
						case ks::eDirection::Left:
							mState.situation = eSituation::None;
							mStatus->SetStateInfo(mState);
							playerRunSoundStop();
							break;
						case ks::eDirection::UpLeft:
						{
							mState.direction = eDirection::Up;
							mStatus->SetStateInfo(mState);
							if (mbRunning)
							{

								directionAnimation(L"Run", true);
							}
							else
							{

								directionAnimation(L"Move", true);
							}
						}
						break;
						case ks::eDirection::DownLeft:
						{
							mState.direction = eDirection::Down;
							mStatus->SetStateInfo(mState);
							if (mbRunning)
							{

								directionAnimation(L"Run", true);
							}
							else
							{

								directionAnimation(L"Move", true);
							}
						}
						break;
						case ks::eDirection::BothX:
						{
							mState.direction = eDirection::Right;
							mStatus->SetStateInfo(mState);
							if (mbRunning)
							{
								playerRunSound();
								directionAnimation(L"Run", true);
							}
							else
							{
								playerRunSound();
								directionAnimation(L"Move", true);
							}
						}
						break;
						case ks::eDirection::BothY:
						{
							mState.direction = eDirection::Left;
							mStatus->SetStateInfo(mState);
							playerRunSoundStop();
							mAnimator->Play(L"Idle_Left");
						}
						break;
						}
						mStatus->SetStateInfo(mState);
					}
				}




				if (Input::GetKeyUp(eKeyCode::S))
				{

					if (mState.situation == eSituation::None || mState.situation == eSituation::Idle
						|| mState.situation == eSituation::Sit || mState.situation == eSituation::Run)
					{
						switch (mState.direction)
						{
						case ks::eDirection::Down:
							mState.situation = eSituation::None;
							mStatus->SetStateInfo(mState);
							playerRunSoundStop();
							break;
						case ks::eDirection::DownLeft:
						{
							mState.direction = eDirection::Left;
							mStatus->SetStateInfo(mState);
							if (mbRunning)
							{

								directionAnimation(L"Run", true);
							}
							else
							{

								directionAnimation(L"Move", true);
							}
						}
						break;
						case ks::eDirection::DownRight:
						{
							mState.direction = eDirection::Right;
							mStatus->SetStateInfo(mState);
							if (mbRunning)
							{

								directionAnimation(L"Run", true);
							}
							else
							{

								directionAnimation(L"Move", true);
							}
						}
						break;
						case ks::eDirection::BothY:
						{
							mState.direction = eDirection::Up;
							mStatus->SetStateInfo(mState);
							if (mbRunning)
							{
								playerRunSound();
								directionAnimation(L"Run", true);
							}
							else
							{
								playerRunSound();
								directionAnimation(L"Move", true);
							}
						}
						break;
						case ks::eDirection::BothX:
						{
							mState.direction = eDirection::Down;
							mStatus->SetStateInfo(mState);
							playerRunSoundStop();
							mAnimator->Play(L"Idle_Down");
						}
						break;
						}
						mStatus->SetStateInfo(mState);
					}
				}



				if (Input::GetKeyUp(eKeyCode::W))
				{
					if (mState.situation == eSituation::None || mState.situation == eSituation::Idle
						|| mState.situation == eSituation::Sit || mState.situation == eSituation::Run)
					{
						switch (mState.direction)
						{
						case ks::eDirection::Up:
							mState.situation = eSituation::None;
							mStatus->SetStateInfo(mState);
							playerRunSoundStop();
							break;
						case ks::eDirection::UpLeft:
						{
							mState.direction = eDirection::Left;
							mStatus->SetStateInfo(mState);
							if (mbRunning)
							{

								directionAnimation(L"Run", true);
							}
							else
							{

								directionAnimation(L"Move", true);
							}
						}
						break;
						case ks::eDirection::UpRight:
						{
							mState.direction = eDirection::Right;
							mStatus->SetStateInfo(mState);
							if (mbRunning)
							{

								directionAnimation(L"Run", true);
							}
							else
							{

								directionAnimation(L"Move", true);
							}
						}
						break;
						case ks::eDirection::BothY:
						{
							mState.direction = eDirection::Down;
							mStatus->SetStateInfo(mState);
							if (mbRunning)
							{
								playerRunSound();
								directionAnimation(L"Run", true);
							}
							else
							{
								playerRunSound();
								directionAnimation(L"Move", true);
							}
						}
						break;
						case ks::eDirection::BothX:
						{
							mState.direction = eDirection::Up;
							mStatus->SetStateInfo(mState);
							playerRunSoundStop();
							mAnimator->Play(L"Idle_Up");
						}
						break;
						}
						mStatus->SetStateInfo(mState);
					}
				}


#pragma endregion



				if (Input::GetKeyDown(eKeyCode::SPACE))
				{
					if (mState.situation == eSituation::Skil || mState.situation == eSituation::Attack)
						return;
					if (!mPlayer->Usestamina(10.f, this))
						return;
					PlayerAttackSound();
					mPlayerState.skil = eSkil::Evade;
					mPlayer->SetPlayerInfo(mPlayerState);
					mState.situation = eSituation::Skil;
					mStatus->SetStateInfo(mState);
					directionAnimation(L"Evade", false, true);
					mCheakTime = 0.f;
					miRef = 0;


				}

				//공격 키
				if (Input::GetKeyDown(eKeyCode::LBTN))
				{
					if (mState.situation == eSituation::Attack || mState.situation == eSituation::Skil
						|| mState.situation == eSituation::Continue || mAttackStop)
						return;




					switch (mPlayerState.weapon)
					{
					case ks::eWeapon::None:
					{
						if (!mPlayer->Usestamina(10.f, this))
							return;
					}
					break;
					case ks::eWeapon::Sword:
					{
						if (!mPlayer->Usestamina(7.f, this))
							return;
					}
					break;
					case ks::eWeapon::Bow:
					{
						if (!mPlayer->Usestamina(5.f, this))
							return;
					}

					break;
					case ks::eWeapon::Staff:
					{
						if (!mPlayer->Usestamina(10.f, this))
							return;
					}
					break;
					case ks::eWeapon::Legend_Sword:
					{
						if (!mPlayer->Usestamina(7.f, this))
							return;
					}
					break;
					case ks::eWeapon::Legend_Bow:
					{
						if (!mPlayer->Usestamina(5.f, this))
							return;
					}

					break;
					case ks::eWeapon::Legend_Staff:
					{
						if (!mPlayer->Usestamina(10.f, this))
							return;
					}
					break;
					}


					mPlayerState = mPlayer->GetPlayerInfo();
					mPlayer->SetPlayerInfo(mPlayerState);


#pragma region 기본 무기 공격 애니메이션
					switch (mPlayerState.weapon)
					{
					case ks::eWeapon::None:
					{
						PlayerAttackSound();
						angleDirection();
						mState.situation = eSituation::Attack;
						directionAnimation(L"Attack_None", false);
						attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_1, 0.45f);
					}
					break;
					case ks::eWeapon::Sword:
					{
						angleDirection();
						mState.situation = eSituation::Attack;
						if (miRef == 0)
						{
							PlayerAttackSound();
							directionAnimation(L"Attack1_Sword", false);
							attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_1, 0.2f);
						}
						else if (miRef == 1)
						{
							PlayerAttackSound();
							directionAnimation(L"Attack2_Sword", false);
							attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_2, 0.2f);
						}
						else if (miRef == 2)
						{
							PlayerAttackSound();
							directionAnimation(L"Attack1_Sword", false);
							attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_1, 0.2f);
						}
						else if (miRef == 3)
						{
							PlayerAttackSound();
							directionAnimation(L"Attack2_Sword", false);
							attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_2, 0.2f);
						}
						else if (miRef == 4)
						{
							PlayerAttackSound();
							directionAnimation(L"Attack3_Sword", false);
						}

						if (miRef >= 5)
							return;
						++miRef;
					}
					break;
					case ks::eWeapon::Bow:
					{
						PlayerAttackSound();
						angleDirection();
						mState.situation = eSituation::Attack;
						directionAnimation(L"Attack_Stand_Bow", false);
						attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_1, 0.2f);

					}

					break;
					case ks::eWeapon::Staff:
					{

						mbAttackWalk = true;
						mStaffAttack = true;
					}
					break;

					case ks::eWeapon::Legend_Sword:
					{
						angleDirection();
						mState.situation = eSituation::Attack;
						if (miRef == 0)
						{
							PlayerAttackSound();
							directionAnimation(L"Attack1_Sword", false);
							attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_1, 0.2f);
						}
						else if (miRef == 1)
						{
							PlayerAttackSound();
							directionAnimation(L"Attack2_Sword", false);
							attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_2, 0.2f);
						}
						else if (miRef == 2)
						{
							PlayerAttackSound();
							directionAnimation(L"Attack1_Sword", false);
							attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_1, 0.2f);
						}
						else if (miRef == 3)
						{
							PlayerAttackSound();
							directionAnimation(L"Attack2_Sword", false);
							attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_2, 0.2f);
						}
						else if (miRef == 4)
						{
							PlayerAttackSound();
							directionAnimation(L"Attack3_Sword", false);
						}

						if (miRef >= 5)
							return;
						++miRef;
					}
					break;
					case ks::eWeapon::Legend_Staff:
					{
						mbAttackWalk = true;
						mStaffAttack = true;
					}
					break;
					case ks::eWeapon::Legend_Bow:
					{
						PlayerAttackSound();
						angleDirection();
						mState.situation = eSituation::Attack;
						directionAnimation(L"Attack_Stand_Bow", false);
						attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_1, 0.3f);
					}
					break;

					}

					mStatus->SetStateInfo(mState);
					mCheakTime = 0.f;

#pragma endregion 

				}


				if (Input::GetKey(eKeyCode::LBTN))
				{
					if (mAttackStop)
						return;
#pragma region 자동 공격 애니메이션
					switch (mPlayerState.weapon)
					{
					case ks::eWeapon::None:
						break;
					case ks::eWeapon::Sword:
					{
						mCheakTime += Time::DeltaTime();

						if (mState.situation == eSituation::Attack || mState.situation == eSituation::Auto)
						{
							if (mCheakTime > 0.26 && mCheakTime < 0.31)
							{
								mState.situation = eSituation::Auto;
								mStatus->SetStateInfo(mState);

								if (miRef > 6)
								{
									mState.situation = eSituation::Auto;
									mStatus->SetStateInfo(mState);
									miRef = 0;
									mCheakTime = 0.f;
									return;
								}
								angleDirection();

								if (miRef == 0)
								{
									if (!mPlayer->Usestamina(7.f, this))
										return;
									PlayerAttackSound();
									directionAnimation(L"Attack1_Sword", false);
									attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_1, 0.2f);
								}
								else if (miRef == 1)
								{
									if (!mPlayer->Usestamina(7.f, this))
										return;
									PlayerAttackSound();
									directionAnimation(L"Attack2_Sword", false);
									attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_2, 0.2f);
								}
								else if (miRef == 2)
								{
									if (!mPlayer->Usestamina(7.f, this))
										return;
									PlayerAttackSound();
									directionAnimation(L"Attack1_Sword", false);
									attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_1, 0.2f);
								}
								else if (miRef == 3)
								{
									if (!mPlayer->Usestamina(7.f, this))
										return;
									PlayerAttackSound();
									directionAnimation(L"Attack2_Sword", false);
									attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_2, 0.2f);
								}
								else if (miRef == 4)
								{
									if (!mPlayer->Usestamina(7.f, this))
										return;
									PlayerAttackSound();
									directionAnimation(L"Attack3_Sword", false);

								}
								else if (miRef == 5)
								{
									if (!mPlayer->Usestamina(7.f, this))
										return;
									PlayerAttackSound();
									directionAnimation(L"Attack4_Sword", false);
									attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_3, 0.2f);
								}

								mCheakTime = 0.f;
								++miRef;
							}
						}
					}
					break;
					case ks::eWeapon::Bow:
					{

						angleDirection();
						mCheakTime += Time::DeltaTime();

						if (mState.situation == eSituation::Attack || mState.situation == eSituation::Auto)
						{

							if (mState.situation == eSituation::Attack)
							{
								if (mCheakTime > 0.35 && mCheakTime < 0.4)
								{
									if (!mPlayer->Usestamina(5.f, this))
										return;
									PlayerAttackSound();
									mState.situation = eSituation::Auto;
									mStatus->SetStateInfo(mState);
									mbAttackWalk = true;
									directionAnimation(L"Attack_Walk_Bow", true);
									attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_1, 0.2f);
									mCheakTime = 0.f;

								}
							}

							else if (mState.situation == eSituation::Auto)
							{
								if (mCheakTime > 0.25 && mCheakTime < 0.3)
								{
									if (!mPlayer->Usestamina(5.f, this))
										return;
									PlayerAttackSound();
									mState.situation = eSituation::Auto;
									mStatus->SetStateInfo(mState);
									mbAttackWalk = true;
									directionAnimation(L"Attack_Walk_Bow", true);
									attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_1, 0.2f);
									mCheakTime = 0.f;
								}

							}

						}
					}
					break;
					case ks::eWeapon::Staff:
					{

						if (mbAttackWalk && mCargeFinsh == false)
						{
							mCheakTime += Time::DeltaTime();
							if (mStaffStnmina)
							{
								if (!mPlayer->Usestamina(0.01f, this))
									return;
							}
							if (mCheakTime >= MIN_TIME && mCarge == false)
							{
								staffChargeSound();
								mStaffStnmina = true;
								mStaffStnminaRecovery = true;
								PlayerEffect* mAttack = object::Instantiate<PlayerEffect>(eLayerType::Player_Effect);
								mPlayerState.skil = eSkil::Attack;
								mPlayerState.progress = eProgress::Step_8;
								mPlayer->SetPlayerInfo(mPlayerState);
								mAttack->SetTarget(mPlayer);
								mAttack->SetPlayer(mPlayerState);
								mAttack->GetComponent<Transform>()->SetPosition(mTransform->GetPosition());
								mCarge = true;
							}
							if (mCheakTime >= MIN_TIME * 3.5f && mCargeSound == false)
							{
								staffChargeSound();
								mCargeSound = true;
							}

							if (mCheakTime >= MAX_TIME && mCargeEffect == false)
							{
								staffChargeFinishSound();
								effectDeath(eLayerType::Player_Effect);
								attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Start, 0.6f);
								mCargeEffect = true;
								mStaffStnmina = false;
							}
						}

					}
					break;
					case ks::eWeapon::Legend_Staff:
					{

						if (mbAttackWalk && mCargeFinsh == false)
						{
							mCheakTime += Time::DeltaTime();
							if (mStaffStnmina)
							{
								if (!mPlayer->Usestamina(0.01f, this))
									return;
							}
							if (mCheakTime >= MIN_TIME && mCarge == false)
							{
								staffChargeSound();
								mStaffStnmina = true;
								mStaffStnminaRecovery = true;
								PlayerEffect* mAttack = object::Instantiate<PlayerEffect>(eLayerType::Player_Effect);
								mPlayerState.skil = eSkil::Attack;
								mPlayerState.progress = eProgress::Step_8;
								mPlayer->SetPlayerInfo(mPlayerState);
								mAttack->SetTarget(mPlayer);
								mAttack->SetPlayer(mPlayerState);
								mAttack->GetComponent<Transform>()->SetPosition(mTransform->GetPosition());
								mCarge = true;
							}

							if (mCheakTime >= MIN_TIME * 3.5f && mCargeSound == false)
							{
								staffChargeSound();
								mCargeSound = true;
							}

							if (mCheakTime >= MAX_TIME && mCargeEffect == false)
							{
								staffChargeFinishSound();
								effectDeath(eLayerType::Player_Effect);
								attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Start, 0.6f);
								mCargeEffect = true;
								mStaffStnmina = false;
							}
						}

					}
					break;
					case ks::eWeapon::Legend_Bow:
					{
						angleDirection();
						mCheakTime += Time::DeltaTime();

						if (mState.situation == eSituation::Attack || mState.situation == eSituation::Auto)
						{

							if (mState.situation == eSituation::Attack)
							{
								if (mCheakTime > 0.35 && mCheakTime < 0.4)
								{
									if (!mPlayer->Usestamina(5.f, this))
										return;
									PlayerAttackSound();
									mState.situation = eSituation::Auto;
									mStatus->SetStateInfo(mState);
									mbAttackWalk = true;
									directionAnimation(L"Attack_Walk_Bow", true);
									attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_1, 0.3f);
									mCheakTime = 0.f;

								}
							}

							else if (mState.situation == eSituation::Auto)
							{
								if (mCheakTime > 0.25 && mCheakTime < 0.3)
								{
									if (!mPlayer->Usestamina(5.f, this))
										return;
									PlayerAttackSound();
									mState.situation = eSituation::Auto;
									mStatus->SetStateInfo(mState);
									mbAttackWalk = true;
									directionAnimation(L"Attack_Walk_Bow", true);
									attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_1, 0.3f);
									mCheakTime = 0.f;
								}

							}

						}
					}
					break;
					case ks::eWeapon::Legend_Sword:
					{
						mCheakTime += Time::DeltaTime();

						if (mState.situation == eSituation::Attack || mState.situation == eSituation::Auto)
						{
							if (mCheakTime > 0.26 && mCheakTime < 0.31)
							{
								mState.situation = eSituation::Auto;
								mStatus->SetStateInfo(mState);

								if (miRef > 6)
								{
									mState.situation = eSituation::Auto;
									mStatus->SetStateInfo(mState);
									miRef = 0;
									mCheakTime = 0.f;
									return;
								}
								angleDirection();

								if (miRef == 0)
								{
									if (!mPlayer->Usestamina(7.f, this))
										return;
									PlayerAttackSound();
									directionAnimation(L"Attack1_Sword", false);
									attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_1, 0.2f);
								}
								else if (miRef == 1)
								{
									if (!mPlayer->Usestamina(7.f, this))
										return;
									PlayerAttackSound();
									directionAnimation(L"Attack2_Sword", false);
									attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_2, 0.2f);
								}
								else if (miRef == 2)
								{
									if (!mPlayer->Usestamina(7.f, this))
										return;
									PlayerAttackSound();
									directionAnimation(L"Attack1_Sword", false);
									attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_1, 0.2f);
								}
								else if (miRef == 3)
								{
									if (!mPlayer->Usestamina(7.f, this))
										return;
									PlayerAttackSound();
									directionAnimation(L"Attack2_Sword", false);
									attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_2, 0.2f);
								}
								else if (miRef == 4)
								{
									if (!mPlayer->Usestamina(7.f, this))
										return;
									PlayerAttackSound();
									directionAnimation(L"Attack3_Sword", false);

								}
								else if (miRef == 5)
								{
									if (!mPlayer->Usestamina(7.f, this))
										return;
									PlayerAttackSound();
									directionAnimation(L"Attack4_Sword", false);
									attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_3, 0.2f);
								}

								mCheakTime = 0.f;
								++miRef;
							}
						}
					}
					break;


					}
#pragma endregion



				}

				if (Input::GetKeyUp(eKeyCode::LBTN))
				{
					if (mAttackStop)
						return;
					switch (mPlayerState.weapon)
					{
					case ks::eWeapon::None:
						break;
					case ks::eWeapon::Sword:
					{
						if (mState.situation == eSituation::Attack)
						{
							mState.situation = eSituation::Continue;
							mStatus->SetStateInfo(mState);

						}
						else if (mState.situation == eSituation::Auto)
						{
							mState.situation = eSituation::None;
							mStatus->SetStateInfo(mState);
							miRef = 0;
							mCheakTime = 0.f;
						}
					}
					break;
					case ks::eWeapon::Bow:
					{
						if (mState.situation == eSituation::Auto)
						{
							mState.situation = eSituation::None;
							mStatus->SetStateInfo(mState);
							mbAttackWalk = false;
							mCheakTime = 0.f;
						}
					}
					break;
					case ks::eWeapon::Staff:
					{
						if (mbAttackWalk)
						{
							mStaffStnminaRecovery = false;
							mStaffStnmina = false;
							if (mCheakTime < MIN_TIME)
							{
								PlayerAttackSound();
								angleDirection();
								mState.situation = eSituation::Attack;
								mStatus->SetStateInfo(mState);
								directionAnimation(L"Attack_None", false);
								attackCommandmagic(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_1, 0.45f, mCheakTime);
								effectDeath(eLayerType::Player_Effect);
								mbAttackWalk = false;
								mCarge = false;
								mCargeSound = false;
								mCargeEffect = false;
								mCheakTime = 0.f;
							}
							else if (mCheakTime >= MIN_TIME && mCheakTime < MAX_TIME)
							{
								PlayerAttackSound();
								angleDirection();
								mState.situation = eSituation::Attack;
								mStatus->SetStateInfo(mState);
								directionAnimation(L"Attack_None", false);
								attackCommandmagic(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_1, 0.45f, mCheakTime);
								effectDeath(eLayerType::Player_Effect);
								mbAttackWalk = false;
								mCarge = false;
								mCargeSound = false;
								mCargeEffect = false;
								mCheakTime = 0.f;
							}

							else if (mCheakTime >= MAX_TIME)
							{
								PlayerAttackSound();
								angleDirection();
								mState.situation = eSituation::Attack;
								mStatus->SetStateInfo(mState);
								directionAnimation(L"Attack_Staffcharge", false);
								attackCommandmagic(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_1, 0.8f, mCheakTime);
								effectDeath(eLayerType::Player_Effect);
								mbAttackWalk = false;
								mCarge = false;
								mCargeSound = false;
								mCargeEffect = false;
								mCargeFinsh = true;
								mCheakTime = 0.f;
							}
						}

					}
					break;
					case ks::eWeapon::Legend_Sword:
					{
						if (mState.situation == eSituation::Attack)
						{
							mState.situation = eSituation::Continue;
							mStatus->SetStateInfo(mState);

						}
						else if (mState.situation == eSituation::Auto)
						{
							mState.situation = eSituation::None;
							mStatus->SetStateInfo(mState);
							miRef = 0;
							mCheakTime = 0.f;
						}
					}
					break;
					case ks::eWeapon::Legend_Bow:
					{
						if (mState.situation == eSituation::Auto)
						{
							mState.situation = eSituation::None;
							mStatus->SetStateInfo(mState);
							mbAttackWalk = false;
							mCheakTime = 0.f;
						}
					}
					break;
					case ks::eWeapon::Legend_Staff:
					{
						if (mbAttackWalk)
						{
							mStaffStnminaRecovery = false;
							mStaffStnmina = false;
							if (mCheakTime < MIN_TIME)
							{
								PlayerAttackSound();
								angleDirection();
								mState.situation = eSituation::Attack;
								mStatus->SetStateInfo(mState);
								directionAnimation(L"Attack_None", false);
								attackCommandmagic(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_1, 0.45f, mCheakTime);
								effectDeath(eLayerType::Player_Effect);
								mbAttackWalk = false;
								mCarge = false;
								mCargeSound = false;
								mCargeEffect = false;
								mCheakTime = 0.f;
							}
							else if (mCheakTime >= MIN_TIME && mCheakTime < MAX_TIME)
							{
								PlayerAttackSound();
								angleDirection();
								mState.situation = eSituation::Attack;
								mStatus->SetStateInfo(mState);
								directionAnimation(L"Attack_None", false);
								attackCommandmagic(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_1, 0.45f, mCheakTime);
								effectDeath(eLayerType::Player_Effect);
								mbAttackWalk = false;
								mCarge = false;
								mCargeSound = false;
								mCargeEffect = false;
								mCheakTime = 0.f;
							}

							else if (mCheakTime >= MAX_TIME)
							{
								PlayerAttackSound();
								angleDirection();
								mState.situation = eSituation::Attack;
								mStatus->SetStateInfo(mState);
								directionAnimation(L"Attack_Staffcharge", false);
								attackCommandmagic(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_1, 0.8f, mCheakTime);
								effectDeath(eLayerType::Player_Effect);
								mbAttackWalk = false;
								mCarge = false;
								mCargeSound = false;
								mCargeEffect = false;
								mCargeFinsh = true;
								mCheakTime = 0.f;
							}
						}

					}
					break;
					}
				}

				if (mPlayerShake)
				{
					playerShake(0.5f, 0.01f, 50.f);
				}


				if (mAttackFailed)
				{
					if (mStaffAttack)
					{
						angleDirection();
						mState.situation = eSituation::Attack;
						mStatus->SetStateInfo(mState);
						directionAnimation(L"Attack_None", false);
						attackCommandmagic(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_1, 0.45f, mCheakTime);
						effectDeath(eLayerType::Player_Effect);
						mbAttackWalk = false;
						mCarge = false;
						mCargeSound = false;
						mCargeEffect = false;
						mCheakTime = 0.f;
						mStaffAttack = false;
					}
					else
					{
						mState.situation = eSituation::None;
						mStatus->SetStateInfo(mState);
						miRef = 0;
						mbAttackWalk = false;
						mCheakTime = 0.f;
					}
					mAttackFailed = false;
					mPlayerShake = true;
					mOnceCheak = false;
				}

				//스킬 키
				if (Input::GetKeyDown(eKeyCode::RBTN))
				{
					if (!(mPlayer->GetSkilUiTarget()->IsActiveSlot()))
						return;
					if (mAttackStop || mState.situation == eSituation::Skil || mState.situation == eSituation::Attack)
						return;
					if (!mPlayer->UseMp(1.0f, this))
						return;
					angleDirection();
					mState.situation = eSituation::Skil;
					mStatus->SetStateInfo(mState);
					mPlayerState.skil = eSkil::Magic;
					mPlayer->SetPlayerInfo(mPlayerState);

					if (mPlayer->GetSkilUiTarget()->GetActiveSkil() == eItem::Lighting)
					{
						skillLightingSound();
						directionAnimation(L"Attack_Dash", false);
					}
					else
					{
						skillSound();
						directionAnimation(L"Attack_Staffcharge", false);
					}


					switch (mPlayer->GetSkilUiTarget()->GetActiveSkil())
					{
					case ks::eItem::Dark:
						skilDark();
						break;
					case ks::eItem::Ice:
						skilIce();
						break;
					case ks::eItem::Barrier:
						skilBarrier();
						break;
					case ks::eItem::Lighting:
						Vec3 playerpos = mTransform->GetPosition();
						Vec3 mousepos = Input::GetMousWorldPosition();
						m_vLightingPos = mousepos - playerpos;
						m_vLightingPos.Normalize();
						m_bLightingAttack = true;
						m_bLightingOneCheak = true;
						Collider2D* collider = mPlayer->GetComponent<Collider2D>();
						collider->SetSize(Vector2(0.0f, 0.0f));
						break;
					}



				}

				//걷기 or 뛰기
				/*if (Input::GetKeyUp(eKeyCode::LSHIFT))
				{
					mState = mStatus->GetStateInfo();
					if (mbRunning)
					{
						mbRunning = false;
						if (mState.situation == eSituation::Run)
							directionAnimation(L"Move", true);
					}
					else
					{
						mbRunning = true;
						if (mState.situation == eSituation::Run)
							directionAnimation(L"Run", true);
					}

				}*/

				if (Input::GetKeyDown(eKeyCode::R))
				{

					mPlayerState = mPlayer->GetPlayerInfo();

					switch (mPlayerState.weapon_Slot)
					{
					case ks::eSlot::Slot_1:
						mPlayerState.weapon_Slot = eSlot::Slot_2;
						break;
					case ks::eSlot::Slot_2:
						mPlayerState.weapon_Slot = eSlot::Slot_1;
						break;
					}

					mPlayer->SetPlayerInfo(mPlayerState);
					mPlayer->SetSlotChange(true);
				}

				if (Input::GetKeyDown(eKeyCode::ESC))
				{
					optionOpenSound();
					if (mOption->GetOption())
					{
						mOption->SetOption(false);
					}
					else
					{
						mOption->SetOption(true);
					}
				}

				if (Input::GetKeyDown(eKeyCode::I))
				{
					playerInventorySound();
					if (mInventory->GetInventoryOnOff())
					{
						mInventory->SetInventoryOnOff(false);
					}
					else
					{
						mInventory->SetInventoryOnOff(true);
					}


				}

				if (m_sbPlayerPower)
				{
					m_fPowerTime += Time::DeltaTime();
					if (m_fPowerTime >= 1.0f)
					{
						m_sbPlayerPower = false;
						m_fPowerTime = 0.f;

					}

				}
				if (m_sbPlayerHit)
				{
					m_fPlayerHitTime += Time::DeltaTime();



					if (m_sfPlayerHitTime >= 1.0f)
					{
						m_bHitCol = false;
						m_sfPlayerHit = 1.0f;
					}
					else if (m_sfPlayerHitTime <= 0.0f)
					{
						m_bHitCol = true;
						m_sfPlayerHit = 0.0f;
					}

					if (!m_bHitCol)
					{
						m_sfPlayerHitTime -= Time::DeltaTime() * 20;
					}
					else
						m_sfPlayerHitTime += Time::DeltaTime() * 20;


					if (m_fPlayerHitTime >= 1.0f)
					{
						m_fPlayerHitTime = 0.f;
						m_sfPlayerHit = 0.0f;
						m_sfPlayerHitTime = 1.f;
						m_sbPlayerHit = false;
						m_bHitCol = false;
					}


				}



			}

			/*Transform* tr = GetOwner()->GetComponent<Transform>();

			Vector3 pos = tr->GetPosition();

			if (Input::GetKeyState(eKeyCode::D) == eKeyState::PRESSED)
			{
				pos.x += 3.0f * Time::DeltaTime();
			}
			else if (Input::GetKeyState(eKeyCode::A) == eKeyState::PRESSED)
			{
				pos.x -= 3.0f * Time::DeltaTime();
			}
			else if (Input::GetKeyState(eKeyCode::W) == eKeyState::PRESSED)
			{
				pos.y += 3.0f * Time::DeltaTime();
			}
			else if (Input::GetKeyState(eKeyCode::S) == eKeyState::PRESSED)
			{
				pos.y -= 3.0f * Time::DeltaTime();
			}
			else if (Input::GetKeyState(eKeyCode::Q) == eKeyState::PRESSED)
			{
				pos.z += 3.0f * Time::DeltaTime();
			}
			else if (Input::GetKeyState(eKeyCode::E) == eKeyState::PRESSED)
			{
				pos.z -= 3.0f * Time::DeltaTime();
			}

			tr->SetPosition(pos);*/
		}
		else
		{
			m_fPlayerDeathTime += Time::DeltaTime();

			if (m_fPlayerDeathTime >= 2.0f)
			{
				if(!m_bChangeScene)
				{
					PlayScene::SetChangeScene(true);
					Stage1_1::SetSoundCheak(false);
					m_bChangeScene = true;
				}
			}


			if(!m_bDeathOneCheak)
			{
				playerDeathSound();
				mAnimator->Play(L"Death_UpLeft", false);
				m_bDeathOneCheak = true;

				
				m_sbPlayerHit = true;
				m_sfPlayerHit = 1.0f;
				
			}
			playerHitColor();
			
			if (m_sbPlayerHit)
			{
				m_fPlayerHitTime += Time::DeltaTime();



				if (m_sfPlayerHitTime >= 1.0f)
				{
					m_bHitCol = false;
					m_sfPlayerHit = 1.0f;
				}
				else if (m_sfPlayerHitTime <= 0.0f)
				{
					m_bHitCol = true;
					m_sfPlayerHit = 0.0f;
				}

				if (!m_bHitCol)
				{
					m_sfPlayerHitTime -= Time::DeltaTime() * 20;
				}
				else
					m_sfPlayerHitTime += Time::DeltaTime() * 20;


				if (m_fPlayerHitTime >= 1.0f)
				{
					m_fPlayerHitTime = 0.f;
					m_sfPlayerHit = 0.0f;
					m_sfPlayerHitTime = 1.f;
					m_sbPlayerHit = false;
					m_bHitCol = false;
				}


			}


		}


	}
	void PlayerScript::Render()
	{
	}


	void PlayerScript::Start()
	{
		
		int a = 0;


	}

	void PlayerScript::Action()
	{
	}

	void PlayerScript::End()
	{
		/*if(mAnimator->GetEndEvent(L"Evade_DownLeft"))
		mAnimator->Play(L"Attack_Dash_Right", false);*/

		//mAnimator->Play(L"Attack_Dash_Right", false);

	}



	
	void PlayerScript::directionAnimation(const std::wstring& name, bool loop, bool save)
	{


		std::wstring aniname;

		if (save)
		{
			switch (mState.direction)
			{
			case ks::eDirection::Left:
			{
				aniname = name + L"_Left";
				mAnimator->Play(aniname, loop, save);
			}
			break;
			case ks::eDirection::Right:
			{
				aniname = name + L"_Right";
				mAnimator->Play(aniname, loop, save);
			}
			break;
			case ks::eDirection::Up:
			{
				aniname = name + L"_Up";
				mAnimator->Play(aniname, loop, save);
			}
			break;
			case ks::eDirection::Down:
			{
				aniname = name + L"_Down";
				mAnimator->Play(aniname, loop, save);
			}
			break;
			case ks::eDirection::UpLeft:
			{
				aniname = name + L"_UpLeft";
				mAnimator->Play(aniname, loop, save);
			}
			break;
			case ks::eDirection::UpRight:
			{
				aniname = name + L"_UpRight";
				mAnimator->Play(aniname, loop, save);
			}
			break;
			case ks::eDirection::DownLeft:
			{
				aniname = name + L"_DownLeft";
				mAnimator->Play(aniname, loop, save);
			}
			break;
			case ks::eDirection::DownRight:
			{
				aniname = name + L"_DownRight";
				mAnimator->Play(aniname, loop, save);
			}
			break;
			}
		}

		else if(save == false)
		{
			switch (mState.direction)
			{
			case ks::eDirection::Left:
			{
				aniname = name + L"_Left";
				mAnimator->Play(aniname, loop);
			}
			break;
			case ks::eDirection::Right:
			{
				aniname = name + L"_Right";
				mAnimator->Play(aniname, loop);
			}
			break;
			case ks::eDirection::Up:
			{
				aniname = name + L"_Up";
				mAnimator->Play(aniname, loop);
			}
			break;
			case ks::eDirection::Down:
			{
				aniname = name + L"_Down";
				mAnimator->Play(aniname, loop);
			}
			break;
			case ks::eDirection::UpLeft:
			{
				aniname = name + L"_UpLeft";
				mAnimator->Play(aniname, loop);
			}
			break;
			case ks::eDirection::UpRight:
			{
				aniname = name + L"_UpRight";
				mAnimator->Play(aniname, loop);
			}
			break;
			case ks::eDirection::DownLeft:
			{
				aniname = name + L"_DownLeft";
				mAnimator->Play(aniname, loop);
			}
			break;
			case ks::eDirection::DownRight:
			{
				aniname = name + L"_DownRight";
				mAnimator->Play(aniname, loop);
			}
			break;
			}
		}



	}

	void PlayerScript::angleDirection()
	{

		Vector3 Pos = mTransform->GetDirection();
		float angle = mTransform->GetAngle();

		//두점 사이의 각도 atan2 함수로 방향 설정 (180~ -180)각도 구해줌
		//Right
		if (angle <= 22.5 && angle > -22.5)
			mState.direction = eDirection::Right;
		//UpRight
		else if (angle <= 67.5 && angle > 22.5)
			mState.direction = eDirection::UpRight;
		//Up
		else if (angle <= 112.5 && angle > 67.5)
			mState.direction = eDirection::Up;
		//UpLeft
		else if (angle <= 157.5 && angle > 112.5)
			mState.direction = eDirection::UpLeft;
		//Left
		else if (angle <= -157.5 || angle > 157.5)
			mState.direction = eDirection::Left;
		//DownLeft
		else if (angle <= -112.5 && angle > -157.5)
			mState.direction = eDirection::DownLeft;
		//Down
		else if (angle <= -67.5 && angle > -112.5)
			mState.direction = eDirection::Down;
		//DownRight
		else if (angle <= -22.5 && angle > -67.5)
			mState.direction = eDirection::DownRight;

		mStatus->SetStateInfo(mState);

		//방향벡터로 위치 확인		
			//좌표 0이 안되서 동서남북 4방향이 안나옴 해결 해야함
			//if (Pos.x > 0)
			//{
			//	//RightUp
			//	if (Pos.y > 0)
			//		mAnimator->Play(L"Attack_staft_UpRight", false);
			//	//RightDown
			//	else if(Pos.y < 0)
			//		mAnimator->Play(L"Attack_staft_DownRight", false);
			//	//Right
			//	else if(Pos.y == 0)
			//		mAnimator->Play(L"Attack_staft_Right", false);
			//}			
			//else if (Pos.x < 0)
			//{
			//	//LeftUp
			//	if (Pos.y > 0)
			//		mAnimator->Play(L"Attack_staft_UpLeft", false);
			//	//LeftDown
			//	else if (Pos.y < 0)
			//		mAnimator->Play(L"Attack_staft_DownLeft", false);
			//	//Left
			//	else if (Pos.y == 0)
			//		mAnimator->Play(L"Attack_staft_Left", false);
			//}
			//else if (Pos.x == 0)
			//{
			//	//Up
			//	if (Pos.y > 0)
			//		mAnimator->Play(L"Attack_staft_Up", false);
			//	//Down
			//	else if (Pos.y < 0)
			//		mAnimator->Play(L"Attack_staft_Down", false);
			//}


	}	

	void PlayerScript::attackCommand(eLayerType type, eDirection dir, eSkil skil, eProgress progress, float colldowntime)
	{
		{
			PlayerAttack* mAttack = object::Instantiate<PlayerAttack>(type);
			mPlayerState.skil = skil;
			mPlayerState.progress = progress;
			mPlayer->SetPlayerInfo(mPlayerState);

			Collider2D* collider = mAttack->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			collider->SetSize(Vec2(0.0f, 0.0f));

			mAttack->SetDirection(dir);
			mAttack->SetCooldownTime(colldowntime);
			mAttack->SetTarget(mPlayer);
			mAttack->GetComponent<Transform>()->SetPosition(mTransform->GetPosition());
			mAttack->Initalize();
		}
	}

	void PlayerScript::attackCommandmagic(eLayerType type, eDirection dir, eSkil skil, eProgress progress, float colldowntime, float scale)
	{
		PlayerAttack* mAttack = object::Instantiate<PlayerAttack>(type);
		mPlayerState.skil = skil;
		mPlayerState.progress = progress;
		mPlayer->SetPlayerInfo(mPlayerState);

		Collider2D* collider = mAttack->AddComponent<Collider2D>();
		collider->SetType(eColliderType::Rect);
		collider->SetSize(Vec2(0.0f, 0.0f));

		mAttack->SetSphereScale(scale);
		mAttack->SetDirection(dir);
		mAttack->SetCooldownTime(colldowntime);
		mAttack->SetTarget(mPlayer);
		mAttack->GetComponent<Transform>()->SetPosition(mTransform->GetPosition());

		mAttack->Initalize();
	}

	void PlayerScript::effectDeath(eLayerType layer)
	{

		Scene* scene = SceneManager::GetActiveScene();

		const std::vector<GameObject*>& obj = scene->GetGameObjects(layer);

		for (size_t i = 0; i < obj.size(); i++)
		{
			if (obj[i] != nullptr)
			{
				obj[i]->Death();
			}
			//scene->Destroy();
		}

	}


	void PlayerScript::playerShake(float time, float distance, float speed)
	{

		mShakePos = mTransform->GetPosition();
		mShakeTime += Time::DeltaTime();
		if (mShakeTime >= time)
		{
			mShakeTime = 0.0f;
			mPlayerShake = false;			
		}
		
		if (!mOnceCheak)
		{
			if (mTransform != nullptr)
			{
				failedSound();
				mShakePos = mTransform->GetPosition();
				mFixPos = Vec3::Zero;
				mOnceCheak = true;

			}
		}
		else
		{

			if (mFixPos.x < distance)
			{
				mShakePos.x += speed * Time::DeltaTime();
				mFixPos.x += speed * Time::DeltaTime();
			}
			else if (mFixPos.x > distance)
			{
				mShakePos.x -= speed * Time::DeltaTime();
				mFixPos.x -= speed * Time::DeltaTime();
			}

		mTransform->SetPosition(mShakePos);
		}



	}

	

	void PlayerScript::playerHitColor()
	{
		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Player_Effect];
		renderer::PLAYEREFFECT data;

		data.playerhit = m_sfPlayerHit;
		//data.playerhit = m_sfPlayerHitTime;
		data.playerhittime = m_sfPlayerHitTime;
		


		cb->Bind(&data);
		cb->SetPipline(eShaderStage::VS);
		cb->SetPipline(eShaderStage::PS);
	}

	void PlayerScript::playerRunSound()
	{

		std::shared_ptr<AudioClip> booksound = Resources::Find<AudioClip>(L"Wood_run_01");
		booksound->SetLoop(true);
		booksound->Play();


	}

	void PlayerScript::playerRunSoundStop()
	{
		std::shared_ptr<AudioClip> booksound = Resources::Find<AudioClip>(L"Wood_run_01");
		booksound->Stop();
	}

	void PlayerScript::PlayerAttackSound()
	{
		std::shared_ptr<AudioClip> booksound = Resources::Find<AudioClip>(L"Attack_Sound");
		booksound->SetLoop(false);
		booksound->Play(3.0f);

	}

	void PlayerScript::playerCoinSound()
	{
		std::shared_ptr<AudioClip> coinsound = Resources::Find<AudioClip>(L"Coin");
		coinsound->SetLoop(false);
		coinsound->Play(3.0f);
	}

	void PlayerScript::playerInventorySound()
	{
		std::shared_ptr<AudioClip> coinsound = Resources::Find<AudioClip>(L"Inventory");
		coinsound->SetLoop(false);
		coinsound->Play(3.0f);
	}

	void PlayerScript::loadSound()
	{
		std::shared_ptr<AudioClip> booksound = Resources::Load<AudioClip>
			(L"Wood_run_01", L"..\\Resources\\Sound\\Wood_run_01.ogg");

		std::shared_ptr<AudioClip> sound = Resources::Load<AudioClip>
			(L"Attack_Sound", L"..\\Resources\\Sound\\Attack_Sound.ogg");

		std::shared_ptr<AudioClip> coinsound = Resources::Load<AudioClip>
			(L"Coin", L"..\\Resources\\Sound\\Coin.ogg");

		std::shared_ptr<AudioClip> inventorysound = Resources::Load<AudioClip>
			(L"Inventory", L"..\\Resources\\Sound\\Inventory.ogg");

		std::shared_ptr<AudioClip> Itemsound = Resources::Load<AudioClip>
			(L"Item", L"..\\Resources\\Sound\\Item.ogg");

		std::shared_ptr<AudioClip> Shopbuysound = Resources::Load<AudioClip>
			(L"Shop_buy", L"..\\Resources\\Sound\\Shop_buy.ogg");

		std::shared_ptr<AudioClip> Failed = Resources::Load<AudioClip>
			(L"Failed", L"..\\Resources\\Sound\\Failed.ogg");

		std::shared_ptr<AudioClip> Staff_Charge_Finish = Resources::Load<AudioClip>
			(L"Staff_Charge_Finish", L"..\\Resources\\Sound\\Staff_Charge_Finish.ogg");

		std::shared_ptr<AudioClip> Staff_Chrage = Resources::Load<AudioClip>
			(L"Staff_Chrage", L"..\\Resources\\Sound\\Staff_Chrage.ogg");

		std::shared_ptr<AudioClip> Skill = Resources::Load<AudioClip>
			(L"Skill", L"..\\Resources\\Sound\\Skill.ogg");

		std::shared_ptr<AudioClip> Lighting_Attack = Resources::Load<AudioClip>
			(L"Lighting_Attack", L"..\\Resources\\Sound\\Lighting_Attack.ogg");

		std::shared_ptr<AudioClip> Option_OPen = Resources::Load<AudioClip>
			(L"Option_OPen", L"..\\Resources\\Sound\\Option_OPen.ogg");

		std::shared_ptr<AudioClip> Evade_Ok = Resources::Load<AudioClip>
			(L"Evade_Ok", L"..\\Resources\\Sound\\Evade_Ok.ogg");

		std::shared_ptr<AudioClip> Evade_Clear = Resources::Load<AudioClip>
			(L"Evade_Clear", L"..\\Resources\\Sound\\Evade_Clear.ogg");

		std::shared_ptr<AudioClip> Player_Hit = Resources::Load<AudioClip>
			(L"Player_Hit", L"..\\Resources\\Sound\\Player_Hit.ogg");

		std::shared_ptr<AudioClip> Player_Death = Resources::Load<AudioClip>
			(L"Player_Death", L"..\\Resources\\Sound\\Player_Death.ogg");

	}

	void PlayerScript::itemLootSound()
	{
		std::shared_ptr<AudioClip> coinsound = Resources::Find<AudioClip>(L"Item");
		coinsound->SetLoop(false);
		coinsound->Play(3.0f);

	}

	void PlayerScript::shopbuySound()
	{
		std::shared_ptr<AudioClip> coinsound = Resources::Find<AudioClip>(L"Shop_buy");
		coinsound->SetLoop(false);
		coinsound->Play(3.0f);
	}

	void PlayerScript::failedSound()
	{
		std::shared_ptr<AudioClip> coinsound = Resources::Find<AudioClip>(L"Failed");
		coinsound->SetLoop(false);
		coinsound->Play(3.0f);
	}

	void PlayerScript::staffChargeSound()
	{
		std::shared_ptr<AudioClip> coinsound = Resources::Find<AudioClip>(L"Staff_Chrage");
		coinsound->SetLoop(false);
		coinsound->Play(3.0f);

	}

	void PlayerScript::staffChargeFinishSound()
	{

		std::shared_ptr<AudioClip> coinsound = Resources::Find<AudioClip>(L"Staff_Charge_Finish");
		coinsound->SetLoop(false);
		coinsound->Play(3.0f);
	}

	void PlayerScript::skillSound()
	{		
		std::shared_ptr<AudioClip> coinsound = Resources::Find<AudioClip>(L"Skill");
		coinsound->SetLoop(false);
		coinsound->Play(3.0f);
	}

	void PlayerScript::skillLightingSound()
	{
		std::shared_ptr<AudioClip> coinsound = Resources::Find<AudioClip>(L"Lighting_Attack");
		coinsound->SetLoop(false);
		coinsound->Play(3.0f);
	}

	void PlayerScript::optionOpenSound()
	{
		std::shared_ptr<AudioClip> sound = Resources::Find<AudioClip>(L"Option_OPen");
		sound->SetLoop(false);
		sound->Play();
	}

	void PlayerScript::evadeOkSound()
	{
		std::shared_ptr<AudioClip> sound = Resources::Find<AudioClip>(L"Evade_Ok");
		sound->SetLoop(false);
		sound->Play();
	}

	void PlayerScript::evadeClearSound()
	{
		std::shared_ptr<AudioClip> sound = Resources::Find<AudioClip>(L"Evade_Clear");
		sound->SetLoop(false);
		sound->Play();
	}

	void PlayerScript::playerHitSound()
	{		
		std::shared_ptr<AudioClip> sound = Resources::Find<AudioClip>(L"Player_Hit");
		sound->SetLoop(false);
		sound->Play();
	}

	void PlayerScript::playerDeathSound()
	{
		std::shared_ptr<AudioClip> sound = Resources::Find<AudioClip>(L"Player_Death");
		sound->SetLoop(false);
		sound->Play();
	}

	void PlayerScript::skilIce()
	{
		Skil_IceFairy* mAttack = object::Instantiate<Skil_IceFairy>(eLayerType::Player_Attack);

		mAttack->SetTarget(mPlayer);
		mAttack->GetComponent<Transform>()->SetPosition(Input::GetMousWorldPosition());
		mAttack->GetComponent<Transform>()->SetScale(Vec3(18.0f, 18.0f, 0.0f));


		Collider2D* collider = mAttack->AddComponent<Collider2D>();
		collider->SetType(eColliderType::Rect);
		collider->SetSize(Vec2(0.43f, 0.43f));


		mAttack->Initalize();

	}

	void PlayerScript::skilDark()
	{

		Skil_Dark* mAttack = object::Instantiate<Skil_Dark>(eLayerType::Player_Attack);

		mAttack->SetTarget(mPlayer);
		mAttack->GetComponent<Transform>()->SetPosition(Input::GetMousWorldPosition());
		mAttack->GetComponent<Transform>()->SetScale(Vec3(12.0f, 12.0f, 0.0f));


		Collider2D* collider = mAttack->AddComponent<Collider2D>();
		collider->SetType(eColliderType::Rect);
		collider->SetSize(Vec2(0.45f, 0.45f));


		mAttack->Initalize();

	}

	void PlayerScript::skilBarrier()
	{
		Skil_Barrier* mAttack = object::Instantiate<Skil_Barrier>(eLayerType::Player_Attack);

		mAttack->SetTarget(mPlayer);
		mAttack->GetComponent<Transform>()->SetPosition(mTransform->GetPosition());
		mAttack->GetComponent<Transform>()->SetScale(Vec3(7.0f, 7.0f, 0.0f));


		Collider2D* collider = mAttack->AddComponent<Collider2D>();
		collider->SetType(eColliderType::Rect);
		collider->SetSize(Vec2(0.31f, 0.31f));

		mAttack->Initalize();

	}

	void PlayerScript::skilLighting()
	{
		Skil_Lighting* mAttack = object::Instantiate<Skil_Lighting>(eLayerType::Player_Attack);

		mAttack->SetTarget(mPlayer);

		Vec3 dir = Input::GetMousWorldPosition();
		Vec3 playerdir = mTransform->GetPosition();
		if (playerdir.x > dir.x)
		{
			mAttack->SetLightionLeft(true);
		}
		else if (playerdir.x < dir.x)
		{
			mAttack->SetLightionRight(true);
		}

		Vec3 playerpos = mTransform->GetPosition();
		playerpos.y += 1.9f;

		mAttack->GetComponent<Transform>()->SetPosition(playerpos);
		//mAttack->GetComponent<Transform>()->SetPosition(mTransform->GetPosition());
		mAttack->GetComponent<Transform>()->SetScale(Vec3(13.0f, 13.0f, 0.0f));

	
		/*Collider2D* collider = mAttack->AddComponent<Collider2D>();
		collider->SetType(eColliderType::Rect);
		collider->SetSize(Vec2(0.35f, 0.35f));*/

		mAttack->Initalize();

	}

	void PlayerScript::targetLighting()
	{
		for (size_t i = 0; i < m_vectorLightingTargetPos.size(); i++)
		{
			Skil_Lighting* mAttack = object::Instantiate<Skil_Lighting>(eLayerType::Player_Attack);

			mAttack->SetTarget(mPlayer);

			int a = rand() % 2;		
			if (a == 0)
			{
				mAttack->SetLightionLeft(true);
			}
			else if (a == 1)
			{
				mAttack->SetLightionRight(true);
			}

			m_vectorLightingTargetPos[i].y += 1.9f;
	 

			mAttack->GetComponent<Transform>()->SetPosition(m_vectorLightingTargetPos[i]);
			
			mAttack->GetComponent<Transform>()->SetScale(Vec3(13.0f, 13.0f, 0.0f));
			mAttack->Initalize();
		}


	}

	void PlayerScript::optionCreate()
	{
		


	}


	

	void PlayerScript::OnCollisionEnter(Collider2D* collider)
	{
		if (dynamic_cast<MonsterMissile*>(collider->GetOwner()))
		{
			MonsterMissile* monstermissile = (MonsterMissile*)collider->GetOwner();
			if (mPlayerState.skil == eSkil::Evade)
			{
				evadeOkSound();
				m_sbPlayerPower = true;
				mPlayer->SetPlayerMp(1.0f);
			}
			
			if (m_sbPlayerPower || m_sfPlayerHit == 1.0f)
				return;
			if (mPlayer->GetPlayerHp() < 0.f)
				return;

			playerHitSound();
			m_sbPlayerHit = true;
			m_sfPlayerHit = 1.0f;
			mPlayer->SetPlayerHp(-0.5f);


		}

		if (dynamic_cast<Snake_Green*>(collider->GetOwner()))
		{
			Snake_Green* sanke = (Snake_Green*)collider->GetOwner();
			if (m_bLightingAttack)
			{
				sanke->YourDeath(true);
				sanke->SetWalkStop(true);
				m_vectorLightingTargetPos.push_back(collider->GetOwner()->GetComponent<Transform>()->GetPosition());
			}
		}
		if (dynamic_cast<Forest_Fairy*>(collider->GetOwner()))
		{
			Snake_Green* forest = (Snake_Green*)collider->GetOwner();
			if (m_bLightingAttack)
			{
				forest->YourDeath(true);
				forest->SetWalkStop(true);
				m_vectorLightingTargetPos.push_back(collider->GetOwner()->GetComponent<Transform>()->GetPosition());
			}
		}
		if (dynamic_cast<Slime_Green*>(collider->GetOwner()))
		{
			Snake_Green* slime = (Snake_Green*)collider->GetOwner();
			if (m_bLightingAttack)
			{
				slime->YourDeath(true);
				slime->SetWalkStop(true);
				m_vectorLightingTargetPos.push_back(collider->GetOwner()->GetComponent<Transform>()->GetPosition());
			}
		}

		if (dynamic_cast<CCoin*>(collider->GetOwner()))
		{
			CCoin* coin = (CCoin*)collider->GetOwner();
			UINT playercoin = coin->GetCoinValue();
			mPlayer->SetPlayerCoin(playercoin);
			coin->ItemLoot(true);
			playerCoinSound();

		}


		if (dynamic_cast<Stage1_1Move*>(collider->GetOwner()))
		{

			switch (mPlayer->GetGroundStage())
			{
			case ks::enums::eGroundStage::Ground1:
			{	
				Stage1_1Move* stge = (Stage1_1Move*)collider->GetOwner();
				stge->SetFedeEffect(true);
			}
			break;
			case ks::enums::eGroundStage::Ground2:
			{
				Stage1_1Move* stge = (Stage1_1Move*)collider->GetOwner();
				stge->SetFedeEffect(true);
			}
				break;
			case ks::enums::eGroundStage::Ground3:
			{
				Stage1_1Move* stge = (Stage1_1Move*)collider->GetOwner();
				stge->SetFedeEffect(true);
			}
				break;
			case ks::enums::eGroundStage::Ground4:
			{
				Stage1_1Move* stge = (Stage1_1Move*)collider->GetOwner();
				stge->SetFedeEffect(true);
				Stage1_1::SetSoundCheak(false);
			}
				break;
			case ks::enums::eGroundStage::Ground5:
			{
				Stage1_1Move* stge = (Stage1_1Move*)collider->GetOwner();
				stge->SetFedeEffect(true);
				Stage1_1::SetSoundCheak(false);
			}
				break;
			case ks::enums::eGroundStage::Ground6:
			{
				Stage1_1Move* stge = (Stage1_1Move*)collider->GetOwner();
				stge->SetFedeEffect(true);
			}
				break;
			case ks::enums::eGroundStage::Ground7:
			{
				Stage1_1Move* stge = (Stage1_1Move*)collider->GetOwner();
				stge->SetFedeEffect(true);
			}
				break;
			case ks::enums::eGroundStage::Ground8:
			{
				Stage1_1Move* stge = (Stage1_1Move*)collider->GetOwner();
				stge->SetFedeEffect(true);
				Stage1_1::SetSoundCheak(false);
			}
				break;
			case ks::enums::eGroundStage::Ground9:
			{
				Stage1_1Move* stge = (Stage1_1Move*)collider->GetOwner();
				stge->SetFedeEffect(true);
			}
				break;
			}


		}
	}

	void PlayerScript::OnCollisionStay(Collider2D* collider)
	{
		if (dynamic_cast<Diary*>(collider->GetOwner()))
		{
			if (Input::GetKeyDown(eKeyCode::F))
			{
				Diary* diary = (Diary*)collider->GetOwner();
				diary->SetCheak(true);
				diary->SetTarget(mPlayer);

				std::shared_ptr<AudioClip> booksound = Resources::Load<AudioClip>
					(L"Book", L"..\\Resources\\Sound\\Book.ogg");
				booksound->SetLoop(false);
				booksound->Play();

			}
		}		
		if (dynamic_cast<GoldBox*>(collider->GetOwner()))
		{
			if (Input::GetKeyDown(eKeyCode::F))
			{
				GoldBox* box = (GoldBox*)collider->GetOwner();				
				if (!(box->IsOpenFinsh()))
				{
					box->IsBoxOpen(true);
				}
			}
		}


		if (dynamic_cast<PlayerItem*>(collider->GetOwner()))
		{
			if (Input::GetKeyDown(eKeyCode::F))
			{
				PlayerItem* item = (PlayerItem*)collider->GetOwner();
			

				if (item->IsShopItem())
				{
					switch (item->GetPlayerItem())
					{					
					case ks::eItem::Legend_Sword:
					{
						itemLootSound();
						Inventory* inventory = (Inventory*)mPlayer->GetInventoryTarget();
						inventory->AddItem(item->GetPlayerItem());
						item->Death();
					}
						break;
					case ks::eItem::Legend_Staff:
					{

						itemLootSound();
						Inventory* inventory = (Inventory*)mPlayer->GetInventoryTarget();
						inventory->AddItem(item->GetPlayerItem());
						item->Death();

					}
						break;
					case ks::eItem::Legend_Bow:
					{
						if (mPlayer->IsShopPurchase(100))
						{
							shopbuySound();
							Inventory* inventory = (Inventory*)mPlayer->GetInventoryTarget();
							inventory->AddItem(item->GetPlayerItem());
							Stage1_1::KeyCount_Up();
							item->Death();
						}
						else
						{
							failedSound();
						}
					}
						break;
					case ks::eItem::Hp:
					{

						if (item->IsFreeItem())
						{
							shopbuySound();
							mPlayer->HpRecovery(true);
							item->Death();
						}
						else if (mPlayer->IsShopPurchase(100))
						{
							shopbuySound();
							mPlayer->HpRecovery(true);
							Stage1_1::KeyCount_Up();
							//Inventory* inventory = (Inventory*)mPlayer->GetInventoryTarget();
							//inventory->AddItem(item->GetPlayerItem());
							item->Death();
						}
						else
						{
							failedSound();
						}
					}
					break;
					case ks::eItem::MP:
					{

						if (item->IsFreeItem())
						{
							shopbuySound();
							mPlayer->MpRecovery(true);
							item->Death();
						}
						else if (mPlayer->IsShopPurchase(100))
						{
							shopbuySound();
							mPlayer->MpRecovery(true);
							Stage1_1::KeyCount_Up();
							/*Inventory* inventory = (Inventory*)mPlayer->GetInventoryTarget();
							inventory->AddItem(item->GetPlayerItem());*/
							item->Death();
						}
						else
						{
							failedSound();
						}
					}
					break;
			
					}



	
				}
				else if (item->IsSkilBook())
				{
					switch (item->GetPlayerItem())
					{
					case ks::eItem::Ice:
					{
						itemLootSound();
						SkilUi* skil = mPlayer->GetSkilUiTarget();						
						skil->CreateSkillbook(eItem::Ice);
						item->Death();
						Stage1_1::KeyCount_Up();
					}
					break;
					case ks::eItem::Dark:
					{
						itemLootSound();
						SkilUi* skil = mPlayer->GetSkilUiTarget();
						skil->CreateSkillbook(eItem::Dark);
						item->Death();

					}
					break;
					case ks::eItem::Barrier:
					{
						itemLootSound();
						SkilUi* skil = mPlayer->GetSkilUiTarget();
						skil->CreateSkillbook(eItem::Barrier);
						item->Death();

					}
					break;
					case ks::eItem::Lighting:
					{
						itemLootSound();
						SkilUi* skil = mPlayer->GetSkilUiTarget();
						skil->CreateSkillbook(eItem::Lighting);
						item->Death();
						Stage1_1::KeyCount_Up();
					}
					break;
					}
				}

				else
				{		
					itemLootSound();
					Inventory* inventory = (Inventory*)mPlayer->GetInventoryTarget();
					inventory->AddItem(item->GetPlayerItem());
					item->Death();
					Stage1_1::KeyCount_Up();
				}
				



			}
		}





		if (dynamic_cast<Stage1_1Move*>(collider->GetOwner()))
		{
			if (Input::GetKeyDown(eKeyCode::F))
			{
				mCheak = true;
			}

			if(mCheak)
			{
				mState.situation = eSituation::None;
				mStatus->SetStateInfo(mState);
				mCheakTime = 0.f;
				if (mPlayer->GetGroundStage() == eGroundStage::Start)
				{
					mTime += Time::DeltaTime();
					if (mTime >= 3.0f)
					{
						Stage1_1Move* stge = (Stage1_1Move*)collider->GetOwner();
						stge->SetFedeEffect(true);
						
						mTime = 0.f;
						mCheak = false;
					}
				}
			}
			
		}



	}

	void PlayerScript::OnCollisionExit(Collider2D* collider)
	{

	}


}



