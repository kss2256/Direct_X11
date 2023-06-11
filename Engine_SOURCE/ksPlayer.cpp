#include "ksPlayer.h"
#include "ksCollider2D.h"
#include "ksFadeEffect.h"
#include "ksPlayerScript.h"
#include "ksObject.h"
#include "ksPlayerItem.h"


#include "ksInput.h"


namespace ks
{
	Player::Player()
	{

		mHp = 5;	
		mMp = 5;	
		mFullMp = 5;

		mStamina = 100;
		mItemWear = false;
		mStaninaFull = true;
		mPlayer.weapon_Slot = eSlot::Slot_1;
	}

	Player::~Player()
	{
		
	}

	void Player::Initalize()
	{


		/*mPlayers.resize((UINT)eWeapon::End);



		for (UINT i = 0; i < (UINT)eWeapon::End ; i++)
		{
			mPlayers[i].weapon = (eWeapon)i;
		}*/


		GameObject::Initalize();

	}

	void Player::Update()
	{
		
		if (Input::GetKeyDown(eKeyCode::N_1))
		{
			if (mHp > 9.f)
				return;
			++mHp;
		}
		if (Input::GetKeyDown(eKeyCode::N_2))
		{
			if (mHp > 9.5f)
				return;
			mHp += 0.5f;
		}
		if (Input::GetKeyDown(eKeyCode::N_3))
		{
			if (mHp < 1)
				return;
			--mHp;
		}
		if (Input::GetKeyDown(eKeyCode::N_4))
		{
			if (mHp < 0.5)
				return;
			mHp -= 0.5f;
		}

		if (Input::GetKeyDown(eKeyCode::N_5))
		{
			if (mMp > mFullMp - 1.f)
				return;
			++mMp;
		}	
		if (Input::GetKeyDown(eKeyCode::N_6))
		{
			if (mMp < 1.f)
				return;
			--mMp;
		}	

		if (Input::GetKeyDown(eKeyCode::N_7))
		{
			if (mFullMp > 9.f)
				return;
			++mFullMp;
		}
		//마나통 줄이기는 사용 안할 예정
		if (Input::GetKeyDown(eKeyCode::N_8))
		{
			if (mFullMp < 1.f)
				return;
			--mFullMp;
		}



		if(mItemWear)
		{
			switch (mPlayer.item)
			{
			case ks::eItem::None:
			{
				mPlayer.weapon = eWeapon::None;				
				mItemWear = false;
			}
			break;
			case ks::eItem::Sword:
			{
				if (mPlayer.weapon_Slot == eSlot::Slot_1)
				{
					mPlayer.weapon = eWeapon::Sword;
					createItemSlot_1(eItem::Sword, L"Sword_Slot1");
					mItemWear = false;

				}
				else if (mPlayer.weapon_Slot == eSlot::Slot_2)
				{
					mPlayer.weapon = eWeapon::Sword;
					createItemSlot_2(eItem::Sword, L"Sword_Slot2");
					mItemWear = false;
				}				
			}
			break;
			case ks::eItem::Staff:
			{
				if (mPlayer.weapon_Slot == eSlot::Slot_1)
				{
					mPlayer.weapon = eWeapon::Staff;
					createItemSlot_1(eItem::Staff, L"Staff_Slot1");
					mItemWear = false;
				}
				else if (mPlayer.weapon_Slot == eSlot::Slot_2)
				{
					mPlayer.weapon = eWeapon::Staff;
					createItemSlot_2(eItem::Staff, L"Staff_Slot2");
					mItemWear = false;
				}

			}
			break;
			case ks::eItem::Bow:
			{
				if (mPlayer.weapon_Slot == eSlot::Slot_1)
				{
					mPlayer.weapon = eWeapon::Bow;
					createItemSlot_1(eItem::Bow, L"Bow_Slot1");
					mItemWear = false;
				}
				else if (mPlayer.weapon_Slot == eSlot::Slot_2)
				{
					mPlayer.weapon = eWeapon::Bow;
					createItemSlot_2(eItem::Bow, L"Bow_Slot2");
					mItemWear = false;
				}

			}
			break;
			}
		}


		switch (mPlayer.weapon)
		{
		case ks::eWeapon::None:
		{
			mStr = 2.f;
		}
			break;
		case ks::eWeapon::Sword:
		{
			mStr = 2.5f;
		}
			break;
		case ks::eWeapon::Bow:
		{
			mStr = 1.5f;
		}
			break;
		case ks::eWeapon::Staff:
		{
			mStr = 5.f;
		}
			break;	
		}
		if(mSlotChange)
		{
			switch (mPlayer.weapon_Slot)
			{
			case ks::eSlot::Slot_1:
			{
				if (mItemSlot_2)
				{
					if (mItemSlot_1 && !mItemSlot_1->IsItemUnlock())
						mItemSlot_1->SetWeaponSlot(true);
					mItemSlot_2->SetWeaponSlot(false);

					Transform* tr = mItemSlot_2->GetComponent<Transform>();
					tr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
					tr->SetScale(Vector3(7.5f, 7.5f, 1.0f));

					mSlotChange = false;
				}
				
			}
			break;
			case ks::eSlot::Slot_2:
			{
				if (mItemSlot_1)
				{
					if (mItemSlot_2 && !mItemSlot_2->IsItemUnlock())
						mItemSlot_2->SetWeaponSlot(true);
					mItemSlot_1->SetWeaponSlot(false);

					Transform* tr = mItemSlot_1->GetComponent<Transform>();
					tr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
					tr->SetScale(Vector3(7.5f, 7.5f, 1.0f));
					mSlotChange = false;

				}
			}
			break;
			}
			mSlotChange = false;
		}


		if (Input::GetKeyDown(eKeyCode::N_0))
		{
			mStamina = 10000;
		}


		if (mStamina >= MAX_STAMINA)
		{
			mStaninaFull = true;
		}
		else if (mStamina < MAX_STAMINA)
		{
			mStaninaFull = false;
		}



		GameObject::Update();
		//head->update();
		//body->update();
	}

