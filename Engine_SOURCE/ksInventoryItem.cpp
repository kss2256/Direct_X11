#include "ksInventoryItem.h"
#include "ksSpriteRenderer.h"
#include "ksMaterial.h"
#include "ksMesh.h"
#include "ksResources.h"
#include "ksTransform.h"
#include "ksShader.h"
#include "ksInventory.h"
#include "ksInventorySlot.h"


#include "ksInput.h"


namespace ks
{

	bool InventoryItem::mDragCheak = false;
	bool InventoryItem::mHandItem = false;
	Vec3 InventoryItem::mUiWalkPos = Vec3::Zero;
	std::wstring InventoryItem::mItemName = {};

	InventoryItem::InventoryItem()
		: mDragWalk(false)
		
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

	InventoryItem::~InventoryItem()
	{
		int a = 0;

	}

	void InventoryItem::Initalize()
	{

		if (mInventory != nullptr)
		{
			Inventory* inven = (Inventory*)mInventory;
			mSlotPosvector = inven->GetSlotPos();

		}

		mUiPos = mTransform->GetPosition();

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
		}

		GameObject::Initalize();
	}

	void InventoryItem::Update()
	{
		SetOneCheak(true);
		SetPos(mUiPrevItemPos);		

		if (mParent)
		{
			if (mDragCheak)
			{
				if (!(GetName() == mItemName))
				{
					mPlayerPos = mParent->GetComponent<Transform>()->GetPosition();

					mFinalPos = mPlayerPos + mUiPos;

					mTransform->SetPosition(mFinalPos);
				}
			}
			else
			{
				mPlayerPos = mParent->GetComponent<Transform>()->GetPosition();

				mFinalPos = mPlayerPos + mUiPos;

				mTransform->SetPosition(mFinalPos);
			}			
		}


		if (mDragWalk && GetName() == mItemName)
		{
			mTransform->SetPosition(mUiWalkPos);
			if (mUiWalkPos == Vec3::Zero)
				mTransform->SetPosition(mFinalPos);

			Vec3 pos = mParent->GetComponent<Transform>()->GetPosition();
			mUiPos = mTransform->GetPosition() - pos;

			mHandItem = false;
			mDragWalk = false;
			mDragCheak = false;
		}


		if (mDragCheak && GetName() == mItemName)
		{
			if (mHandItem)
				return;
			
			Vec3 mousepos = Input::GetMousWorldPosition();

			Vec3 movepos = mousepos - mUiPrevMousePos;
			

			Vec3 pos = mTransform->GetPosition();
			Vec3 Campos = mainCamera->GetOwner()->GetComponent<Transform>()->GetPosition();

			pos += movepos;

			mTransform->SetPosition(pos);
			

			mUiPrevMousePos = Input::GetMousWorldPosition();

			bool Lbtnup = Input::GetKeyUp(eKeyCode::LBTN);
			bool LbtnPressed = Input::GetKey(eKeyCode::LBTN);
			bool Lbtndown = Input::GetKeyDown(eKeyCode::LBTN);
			if (IsMouseOn() && GetName() == mItemName)
			{

				if (Lbtndown)
				{
					mDragWalk = true;
					InventorySlot::SetItemDragCheak(true);
				}
			}
			else
			{
				if (Lbtndown)
				{					
					mDragWalk = true;			
					InventorySlot::SetItemDragCheak(true);
				}
			}
		}


		if (IsMouseOn())
		{		
			bool Lbtnup = Input::GetKeyUp(eKeyCode::LBTN);
			bool Lbtndown = Input::GetKeyDown(eKeyCode::LBTN);
			
			if (Lbtndown)
			{
				//SetTwoCheak(true);
				mItemName = GetName();
				mUiPrevItemPos = mTransform->GetPosition();
				mDragCheak = true;				
				mUiPrevMousePos = Input::GetMousWorldPosition();

			}

			
		

			if (Input::GetKeyDown(eKeyCode::RBTN))
			{
				s_PlayerInfo iteminfo = mTarget->GetPlayerInfo();
				iteminfo.item = mPlayerItem;
				mTarget->SetItemWear(true);
				mTarget->SetPlayerInfo(iteminfo);
				
			}
		


		}

		

		UIBase::Update();
	}

	void InventoryItem::FixedUpdate()
	{
		
		GameObject::FixedUpdate();
	}

	void InventoryItem::Render()
	{

		GameObject::Render();
	}

	

	void InventoryItem::loadAnimation()
	{

		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"item_test2", L"Player_UI\\item_test2.png");



		mNumbers.push_back(0);
		CreateAnimation(L"Staff", texture, mAnimator, Vector2(32.0f, 32.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();

		mNumbers.push_back(16);
		CreateAnimation(L"Bow", texture, mAnimator, Vector2(32.0f, 32.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();

		mNumbers.push_back(32);
		CreateAnimation(L"Sword", texture, mAnimator, Vector2(32.0f, 32.0f), Vec2::Zero, mNumbers, 0.35f);
		mNumbers.clear();

	}

	void InventoryItem::CreateAnimation(const std::wstring& name, std::shared_ptr<Texture> texture, Animator* animaotr, Vec2 scale, Vector2 offset, std::vector<UINT> numbers, float duration)
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

}