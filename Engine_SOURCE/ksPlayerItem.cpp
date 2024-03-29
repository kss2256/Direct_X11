#include "ksPlayerItem.h"
#include "ksSpriteRenderer.h"
#include "ksMaterial.h"
#include "ksMesh.h"
#include "ksResources.h"
#include "ksTransform.h"
#include "ksShader.h"
#include "ksInventory.h"

#include "ksInput.h"
#include "ksTime.h"

namespace ks
{


	PlayerItem::PlayerItem()
		: mItemChangeCheak(false)
		, mItemUnlock(false)
		, mPlayerItem(eItem::None)
		, m_bShopItem(false)
		, m_BoxItemFixPos(false)
	{

		mTransform = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>();

		loadAnimation();


		SpriteRenderer* sr = AddComponent<SpriteRenderer>();


		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"WeaponUIMaterial");
		sr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);
	}



	PlayerItem::~PlayerItem()
	{


	}

	void PlayerItem::Initalize()
	{	

		if (mWeaponSlot)
		{
			mUiPos = mTransform->GetPosition();
		}
		
		switch (mPlayerItem)
		{
		case ks::eItem::None:
			break;
		case ks::eItem::Sword:
		{		
			mAnimator->Play(L"Sword", true);
		}
			break;
		case ks::eItem::Staff:
		{
			mAnimator->Play(L"Staff", true);
		}
			break;
		case ks::eItem::Bow:
		{
			mAnimator->Play(L"Bow", true);
		}
			break;
		case ks::eItem::Legend_Bow:
		{
			mAnimator->Play(L"Legend_Bow", true);
		}
		break;
		case ks::eItem::Legend_Staff:
		{
			mAnimator->Play(L"Legend_Staff", true);
		}
		break;
		case ks::eItem::Legend_Sword:
		{
			mAnimator->Play(L"Legend_Sword", true);
		}
		break;
		case ks::eItem::Hp:
		{
			mAnimator->Play(L"hp_Recovery", true);
		}
		break;
		case ks::eItem::MP:
		{
			mAnimator->Play(L"Mp_Recovery", true);
		}
		break;
		case ks::eItem::Dark:
		{
			mUiPos = mTransform->GetPosition();
			mAnimator->Play(L"Dark_Skil", true);
		}
		break;
		case ks::eItem::Ice:
		{
			mUiPos = mTransform->GetPosition();
			mAnimator->Play(L"Ice_Skil", true);
		}
		break;
		case ks::eItem::Barrier:
		{
			mUiPos = mTransform->GetPosition();
			mAnimator->Play(L"Barrier_Skil", true);
		}
		break;
		case ks::eItem::Lighting:
		{
			mUiPos = mTransform->GetPosition();
			mAnimator->Play(L"Lighting_Skil", true);
		}
		break;

		}

		if (m_BoxItem)
		{			
			if(m_BoxItemFixPos)
			{

				if(GetName() == L"Box_Item_Sword")					
				{
					mUiPos = mTransform->GetPosition();
					mFinalPos = mUiPos;
					mJumpPos = mUiPos;
					mJumpPos.y += 1.0f;
					mJumpPos.x -= 0.8f;

					mNomarlizeUp = mJumpPos - mFinalPos;
					mNomarlizeUp.Normalize();


					mJumpPos.x += 1.5f;

					mNomarlizeDown = mFinalPos - mJumpPos;
					mNomarlizeDown.Normalize();
					m_BoxItemFixPos = false;
				}
				
				if (GetName() == L"Box_Item_Hp" || GetName() == L"Box_Item_Staff")
				{
					mUiPos = mTransform->GetPosition();
					mFinalPos = mUiPos;
					mJumpPos = mUiPos;
					mJumpPos.y += 1.3f;					

					mNomarlizeUp = mJumpPos - mFinalPos;
					mNomarlizeUp.Normalize();					

					mNomarlizeDown = mFinalPos - mJumpPos;
					mNomarlizeDown.Normalize();
					m_BoxItemFixPos = false;
				}
				if (GetName() == L"Box_Item_Mp")
				{
					mUiPos = mTransform->GetPosition();
					mFinalPos = mUiPos;
					mJumpPos = mUiPos;
					mJumpPos.y += 1.0f;
					mJumpPos.x += 0.8f;


					mNomarlizeUp = mJumpPos - mFinalPos;
					mNomarlizeUp.Normalize();



					mJumpPos.x -= 1.5f;

					mNomarlizeDown = mFinalPos - mJumpPos;
					mNomarlizeDown.Normalize();
					m_BoxItemFixPos = false;
				}


			}
		}


		GameObject::Initalize();

	}

	void PlayerItem::Update()
	{
		if (mWeaponSlot)
		{
			SetOneCheak(true);

			Vec3 pos = mainCamera->GetOwner()->GetComponent<Transform>()->GetPosition();
			pos += mUiPos;
			mTransform->SetPosition(pos);


			if (IsMouseOn())
			{

				if (Input::GetKeyDown(eKeyCode::RBTN))
				{


					mWeaponSlot = false;
					Transform* tr = GetComponent<Transform>();
					tr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
					tr->SetScale(Vector3(7.5f, 7.5f, 1.0f));
					mItemUnlock = true;
					mPlayerItem = eItem::None;
					s_PlayerInfo iteminfo = mTarget->GetPlayerInfo();
					iteminfo.item = eItem::None;
					mTarget->SetItemWear(true);
					mTarget->SetPlayerInfo(iteminfo);

				}
			}
		}

		if (m_BoxItem)
		{
			if (!m_bStartCheak)
			{
				if (mFinalPos.y <= mJumpPos.y)
				{
					mFinalPos += mNomarlizeUp * Time::DeltaTime() * 6.0f;
					mTransform->SetPosition(mFinalPos);
				}
				else
				{
					m_bStartCheak = true;
					m_bEndCheak = true;
				}
			}
			if (m_bEndCheak)
			{
				if (mFinalPos.y >= mUiPos.y)
				{
					mFinalPos += mNomarlizeDown * Time::DeltaTime() * 6.0f;
					mTransform->SetPosition(mFinalPos);
				}
				else
				{
					m_bEndCheak = false;
					m_BoxItem = false;
				}
			}
		}

		if (m_bSkillSlot)
		{
			mPlayerPos = mainCamera->GetOwner()->GetComponent<Transform>()->GetPosition();


			mFinalPos = mPlayerPos + mUiPos;

			mTransform->SetPosition(mFinalPos);
		}




		UIBase::Update();
	}

	void PlayerItem::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void PlayerItem::Render()
	{
		GameObject::Render();
	}



	void PlayerItem::CreateAnimation(const std::wstring& name, std::shared_ptr<Texture> texture, Animator* animaotr, Vec2 scale, Vector2 offset, std::vector<UINT> numbers, float duration)
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


	void PlayerItem::ItemChange(eItem item)
	{
		if (!mItemChangeCheak)
		{

			switch (item)
			{
			case ks::eItem::None:
				break;
			case ks::eItem::Sword:
			{
				mAnimator->Play(L"Sword", true);
			}
			break;
			case ks::eItem::Staff:
			{
				mAnimator->Play(L"Staff", true);
			}
			break;
			case ks::eItem::Bow:
			{
				mAnimator->Play(L"Bow", true);
			}
			break;
			case ks::eItem::Legend_Sword:
			{
				mAnimator->Play(L"Legend_Sword", true);
			}
			break;
			case ks::eItem::Legend_Staff:
			{
				mAnimator->Play(L"Legend_Staff", true);
			}
			break;
			case ks::eItem::Legend_Bow:
			{
				mAnimator->Play(L"Legend_Bow", true);
			}
			break;
			}
			mItemChangeCheak = true;
		}


	}

	void PlayerItem::loadAnimation()
	{

		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"item_test2", L"Player_UI\\item_test2.png");
		std::shared_ptr<Texture> skil = Resources::Load<Texture>(L"Skil", L"Skil\\item_magic.png");
		std::shared_ptr<Texture> mp = Resources::Load<Texture>(L"mp", L"Player_UI\\FullMp.png");
		std::shared_ptr<Texture> hp = Resources::Load<Texture>(L"hp", L"Player_UI\\FullHp.png");

		mNumbers.push_back(0);		
		CreateAnimation(L"Staff", texture, mAnimator, Vector2(32.0f, 32.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();

		mNumbers.push_back(16);
		CreateAnimation(L"Bow", texture, mAnimator, Vector2(32.0f, 32.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();

		mNumbers.push_back(32);
		CreateAnimation(L"Sword", texture, mAnimator, Vector2(32.0f, 32.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();


		mNumbers.push_back(61);
		CreateAnimation(L"Legend_Staff", texture, mAnimator, Vector2(32.0f, 32.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();

		mNumbers.push_back(28);
		CreateAnimation(L"Legend_Bow", texture, mAnimator, Vector2(32.0f, 32.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();

		mNumbers.push_back(44);
		CreateAnimation(L"Legend_Sword", texture, mAnimator, Vector2(32.0f, 32.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();
			

		mNumbers.push_back(0);
		CreateAnimation(L"hp_Recovery", hp, mAnimator, Vector2(23.0f, 22.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();


		mNumbers.push_back(0);
		CreateAnimation(L"Mp_Recovery", mp, mAnimator, Vector2(24.0f, 24.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();


		mNumbers.push_back(21);

		CreateAnimation(L"Ice_Skil", skil, mAnimator, Vector2(32.0f, 32.0f), Vec2::Zero, mNumbers, 0.15f);
		mNumbers.clear();

		mNumbers.push_back(17);

		CreateAnimation(L"Dark_Skil", skil, mAnimator, Vector2(32.0f, 32.0f), Vec2::Zero, mNumbers, 0.15f);
		mNumbers.clear();


		mNumbers.push_back(13);

		CreateAnimation(L"Barrier_Skil", skil, mAnimator, Vector2(32.0f, 32.0f), Vec2::Zero, mNumbers, 0.15f);
		mNumbers.clear();


		mNumbers.push_back(16);

		CreateAnimation(L"Lighting_Skil", skil, mAnimator, Vector2(32.0f, 32.0f), Vec2::Zero, mNumbers, 0.15f);
		mNumbers.clear();


	}

}