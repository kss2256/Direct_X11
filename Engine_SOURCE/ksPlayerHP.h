#pragma once
#include "ksUIBase.h"

namespace ks
{
	class PlayerCreateHp;
	class SpriteRenderer;
	class Player;
	class Transform;
    class PlayerHP :
        public UIBase
    {
	public:

		PlayerHP();
		virtual ~PlayerHP();


		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		Player* GetTarget() { return mTarget; }


		void SetTarget(Player* player) { mTarget = player; }


	private:


		void createHpSet();
		void hpSetPos();

		void createMpSet();
		void mpSetPos();



	private:

		Transform*		mTransform;
		Player*			mTarget;
		Vec3			mPlayerPos;
		Vec3			mUiPos;
		//Vec3			mUiScale;
		Vec3			mFinalPos;

		SpriteRenderer* mSprite;

		std::vector<PlayerCreateHp*> m_vCreateHps;
		std::vector<PlayerCreateHp*> m_vCreateFullMps;
		std::vector<PlayerCreateHp*> m_vCreateHalfMps;

		float			mPlayerHp;
		float			mPlayerPrevHp;
		float			mPlayerFullHp;
		float			mPlayerFullPrevHp;
		float			mPlayerFullMp;
		float			mPlayerFullPrevMp;
		float			mPlayerMp;
		float			mPlayerPrevMp;

		int				mFullHp;
		int				mFullMp;
		float			mHalfHp;
		static UINT		mHpCount;
		static UINT		mFullMpCount;
		static UINT		mHalfMpCount;
		


    };
}

