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

	private:
		void loadAnimation();
		void trapAttack();
		void poisonAttack(UINT dir, UINT random);
		void sphereAttack();
		void targetDir();
		void sphereAttack_Phase(UINT dir);
		void earthquakeAttack();

	private:

		UINT        mTrapCount;
		UINT		mPoisonRnadom;
		UINT		mEartquake;
		float		mTargetDir;
		Phase		mPhase;


	};
}
