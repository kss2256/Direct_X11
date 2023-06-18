#pragma once
#include "ksMonster.h"

enum class Phase
{
	None,
	Phase_1,	
};

namespace ks
{
	class Boss_Ent
		: public Monster
	{

	public:
		Boss_Ent();
		~Boss_Ent();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;


		void directionAnimation(const std::wstring& name, bool loop);


	public:

		Phase GetPhase() { return mPhase; }


		void SetPhase(Phase phase) { mPhase = phase; }

		void SetEntAnimation(const std::wstring& name);


	private:
		void loadAnimation();
		void trapAttack();
		void poisonAttack(UINT dir, UINT random);
		void sphereAttack();
		void targetDir();
		void sphereAttack_Phase(UINT dir);
		void earthquakeAttack();
		void loadSound();
		void poisonAttackSound();
		void missileAttackSound();
		void earthquakeAttackSound();
		void poisonAttackSoundStop();
		void missileAttackSoundStop();
		void earthquakeAttackSoundStop();
		void soundClear();
		void soundDeath();
		void createBox();


	private:

		UINT        mTrapCount;
		UINT		mPoisonRnadom;
		UINT		mEartquake;
		float		mTargetDir;
		float       m_fTime;
		Phase		mPhase;


		bool		m_bSoundCheak;

		bool        mEntCheak;
		bool        mEntSoundCheak;

		bool        m_bSoundDeathCheak;


	};
}