	void Player::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void Player::Render()
	{
		GameObject::Render();
	}

	bool Player::Usestamina(float value, PlayerScript* script)
	{
		if (mStamina < value)
		{
			script->SetAttackFailed(true);
			return false;
		}
		else
		{
			mStamina -= value;
			return true;
		}
	}

	void Player::createItemSlot_1(eItem item, const std::wstring name)
	{
		if(mItemSlot_1 == nullptr)
		{
			mItemSlot_1 = object::Instantiate<PlayerItem>(eLayerType::UI);

			mItemSlot_1->SetName(name);
			mItemSlot_1->SetPlayerItem(item);
			mItemSlot_1->SetTarget(this);
			mItemSlot_1->SetWeaponSlot(true);


			Transform* tr = mItemSlot_1->GetComponent<Transform>();
			tr->SetPosition(Vector3(8.25f, -4.05f, 0.0f));
			tr->SetScale(Vector3(7.5f, 7.5f, 1.0f));

			mItemSlot_1->Initalize();
		}

		else
		{
			mItemSlot_1->SetItemChange(false);
			mItemSlot_1->SetWeaponSlot(true);
			mItemSlot_1->ItemChange(item);
			mItemSlot_1->SetItemUnlock(false);
		}

	}

	void Player::createItemSlot_2(eItem item, const std::wstring name)
	{

		if (mItemSlot_2 == nullptr)
		{
			mItemSlot_2 = object::Instantiate<PlayerItem>(eLayerType::UI);

			mItemSlot_2->SetName(name);
			mItemSlot_2->SetPlayerItem(item);
			mItemSlot_2->SetTarget(this);
			mItemSlot_2->SetWeaponSlot(true);


			Transform* tr = mItemSlot_2->GetComponent<Transform>();
			tr->SetPosition(Vector3(8.35f, -4.15f, 0.0f));
			tr->SetScale(Vector3(7.5f, 7.5f, 1.0f));

			mItemSlot_2->Initalize();
		}
		else
		{
			mItemSlot_2->SetItemChange(false);
			mItemSlot_2->SetWeaponSlot(true);
			mItemSlot_2->ItemChange(item);
			mItemSlot_2->SetItemUnlock(false);
		}


	}

	

}
