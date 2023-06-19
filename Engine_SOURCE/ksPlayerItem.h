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
		bool IsFreeItem() { return m_bFreeItem; }
		bool IsItemUnlock() { return mItemUnlock; }
		bool IsShopItem() { return m_bShopItem; }
		bool IsSkilBook() { return m_bSkilBook; }

		void SetTarget(Player* player) { mTarget = player; }
		void SetInventoryTarget(UIBase* inventory) { mInventory = inventory; }
		void SetPlayerItem(eItem item) { mPlayerItem = item; }		
		void SetShopItem(bool shop) { m_bShopItem = shop; }
		void SetSkilBook(bool book) { m_bSkilBook = book; }
		void SetSkilSlot(bool slot) { m_bSkillSlot = slot; }
		void SetWeaponSlot(bool slot) { mWeaponSlot = slot; }
		void SetItemChange(bool change) { mItemChangeCheak = change; }
		void SetItemUnlock(bool unlock) { mItemUnlock = unlock; }
		void ItemUnBoxing(bool unlock) { m_BoxItemFixPos = unlock; }
		void IsBoxItem(bool box) { m_BoxItem = box; }
		void SetFreeItem(bool box) { m_bFreeItem = box; }
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

		Vec3			mJumpPos;
		Vec3			mNomarlizeUp;
		Vec3			mNomarlizeDown;


		std::vector<Sprite>		mSprites;
		std::vector<Sprite>		mSvaeSprite;

		std::vector<UINT>       mNumbers;


		bool					mWeaponSlot;
		bool					mItemChangeCheak;
		bool					mItemUnlock;
		bool					m_bShopItem;
		bool					m_bFreeItem;
		bool					m_BoxItem;
		bool					m_BoxItemFixPos;
		bool					m_bSkilBook;
		bool					m_bSkillSlot;



		bool					m_bStartCheak;
		bool					m_bEndCheak;



    };
}
