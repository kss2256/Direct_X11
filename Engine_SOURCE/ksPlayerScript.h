#pragma once
#include "ksScript.h"
#include "ksStatus.h"
#include "ksPlayer.h"


namespace ks
{
	class Inventory;
	class Afterimage;
	class PlayerAttack;
	class GameObject;
	class Player;
	class Animator;
	class Transform;
	class PlayerScript : public Script
	{

	public:



	public:
		PlayerScript();
		~PlayerScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		void Start();
		void Action();
		void End();


		GameObject* GetTarget() { return (Player*)mPlayer; }

		void SetTarget(GameObject* target) { mPlayer = (Player*)target; }
		void SetAttackFailed(bool failed) { mAttackFailed = failed; }
		

		static void SetPlayerStop(bool stop) { mPlayerStop = stop; }
		static void SetPlayerAttackStop(bool stop) { mAttackStop = stop; }
		

	private:

		void directionAnimation(const std::wstring& name, bool loop, bool save = false);
		void angleDirection();
		void attackCommand(eLayerType type, eDirection dir, eSkil skil, eProgress progress, float colldowntime);
		void attackCommandmagic(eLayerType type, eDirection dir, eSkil skil, eProgress progress, float colldowntime, float scale);
		void effectDeath(eLayerType layer);
		void playerShake(float time, float distance, float speed);
		void playerRunSound();
		void playerRunSoundStop();
		void PlayerAttackSound();
		
		


	private:

		Animator*			mAnimator;
		Status*				mStatus;
		Transform*			mTransform;
		Player*				mPlayer;
		Afterimage*			mAfterimage;
		Inventory*			mInventory;

		//PlayerAttack*		mAttack;

		tStateInfo			mState;
		s_PlayerInfo		mPlayerState;

		Vec3				mPrevPos;
		Vec3				mFixPos;
		Vec3				mShakePos;


		static bool			mbRunning;
		static bool			mbAttackWalk;
		static bool			mCarge;
		static bool			mCargeEffect;
		static bool			mCargeFinsh;
		static bool			mAttackStop;
		static bool			mPlayerStop;
		bool				mCheak;
		bool				mStaffStnmina;
		bool				mStaffStnminaRecovery;
		bool				mStaffAttack;
		bool				mAttackFailed;
		bool				mPlayerShake;
		bool				mOnceCheak;

		float				mCheakTime;
		static float		mfStaff;
		float				mDelayTime;
		float				mTime;
		float				mShakeTime;

		static UINT			miRef;

		

	};
}
