#include "ksPlayerAttackScript.h"
#include "ksPlayer.h"
#include "ksPlayerAttack.h"
#include "ksSlime_Green.h"
#include "ksSnake_Green.h"
#include "ksBoss_Flime.h"
#include "ksBoss_Ent.h"
#include "ksForest_Fairy.h"



namespace ks
{


	PlayerAttackScript::PlayerAttackScript()		
	{
	}

	PlayerAttackScript::~PlayerAttackScript()
	{
	}

	void PlayerAttackScript::Initalize()
	{

	}

	void PlayerAttackScript::Update()
	{
		
	}

	void PlayerAttackScript::FixedUpdate()
	{

	}

	void PlayerAttackScript::Render()
	{

	}

	void PlayerAttackScript::OnCollisionEnter(Collider2D* collider)
	{
		if (dynamic_cast<Slime_Green*>(collider->GetOwner()))
		{
			Slime_Green* slime = (Slime_Green*)collider->GetOwner();
			if (slime->GetSituation() == eSituation::Death)
				return;

			if(slime->GetSituation() != eSituation::Hit)
			{
				slime->SetStep(eStep::None);
				slime->SetSituation(eSituation::Hit);
				slime->SetMonsterHp(mPlayer->GetPlayerStr());

			}
		}


		if (dynamic_cast<Snake_Green*>(collider->GetOwner()))
		{
			Snake_Green* snake = (Snake_Green*)collider->GetOwner();
			if (snake->GetSituation() == eSituation::Death)
				return;

			if (snake->GetSituation() != eSituation::Hit)
			{
				snake->SetStep(eStep::None);
				snake->SetSituation(eSituation::Hit);
				snake->SetMonsterHp(mPlayer->GetPlayerStr());
			}
		}


		if (dynamic_cast<Boss_Flime*>(collider->GetOwner()))
		{
			Boss_Flime* flime = (Boss_Flime*)collider->GetOwner();
			if (flime->GetSituation() == eSituation::Death)
				return;

			if (!flime->GetBossHit())
			{
				flime->SetBossHit(true);
				flime->SetMonsterHp(mPlayer->GetPlayerStr());
			}
		}

		if (dynamic_cast<Boss_Ent*>(collider->GetOwner()))
		{
			Boss_Ent* ent = (Boss_Ent*)collider->GetOwner();
			if (ent->GetSituation() == eSituation::Death)
				return;

			if (!ent->GetBossHit())
			{			

				ent->SetBossHit(true);
				ent->SetMonsterHp(mPlayer->GetPlayerStr());
			}
		}


		if (dynamic_cast<Forest_Fairy*>(collider->GetOwner()))
		{
			Forest_Fairy* fairy	= (Forest_Fairy*)collider->GetOwner();
			if (fairy->GetSituation() == eSituation::Death)
				return;

			if (fairy->GetSituation() != eSituation::Hit)
			{
				fairy->SetStep(eStep::None);
				fairy->SetSituation(eSituation::Hit);
				fairy->SetMonsterHp(mPlayer->GetPlayerStr());
			}
		}


	}

	void PlayerAttackScript::OnCollisionStay(Collider2D* collider)
	{
	}

	void PlayerAttackScript::OnCollisionExit(Collider2D* collider)
	{
	}

}
