#pragma once
#include "ksGameObject.h"



namespace ks
{
	enum class eWeapon
	{
		None,
		Sword,
		Staff,
		Bow,
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


	enum class eSlot
	{
		Slot_1,
		Slot_2,
	};


	enum class eItem
	{
		None,
		Sword,
		Staff,
		Bow,
		End,
	};

	struct s_PlayerInfo
	{
		eSkil skil;
		eItem item;
		eWeapon weapon;
		eSlot weapon_Slot;
		eProgress progress;
	};

	class PlayerItem;
	class UIBase;
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

		s_PlayerInfo GetPlayerInfo() { return mPlayer; }
		eGroundStage GetGroundStage() { return mPlayerStage; }
		float GetPlayerHp() { return mHp; }
		float GetPlayerMp() { return mMp; }
		float GetPlayerFullMp() { return mFullMp; }
		float GetPlayerStr() { return mStr; }
		float GetStamina() { return mStamina; }
		UIBase* GetInventoryTarget() { return mInventory; }
		

		void SetInventoryTarget(UIBase* inventory) { mInventory = inventory; }
		bool StaminaFull() { return mStaninaFull; }
		bool Usestamina(float value, PlayerScript* script);
		void RestoreStamina(float value) { mStamina = value; }
		bool GetItemWear() { return mItemWear; }

		void SetPlayerInfo(s_PlayerInfo weapon) { mPlayer = weapon; }
		void SetGroundStage(eGroundStage stage) { mPlayerStage = stage; }
		void SetPlayerHp(float value) { mHp = value; }
		void SetPlayerMp(float value) { mMp = value; }
		void SetPlayerStr(float value) { mStr = value; }
		void SetItemWear(bool item) { mItemWear = item; }
		void SetSlotChange(bool change) { mSlotChange = change; }


	private:

		void createItemSlot_1(eItem item, const std::wstring name);
		void createItemSlot_2(eItem item, const std::wstring name);



	private:


		s_PlayerInfo					mPlayer;
		std::vector<s_PlayerInfo>		mPlayers;

		eGroundStage					mPlayerStage;
		UIBase*							mInventory;
		PlayerItem*						mItemSlot_1;
		PlayerItem*						mItemSlot_2;

		float							mHp;
		float							mMp;
		float							mFullMp;
		float							mStamina;
		float							mStr;

		bool							mStaninaFull;
		bool							mItemWear;
		bool							mSlotChange;

		//GameObject* head;
		//GameObject* body;

	private:



		//GameObject* head;
		//GameObject* body;
	};
}
