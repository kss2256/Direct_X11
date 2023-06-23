#pragma once
#include "ksScript.h"
#include "ksStatus.h"
#include "ksPlayer.h"


namespace ks
{
	class OptionUi;
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
		
		static bool IsPlayerPower() { return m_sbPlayerPower ; }
		static void SetPlayerStop(bool stop) { mPlayerStop = stop; }
		static void SetPlayerAttackStop(bool stop) { mAttackStop = stop; }
		static void SetPlayerRunning(bool running) { mbRunning = running; }
		static void SetPlayerPower(bool power) { m_sbPlayerPower = power; }
		

	private:

		void directionAnimation(const std::wstring& name, bool loop, bool save = false);
		void angleDirection();
		void attackCommand(eLayerType type, eDirection dir, eSkil skil, eProgress progress, float colldowntime);
		void attackCommandmagic(eLayerType type, eDirection dir, eSkil skil, eProgress progress, float colldowntime, float scale);
		void effectDeath(eLayerType layer);
		void playerShake(float time, float distance, float speed);

		void playerHitColor();
		void playerRunSound();
		void playerRunSoundStop();
		void PlayerAttackSound();
		void playerCoinSound();
		void playerInventorySound();
		void loadSound();
		void itemLootSound();
		void shopbuySound();
		void failedSound();
		void staffChargeSound();
		void staffChargeFinishSound();
		void skillSound();
		void skillLightingSound();
		void optionOpenSound();
		void evadeOkSound();
		void evadeClearSound();
		void playerHitSound();
		void playerDeathSound();


		void skilIce();
		void skilDark();
		void skilBarrier();
		void skilLighting();
		void targetLighting();
		void optionCreate();

	private:

		Animator*			mAnimator;
		Status*				mStatus;
		Transform*			mTransform;
		Player*				mPlayer;
		Afterimage*			mAfterimage;
		Inventory*			mInventory;
		OptionUi*			mOption;

		//PlayerAttack*		mAttack;

		tStateInfo			mState;
		s_PlayerInfo		mPlayerState;

		Vec3				mPrevPos;
		Vec3				mFixPos;
		Vec3				mShakePos;
		Vec3				m_vLightingPos;

		std::vector<Vec3>	m_vectorLightingTargetPos;


		static bool			mbRunning;
		static bool			mbAttackWalk;
		static bool			mCarge;
		static bool			mCargeSound;
		static bool			mCargeEffect;
		static bool			mCargeFinsh;
		static bool			mAttackStop;
		static bool			mPlayerStop;
		static bool			m_sbPlayerPower;
		static bool			m_sbPlayerHit;
		bool				mCheak;
		bool				mStaffStnmina;
		bool				mStaffStnminaRecovery;
		bool				mStaffAttack;
		bool				mAttackFailed;
		bool				mPlayerShake;
		bool				mOnceCheak;
		bool				m_bLightingAttack;
		bool				m_bLightingOneCheak;
		bool				m_bHitCol;
		bool				m_bDeathOneCheak;
		bool				m_bChangeScene;


		float				mCheakTime;
		float				m_fSkilTime;
		static float		mfStaff;
		static float		m_sfPlayerHit;
		static float		m_sfPlayerHitTime;
		float				m_fPlayerHitTime;
		float				mDelayTime;
		float				mTime;
		float				mShakeTime;
		float				m_fPowerTime;
		float				m_fPlayerDeathTime;

		static UINT			miRef;

		

	};
}
