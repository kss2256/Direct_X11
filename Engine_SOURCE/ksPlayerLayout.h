#pragma once
#include "ksUIBase.h"



namespace ks
{
	class Player;
	class Transform;
	class PlayerLayout :
		public UIBase
	{
	public:

		PlayerLayout();
		virtual ~PlayerLayout();


		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		Player* GetTarget() { return mTarget; }


		void SetTarget(Player* player) { mTarget = player; }

		


		//void SetUiPos(Vec3 pos) { mUiPos = pos; }
		//void SetUiScale(Vec3 scale) { mUiScale = scale; }



	private:

		Transform*		mTransform;
		Player*			mTarget;
		Vec3			mPlayerPos;
		Vec3			mUiPos;
		//Vec3			mUiScale;
		Vec3			mFinalPos;

		
		

	};

}
