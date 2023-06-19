#include "ksPlayer.h"
#include "ksCollider2D.h"
#include "ksFadeEffect.h"
#include "ksPlayerScript.h"
#include "ksObject.h"
#include "ksPlayerItem.h"
#include "ksAudioClip.h"
#include "ksResources.h"

#include "ksInput.h"
#include "ksTime.h"


namespace ks
{
	UINT Player::mPlayerCoin = 0;


	Player::Player()
	{

		mHp = 5;	
		mFullHp = 5;
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
		
	


		if (Input::GetKeyDown(eKeyCode::NUM_1))
		{
			if (mPlayerCoin >= 999)
				return;
			mPlayerCoin += 10;
		}
		if (Input::GetKeyDown(eKeyCode::NUM_2))
		{
			if(mPlayerCoin <= 1)
				return;
			--mPlayerCoin;
		}
		if (Input::GetKeyDown(eKeyCode::NUM_3))
		{
			if (mHp > 9.5f)
				return;
			mHp += 0.5f;
		}


		if (m_bHpRecoveryCheak)
		{
			m_fTime += Time::DeltaTime();
			m_fTime1 += Time::DeltaTime();
			if (m_fTime1 >= 0.2f && m_bRecoveryCheak == false)
			{
				hpPotionSound();
				m_bRecoveryCheak = true;
			}


			if (m_fTime >= 0.4f)
			{				
				m_bHpRecoveryCheak = false;
				m_fTime = 0.f;
				if (mHp > 9)
					return;
				recoverySound();
				mHp += 1;
			}
		}

		if (m_bMpRecoveryCheak)
		{
			m_fTime += Time::DeltaTime();
			m_fTime1 += Time::DeltaTime();
			if (m_fTime1 >= 0.2f && m_bRecoveryCheak == false)
			{
				hpPotionSound();
				m_bRecoveryCheak = true;
			}

			if (m_fTime >= 0.4f)
			{
				m_bMpRecoveryCheak = false;
				m_fTime = 0.f;
				if (mFullMp <= mMp)
					return;
				mMp += 1;
				recoverySound();
			}

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
			case ks::eItem::Legend_Sword:
			{
				if (mPlayer.weapon_Slot == eSlot::Slot_1)
				{
					mPlayer.weapon = eWeapon::Legend_Sword;
					createItemSlot_1(eItem::Legend_Sword, L"Legend_Sword_Slot1");
					mItemWear = false;

				}
				else if (mPlayer.weapon_Slot == eSlot::Slot_2)
				{
					mPlayer.weapon = eWeapon::Legend_Sword;
					createItemSlot_2(eItem::Legend_Sword, L"Legend_Sword_Slot2");
					mItemWear = false;
				}
			}
			break;
			case ks::eItem::Legend_Staff:
			{
				if (mPlayer.weapon_Slot == eSlot::Slot_1)
				{
					mPlayer.weapon = eWeapon::Legend_Staff;
					createItemSlot_1(eItem::Legend_Staff, L"Legend_Staff_Slot1");
					mItemWear = false;
				}
				else if (mPlayer.weapon_Slot == eSlot::Slot_2)
				{
					mPlayer.weapon = eWeapon::Legend_Staff;
					createItemSlot_2(eItem::Legend_Staff, L"Legend_Staff_Slot2");
					mItemWear = false;
				}

			}
			break;
			case ks::eItem::Legend_Bow:
			{
				if (mPlayer.weapon_Slot == eSlot::Slot_1)
				{
					mPlayer.weapon = eWeapon::Legend_Bow;
					createItemSlot_1(eItem::Legend_Bow, L"Legend_Bow_Slot1");
					mItemWear = false;
				}
				else if (mPlayer.weapon_Slot == eSlot::Slot_2)
				{
					mPlayer.weapon = eWeapon::Legend_Bow;
					createItemSlot_2(eItem::Legend_Bow, L"Legend_Bow_Slot2");
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
			mStr = 5.0f;
		}
			break;	
		case ks::eWeapon::Legend_Sword:
		{
			mStr = 4.0f;
		}
		break;
		case ks::eWeapon::Legend_Bow:
		{
			mStr = 2.5f;
		}
		break;
		case ks::eWeapon::Legend_Staff:
		{
			mStr = 8.0f;
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
		
				if (mItemSlot_1 != nullptr)
				mPlayer.item = mItemSlot_1->GetPlayerItem();
				else
				mPlayer.item = eItem::None;
				mItemWear = true;
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
			
				if(mItemSlot_2 != nullptr)
				mPlayer.item = mItemSlot_2->GetPlayerItem();
				else
				mPlayer.item = eItem::None;
				mItemWear = true;

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

	bool Player::IsShopPurchase(UINT money)
	{
		if (mPlayerCoin < money)
			return false;
		

		mPlayerCoin -= money;
		return true;
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

	void Player::loadSound()
	{
		std::shared_ptr<AudioClip> Recovery_Item_Slot = Resources::Load<AudioClip>
			(L"Hp_Recovery", L"D:\\50\\Resources\\Sound\\Hp_Recovery.ogg");

		std::shared_ptr<AudioClip> Potion_Item_Slot = Resources::Load<AudioClip>
			(L"Hp_Potion", L"D:\\50\\Resources\\Sound\\Hp_Potion.ogg");

	}

	void Player::recoverySound()
	{
		std::shared_ptr<AudioClip> sound = Resources::Find<AudioClip>(L"Hp_Recovery");
		sound->SetLoop(false);
		sound->Play();
	}

	void Player::hpPotionSound()
	{
		std::shared_ptr<AudioClip> sound = Resources::Find<AudioClip>(L"Hp_Potion");
		sound->SetLoop(false);
		sound->Play();
	}

	

}
