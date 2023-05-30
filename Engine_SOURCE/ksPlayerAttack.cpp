#include "ksPlayerAttack.h"
#include "ksTransform.h"
#include "ksSpriteRenderer.h"
#include "ksResources.h"
#include "ksTexture.h"
#include "ksMaterial.h"
#include "ksMesh.h"
#include "ksAnimator.h"
#include "ksTime.h"
#include "ksMeshRenderer.h"
#include "ksCollider2D.h"


#include "ksScene.h"
#include "ksSceneManager.h"

#include "ksInput.h"

#define MIN_TIME 0.5f
#define MAX_TIME 3.0f

#define BASIC_SCALE 7.4f								//기본 크기
#define MAX_SCALE 22.2f									//최대 크기
#define INCREMENT (MAX_SCALE - BASIC_SCALE)				//크기 증가량
#define TIME_SCALE (INCREMENT / MAX_TIME)				//초당 크기 증가량  

/*

크기 증가량 = (최대 크기 - 최소 크기)
초당 크기 증가율 = 크기 증가량 / 최대 충전 시간
크기 = 최소 크기 + (초당 크기 증가율 *  충전 시간)				(이게 필요한 충전중 크기)

크기 비율 = 최대 크기 / 최소 크기 (이건 나중에 사용)

*/



namespace ks
{

	float PlayerAttack::mSphereScale = 0.f;

	PlayerAttack::PlayerAttack()
		: mPlayer(nullptr)
		, mTransform(nullptr)
		, mAnimator(nullptr)
		, mCheakTime(0.f)
		, mCooldownTime (0.f)
		
	{


		std::shared_ptr<Texture> sword1 = Resources::Load<Texture>(L"sword1", L"Attack\\sword1.png");
		std::shared_ptr<Texture> bow1 = Resources::Load<Texture>(L"bow1", L"Attack\\bow1.png");
		std::shared_ptr<Texture> none1 = Resources::Load<Texture>(L"none1", L"Attack\\none1.png");
		std::shared_ptr<Texture> staff1 = Resources::Load<Texture>(L"staff1", L"Attack\\staff1.png");
		std::shared_ptr<Texture> Player_Effect_Staff_Finish	= Resources::Load<Texture>(L"Staff_Charge_Finish", L"Attack\\Staff_Charge_Finish.png");

		mAnimator = AddComponent<Animator>();
		mPlayerScript = AddComponent<PlayerAttackScript>();
		

		mAnimator->Create(L"Attack_sword1", sword1, Vector2(0.0f, 0.0f), Vector2(192.0f, 192.0f), Vector2::Zero, 10, 0.025f);
		mAnimator->Create(L"Attack_sword2", sword1, Vector2(0.0f, 192.0f), Vector2(192.0f, 192.0f), Vector2::Zero, 10, 0.025f);
		mAnimator->Create(L"Attack_sword3", sword1, Vector2(0.0f, 384.0f), Vector2(192.0f, 192.0f), Vector2::Zero, 10, 0.025f);
		

		mAnimator->Create(L"Attack_bow1", bow1, Vector2(0.0f, 0.0f), Vector2(50.0f, 50.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"Attack_none1", none1, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"Attack_staff1", staff1, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);

		//이펙트 효과
		mAnimator->Create(L"Effect_Charge_Finish", Player_Effect_Staff_Finish, Vector2(0.0f, 0.0f), Vector2(192.0f, 192.0f), Vector2::Zero, 30, 0.02f);



		mTransform = GetComponent<Transform>();
		

		SpriteRenderer* sr = AddComponent<SpriteRenderer>();

		

		std::shared_ptr<Material> material = Resources::Find<Material>(L"SpriteMaterial");
		sr->SetMaterial(material);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);


	}
	PlayerAttack::~PlayerAttack()
	{



	}


