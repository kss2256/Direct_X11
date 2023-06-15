#pragma once
#include "ksUIBase.h"
#include "ksPlayer.h"
#include "ksAnimation.h"
#include "ksAnimator.h"



namespace ks
{	
	class InventorySlot;
	class Transform;
    class InventoryItem :
        public UIBase
    {
	public:
		InventoryItem();
		virtual ~InventoryItem();


		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	

		Player* GetTarget() { return mTarget; }
		UIBase* GetInventoryTarget() { return mInventory; }
		std::vector<InventorySlot*> GetInventorySlot() { return mInventorysSlot; }
		eItem GetPlayerItem() { return mPlayerItem; }

		void SetTarget(Player* player) { mTarget = player; }
		void SetInventoryTarget(UIBase* inventory) { mInventory = inventory; }
		void SetInventorySlot(std::vector<InventorySlot*> inventory) { mInventorysSlot = inventory; }
		void SetPlayerItem(eItem item) { mPlayerItem = item; }

		static void SetUiWalkPos(Vec3 pos) { mUiWalkPos = pos; }
		static void SetHandItem(bool item) { mHandItem = item; }

	private:

		void loadAnimation();
		void CreateAnimation(const std::wstring& name, std::shared_ptr<Texture> texture, Animator* animaotr
			, Vec2 scale, Vector2 offset, std::vector<UINT> numbers, float duration);
		void loadSound();
		void swordSound();
		void staffSound();
		void bowSound();
		void hpPotionSound();
		void hpRecoverySound();



	private:

		Transform*		mTransform;
		Animator*		mAnimator;
		Player*			mTarget;
		UIBase*			mInventory;
		std::vector<InventorySlot*>	mInventorysSlot;
		Vec3			mPlayerPos;
		Vec3			mUiPos;
		Vec3			mFinalPos;
		Vec3			mUiPrevMousePos;
		Vec3			mUiPrevItemPos;
		

		eItem			mPlayerItem;

		std::vector<Vec3>		mSlotPosvector;
		std::vector<Sprite>		mSprites;
		std::vector<Sprite>		mSvaeSprite;

		std::vector<UINT>			mNumbers;
		static std::wstring			mItemName;


		bool					mDragWalk;
		static bool				mHandItem;
		static bool				mDragCheak;
		static Vec3				mUiWalkPos;
		bool					m_bSoundDeathCheak;


		float					m_fTime;


    };
}
