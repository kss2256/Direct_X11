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
		UINT GetPlayerHp() { return mHp; }
		float GetPlayerStr() { return mStr; }


		void SetPlayer(sPlayer weapon) { mPlayer = weapon; }
		void SetGroundStage(eGroundStage stage) { mPlayerStage = stage; }
		void SetPlayerHp(UINT value) { mHp = value; }
		void SetPlayerStr(float value) { mStr = value; }



	private:


		sPlayer					mPlayer;
		std::vector<sPlayer>	mPlayers;
		eGroundStage			mPlayerStage;

		UINT					mHp;
		float					mStr;



		//GameObject* head;
		//GameObject* body;

	private:



		//GameObject* head;
		//GameObject* body;
	};
}
