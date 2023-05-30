#include "ksPlayerEffect.h"
#include "ksTransform.h"
#include "ksSpriteRenderer.h"
#include "ksResources.h"
#include "ksTexture.h"
#include "ksMaterial.h"
#include "ksMesh.h"
#include "ksAnimator.h"

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

	PlayerEffect::PlayerEffect()
		: mPlayer(nullptr)
		, mTransform(nullptr)
		, mAnimator(nullptr)
	{

		mAnimator = AddComponent<Animator>();
		mTransform = GetComponent<Transform>();



		std::shared_ptr<Texture> Player_Effect_Staff 
			= Resources::Load<Texture>(L"Staff_Charge", L"Attack\\Staff_Charge.png");





		mAnimator->Create(L"Effect_Staff_Charge", Player_Effect_Staff
			, Vector2(0.0f, 0.0f), Vector2(192.0f, 192.0f), Vector2::Zero, 30, 0.1f);

		SpriteRenderer* sr = AddComponent<SpriteRenderer>();

		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"SpriteMaterial");
		sr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);


	}

	PlayerEffect::~PlayerEffect()
	{
	}

	void PlayerEffect::Initalize()
	{


		GameObject::Initalize();
	}

	void PlayerEffect::Update()
	{
		


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
				
			}
			break;
			case ks::eWeapon::Sword:
			{
			
			}
			break;
			case ks::eWeapon::Bow:
			{			

			}
			break;
			case ks::eWeapon::Staff:
			{

				if (mState.progress == eProgress::Step_8)
				{
					mTransform->SetScale(Vec3(BASIC_SCALE - 0.7f, BASIC_SCALE - 0.7f, 1.0f));
					mTransform->SetPosition(mPlayer->GetComponent<Transform>()->GetPosition() + Vector3(0.0f, -0.5f, 0.0f));
					
					mAnimator->Play(L"Effect_Staff_Charge", true);
					mState.progress = eProgress::Step_9;
				}


				if (mState.progress == eProgress::Step_9)
				{
					mTransform->SetScale(Vec3(BASIC_SCALE - 0.7f, BASIC_SCALE - 0.7f, 1.0f));
					mTransform->SetPosition(mPlayer->GetComponent<Transform>()->GetPosition() + Vector3(0.0f, -0.5f, 0.0f));
					
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

	void PlayerEffect::FixedUpdate()
	{


		GameObject::FixedUpdate();
	}

	void PlayerEffect::Render()
	{


		GameObject::Render();
	}

}