#include "ksGoldBox.h"
#include "ksSpriteRenderer.h"
#include "ksMaterial.h"
#include "ksMesh.h"
#include "ksResources.h"
#include "ksTransform.h"
#include "ksShader.h"
#include "ksInventory.h"
#include "ksAudioClip.h"
#include "ksPlayerItem.h"
#include "ksObject.h"




#include "ksInput.h"
#include "ksTime.h"


namespace ks
{

	GoldBox::GoldBox()
		: m_bAniChange(false)
		, mShakeTime(0.0f)
		, m_bBoxItemCteate(false)
		, m_fTime(0.f)
	{

		mTransform = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>();

		loadSound();
		loadAnimation();


		SpriteRenderer* sr = AddComponent<SpriteRenderer>();


		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"WeaponUIMaterial");
		sr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);
	}

	GoldBox::~GoldBox()
	{
	}

	void GoldBox::Initalize()
	{
		mUiPos = mTransform->GetPosition();

		switch (m_eBoxType)
		{
		case e_BoxType::Gold:
			goldSound();
			mAnimator->Play(L"Gold_Box_Idle", true);
			break;
		case e_BoxType::Platinum:
			PlatinumSound();
			mAnimator->Play(L"Platinum_Box_Idle", true);
			break;
		}
		
		


		GameObject::Initalize();
	}

	void GoldBox::Update()
	{

		if (m_bAniChange)
		{
		

			switch (m_eBoxType)
			{
			case e_BoxType::Gold:
				mAnimator->Play(L"Gold_Box_Open", false);
				break;
			case e_BoxType::Platinum:
				mAnimator->Play(L"Platinum_Box_Open", false);
				break;
			}
			m_bAniChange = false;
			m_bBoxItemCteate = true;
		}

		if (m_bBoxShake)
		{
			boxStartShake();
		}

		if (m_bBoxItemCteate)
		{
			m_fTime += Time::DeltaTime();
			if (m_fTime >= 0.8f)
			{
				createMpItem();
				createHpItem();
				createSword();
				m_bBoxItemCteate = false;
				m_fTime = 0.f;
				m_bOpenFinsh = true;
			}			
		}




		UIBase::Update();
	}

	void GoldBox::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void GoldBox::Render()
	{
		GameObject::Render();
	}


	void GoldBox::loadAnimation()
	{
		std::shared_ptr<Texture> goldbox = Resources::Load<Texture>(L"Gold_Box", L"UI\\Gold_Box.png");
		std::shared_ptr<Texture> platinumbox = Resources::Load<Texture>(L"Platinum_Box", L"UI\\Platinum_Box.png");



		mNumbers.push_back(2);
		CreateAnimation(L"Gold_Box_Idle", goldbox, mAnimator, Vector2(96.0f, 96.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();

		mNumbers.push_back(2);
		mNumbers.push_back(5);
		mNumbers.push_back(8);
		mNumbers.push_back(11);
		CreateAnimation(L"Gold_Box_Open", goldbox, mAnimator, Vector2(96.0f, 96.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();


		mNumbers.push_back(0);
		CreateAnimation(L"Platinum_Box_Idle", platinumbox, mAnimator, Vector2(96.0f, 96.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();


		mNumbers.push_back(0);
		mNumbers.push_back(3);
		mNumbers.push_back(6);
		mNumbers.push_back(9);
		CreateAnimation(L"Platinum_Box_Open", platinumbox, mAnimator, Vector2(96.0f, 96.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();


	}

	void GoldBox::CreateAnimation(const std::wstring& name, std::shared_ptr<Texture> texture, Animator* animaotr, Vec2 scale, Vector2 offset, std::vector<UINT> numbers, float duration)
	{
		// 이중 포문 		
		Vec2 value = Vec2(texture->GetWidth() / scale.x, texture->GetHeight() / scale.y);
		UINT Col = (UINT)value.x;					//3개?
		UINT Row = (UINT)value.y;					//10개?

		UINT textureeLegth = (UINT)(value.x * value.y);		//총 개수 30개

		//이중 포문 이건 10행
		for (UINT i = 0; i < Row; i++)
		{
			//이중 포문 이건 3열
			for (UINT j = 0; j < Col; j++)
			{
				Sprite animation;

				animation.AnimationName = name;
				animation.atlasSize = scale;
				animation.duration = duration;
				animation.leftTop = Vec2(j * scale.x, i * scale.y);
				animation.offset = offset;
				animation.size = scale;


				mSvaeSprite.push_back(animation);
			}
		}

		for (size_t i = 0; i < numbers.size(); i++)
		{
			std::vector<UINT>::iterator iter = numbers.begin();

			mSprites.push_back(mSvaeSprite[iter[i]]);
		}


		for (size_t i = 0; i < mSprites.size(); i++)
		{
			mSprites[i].leftTop = Vector2((mSprites[i].leftTop.x / texture->GetWidth()), (mSprites[i].leftTop.y) / texture->GetHeight());
			mSprites[i].size = Vector2(mSprites[i].size.x / texture->GetWidth(), mSprites[i].size.y / texture->GetHeight());
			mSprites[i].offset = mSprites[i].offset;
			mSprites[i].duration = mSprites[i].duration;
			mSprites[i].atlasSize = Vector2(400.0f / texture->GetWidth(), 400.0f / texture->GetHeight());
			mSprites[i].AnimationName = mSprites[i].AnimationName;
		}



		animaotr->CreateAfter(mSprites, texture);
		mSvaeSprite.clear();
		mSprites.clear();


	}

	void GoldBox::loadSound()
	{
		std::shared_ptr<AudioClip> Box_Open = Resources::Load<AudioClip>
			(L"Box_Open", L"D:\\50\\Resources\\Sound\\Box_Open.ogg");

		std::shared_ptr<AudioClip> Platinum_Box = Resources::Load<AudioClip>
			(L"Platinum_Box", L"D:\\50\\Resources\\Sound\\Platinum_Box.ogg");

		std::shared_ptr<AudioClip> Gold_Box = Resources::Load<AudioClip>
			(L"Gold_Box", L"D:\\50\\Resources\\Sound\\Gold_Box.ogg");


	}

	void GoldBox::boxOpenSound()
	{
		std::shared_ptr<AudioClip> sound = Resources::Find<AudioClip>(L"Box_Open");
		sound->SetLoop(false);
		sound->Play();
	}

	void GoldBox::PlatinumSound()
	{
		std::shared_ptr<AudioClip> sound = Resources::Find<AudioClip>(L"Platinum_Box");
		sound->SetLoop(false);
		sound->Play(3.0f);
	}

	void GoldBox::goldSound()
	{
		std::shared_ptr<AudioClip> sound = Resources::Find<AudioClip>(L"Gold_Box");
		sound->SetLoop(false);
		sound->Play(3.0f);
	}

	void GoldBox::boxStartShake()
	{
		mShakePos = mTransform->GetPosition();
		mShakeTime += Time::DeltaTime();

		if (mShakeTime >= 0.5f)
		{
			mShakeTime = 0.0f;
			m_bBoxShake = false;
			m_bAniChange = true;
		}

		if (!m_bOnceCheak)
		{
			if (mTransform != nullptr)
			{				
				boxOpenSound();
				mShakePos = mTransform->GetPosition();
				mFixPos = Vec3::Zero;
				m_bOnceCheak = true;

			}
		}
		else
		{

			if (mFixPos.x < 0.2f)
			{
				mShakePos.x += 50.f * Time::DeltaTime();
				mFixPos.x += 50.f * Time::DeltaTime();
			}
			else if (mFixPos.x > 0.2f)
			{
				mShakePos.x -= 50.f * Time::DeltaTime();
				mFixPos.x -= 50.f * Time::DeltaTime();
			}

			mTransform->SetPosition(mShakePos);
		}



	}

	void GoldBox::createSword()
	{

		PlayerItem* Legendmp = object::Instantiate<PlayerItem>(eLayerType::Shop_Item);
		Legendmp->SetName(L"Box_Item_Sword");
		Legendmp->SetTarget(mTarget);
		Legendmp->SetShopItem(true);
		Legendmp->IsBoxItem(true);
		Legendmp->ItemUnBoxing(true);
		Legendmp->SetPlayerItem(eItem::Legend_Sword);


		Collider2D* mpcollider = Legendmp->AddComponent<Collider2D>();
		mpcollider->SetType(eColliderType::Rect);
		mpcollider->SetSize(Vector2(0.07f, 0.09f));

		Transform* mptr = Legendmp->GetComponent<Transform>();
		mptr->SetPosition(mUiPos);
		mptr->SetScale(Vector3(11.0f, 11.0f, 1.0f));

		Legendmp->Initalize();
	

	}

	void GoldBox::createHpItem()
	{
		PlayerItem* Legendmp = object::Instantiate<PlayerItem>(eLayerType::Shop_Item);
		Legendmp->SetName(L"Box_Item_Hp");
		Legendmp->SetTarget(mTarget);
		Legendmp->SetShopItem(true);
		Legendmp->IsBoxItem(true);
		Legendmp->ItemUnBoxing(true);
		Legendmp->SetFreeItem(true);

		Legendmp->SetPlayerItem(eItem::Hp);


		Collider2D* mpcollider = Legendmp->AddComponent<Collider2D>();
		mpcollider->SetType(eColliderType::Rect);
		mpcollider->SetSize(Vector2(0.07f, 0.09f));

		Transform* mptr = Legendmp->GetComponent<Transform>();
		mptr->SetPosition(mUiPos);
		mptr->SetScale(Vector3(11.0f, 11.0f, 1.0f));

		Legendmp->Initalize();


	}

	void GoldBox::createMpItem()
	{
		PlayerItem* Legendmp = object::Instantiate<PlayerItem>(eLayerType::Shop_Item);
		Legendmp->SetName(L"Box_Item_Mp");
		Legendmp->SetTarget(mTarget);
		Legendmp->SetShopItem(true);
		Legendmp->IsBoxItem(true);
		Legendmp->ItemUnBoxing(true);
		Legendmp->SetFreeItem(true);

		Legendmp->SetPlayerItem(eItem::MP);


		Collider2D* mpcollider = Legendmp->AddComponent<Collider2D>();
		mpcollider->SetType(eColliderType::Rect);
		mpcollider->SetSize(Vector2(0.07f, 0.09f));

		Transform* mptr = Legendmp->GetComponent<Transform>();
		mptr->SetPosition(mUiPos);
		mptr->SetScale(Vector3(11.0f, 11.0f, 1.0f));

		Legendmp->Initalize();


	}

}