	void PlayerAttack::Initalize()
	{

		mCollider = GetComponent<Collider2D>();
		mCollider->SetType(eColliderType::Rect);
		mPlayerScript->SetPlayer(mPlayer);
		GameObject::Initalize();

	}
	void PlayerAttack::Update()
	{
		if (mPlayer != nullptr)
			mState = mPlayer->GetPlayer();	
		eWeapon weapon = mState.weapon;

		mCheakTime;


		switch (mState.skil)
		{
		case ks::eSkil::None:
			break;
		case ks::eSkil::Attack:
		{
			switch (mState.weapon)
			{
			case ks::eWeapon::None:
			{
				if (mState.progress == eProgress::Step_1)
				{
					mPlayerScript->SetPlayerStr(1.0f);
					mCollider->SetSize(Vec2(0.06f, 0.06f));

					bulletAnipos(Vector3(BASIC_SCALE, BASIC_SCALE, 1.0f), 1);
					dirAnimation(1.56f);
					mAnimator->Play(L"Attack_none1", false);
					mState.progress = eProgress::Step_2;
					mPlayer->SetPlayer(mState);

					mDir = mPlayer->GetComponent<Transform>()->GetDirection();
					mPos = mTransform->GetPosition();

					mDir.Normalize();
				}

				if (mState.progress == eProgress::Step_2)
				{
					mPos.x += mDir.x * 12.f * Time::DeltaTime();
					mPos.y += mDir.y * 12.f * Time::DeltaTime();

					mTransform->SetPosition(mPos);
					mState.progress = eProgress::End;
				}


				if (mState.progress == eProgress::End)
				{

					deathTime(mCooldownTime);
				}
			}
				break;
			case ks::eWeapon::Sword:
			{

				if (mState.progress == eProgress::Step_1)
				{					

					mCollider->SetSize(Vec2(0.35f, 0.35f));
					swordAnipos(Vector3(BASIC_SCALE, BASIC_SCALE, 1.0f), 7);
					dirAnimation();
					mAnimator->Play(L"Attack_sword1", false);
					mState.progress = eProgress::End;
					mPlayer->SetPlayer(mState);
				}

				if (mState.progress == eProgress::Step_2)
				{
					mCollider->SetSize(Vec2(0.35f, 0.35f));
					swordAnipos(Vector3(BASIC_SCALE, BASIC_SCALE, 1.0f), 7);
					dirAnimation();
					mAnimator->Play(L"Attack_sword2", false);
					mState.progress = eProgress::End;
					mPlayer->SetPlayer(mState);
				}

				if (mState.progress == eProgress::Step_3)
				{
					mCollider->SetSize(Vec2(0.35f, 0.35f));
					swordAnipos(Vector3(BASIC_SCALE, BASIC_SCALE, 1.0f), 7);
					dirAnimation();
					mAnimator->Play(L"Attack_sword3", false);
					mState.progress = eProgress::End;
					mPlayer->SetPlayer(mState);
				}
				if (mState.progress == eProgress::End)
				{
					
					deathTime(mCooldownTime);
				}
			}
			break;
			case ks::eWeapon::Bow:
			{
				if (mState.progress == eProgress::Step_1)
				{
					mCollider->SetSize(Vec2(0.03f, 0.03f));
					bulletAnipos(Vector3(BASIC_SCALE, BASIC_SCALE, 1.0f), 1);
					dirAnimation(1.56f);
					mAnimator->Play(L"Attack_bow1", false);
					mState.progress = eProgress::Step_2;
					mPlayer->SetPlayer(mState);

					mDir = mPlayer->GetComponent<Transform>()->GetDirection();
					mPos = mTransform->GetPosition();
										
					mDir.Normalize();

				}

				if (mState.progress == eProgress::Step_2)
				{					
					mPos.x += mDir.x * 30.f * Time::DeltaTime();
					mPos.y += mDir.y * 30.f * Time::DeltaTime();
					
					mTransform->SetPosition(mPos);
					mState.progress = eProgress::End;
				}


				if (mState.progress == eProgress::End)
				{

					deathTime(mCooldownTime);
				}

			}
				break;
			case ks::eWeapon::Staff:
			{

				if (mState.progress == eProgress::Start)
				{
					//기 완충 됬을때
					
					swordAnipos(Vector3(BASIC_SCALE + 2.3f, BASIC_SCALE + 2.3f, 1.0f), 1);
					//dirAnimation(1.56f);
					mAnimator->Play(L"Effect_Charge_Finish", false);
					mState.progress = eProgress::Step_3;	
					mPlayer->SetPlayer(mState);
				}

				if (mState.progress == eProgress::Step_3)
				{					
					
					swordAnipos(Vector3(BASIC_SCALE + 2.3f, BASIC_SCALE + 2.3f, 1.0f), 1);
					//deathTime(mCooldownTime);				
				}

				if (mState.progress == eProgress::Step_1)
				{
					if (mSphereScale <= MIN_TIME)
					{
						mCollider->SetSize(Vec2(0.06f, 0.06f));
						bulletAnipos(Vector3(BASIC_SCALE, BASIC_SCALE, 1.0f), 1);
					}
					else if (mSphereScale >= MIN_TIME && mSphereScale < MAX_TIME)
					{
						mCollider->SetSize(Vec2(0.06f + (0.006f * mSphereScale), 0.06f + (0.006f * mSphereScale)));
						float sacle = BASIC_SCALE + (TIME_SCALE * mSphereScale);
						bulletAnipos(Vector3(sacle, sacle, 1.0f), 1);
					}
					
					else if (mSphereScale >= MAX_TIME)
					{
						mCollider->SetSize(Vec2(0.06f + 0.018f, 0.06f + 0.018f));
						bulletAnipos(Vector3(MAX_SCALE, MAX_SCALE, 1.0f), 1);
					}									
					
					dirAnimation(1.56f);
					//mAnimator->Play(L"Effect_Charge_Finish", false);
					mAnimator->Play(L"Attack_staff1", false);

					mState.progress = eProgress::Step_2;
					mPlayer->SetPlayer(mState);

					mDir = mPlayer->GetComponent<Transform>()->GetDirection();
					mPos = mTransform->GetPosition();

					mDir.Normalize();
				}

				if (mState.progress == eProgress::Step_2)
				{
					mPos.x += mDir.x * 15.f * Time::DeltaTime();
					mPos.y += mDir.y * 15.f * Time::DeltaTime();

					mTransform->SetPosition(mPos);
					mState.progress = eProgress::End;					
				}


				if (mState.progress == eProgress::End)
				{					
					//mAnimator->Clear();
					deathTime(mCooldownTime);
				}
			}
				break;		
			}
		}
		break;
		case ks::eSkil::Evade:
			break;
		}





		GameObject::Update();
	}
	void PlayerAttack::FixedUpdate()
	{

		GameObject::FixedUpdate();
	}
	void PlayerAttack::Render()
	{

		GameObject::Render();
	}

