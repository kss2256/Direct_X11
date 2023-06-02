#pragma once
#include "ksUIBase.h"


namespace ks
{
	class Monster;
    class BossTpMeter :
        public UIBase
    {
    public:

		BossTpMeter();
		virtual ~BossTpMeter();


		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;


		Monster* GetTarget() { return mTarget; }


		void SetMonster(Monster* monster) { mTarget = monster; }






	private:

		Transform*				mTransform;
		Monster*				mTarget;
		Vec3					mPlayerPos;
		Vec3					mUiPos;
		Vec3					mFinalPos;

		static float			mFlimeHp;




    };
}

