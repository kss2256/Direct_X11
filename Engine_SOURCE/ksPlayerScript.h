#pragma once
#include "ksScript.h"
#include "ksStatus.h"
#include "ksPlayer.h"


namespace ks
{

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





	private:

		void directionAnimation(const std::wstring& name, bool loop, bool save = false);
		void angleDirection();
		void attackCommand(eLayerType type, eDirection dir, eSkil skil, eProgress progress, float colldowntime);
		void attackCommandmagic(eLayerType type, eDirection dir, eSkil skil, eProgress progress, float colldowntime, float scale);
		void effectDeath(eLayerType layer);


	private:

		Animator*			mAnimator;
		Status*				mStatus;
		Transform*			mTransform;
		Player*				mPlayer;
		Afterimage*			mAfterimage;

		//PlayerAttack*		mAttack;

		tStateInfo			mState;
		sPlayer				mPlayerState;

		Vec3				mPrevPos;


		static bool			mbRunning;
		static bool			mbAttackWalk;
		static bool			mCarge;
		static bool			mCargeEffect;
		static bool			mCargeFinsh;
		bool				mCheak;

		float		mCheakTime;
		static float		mfStaff;
		float		mDelayTime;
		float		mTime;
		
		static UINT			miRef;
	};
}
