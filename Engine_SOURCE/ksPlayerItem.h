#pragma once
#include "ksUIBase.h"
#include "ksPlayer.h"
#include "ksAnimation.h"
#include "ksAnimator.h"


namespace ks
{	
	class Transform;
    class PlayerItem :
        public UIBase
    {

	public:
		PlayerItem();
		virtual ~PlayerItem();


		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		Player* GetTarget() { return mTarget; }
		UIBase* GetInventoryTarget() { return mInventory; }
		eItem GetPlayerItem() { return mPlayerItem; }
		bool IsItemUnlock() { return mItemUnlock; }
		bool IsShopItem() { return m_bShopItem; }

		void SetTarget(Player* player) { mTarget = player; }
		void SetInventoryTarget(UIBase* inventory) { mInventory = inventory; }
		void SetPlayerItem(eItem item) { mPlayerItem = item; }		
		void SetShopItem(bool shop) { m_bShopItem = shop; }
		void SetWeaponSlot(bool slot) { mWeaponSlot = slot; }
		void SetItemChange(bool change) { mItemChangeCheak = change; }
		void SetItemUnlock(bool unlock) { mItemUnlock = unlock; }
		void ItemChange(eItem item);
		

	private:

		void loadAnimation();
		void CreateAnimation(const std::wstring& name, std::shared_ptr<Texture> texture, Animator* animaotr
			, Vec2 scale, Vector2 offset, std::vector<UINT> numbers, float duration);


	private:

		Transform*		mTransform;
		Animator*		mAnimator;
		Player*			mTarget;
		UIBase*			mInventory;
		Vec3			mPlayerPos;
		Vec3			mUiPos;
		Vec3			mFinalPos;

		eItem			mPlayerItem;


		std::vector<Sprite>		mSprites;
		std::vector<Sprite>		mSvaeSprite;

		std::vector<UINT>       mNumbers;


		bool					mWeaponSlot;
		bool					mItemChangeCheak;
		bool					mItemUnlock;
		bool					m_bShopItem;



    };
}
