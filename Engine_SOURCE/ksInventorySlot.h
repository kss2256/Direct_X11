#pragma once
#include "ksUIBase.h"
#include "ksPlayer.h"

namespace ks
{	
	class SpriteRenderer;
	class Transform;
    class InventorySlot :
        public UIBase
    {

	public:

		InventorySlot();
		~InventorySlot();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		Player* GetTarget() { return mTarget; }


		void SetTarget(Player* player) { mTarget = player; }
		bool GetItenOnOff() { return mItemOnOff; }

		void SetItemOnOff(bool onoff) { mItemOnOff = onoff; }
		static void SetItemDragCheak(bool cheak) { mItemDragCheak = cheak; }

		//void SetUiPos(Vec3 pos) { mUiPos = pos; }
		//void SetUiScale(Vec3 scale) { mUiScale = scale; }



	private:

		static bool				mItemDragCheak;
		bool					mItemOnOff;


		Transform*				mTransform;
		InventorySlot*			mPrevSlot;
		Player*					mTarget;
		Vec3					mPlayerPos;
		Vec3					mUiPos;
		//Vec3					mUiScale;
		Vec3					mFinalPos;

	
		SpriteRenderer*			mSprite;


    };
}
