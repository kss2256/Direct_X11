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
		mHp = 10;
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
				mPlayer.weapon = eWeapon::Sword;
				createItem(eItem::Sword, L"Sword_Slot");
				mItemWear = false;
			}
			break;
			case ks::eItem::Staff:
			{
				mPlayer.weapon = eWeapon::Staff;
				createItem(eItem::Staff, L"Staff_Slot");
				mItemWear = false;
			}
			break;
			case ks::eItem::Bow:
			{
				mPlayer.weapon = eWeapon::Bow;
				createItem(eItem::Bow, L"Bow_Slot");
				mItemWear = false;
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

	void Player::createItem(eItem item, const std::wstring name)
	{
		PlayerItem* playeritem = object::Instantiate<PlayerItem>(eLayerType::UI);

		playeritem->SetName(name);		
		playeritem->SetPlayerItem(item);	
		playeritem->SetTarget(this);
		playeritem->SetWeaponSlot(true);


		Transform* tr = playeritem->GetComponent<Transform>();
		tr->SetPosition(Vector3(8.25f, -4.05f, 0.0f));
		tr->SetScale(Vector3(7.5f, 7.5f, 1.0f));

		playeritem->Initalize();

	}

	

}
