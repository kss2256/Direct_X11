#pragma once
#include "ksGameObject.h"
#include "ksStatus.h"
#include "ksAnimation.h"
#include "ksAnimator.h"
#include "ksTexture.h"
#include "ksPlayer.h"
#include "ksTime.h"
#include "ksCollider2D.h"
#include "ksObject.h"

#include <time.h>

namespace ks
{
	
	enum class eStep
	{
		None,
		Step_1,
		Step_2,
		Step_3,
		Step_4,
		Step_5,
		Step_6,
		Step_7,
		Step_8,
		Step_9,
		End,
	};

	class Transform;
	class Monster : public GameObject
	{
	public:
		Monster();
		virtual ~Monster();

		virtual void Initalize() = 0;
		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Render() = 0;
		

		Player* GetTarget() { return mPlayer; }
		Status* GetStatus() { return mStatus; }
		float GetMonsterHp() { return mHp; }
		Vec3 GetTargetPos() { return mTargetPos; }
		bool GetDetection() { return mDetection; }
		float GetMonsterStr() { return mStr; }
		eSituation GetSituation() { return mStateInfo.situation; }
		bool GetBossHit() { return mBossHit; }


		void SetTarget(Player* target) { mPlayer = target; }
		void SetStatus(Status* status) { mStatus = status; }
		void SetMonsterHp(float value);
		void SetTargetPos(Vec3 pos) { mTargetPos = pos; }
		void SetDetection(bool value) { mDetection = value; }
		void SetMonsterStr(float value) { mStr = value; }
		void SetBossHit(bool value) { mBossHit = value; }


		void SetSituation(eSituation value) { mStateInfo.situation = value; }
		void SetStep(eStep value) { mStep = value; }


	


	protected:

		void CreateAnimation(const std::wstring& name, std::shared_ptr<Texture> texture, Animator* animaotr
			, Vec2 scale, Vector2 offset, std::vector<UINT> numbers, float duration);

		bool Range();
		void Patrol();
		void AngleDirection();
		void directionAnimation(const std::wstring& name, bool loop);
		void oneDirectionAnimation(const std::wstring& name, eDirection dir, bool loop);
		void hit(float time, float distance, float speed);
		void boss_hit(float time, float distance, float speed);


	protected:

		Status*					mStatus;
		tStateInfo				mStateInfo;
		eDirection				mOneDirection;
		eStep					mStep;
		Vec3					mTargetPos;
		Vec3					mMonsterPos;
		Vec3					mMovePos;
		Vec3					mSphereMovePos;
		Vec3					mFixPos;
		Vec3					mSphereFixPos;
		Vec3					mShakePos;

		Player*					mPlayer;

		Transform*				mTransform;
		Animator*				mAnimator;
		Collider2D*				mCollider;

		float					mHp;
		float					mStr;
		float					mTime;
		float					mShakeTime;


		
		bool					mDirectionCheak;
		bool					mAttackCool;
		bool					mCheak;
		bool					mDetection;
		bool					mOnceCheak;
		bool					mBossHit;
		float					mRnadomAttack;
		float					mPrevRnadom;

		

		std::vector<Sprite>		mSprites;
		std::vector<Sprite>		mSvaeSprite;

		std::vector<UINT>       mNumbers;
	};
}