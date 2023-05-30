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


#include <time.h>



#define MIN_TIME 0.5f
#define MAX_TIME 3.0f

//#define BASIC_SCALE 3.7f								//�⺻ ũ��
//#define MAX_SCALE 11.1f									//�ִ� ũ��
#define BASIC_SCALE 7.4f								//�⺻ ũ��
#define MAX_SCALE 22.2f									//�ִ� ũ��
#define INCREMENT (MAX_SCALE - BASIC_SCALE)				//ũ�� ������
#define TIME_SCALE (INCREMENT / MAX_TIME)				//�ʴ� ũ�� ������  

namespace ks
{
	bool PlayerScript::mbRunning = false;
	bool PlayerScript::mbAttackWalk = false;
	bool PlayerScript::mCarge = false;
	bool PlayerScript::mCargeFinsh = false;
	bool PlayerScript::mCargeEffect = false;
	UINT PlayerScript::miRef = 0;
	float PlayerScript::mfStaff = 0.f;
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

		if (nullptr != mStatus)
			mState = mStatus->GetStateInfo();

		mTransform->GetPosition();


#pragma region None -> Idle �� ����, Idle ���� �޽�(Sit) �ִϸ��̼����� ��ȯ


		//�ൿ ������ ���� None ���·� ���� None ���¿����� Idle�� ���� �� Default �ִϸ��̼����� ����
		if (mState.situation == eSituation::None && (mbAttackWalk == false))
		{
				mCheakTime = 0.f;
				mState.situation = eSituation::Idle;
				mStatus->SetStateInfo(mState);
				directionAnimation(L"Idle", false);
		}
		//Idle ���� 3�� �̻� ���� �Ǹ� Sit ���·� ���� �� �޽� �ִϸ��̼� �������� ���
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
				if(a == 1)
				mAnimator->Play(L"Sit_Pray", true);
				if(a == 0)
				mAnimator->Play(L"Sit_Down", false);
								
				mCheakTime = 0.f;
			}

		}

#pragma endregion



#pragma region �⺻ ���� ���� �� ������ ���� (None, Sword, Bow, Staff)

		if (mState.situation == eSituation::Attack || mState.situation == eSituation::Continue || mState.situation == eSituation::Connect)
		{
			mCheakTime += Time::DeltaTime();
			mPlayerState = mPlayer->GetPlayer();

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
			}

		}

#pragma endregion



