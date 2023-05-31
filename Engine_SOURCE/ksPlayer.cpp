#include "ksPlayer.h"
#include "ksCollider2D.h"
#include "ksFadeEffect.h"


#define MAX_STAMINA 100



namespace ks
{
	Player::Player()
	{
		mHp = 10;
		mStamina = 100;
		mStaninaFull = true;
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

	bool Player::Usestamina(float value)
	{
		if (mStamina < value)
			return false;
		else
		{
			mStamina -= value;
			return true;
		}
	}

	

}
