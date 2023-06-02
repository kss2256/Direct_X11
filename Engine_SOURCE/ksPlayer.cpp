#include "ksPlayer.h"
#include "ksCollider2D.h"
#include "ksFadeEffect.h"
#include "ksPlayerScript.h"


#include "ksInput.h"


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

	

}
