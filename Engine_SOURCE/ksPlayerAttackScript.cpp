#include "ksPlayerAttackScript.h"
#include "ksPlayer.h"
#include "ksPlayerAttack.h"
#include "ksSlime_Green.h"
#include "ksSnake_Green.h"
#include "ksBoss_Flime.h"
#include "ksBoss_Ent.h"
#include "ksForest_Fairy.h"
#include "ksAudioClip.h"
#include "ksResources.h"


namespace ks
{


	PlayerAttackScript::PlayerAttackScript()		
	{

		loadSound();

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
				attackHitSound();
				attackDeath();

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
				attackHitSound();
				attackDeath();
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
				attackHitSound();
				attackDeath();
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
				attackHitSound();
				attackDeath();
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
				attackHitSound();
				attackDeath();
			}
		}


	}

	void PlayerAttackScript::OnCollisionStay(Collider2D* collider)
	{
	}

	void PlayerAttackScript::OnCollisionExit(Collider2D* collider)
	{
	}

	void PlayerAttackScript::attackDeath()
	{
		switch (mPlayer->GetPlayerInfo().weapon)
		{
		case ks::eWeapon::None:
			mPlayerAttack->AttackDeath();
			break;
		case ks::eWeapon::Sword:
			break;
		case ks::eWeapon::Staff:
			mPlayerAttack->AttackDeath();
			break;
		case ks::eWeapon::Bow:
			mPlayerAttack->AttackDeath();
			break;
		case ks::eWeapon::Legend_Sword:
			break;
		case ks::eWeapon::Legend_Staff:
			mPlayerAttack->AttackDeath();
			break;
		case ks::eWeapon::Legend_Bow:
			mPlayerAttack->AttackDeath();
			break;
		}



	}

	void PlayerAttackScript::loadSound()
	{

		std::shared_ptr<AudioClip> booksound = Resources::Load<AudioClip>
			(L"None_Attack_Hit", L"D:\\50\\Resources\\Sound\\None_Attack_Hit.ogg");

		std::shared_ptr<AudioClip> coinsound = Resources::Load<AudioClip>
			(L"Bow_Attack_Hit", L"D:\\50\\Resources\\Sound\\Bow_Attack_Hit.ogg");	


	}

	void PlayerAttackScript::attackHitSound()
	{

		switch (mPlayer->GetPlayerInfo().weapon)
		{
		case ks::eWeapon::None:
			attackHitSoundStaff();
			break;
		case ks::eWeapon::Sword:
			attackHitSoundBow();
			break;
		case ks::eWeapon::Staff:
			attackHitSoundStaff();
			break;
		case ks::eWeapon::Bow:
			attackHitSoundBow();
			break;
		case ks::eWeapon::Legend_Sword:
			attackHitSoundBow();
			break;
		case ks::eWeapon::Legend_Staff:
			attackHitSoundStaff();
			break;
		case ks::eWeapon::Legend_Bow:
			attackHitSoundBow();
			break;
		}



	}

	void PlayerAttackScript::attackHitSoundStaff()
	{

		std::shared_ptr<AudioClip> coinsound = Resources::Find<AudioClip>(L"None_Attack_Hit");
		coinsound->SetLoop(false);
		coinsound->Play(3.0f);

	}

	void PlayerAttackScript::attackHitSoundBow()
	{
		std::shared_ptr<AudioClip> coinsound = Resources::Find<AudioClip>(L"Bow_Attack_Hit");
		coinsound->SetLoop(false);
		coinsound->Play(3.0f);

	}

}
