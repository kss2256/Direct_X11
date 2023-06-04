#pragma once
#include "ksGameObject.h"



namespace ks
{
	enum class eWeapon
	{
		None,
		Sword,
		Bow,
		Staff,
		End,
	};

	enum class eSkil
	{
		None,
		Attack,
		Evade,

	};

	enum class eProgress
	{
		None,
		Start,
		Step_1,
		Step_2,
		Step_3,
		Step_4,
		Step_5,
		Step_6,
		Step_7,
		Step_8,
		Step_9,
		End,
	};


	struct sPlayer
	{
		eSkil skil;
		eWeapon weapon;
		eProgress progress;
	};

	class PlayerScript;
	class Player : public GameObject
	{
	public:
		Player();
		virtual ~Player();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	public:

		sPlayer GetPlayer() { return mPlayer; }
		eGroundStage GetGroundStage() { return mPlayerStage; }
		float GetPlayerHp() { return mHp; }
		float GetPlayerStr() { return mStr; }
		float GetStamina() { return mStamina; }


		bool StaminaFull() { return mStaninaFull; }
		bool Usestamina(float value, PlayerScript* script);
		void RestoreStamina(float value) { mStamina = value; }


		void SetPlayer(sPlayer weapon) { mPlayer = weapon; }
		void SetGroundStage(eGroundStage stage) { mPlayerStage = stage; }
		void SetPlayerHp(float value) { mHp = value; }
		void SetPlayerStr(float value) { mStr = value; }



	private:


		sPlayer					mPlayer;
		std::vector<sPlayer>	mPlayers;
		eGroundStage			mPlayerStage;

		float					mHp;
		float					mStamina;
		float					mStr;

		bool					mStaninaFull;

		//GameObject* head;
		//GameObject* body;

	private:



		//GameObject* head;
		//GameObject* body;
	};
}
