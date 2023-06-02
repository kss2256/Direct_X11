#pragma once
#include "ksUIBase.h"


namespace ks
{
	class Monster;
    class BossLayout :
        public UIBase
    {

	public:
		BossLayout();
		virtual ~BossLayout();


		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		Monster* GetTarget() { return mTarget; }


		void SetTarget(Monster* player) { mTarget = player; }






	private:

		Transform*		mTransform;
		Monster*		mTarget;
		Vec3			mPlayerPos;
		Vec3			mUiPos;
		Vec3			mFinalPos;




    };
}
