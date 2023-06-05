#pragma once
#include "ksUIBase.h"
#include "ksPlayer.h"

namespace ks
{

	class Transform;
	class PlayerSlot :
		public UIBase
	{

	public:
		PlayerSlot();
		virtual ~PlayerSlot();


		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		Player* GetTarget() { return mTarget; }


		void SetTarget(Player* player) { mTarget = player; }





	private:

		Transform*		mTransform;
		Player*			mTarget;
		Vec3			mPlayerPos;
		Vec3			mUiPos;
		Vec3			mFinalPos;

		eSlot			mPlayerWeaponSlot;

	};
}