	void PlayerAttack::deathTime(float time)
	{
		mCheakTime += Time::DeltaTime();
		if (mCheakTime >= time)
		{
			Scene* scene = SceneManager::GetActiveScene();

			const std::vector<GameObject*>& obj = scene->GetGameObjects(eLayerType::Player_Attack);

			for (size_t i = 0; i < obj.size(); i++)
			{
				if (obj[i] != nullptr)
				{
					obj[i]->Death();
				}
				//scene->Destroy();
			}
			mCheakTime = 0.f;
		}


	}

	void PlayerAttack::dirAnimation(float value)
	{

		Vector3 rot = mTransform->GetRotation();

		
		switch (mDirection)
		{
		case ks::eDirection::Up:
		{
			
			rot.z = float(0.0f + value);
			mTransform->SetRotation(rot);
		}
		break;
		case ks::eDirection::UpLeft:
		{
			
			rot.z = float(0.78 * 1 + value);
			mTransform->SetRotation(rot);
		}
		break;
		case ks::eDirection::Left:
		{
			rot.z = float(0.78 * 2 + value);
			mTransform->SetRotation(rot);
		}
		break;
		case ks::eDirection::DownLeft:
		{
			rot.z = float(0.78 * 3 + value);
			mTransform->SetRotation(rot);
		}
		break;
		case ks::eDirection::Down:
		{
			rot.z = float(0.78 * 4 + value);
			mTransform->SetRotation(rot);
		}
		break;
		case ks::eDirection::DownRight:
		{
			rot.z = float(0.78 * 5 + value);
			mTransform->SetRotation(rot);
		}
		break;
		case ks::eDirection::Right:
		{
			rot.z = float(0.78 * 6 + value);
			mTransform->SetRotation(rot);
		}
		break;
		case ks::eDirection::UpRight:
		{
			rot.z = float(0.78 * 7 + value);
			mTransform->SetRotation(rot);
		}
		break;
		}

		/*switch (mDir)
		{
		case ks::eDirection::Up:
		{
			rot.z = 0.0f;
			mTransform->SetRotation(rot);
		}
		break;
		case ks::eDirection::UpLeft:
		{
			rot.z = 0.5f;
			mTransform->SetRotation(rot);
		}
		break;
		case ks::eDirection::Left:
		{
			rot.z = 1.0f;
			mTransform->SetRotation(rot);
		}
		break;
		case ks::eDirection::DownLeft:
		{
			rot.z = 2.0f;
			mTransform->SetRotation(rot);
		}
		break;
		case ks::eDirection::Down:
		{
			rot.z = 3.0f;
			mTransform->SetRotation(rot);
		}
		break;
		case ks::eDirection::DownRight:
		{
			rot.z = 4.0f;
			mTransform->SetRotation(rot);
		}
		break;
		case ks::eDirection::Right:
		{
			rot.z = 5.0f;
			mTransform->SetRotation(rot);
		}
		break;
		case ks::eDirection::UpRight:
		{
			rot.z = 6.0f;
			mTransform->SetRotation(rot);
		}
		break;
		}*/




	}

