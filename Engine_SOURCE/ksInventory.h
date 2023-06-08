#pragma once
#include "ksUIBase.h"
#include "ksPlayer.h"


namespace ks
{
	class InventorySlot;
	class Transform;
	class Inventory
		: public UIBase
	{
	public:

		Inventory();
		~Inventory();



		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;




		virtual void MouseLbtnDown() override;



		Player* GetTarget() { return mTarget; }
		void SetTarget(Player* player) { mTarget = player; }

		std::vector<InventorySlot*> GetSlot() { return mInventorysSlot; }
		std::vector<Vec3> GetSlotPos() { return mSlotPosvector; }

		void SetSlotPos(Vec3 pos) { mSlotPosvector.push_back(pos); }
		void SetSlot(InventorySlot* slot) { mInventorysSlot.push_back(slot); }
		void AddItem(eItem item);

		static bool IsInventoryFull() { return mInventoryFull; }

		static bool GetInventoryOnOff() { return mInventoryOnOff; }

		static void SetInventoryOnOff(bool onoff) { mInventoryOnOff = onoff; }

		static void SetInventoryDragStop(bool onoff) { mInventoryDragStop = onoff; }


	private:

		Transform*		mTransform;
		Player*			mTarget;
		Vec3			mCamPos;
		Vec3			mUiPos;
		Vec3			mUiPrevPos;
		Vec3			mUiPrevMousePos;
		Vec3			mFinalPos;
		Vec3			mInventoryPos;
		



		eItem						mItem;

		std::vector<InventorySlot*>	mInventorysSlot;
		std::vector<Vec3>			mSlotPosvector;

		UINT						mItemSlot;
		UINT						mSlotCheak;

		static bool					mInventoryFull;

		static bool					mInventoryOnOff;
		static bool					mInventoryCheak;
		static bool					mInventoryDrag;
		static bool					mInventoryDragStop;



	};
}