#pragma region �÷��̾� ��ų �� ������ ���� (Evade, )



		if (mState.situation == eSituation::Skil)
		{
			mCheakTime += Time::DeltaTime();

			mPlayerState = mPlayer->GetPlayer();

			switch (mPlayerState.skil)
			{
			case ks::eSkil::Evade:
			{
				if (mCheakTime > 0.5f)
				{
					mPlayerState.skil = eSkil::None;
					mPlayer->SetPlayer(mPlayerState);
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

			}
		}

#pragma endregion









		if (Input::GetKeyState(eKeyCode::Q) == eKeyState::PRESSED)
		{


		}

		if (Input::GetKeyState(eKeyCode::R) == eKeyState::PRESSED)
		{


		}


#pragma	region �̵� ���� ASDW Idle, Run, Sit ���¿����� �̵� ���� + ���� Ȱ�ϋ��� �̵� ���� + ���� ������ ���� ���϶��� ����


		if (Input::GetKey(eKeyCode::D))
		{
			if (mState.situation == eSituation::Idle || mState.situation == eSituation::Run
				|| mState.situation == eSituation::Sit || mbAttackWalk == true)
			{
				Vector3 pos = mTransform->GetPosition();
				if (mbAttackWalk && mPlayerState.weapon == eWeapon::Bow)
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
				if (mbAttackWalk && mPlayerState.weapon == eWeapon::Bow)
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
					else if(mState.direction == eDirection::Left)
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
				if (mbAttackWalk && mPlayerState.weapon == eWeapon::Bow)
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
				if (mbAttackWalk && mPlayerState.weapon == eWeapon::Bow)
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


#pragma region Ű �������� ( (None, Idle, Sit), Run ���¿����� ���� )
		//Animation Start
		if (Input::GetKeyDown(eKeyCode::D))
		{
			if (mState.situation == eSituation::None || mState.situation == eSituation::Idle
				|| mState.situation == eSituation::Sit)
			{
				mState.direction = eDirection::Right;
				mState.situation = eSituation::Run;
				if (mbRunning)
					directionAnimation(L"Run", true);
				else
					directionAnimation(L"Move", true);

			}
			else if (mState.situation == eSituation::Run)
			{
				switch (mState.direction)
				{

				case ks::eDirection::Left:
				{
					mState.direction = eDirection::BothX;
					mAnimator->Play(L"Idle_Left");
				}
				break;
				case ks::eDirection::Up:
				{
					mState.direction = eDirection::UpRight;
					if (mbRunning)
						directionAnimation(L"Run", true);
					else
						directionAnimation(L"Move", true);

				}
				break;
				case ks::eDirection::Down:
				{
					mState.direction = eDirection::DownRight;
					if (mbRunning)
						directionAnimation(L"Run", true);
					else
						directionAnimation(L"Move", true);
				}
				break;

				case ks::eDirection::BothY:
				{
					mState.direction = eDirection::Right;
					mState.situation = eSituation::Run;

					if (mbRunning)
						directionAnimation(L"Run", true);
					else
						directionAnimation(L"Move", true);
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
					directionAnimation(L"Run", true);
				else
					directionAnimation(L"Move", true);
			}
			else if (mState.situation == eSituation::Run)
			{
				switch (mState.direction)
				{
				case ks::eDirection::Right:
				{
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
						directionAnimation(L"Run", true);
					else
						directionAnimation(L"Move", true);
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
					directionAnimation(L"Run", true);
				else
					directionAnimation(L"Move", true);
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
					mState.direction = eDirection::BothY;
					mAnimator->Play(L"Idle_Up");
				}
				break;
				case ks::eDirection::BothX:
				{
					mState.direction = eDirection::Down;
					mState.situation = eSituation::Run;

					if (mbRunning)
						directionAnimation(L"Run", true);
					else
						directionAnimation(L"Move", true);
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
					directionAnimation(L"Run", true);
				else
					directionAnimation(L"Move", true);
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
					mState.direction = eDirection::BothY;
					mAnimator->Play(L"Idle_Down");
				}
				break;

				case ks::eDirection::BothX:
				{
					mState.direction = eDirection::Up;
					mState.situation = eSituation::Run;


					if (mbRunning)
							directionAnimation(L"Run", true);
						else
							directionAnimation(L"Move", true);
				}
				break;
				}
			}
			mStatus->SetStateInfo(mState);
		}
#pragma endregion



#pragma region Ű ������ �ö�ö�  (None, Idle, Sit, Run ���¿����� ����)
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
					break;
				case ks::eDirection::UpRight:
				{
					mState.direction = eDirection::Up;
					mStatus->SetStateInfo(mState);
					if (mbRunning)
						directionAnimation(L"Run", true);
					else
						directionAnimation(L"Move", true);
				}
				break;
				case ks::eDirection::DownRight:
				{
					mState.direction = eDirection::Down;
					mStatus->SetStateInfo(mState);
					if (mbRunning)
						directionAnimation(L"Run", true);
					else
						directionAnimation(L"Move", true);
				}
				break;
				case ks::eDirection::BothX:
				{
					mState.direction = eDirection::Left;
					mStatus->SetStateInfo(mState);
					if (mbRunning)
						directionAnimation(L"Run", true);
					else
						directionAnimation(L"Move", true);
				}
				break;
				case ks::eDirection::BothY:
				{
					mState.direction = eDirection::Right;
					mStatus->SetStateInfo(mState);

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
					break;
				case ks::eDirection::UpLeft:
				{
					mState.direction = eDirection::Up;
					mStatus->SetStateInfo(mState);
					if (mbRunning)
						directionAnimation(L"Run", true);
					else
						directionAnimation(L"Move", true);
				}
				break;
				case ks::eDirection::DownLeft:
				{
					mState.direction = eDirection::Down;
					mStatus->SetStateInfo(mState);
					if (mbRunning)
						directionAnimation(L"Run", true);
					else
						directionAnimation(L"Move", true);
				}
				break;
				case ks::eDirection::BothX:
				{
					mState.direction = eDirection::Right;
					mStatus->SetStateInfo(mState);
					if (mbRunning)
						directionAnimation(L"Run", true);
					else
						directionAnimation(L"Move", true);
				}
				break;
				case ks::eDirection::BothY:
				{
					mState.direction = eDirection::Left;
					mStatus->SetStateInfo(mState);

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
					break;
				case ks::eDirection::DownLeft:
				{
					mState.direction = eDirection::Left;
					mStatus->SetStateInfo(mState);
					if (mbRunning)
						directionAnimation(L"Run", true);
					else
						directionAnimation(L"Move", true);
				}
				break;
				case ks::eDirection::DownRight:
				{
					mState.direction = eDirection::Right;
					mStatus->SetStateInfo(mState);
					if (mbRunning)
						directionAnimation(L"Run", true);
					else
						directionAnimation(L"Move", true);
				}
				break;
				case ks::eDirection::BothY:
				{
					mState.direction = eDirection::Up;
					mStatus->SetStateInfo(mState);
					if (mbRunning)
						directionAnimation(L"Run", true);
					else
						directionAnimation(L"Move", true);
				}
				break;
				case ks::eDirection::BothX:
				{
					mState.direction = eDirection::Down;
					mStatus->SetStateInfo(mState);
					
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
					break;
				case ks::eDirection::UpLeft:
				{
					mState.direction = eDirection::Left;
					mStatus->SetStateInfo(mState);
					if (mbRunning)
						directionAnimation(L"Run", true);
					else
						directionAnimation(L"Move", true);
				}
				break;
				case ks::eDirection::UpRight:
				{
					mState.direction = eDirection::Right;
					mStatus->SetStateInfo(mState);
					if (mbRunning)
						directionAnimation(L"Run", true);
					else
						directionAnimation(L"Move", true);
				}
				break;
				case ks::eDirection::BothY:
				{
					mState.direction = eDirection::Down;
					mStatus->SetStateInfo(mState);
					if (mbRunning)
						directionAnimation(L"Run", true);
					else
						directionAnimation(L"Move", true);
				}
				break;
				case ks::eDirection::BothX:
				{
					mState.direction = eDirection::Up;
					mStatus->SetStateInfo(mState);

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
			if (mPlayerState.skil == eSkil::Evade)
				return;
			mPlayerState.skil = eSkil::Evade;
			mPlayer->SetPlayer(mPlayerState);
			mState.situation = eSituation::Skil;
			mStatus->SetStateInfo(mState);
			directionAnimation(L"Evade", false, true);			
			mCheakTime = 0.f;
			miRef = 0;
		}

		//���� Ű
		if (Input::GetKeyDown(eKeyCode::LBTN))
		{
			if (mState.situation == eSituation::Attack || mState.situation == eSituation::Skil
				|| mState.situation == eSituation::Continue)
				return;




			mPlayerState = mPlayer->GetPlayer();
			mPlayer->SetPlayer(mPlayerState);


#pragma region �⺻ ���� ���� �ִϸ��̼�
			switch (mPlayerState.weapon)
			{
			case ks::eWeapon::None:
			{
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
					directionAnimation(L"Attack1_Sword", false);
					attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_1, 0.2f);	
				}
				else if (miRef == 1)
				{
					directionAnimation(L"Attack2_Sword", false);
					attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_2, 0.2f);
				}
				else if (miRef == 2)
				{
					directionAnimation(L"Attack1_Sword", false);
					attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_1, 0.2f);
				}
				else if (miRef == 3)
				{
					directionAnimation(L"Attack2_Sword", false);
					attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_2, 0.2f);
				}
				else if (miRef == 4)
				{
					directionAnimation(L"Attack3_Sword", false);
				}

				if (miRef >= 5)
					return;
				++miRef;
			}
			break;
			case ks::eWeapon::Bow:
			{
				angleDirection();
				mState.situation = eSituation::Attack;
				directionAnimation(L"Attack_Stand_Bow", false);
				attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_1, 0.2f);

				//PlayerMissile* mAttack = object::Instantiate<PlayerMissile>(eLayerType::Player_Effect);
				//mPlayerState.skil = eSkil::Attack;
				//mPlayerState.progress = eProgress::Step_1;
				//mPlayer->SetPlayer(mPlayerState);
				//
				////mAttack->SetDirection(mState.direction);
				////mAttack->SetCooldownTime(2.2f);
				//mAttack->SetTarget(mPlayer);
				//mAttack->GetComponent<Transform>()->SetPosition(mTransform->GetPosition());
				//mAttack->SetDirection(mTransform->GetDirection());								
			}

				break;
			case ks::eWeapon::Staff:
				mbAttackWalk = true;
				break;
			}

			mStatus->SetStateInfo(mState);
			mCheakTime = 0.f;

#pragma endregion 

		}


		if (Input::GetKey(eKeyCode::LBTN))
		{

#pragma region �ڵ� ���� �ִϸ��̼�
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
							directionAnimation(L"Attack1_Sword", false);
							attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_1, 0.2f);
						}
						else if (miRef == 1)
						{
							directionAnimation(L"Attack2_Sword", false);
							attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_2, 0.2f);
						}
						else if (miRef == 2)
						{
							directionAnimation(L"Attack1_Sword", false);
							attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_1, 0.2f);
						}
						else if (miRef == 3)
						{
							directionAnimation(L"Attack2_Sword", false);
							attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_2, 0.2f);
						}
						else if (miRef == 4)
						{
							directionAnimation(L"Attack3_Sword", false);

						}
						else if (miRef == 5)
						{
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
				if(mbAttackWalk &&mCargeFinsh == false)
				{
					mCheakTime += Time::DeltaTime();

					if (mCheakTime >= MIN_TIME && mCarge == false)
					{
						PlayerEffect* mAttack = object::Instantiate<PlayerEffect>(eLayerType::Player_Effect);
						mPlayerState.skil = eSkil::Attack;
						mPlayerState.progress = eProgress::Step_8;
						mPlayer->SetPlayer(mPlayerState);
						mAttack->SetTarget(mPlayer);
						mAttack->SetPlayer(mPlayerState);
						mAttack->GetComponent<Transform>()->SetPosition(mTransform->GetPosition());
						mCarge = true;
					}

					if (mCheakTime >= MAX_TIME && mCargeEffect == false)
					{
						effectDeath(eLayerType::Player_Effect);
						attackCommand(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Start, 0.6f);
						mCargeEffect = true;
					}
				}

			}
			break;
			}
