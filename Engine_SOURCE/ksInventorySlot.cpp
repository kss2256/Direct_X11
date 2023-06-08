#include "ksInventorySlot.h"
#include "ksPlayer.h"
#include "ksSpriteRenderer.h"
#include "ksMaterial.h"
#include "ksMesh.h"
#include "ksResources.h"
#include "ksTransform.h"
#include "ksInventory.h"
#include "ksInventoryItem.h"

#include "ksInput.h"


namespace ks
{

	bool InventorySlot::mItemDragCheak = false;

	InventorySlot::InventorySlot()
	{

		mTransform = GetComponent<Transform>();



		//SpriteRenderer* sr = AddComponent<SpriteRenderer>();
		mSprite = AddComponent<SpriteRenderer>();
		

		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"InventorySlotUIMaterial");
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"InventorySlot_00", L"Player_UI\\InventorySlot_00.png");
		mateiral->SetTexture(texture);

		std::shared_ptr<Material> mateiral1 = Resources::Find<Material>(L"InventorySlot_1UIMaterial");
		std::shared_ptr<Texture> texture1 = Resources::Load<Texture>(L"InventorySlot_01", L"Player_UI\\InventorySlot_01.png");
		mateiral1->SetTexture(texture1);

		mSprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		mSprite->SetMesh(mesh);

	}

	InventorySlot::~InventorySlot()
	{

		
	}

	void InventorySlot::Initalize()
	{

		mUiPos = mTransform->GetPosition();
		
		


		GameObject::Initalize();
	}

	void InventorySlot::Update()
	{

		


		if (mParent)
		{
			mPlayerPos = mParent->GetComponent<Transform>()->GetPosition();
			
			mFinalPos = mPlayerPos + mUiPos;
			
			mTransform->SetPosition(mFinalPos);
		}


	

		if (IsMouseOn())
		{
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"InventorySlot_1UIMaterial");
			mSprite->SetMaterial(mateiral);
			
			
			bool Lbtndown = Input::GetKeyDown(eKeyCode::LBTN);
			bool Lbtnup = Input::GetKeyUp(eKeyCode::LBTN);
			if (Lbtndown)
			{
				
				if (mItemOnOff)
				{
					std::wstring test = GetName();
					mItemOnOff = false;
 					int a = 0;
				}

				Inventory::SetInventoryDragStop(true);				
			}
			if (Lbtnup)
			{
				std::wstring test = GetName();
				Inventory::SetInventoryDragStop(false);
			}	
		}

		if (!IsMouseOn())
		{
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"InventorySlotUIMaterial");
			mSprite->SetMaterial(mateiral);	
			bool Lbtndown = Input::GetKeyDown(eKeyCode::LBTN);
			bool Lbtnup = Input::GetKeyUp(eKeyCode::LBTN);
			if (Lbtndown)
			{
				std::wstring test = GetName();
				Inventory::SetInventoryDragStop(false);
			}
		}			

		if (mItemDragCheak)
		{
			if (IsMouseOn())
			{

			
				if (mItemOnOff)
				{
					int a = 0;
				}

				else
				{
					mItemOnOff = true;
					std::wstring test = GetName();
					InventoryItem::SetUiWalkPos(mTransform->GetPosition());
				}
				mItemDragCheak = false;

			}
			//else
			//{
			//	std::wstring test = GetName();
			//	InventoryItem::SetUiWalkPos(Vec3::Zero);
			//	mItemDragCheak = false;
			//}


		}

		UIBase::Update();

	}

	void InventorySlot::FixedUpdate()
	{

		GameObject::FixedUpdate();
	}

	void InventorySlot::Render()
	{

		GameObject::Render();
	}

}