	void PlayerAttack::bulletAnipos(Vector3 Scale, float offset)
	{
		switch (mDirection)
		{
		case ks::eDirection::Left:
			mTransform->SetPosition(mTransform->GetPosition() + Vector3(offset * -0.1f, 0.0f, 0.0f));
			break;
		case ks::eDirection::Right:
			mTransform->SetPosition(mTransform->GetPosition() + Vector3(offset * 0.1f, 0.0f, 0.0f));
			break;
		case ks::eDirection::Up:
			mTransform->SetPosition(mTransform->GetPosition() + Vector3(0.0f, offset * 0.1f, 0.0f));
			break;
		case ks::eDirection::Down:
			mTransform->SetPosition(mTransform->GetPosition() + Vector3(0.0f, offset * -0.1f, 0.0f));
			break;
		case ks::eDirection::UpLeft:
			mTransform->SetPosition(mTransform->GetPosition() + Vector3(offset * -0.075f, offset * 0.075f, 0.0f));
			break;
		case ks::eDirection::UpRight:
			mTransform->SetPosition(mTransform->GetPosition() + Vector3(offset * 0.075f, offset * 0.075f, 0.0f));
			break;
		case ks::eDirection::DownLeft:
			mTransform->SetPosition(mTransform->GetPosition() + Vector3(offset * -0.075f, offset * -0.075f, 0.0f));
			break;
		case ks::eDirection::DownRight:
			mTransform->SetPosition(mTransform->GetPosition() + Vector3(offset * 0.075f, offset * -0.075f, 0.0f));
			break;
		}


		mTransform->SetScale(Scale);


	}

	void PlayerAttack::swordAnipos(Vector3 Scale, float offset)
	{
		switch (mDirection)
		{
		case ks::eDirection::Left:
			mTransform->SetPosition(mPlayer->GetComponent<Transform>()->GetPosition() + Vector3(offset * -0.1f, 0.0f, 0.0f));
			break;
		case ks::eDirection::Right:
			mTransform->SetPosition(mPlayer->GetComponent<Transform>()->GetPosition() + Vector3(offset * 0.1f, 0.0f, 0.0f));
			break;
		case ks::eDirection::Up:
			mTransform->SetPosition(mPlayer->GetComponent<Transform>()->GetPosition() + Vector3(0.0f, offset * 0.1f, 0.0f));
			break;
		case ks::eDirection::Down:
			mTransform->SetPosition(mPlayer->GetComponent<Transform>()->GetPosition() + Vector3(0.0f, offset * -0.1f, 0.0f));
			break;
		case ks::eDirection::UpLeft:
			mTransform->SetPosition(mPlayer->GetComponent<Transform>()->GetPosition() + Vector3(offset * -0.075f, offset * 0.075f, 0.0f));
			break;
		case ks::eDirection::UpRight:
			mTransform->SetPosition(mPlayer->GetComponent<Transform>()->GetPosition() + Vector3(offset * 0.075f, offset * 0.075f, 0.0f));
			break;
		case ks::eDirection::DownLeft:
			mTransform->SetPosition(mPlayer->GetComponent<Transform>()->GetPosition() + Vector3(offset * -0.075f, offset * -0.075f, 0.0f));
			break;
		case ks::eDirection::DownRight:
			mTransform->SetPosition(mPlayer->GetComponent<Transform>()->GetPosition() + Vector3(offset * 0.075f, offset * -0.075f, 0.0f));
			break;
		}


		mTransform->SetScale(Scale);

	}

}




