#include "ksAfterimage.h"
#include "ksTransform.h"
#include "ksGameObject.h"
#include "ksAnimator.h"
#include "ksSpriteRenderer.h"
#include "ksMaterial.h"
#include "ksMesh.h"
#include "ksResources.h"
#include "ksTime.h"
#include "ksScene.h"
#include "ksSceneManager.h"




namespace ks
{

	float Afterimage::mTime = 0.f;
	float Afterimage::mDelayTime = 0.f;

	Afterimage::Afterimage()
		: mTransform(nullptr)
		, mAnimator(nullptr)
		, mPlayer(nullptr)

	{

		mTransform = GetComponent<Transform>();

		mAnimator = AddComponent<Animator>();

		mTexture = Resources::Load<Texture>(L"Player_State", L"Player_State.png");


		mAnimator->Create(L"Evade_DownLeft", mTexture, Vector2(0.0f, 4000.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 6, 0.075f);
		mAnimator->Create(L"Evade_Down", mTexture, Vector2(0.0f, 4100.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 6, 0.075f);
		mAnimator->Create(L"Evade_DownRight", mTexture, Vector2(0.0f, 4200.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 6, 0.075f);
		mAnimator->Create(L"Evade_Left", mTexture, Vector2(0.0f, 4300.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 6, 0.075f);
		mAnimator->Create(L"Evade_Right", mTexture, Vector2(0.0f, 4400.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 6, 0.075f);
		mAnimator->Create(L"Evade_UpLeft", mTexture, Vector2(0.0f, 4500.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 6, 0.075f);
		mAnimator->Create(L"Evade_Up", mTexture, Vector2(0.0f, 4600.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 6, 0.075f);
		mAnimator->Create(L"Evade_UpRight", mTexture, Vector2(0.0f, 4700.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 6, 0.075f);

		mAnimator->Create(L"Attack1_Sword_DownLeft", mTexture, Vector2(0.0f, 6100.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		mAnimator->Create(L"Attack2_Sword_DownLeft", mTexture, Vector2(200.0f, 6100.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		mAnimator->Create(L"Attack3_Sword_DownLeft", mTexture, Vector2(400.0f, 6100.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		mAnimator->Create(L"Attack4_Sword_DownLeft", mTexture, Vector2(0.0f, 6200.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);

		mAnimator->Create(L"Attack1_Sword_Down", mTexture, Vector2(200.0f, 6200.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		mAnimator->Create(L"Attack2_Sword_Down", mTexture, Vector2(400.0f, 6200.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		mAnimator->Create(L"Attack3_Sword_Down", mTexture, Vector2(0.0f, 6300.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		mAnimator->Create(L"Attack4_Sword_Down", mTexture, Vector2(200.0f, 6300.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);

		mAnimator->Create(L"Attack1_Sword_DownRight", mTexture, Vector2(400.0f, 6300.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		mAnimator->Create(L"Attack2_Sword_DownRight", mTexture, Vector2(0.0f, 6400.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		mAnimator->Create(L"Attack3_Sword_DownRight", mTexture, Vector2(200.0f, 6400.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		mAnimator->Create(L"Attack4_Sword_DownRight", mTexture, Vector2(400.0f, 6400.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);

		mAnimator->Create(L"Attack1_Sword_Right", mTexture, Vector2(0.0f, 6500.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		mAnimator->Create(L"Attack2_Sword_Right", mTexture, Vector2(200.0f, 6500.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		mAnimator->Create(L"Attack3_Sword_Right", mTexture, Vector2(400.0f, 6500.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		mAnimator->Create(L"Attack4_Sword_Right", mTexture, Vector2(0.0f, 6600.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);

		mAnimator->Create(L"Attack1_Sword_Left", mTexture, Vector2(200.0f, 6600.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		mAnimator->Create(L"Attack2_Sword_Left", mTexture, Vector2(400.0f, 6600.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		mAnimator->Create(L"Attack3_Sword_Left", mTexture, Vector2(0.0f, 6700.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		mAnimator->Create(L"Attack4_Sword_Left", mTexture, Vector2(200.0f, 6700.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);

		mAnimator->Create(L"Attack1_Sword_UpLeft", mTexture, Vector2(400.0f, 6700.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		mAnimator->Create(L"Attack2_Sword_UpLeft", mTexture, Vector2(0.0f, 6800.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		mAnimator->Create(L"Attack3_Sword_UpLeft", mTexture, Vector2(200.0f, 6800.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		mAnimator->Create(L"Attack4_Sword_UpLeft", mTexture, Vector2(400.0f, 6800.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);

		mAnimator->Create(L"Attack1_Sword_Up", mTexture, Vector2(0.0f, 6900.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		mAnimator->Create(L"Attack2_Sword_Up", mTexture, Vector2(200.0f, 6900.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		mAnimator->Create(L"Attack3_Sword_Up", mTexture, Vector2(400.0f, 6900.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		mAnimator->Create(L"Attack4_Sword_Up", mTexture, Vector2(0.0f, 7000.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);

		mAnimator->Create(L"Attack1_Sword_UpRight", mTexture, Vector2(200.0f, 7000.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		mAnimator->Create(L"Attack2_Sword_UpRight", mTexture, Vector2(400.0f, 7000.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		mAnimator->Create(L"Attack3_Sword_UpRight", mTexture, Vector2(0.0f, 7100.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		mAnimator->Create(L"Attack4_Sword_UpRight", mTexture, Vector2(200.0f, 7100.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);


		SpriteRenderer* sr = AddComponent<SpriteRenderer>();

		std::shared_ptr<Material> material = Resources::Find<Material>(L"AfterimageMaterial");
		sr->SetMaterial(material);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);

	}
	Afterimage::~Afterimage()
	{

	}

	void Afterimage::Initalize()
	{

		GameObject::Initalize();
	}

	void Afterimage::Update()
	{
		if (mprogress == progress::Start)
		{
			mAnimator->Play(msprite.AnimationName, false);
			mprogress = progress::Step_1;
		}

		if (mprogress == progress::Step_1)
		{
			mTime += Time::DeltaTime();
			if (mTime >= 0.15f)
			{
				this->Death();
				mTime = 0.f;
			}
		}

		GameObject::Update();
	}

	void Afterimage::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void Afterimage::Render()
	{

		GameObject::Render();
	}

	void Afterimage::PlayAfterimage(Sprite sprite, Vec3 pos)
	{
		if (mPlayer)
		{
			mTransform->SetPosition(pos);
			mTransform->SetScale(mPlayer->GetComponent<Transform>()->GetScale());
		}

		msprite = sprite;
		mprogress = progress::Start;

	}


}