#pragma endregion



		}

		if (Input::GetKeyUp(eKeyCode::LBTN))
		{

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
					if (mCheakTime < MIN_TIME)
					{
						angleDirection();
						mState.situation = eSituation::Attack;
						mStatus->SetStateInfo(mState);
						directionAnimation(L"Attack_None", false);
						attackCommandmagic(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_1, 0.45f, mCheakTime);
						effectDeath(eLayerType::Player_Effect);
						mbAttackWalk = false;
						mCarge = false;
						mCargeEffect = false;
						mCheakTime = 0.f;
					}
					else if (mCheakTime >= MIN_TIME && mCheakTime < MAX_TIME)
					{
						angleDirection();
						mState.situation = eSituation::Attack;
						mStatus->SetStateInfo(mState);
						directionAnimation(L"Attack_None", false);
						attackCommandmagic(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_1, 0.45f, mCheakTime);
						effectDeath(eLayerType::Player_Effect);
						mbAttackWalk = false;
						mCarge = false;
						mCargeEffect = false;
						mCheakTime = 0.f;
					}

					else if (mCheakTime >= MAX_TIME)
					{
						angleDirection();
						mState.situation = eSituation::Attack;
						mStatus->SetStateInfo(mState);
						directionAnimation(L"Attack_Staffcharge", false);
						attackCommandmagic(eLayerType::Player_Attack, mState.direction, eSkil::Attack, eProgress::Step_1, 0.8f, mCheakTime);
						effectDeath(eLayerType::Player_Effect);
						mbAttackWalk = false;
						mCarge = false;
						mCargeEffect = false;
						mCargeFinsh = true;
						mCheakTime = 0.f;
					}
				}

			}
			break;

			}



		}



		//��ų Ű
		if (Input::GetKeyDown(eKeyCode::RBTN))
		{


			//mPlayer->GetComponent<Camera>()->SetShock(true); //ī�޶� ����ũ ȿ��

			//mAnimator->Play(L"Charge_Staff", false);



			//directionAnimation(L"Attack_Dash", false);
			//mAnimator->Play(L"Sit_Down1", false);
			


			//mAnimator->Play(L"Move_Down", false);
			//mAnimator->GetStartEvent(L"Evade_DownLeft") = std::bind(&PlayerScript::Start, this);
			//mAnimator->GetEndEvent(L"Evade_DownLeft") = std::bind(&PlayerScript::End, this);
			//mAnimator->GetEndEvent(L"Move_Down") = std::bind(&PlayerScript::End, this);

			//mAnimator->GetEvent(L"Move_Down", 1) = std::bind(&PlayerScript::End, this);
			//mAnimator->GetCompleteEvent(L"Idle") = std::bind(&PlayerScript::Action, this);
			//mAnimator->GetEndEvent(L"Idle") = std::bind(&PlayerScript::End, this);
			//mAnimator->GetEvent(L"Idle", 1) = std::bind(&PlayerScript::End, this);

			//mState.situation = eSituation::None;
			//mStatus->SetStateInfo(mState);
		}

		//�ȱ� or �ٱ�
		if (Input::GetKeyUp(eKeyCode::LSHIFT))
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

		}

		if (Input::GetKeyDown(eKeyCode::R))
		{

			mPlayerState = mPlayer->GetPlayer();

			switch (mPlayerState.weapon)
			{
			case ks::eWeapon::None:
				mPlayerState.weapon = eWeapon::Sword;
				break;
			case ks::eWeapon::Sword:
				mPlayerState.weapon = eWeapon::Bow;
				break;
			case ks::eWeapon::Bow:
				mPlayerState.weapon = eWeapon::Staff;
				break;
			case ks::eWeapon::Staff:
				mPlayerState.weapon = eWeapon::None;
				break;
			}

			mPlayer->SetPlayer(mPlayerState);
		}



		if (Input::GetKeyDown(eKeyCode::LBTN))
		{



		}

		if (Input::GetKeyDown(eKeyCode::RBTN))
		{

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


		mCheakTime;


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

		//���� ������ ���� atan2 �Լ��� ���� ���� (180~ -180)���� ������
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

		//���⺤�ͷ� ��ġ Ȯ��		
			//��ǥ 0�� �ȵǼ� �������� 4������ �ȳ��� �ذ� �ؾ���
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
			mPlayer->SetPlayer(mPlayerState);

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
		mPlayer->SetPlayer(mPlayerState);

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

	void PlayerScript::OnCollisionEnter(Collider2D* collider)
	{
		if (dynamic_cast<Snake_Green*>(collider->GetOwner()))
		{
			int a = 0;
		}
		if (dynamic_cast<Forest_Fairy*>(collider->GetOwner()))
		{
			int a = 0;
		}

		if (dynamic_cast<MonsterMissile*>(collider->GetOwner()))
		{
			int a = 0;
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
			}
				break;
			case ks::enums::eGroundStage::Ground5:
			{
				Stage1_1Move* stge = (Stage1_1Move*)collider->GetOwner();
				stge->SetFedeEffect(true);
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


