#include "ksMonster_Trap_Line.h"
#include "ksTransform.h"
#include "ksSpriteRenderer.h"
#include "ksResources.h"
#include "ksTexture.h"
#include "ksMaterial.h"
#include "ksMesh.h"
#include "ksAnimator.h"
#include "ksTime.h"
#include "ksCollider2D.h"

#include "ksScene.h"
#include "ksSceneManager.h"
#include "ksAudioClip.h"
#include "ksInput.h"


#define PI 3.1415926535f


namespace ks
{

	Monster_Trap_Line::Monster_Trap_Line()
	{

		mTransform = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>();



		std::shared_ptr<Texture> bow1 = Resources::Load<Texture>(L"BossFlime_Skil_Line", L"Attack\\BossFlime_Skil_Line.png");
		


		SpriteRenderer* sr = AddComponent<SpriteRenderer>();


		std::shared_ptr<Material> mr = Resources::Find<Material>(L"TrapMaterial");
		mr->SetTexture(bow1);
		sr->SetMaterial(mr);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);

		loadAnimation();
		
		
	}

	Monster_Trap_Line::~Monster_Trap_Line()
	{
	}

	void Monster_Trap_Line::Initalize()
	{

		GameObject::Initalize();
	}

	void Monster_Trap_Line::Update()
	{



		
		switch (mMonLine)
		{
		case Monster_Line::Flime_Missile:
		{
			mTime += Time::DeltaTime();
			if (mTime >= 0.9f)
			{
				if (mStep == eStep::None)
				{
					soundTrapAttack();
					mCollider = AddComponent<Collider2D>();

					mCollider->SetType(eColliderType::Rect);
					mCollider->SetSize(Vec2(0.2f, 0.18f));
					mCollider->SetCenter(Vec2(0.14f, 0.27f));
					Initalize();

					mTransform->SetScale(Vec3(6.0f, 6.0f, 2.0f));
					mAnimator->Play(L"Attack_Trap", false);
					mStep = eStep::Step_1;
				}

				if (mStep == eStep::Step_1)
				{
					//2.5段
					if (mTime >= 4.0f)
					{
						this->Death();
						mTime = 0.f;
					}
				}

			}
		}
		break;

		case Monster_Line::Flime_Trap:
		{
			mTime += Time::DeltaTime();
			if (mTime >= 0.9f)
			{
				if (mStep == eStep::None)
				{
					soundTrapAttack();
					mCollider = AddComponent<Collider2D>();

					mCollider->SetType(eColliderType::Rect);
					mCollider->SetSize(Vec2(0.18f, 0.16f));
					mCollider->SetCenter(Vec2(0.14f, 0.27f));
					Initalize();

					mTransform->SetScale(Vec3(5.2f, 5.2f, 2.0f));
					mAnimator->Play(L"Attack_Trap", false);
					mStep = eStep::Step_1;
				}

				if (mStep == eStep::Step_1)
				{
					//2.5段
					if (mTime >= 4.0f)
					{
						this->Death();
						mTime = 0.f;
					}
				}

			}
		}
		break;
		case Monster_Line::Ent_Trap:
		{
			mTime += Time::DeltaTime();
			if (mTime >= 1.2f)
			{
				if (mStep == eStep::None)
				{
					mCollider = AddComponent<Collider2D>();

					mCollider->SetType(eColliderType::Rect);
					mCollider->SetSize(Vec2(0.21f, 0.18f));
					mCollider->SetCenter(Vec2(0.14f, 0.27f));
					Initalize();

					mTransform->SetScale(Vec3(8.0f, 8.0f, 2.0f));
					mAnimator->Play(L"Attack_Trap", false);
					soundTrapAttack();
					mStep = eStep::Step_1;
				}

				if (mStep == eStep::Step_1)
				{
					//2.5段
					if (mTime >= 4.0f)
					{
						this->Death();
						mTime = 0.f;
					}
				}

			}



		}
		break;
		case Monster_Line::Ent_Earthquake:
		{
			mTime += Time::DeltaTime();
			if (mTime >= 2.0f)
			{
				if (mStep == eStep::None)
				{
					mCollider = AddComponent<Collider2D>();

					mCollider->SetType(eColliderType::Rect);
					mCollider->SetSize(Vec2(0.78f, 0.65f));
					mCollider->SetCenter(Vec2(0.14f, 0.27f));
					Initalize();

					mTransform->SetScale(Vec3(15.0f, 15.0f, 2.0f));
					mAnimator->Play(L"Attack_Ent_Trap", false);
					mStep = eStep::Step_1;
					mTime = 0.f;
				}

			}
			if (mStep == eStep::Step_1)
			{
				//2.5段
				if (mTime >= 0.5f)
				{

					mStep = eStep::Step_2;
					mCollider->SetSize(Vec2(0.0f, 0.0f));
					mTime = 0.f;
				}
			}
			if (mStep == eStep::Step_2)
			{
				//2.5段
				if (mTime >= 1.5f)
				{
					this->Death();
					mTime = 0.f;
				}
			}




		}
		break;
		}



		

		//mTransform->SetPosition(Vec3(35.f, 0.f, 2.0f));

		/*if (Input::GetKeyDown(eKeyCode::N_1))
		{
			ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Trap_Line];
			renderer::Trap data;

			data.linecolor = test;


			cb->Bind(&data);
			cb->SetPipline(eShaderStage::VS);
			cb->SetPipline(eShaderStage::PS);
		}
		if (Input::GetKeyDown(eKeyCode::N_2))
		{
			ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Trap_Line];
			renderer::Trap data;

			data.linecolor = TEST;


			cb->Bind(&data);
			cb->SetPipline(eShaderStage::VS);
			cb->SetPipline(eShaderStage::PS);
		}*/

		GameObject::Update();
	}

	void Monster_Trap_Line::FixedUpdate()
	{


		GameObject::FixedUpdate();
	}

	void Monster_Trap_Line::Render()
	{
		GameObject::Render();
	}

	void Monster_Trap_Line::Lineinterval(float interval)
	{
		Vec3 pos = mTransform->GetPosition();

		float fRadian = (mDegree * PI) / 180.f;



		pos.x = mTransform->GetPosition().x - 0.1f + interval * cosf(fRadian);
		pos.y = mTransform->GetPosition().y - 0.7f - interval * sinf(fRadian);



		mTransform->SetPosition(pos);
	}

	void Monster_Trap_Line::loadAnimation()
	{

		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"skill_flime2", L"Attack\\skill_flime2.png");
		
		
		mNumbers.push_back(0);
		mNumbers.push_back(1);
		mNumbers.push_back(2);
		mNumbers.push_back(3);
		mNumbers.push_back(4);
		mNumbers.push_back(5);
		mNumbers.push_back(6);
		mNumbers.push_back(7);
		mNumbers.push_back(8);
		mNumbers.push_back(9);
		mNumbers.push_back(10);
		mNumbers.push_back(11);
		mNumbers.push_back(12);
		mNumbers.push_back(13);
		CreateAnimation(L"Attack_Trap", texture, mAnimator, Vector2(192.0f, 192.0f), Vec2::Zero, mNumbers, 0.1f);
		mNumbers.clear();

		std::shared_ptr<Texture> enttexture = Resources::Load<Texture>(L"3Ent_6", L"Attack\\3Ent_6.png");


		mNumbers.push_back(0);
		mNumbers.push_back(1);
		mNumbers.push_back(2);
		mNumbers.push_back(3);
		mNumbers.push_back(4);
		mNumbers.push_back(5);
		mNumbers.push_back(6);
		mNumbers.push_back(7);
		mNumbers.push_back(8);
		mNumbers.push_back(9);
		mNumbers.push_back(10);
		mNumbers.push_back(11);
		mNumbers.push_back(12);
		mNumbers.push_back(13);
		mNumbers.push_back(14);
		mNumbers.push_back(15);
		CreateAnimation(L"Attack_Ent_Trap", enttexture, mAnimator, Vector2(192.0f, 192.0f), Vec2::Zero, mNumbers, 0.05f);
		mNumbers.clear();


	}

	void Monster_Trap_Line::loadSound()
	{
		std::shared_ptr<AudioClip> Flime_TrapAttack = Resources::Load<AudioClip>
			(L"Flime_Attack_Trap", L"..\\Resources\\Sound\\Flime_Attack_Trap.ogg");

	}

	void Monster_Trap_Line::soundTrapAttack()
	{
		std::shared_ptr<AudioClip> sound = Resources::Find<AudioClip>(L"Flime_Attack_Trap");
		sound->SetLoop(false);
		sound->Play();

	}





}