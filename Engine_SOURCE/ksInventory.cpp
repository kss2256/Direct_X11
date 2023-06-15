#include "ksInventory.h"
#include "ksSpriteRenderer.h"
#include "ksMaterial.h"
#include "ksMesh.h"
#include "ksResources.h"
#include "ksTransform.h"
#include "ksShader.h"
#include "ksPlayerScript.h"
#include "ksInventoryItem.h"
#include "ksInventorySlot.h"

#include "ksInput.h"


namespace ks
{

	bool Inventory::mInventoryOnOff = false;
	bool Inventory::mInventoryCheak = false;
	bool Inventory::mInventoryDrag = false;
	bool Inventory::mInventoryFull = false;
	bool Inventory::mInventoryDragStop = false;
	


	Inventory::Inventory()
	{
		mTransform = GetComponent<Transform>();

		

		SpriteRenderer* sr = AddComponent<SpriteRenderer>();


		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"InventoryUIMaterial");
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"inventoryBackground", L"Player_UI\\inventoryBackground.png");
		mateiral->SetTexture(texture);
		sr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);

	}

	Inventory::~Inventory()
	{


		if (GetChild().empty())
			return;
		const std::vector<UIBase*>& chide = GetChild();

		for (size_t i = 0; i < chide.size(); i++)
		{
			delete chide[i];			
		}

	}

	void Inventory::Initalize()
	{

		mUiPos = mTransform->GetPosition();	




		

		if (GetChild().empty())
			return;
		const std::vector<UIBase*>& chide = GetChild();

		for (size_t i = 0; i < chide.size(); i++)
		{
			chide[i]->Initalize();
		}


		GameObject::Initalize();
	}

	void Inventory::Update()
	{
		
		UIBase::Update();

		if (GetChild().empty())
			return;
		const std::vector<UIBase*>& chide = GetChild();

		for (size_t i = 0; i < chide.size(); i++)
		{
			chide[i]->Update();
		}		

		/*if (mInventorysSlot.size() >= 15)
		{
			mInventoryFull = true;
		}*/

		//플레이어 스크립트에서 i 누르면 인벤토리 포지션 = 플레이어 위치로 이동
		if (mInventoryOnOff)
		{
			if (!mInventoryCheak)
			{
				//Vec3 pos = mTarget->GetComponent<Transform>()->GetPosition();
				Vec3 pos = mainCamera->GetOwner()->GetComponent<Transform>()->GetPosition();
				pos += mUiPos;
				mTransform->SetPosition(pos);			
				
			}
			if (mInventoryDrag)
			{
				Vec3 pos = mainCamera->GetOwner()->GetComponent<Transform>()->GetPosition();
				pos += mUiPrevPos;
				mTransform->SetPosition(pos);
			}
			
		}
		//인벤토리 켜진상태에서 다시 i 누르면 안보이는 장소로 인벤토리 이동
		else
		{
			mTransform->SetPosition(mUiPos);	
			mInventoryCheak = false;
		}


		//마우스가 인벤토리로 올라오면 플레이어 공격 기능 X
		if (IsMouseOn())
		{
			PlayerScript* player = nullptr;
			player->SetPlayerAttackStop(true);
		}
		//마우스가 인벤토리에서 벗어나면 공격 기능 On
		else
		{
			PlayerScript* player = nullptr;
			player->SetPlayerAttackStop(false);		
		}
		

		//마우스로 인벤토리 드래그 기능
		if (IsLbtnDown())
		{
			if (mInventoryDragStop)
				return;
			mInventoryCheak = true;
			mInventoryDrag = false;


			Vec3 mousepos = Input::GetMousWorldPosition();

			Vec3 movepos = mousepos - mUiPrevMousePos;

			Vec3 pos = mTransform->GetPosition();
			Vec3 Campos = mainCamera->GetOwner()->GetComponent<Transform>()->GetPosition();

			pos += movepos;

			mTransform->SetPosition(pos);

			mUiPrevMousePos = Input::GetMousWorldPosition();
		}

		
		if (IsLbtnUp())
		{
			if (mInventoryDragStop)
				return;
			mInventoryCheak = false;
			mInventoryDrag = true;
			
			Vec3 pos = mainCamera->GetOwner()->GetComponent<Transform>()->GetPosition();
			mUiPrevPos = mTransform->GetPosition() - pos;			
		}
	
	}

	void Inventory::FixedUpdate()
	{



		GameObject::FixedUpdate();



		if (GetChild().empty())
			return;
		const std::vector<UIBase*>& chide = GetChild();

		for (size_t i = 0; i < chide.size(); i++)
		{
			chide[i]->FixedUpdate();
		}
	
	}

	void Inventory::Render()
	{
		GameObject::Render();

		if (GetChild().empty())
			return;
		const std::vector<UIBase*>& chide = GetChild();

		for (size_t i = 0; i < chide.size(); i++)
		{
			chide[i]->Render();
		}
	}

	void Inventory::MouseLbtnDown()
	{
		UIBase::MouseLbtnDown();

		mUiPrevMousePos = Input::GetMousWorldPosition();

	}

	void Inventory::AddItem(eItem item)
	{
		if (mInventoryFull)
			return;
		
		
		//mItemSlot = mInventorySlot.size();
		mItemSlot = 0;
		mSlotCheak = 0;
		const std::vector<UIBase*>&  chide = GetChild();
		for (size_t i = 0; i < chide.size(); i++)
		{			
			if (dynamic_cast<InventorySlot*>(chide[i]))
			{
				++mItemSlot;
				InventorySlot* slot = (InventorySlot*)chide[i];
				if (!slot->GetItenOnOff())
				{					
					slot->SetItemOnOff(true);					
					break;
				}
			}

		}


		for (int j = 0; j < 3; j++)
		{
			for (int i = -2; i < 3; i++)
			{	
				++mSlotCheak;
				if (mItemSlot == mSlotCheak)
				{
					mInventoryPos = Vector3(1 * i, 1.5f - j, 0.0f);
					break;
				}

				
			}
		}

		

		switch (item)
		{
		case ks::eItem::None:
		{

		}
			break;
		case ks::eItem::Sword:
		{
			InventoryItem* inventoryitem = new InventoryItem;
			
			inventoryitem->SetName(L"SwordItem");
			inventoryitem->SetTarget(mTarget);
			inventoryitem->SetPlayerItem(item);
			Transform* inventorytr = inventoryitem->GetComponent<Transform>();
			inventorytr->SetPosition(mInventoryPos);
			inventorytr->SetScale(Vector3(7.0f, 7.0f, 1.0f));
			

			inventoryitem->SetInventoryTarget(this);
			inventoryitem->SetInventorySlot(mInventorysSlot);
			inventoryitem->Initalize();

			this->AddChild(inventoryitem);
		
		}
			break;
		case ks::eItem::Staff:
		{
			InventoryItem* inventoryitem = new InventoryItem;

			inventoryitem->SetName(L"StaffItem");
			inventoryitem->SetTarget(mTarget);
			inventoryitem->SetPlayerItem(item);
			Transform* inventorytr = inventoryitem->GetComponent<Transform>();
			inventorytr->SetPosition(mInventoryPos);
			inventorytr->SetScale(Vector3(7.0f, 7.0f, 1.0f));

			inventoryitem->SetInventoryTarget(this);
			inventoryitem->SetInventorySlot(mInventorysSlot);
			inventoryitem->Initalize();

			AddChild(inventoryitem);
		}
			break;
		case ks::eItem::Bow:
		{
			InventoryItem* inventoryitem = new InventoryItem;

			inventoryitem->SetName(L"BowItem");
			inventoryitem->SetTarget(mTarget);
			inventoryitem->SetPlayerItem(item);
			Transform* inventorytr = inventoryitem->GetComponent<Transform>();
			inventorytr->SetPosition(mInventoryPos);
			inventorytr->SetScale(Vector3(7.0f, 7.0f, 1.0f));

			inventoryitem->SetInventoryTarget(this);
			inventoryitem->SetInventorySlot(mInventorysSlot);
			inventoryitem->Initalize();

			AddChild(inventoryitem);
		}
			break;		
		case ks::eItem::Legend_Sword:
		{
			InventoryItem* inventoryitem = new InventoryItem;

			inventoryitem->SetName(L"Legend_Sword_Item");
			inventoryitem->SetTarget(mTarget);
			inventoryitem->SetPlayerItem(item);
			Transform* inventorytr = inventoryitem->GetComponent<Transform>();
			inventorytr->SetPosition(mInventoryPos);
			inventorytr->SetScale(Vector3(7.0f, 7.0f, 1.0f));


			inventoryitem->SetInventoryTarget(this);
			inventoryitem->SetInventorySlot(mInventorysSlot);
			inventoryitem->Initalize();

			this->AddChild(inventoryitem);

		}
		break;
		case ks::eItem::Legend_Staff:
		{
			InventoryItem* inventoryitem = new InventoryItem;

			inventoryitem->SetName(L"Legend_Staff_Item");
			inventoryitem->SetTarget(mTarget);
			inventoryitem->SetPlayerItem(item);
			Transform* inventorytr = inventoryitem->GetComponent<Transform>();
			inventorytr->SetPosition(mInventoryPos);
			inventorytr->SetScale(Vector3(7.0f, 7.0f, 1.0f));

			inventoryitem->SetInventoryTarget(this);
			inventoryitem->SetInventorySlot(mInventorysSlot);
			inventoryitem->Initalize();

			AddChild(inventoryitem);
		}
		break;
		case ks::eItem::Legend_Bow:
		{
			InventoryItem* inventoryitem = new InventoryItem;

			inventoryitem->SetName(L"Legend_Bow_Item");
			inventoryitem->SetTarget(mTarget);
			inventoryitem->SetPlayerItem(item);
			Transform* inventorytr = inventoryitem->GetComponent<Transform>();
			inventorytr->SetPosition(mInventoryPos);
			inventorytr->SetScale(Vector3(7.0f, 7.0f, 1.0f));

			inventoryitem->SetInventoryTarget(this);
			inventoryitem->SetInventorySlot(mInventorysSlot);
			inventoryitem->Initalize();

			AddChild(inventoryitem);
		}
		break;
		case ks::eItem::Hp:
		{
			InventoryItem* inventoryitem = new InventoryItem;

			inventoryitem->SetName(L"Hp_Item");
			inventoryitem->SetTarget(mTarget);
			inventoryitem->SetPlayerItem(item);
			Transform* inventorytr = inventoryitem->GetComponent<Transform>();
			inventorytr->SetPosition(mInventoryPos);
			inventorytr->SetScale(Vector3(7.0f, 7.0f, 1.0f));

			inventoryitem->SetInventoryTarget(this);
			inventoryitem->SetInventorySlot(mInventorysSlot);
			inventoryitem->Initalize();

			AddChild(inventoryitem);
		}
		break;
		case ks::eItem::MP:
		{
			InventoryItem* inventoryitem = new InventoryItem;

			inventoryitem->SetName(L"Mp_Item");
			inventoryitem->SetTarget(mTarget);
			inventoryitem->SetPlayerItem(item);
			Transform* inventorytr = inventoryitem->GetComponent<Transform>();
			inventorytr->SetPosition(mInventoryPos);
			inventorytr->SetScale(Vector3(7.0f, 7.0f, 1.0f));

			inventoryitem->SetInventoryTarget(this);
			inventoryitem->SetInventorySlot(mInventorysSlot);
			inventoryitem->Initalize();

			AddChild(inventoryitem);
		}
		break;

		}


		
	}

}