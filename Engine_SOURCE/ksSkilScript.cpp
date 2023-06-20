#include "ksSkilScript.h"
#include "ksSkil_Dark.h"
#include "ksSnake_Green.h"
#include "ksSlime_Green.h"
#include "ksForest_Fairy.h"
#include "ksTime.h"
#include "ksBoss_Ent.h"
#include "ksBoss_Flime.h"
#include "ksAudioClip.h"

namespace ks
{

	SkilScript::SkilScript()
	{
		loadSound();
	}

	SkilScript::~SkilScript()
	{
	}

	void SkilScript::Initalize()
	{
	}

	void SkilScript::Update()
	{


	}

	void SkilScript::FixedUpdate()
	{
	}

	void SkilScript::Render()
	{
	}

	void SkilScript::OnCollisionEnter(Collider2D* collider)
	{
		if (dynamic_cast<Forest_Fairy*>(collider->GetOwner()))
		{
			switch (m_eSkil)
			{
			case ks::eItem::Ice:
			{
				Forest_Fairy* forest = (Forest_Fairy*)collider->GetOwner();
				if (forest->GetSituation() == eSituation::Death)
					return;

				if (forest->GetSituation() != eSituation::Hit)
				{
					iceHitSound();
					forest->SetStep(eStep::None);
					forest->SetSituation(eSituation::Hit);
					forest->SetMonsterHp(25);
				}
			}
			break;
			case ks::eItem::Lighting:
				break;
			}

		}

		if (dynamic_cast<Snake_Green*>(collider->GetOwner()))
		{
			switch (m_eSkil)
			{
			case ks::eItem::Ice:
			{
				Snake_Green* snake = (Snake_Green*)collider->GetOwner();
				if (snake->GetSituation() == eSituation::Death)
					return;

				if (snake->GetSituation() != eSituation::Hit)
				{
					iceHitSound();
					snake->SetStep(eStep::None);
					snake->SetSituation(eSituation::Hit);
					snake->SetMonsterHp(25);
				}
			}
			break;
			case ks::eItem::Lighting:
				break;
			}

		}

		if (dynamic_cast<Slime_Green*>(collider->GetOwner()))
		{
			switch (m_eSkil)
			{
			case ks::eItem::Ice:
			{
				Slime_Green* slime = (Slime_Green*)collider->GetOwner();
				if (slime->GetSituation() == eSituation::Death)
					return;

				if (slime->GetSituation() != eSituation::Hit)
				{
					iceHitSound();
					slime->SetStep(eStep::None);
					slime->SetSituation(eSituation::Hit);
					slime->SetMonsterHp(25);
				}
			}
			break;
			case ks::eItem::Lighting:
				break;
			}
		}

		if (dynamic_cast<Boss_Ent*>(collider->GetOwner()))
		{
			switch (m_eSkil)
			{
			case ks::eItem::Ice:
			{
				Boss_Ent* ent = (Boss_Ent*)collider->GetOwner();
				if (ent->GetSituation() == eSituation::Death)
					return;

				if (!ent->GetBossHit())
				{
					iceHitSound();
					ent->SetBossHit(true);
					ent->SetMonsterHp(25);
				}
			}
			break;
			case ks::eItem::Lighting:
				break;
			}

		}
		if (dynamic_cast<Boss_Flime*>(collider->GetOwner()))
		{
			switch (m_eSkil)
			{
			case ks::eItem::Ice:
			{
				Boss_Flime* flime = (Boss_Flime*)collider->GetOwner();
				if (flime->GetSituation() == eSituation::Death)
					return;

				if (!flime->GetBossHit())
				{
					iceHitSound();
					flime->SetBossHit(true);
					flime->SetMonsterHp(25);
				}
			}
			break;
			case ks::eItem::Lighting:
				break;
			}

		}
	}


	void SkilScript::OnCollisionStay(Collider2D* collider)
	{
		if (dynamic_cast<Forest_Fairy*>(collider->GetOwner()))
		{
			switch (m_eSkil)

			{
			case ks::eItem::Dark:
			{
				Skil_Dark* skil = (Skil_Dark*)mSkilOwner;
				Forest_Fairy* fairy = (Forest_Fairy*)collider->GetOwner();
				if (skil->IsVoidAttack())
				{
					fairy->SetWalkStop(true);
					m_bDarkVoid = true;
					m_vTargetPos = fairy->GetComponent<Transform>()->GetPosition();
					m_vPos = mSkilOwner->GetComponent<Transform>()->GetPosition();
					m_vNomal = m_vPos - m_vTargetPos;

					m_vNomal.Normalize();
				}
				if (m_bDarkVoid)
				{
					m_fTime += Time::DeltaTime();
					if (m_fTime >= 0.3f)
					{
						darkTickSound();
						m_fTime = 0.f;
					}
				}
				if (m_bDarkVoid)
				{
					Vec3 pos = fairy->GetComponent<Transform>()->GetPosition();

					pos += m_vNomal * 0.5f * Time::DeltaTime();

					fairy->GetComponent<Transform>()->SetPosition(pos);
				}
				if (m_bDarkAttackFinsh)
				{
					fairy->SetMonsterHp(25);				
				}
			}
			break;

			}
		}

		if (dynamic_cast<Slime_Green*>(collider->GetOwner()))
		{
			switch (m_eSkil)
			{
			case ks::eItem::Dark:
			{
				Skil_Dark* skil = (Skil_Dark*)mSkilOwner;
				Slime_Green* slime = (Slime_Green*)collider->GetOwner();

				if (slime->GetSituation() == eSituation::Death)
					return;


				if (skil->IsVoidAttack())
				{

					slime->SetWalkStop(true);
					m_bDarkVoid = true;
					m_vTargetPos = slime->GetComponent<Transform>()->GetPosition();
					m_vPos = mSkilOwner->GetComponent<Transform>()->GetPosition();
					m_vNomal = m_vPos - m_vTargetPos;

					m_vNomal.Normalize();
				}


				if (m_bDarkVoid)
				{
					m_fTime += Time::DeltaTime();
					if (m_fTime >= 0.3f)
					{
						darkTickSound();
						m_fTime = 0.f;
					}

					Vec3 pos = slime->GetComponent<Transform>()->GetPosition();

					pos += m_vNomal * 0.5f * Time::DeltaTime();

					slime->GetComponent<Transform>()->SetPosition(pos);
				}

				if (m_bDarkAttackFinsh)
				{
					slime->SetMonsterHp(25);					
				}

			}
			break;
			}
		}

		if (dynamic_cast<Snake_Green*>(collider->GetOwner()))
		{
			switch (m_eSkil)
			{
			case ks::eItem::Dark:
			{
				Skil_Dark* skil = (Skil_Dark*)mSkilOwner;
				Snake_Green* snake = (Snake_Green*)collider->GetOwner();
				if (snake->GetSituation() == eSituation::Death)
					return;

				if (skil->IsVoidAttack())
				{
					snake->SetWalkStop(true);
					m_bDarkVoid = true;
					m_vTargetPos = snake->GetComponent<Transform>()->GetPosition();
					m_vPos = mSkilOwner->GetComponent<Transform>()->GetPosition();
					m_vNomal = m_vPos - m_vTargetPos;

					m_vNomal.Normalize();
				}

				if (m_bDarkVoid)
				{
					m_fTime += Time::DeltaTime();
					if (m_fTime >= 0.3f)
					{
						darkTickSound();
						m_fTime = 0.f;
					}

					Vec3 pos = snake->GetComponent<Transform>()->GetPosition();

					pos += m_vNomal * 0.5f * Time::DeltaTime();

					snake->GetComponent<Transform>()->SetPosition(pos);
				}

				if (m_bDarkAttackFinsh)
				{
					snake->SetMonsterHp(25);					
				}

			}
			break;
			}
		}
		if (dynamic_cast<Boss_Flime*>(collider->GetOwner()))
		{
			switch (m_eSkil)
			{
			case ks::eItem::Dark:
			{
				Skil_Dark* skil = (Skil_Dark*)mSkilOwner;
				Boss_Flime* flime = (Boss_Flime*)collider->GetOwner();
				if (flime->GetSituation() == eSituation::Death)
					return;
				if (skil->IsVoidAttack())
				{
					m_bDarkVoid = true;
					m_vTargetPos = flime->GetComponent<Transform>()->GetPosition();
					m_vPos = mSkilOwner->GetComponent<Transform>()->GetPosition();

				}
				if (m_bDarkVoid)
				{
					m_fTime += Time::DeltaTime();
					if (m_fTime >= 0.3f)
					{
						darkTickSound();
						flime->SetMonsterHp(5);
						m_fTime = 0.f;
					}
				}

				if (m_bDarkAttackFinsh)
				{
					flime->SetMonsterHp(25);
					m_bDarkAttackFinsh = false;
				}

			}
			break;

			}

		}
		if (dynamic_cast<Boss_Ent*>(collider->GetOwner()))
		{
			switch (m_eSkil)
			{
			case ks::eItem::Dark:
			{
				Skil_Dark* skil = (Skil_Dark*)mSkilOwner;
				Boss_Ent* ent = (Boss_Ent*)collider->GetOwner();
				if (ent->GetSituation() == eSituation::Death)
					return;
				if (skil->IsVoidAttack())
				{

					m_bDarkVoid = true;
					m_vTargetPos = ent->GetComponent<Transform>()->GetPosition();
					m_vPos = mSkilOwner->GetComponent<Transform>()->GetPosition();

				}
				if (m_bDarkVoid)
				{
					m_fTime += Time::DeltaTime();
					if (m_fTime >= 0.3f)
					{
						darkTickSound();
						ent->SetMonsterHp(5);
						m_fTime = 0.f;
					}
				}

				if (m_bDarkAttackFinsh)
				{
					ent->SetMonsterHp(25);
					m_bDarkAttackFinsh = false;
				}

			}
			break;
			}
		}

	}

	void SkilScript::OnCollisionExit(Collider2D* collider)
	{
		if (dynamic_cast<Snake_Green*>(collider->GetOwner()))
		{
			switch (m_eSkil)
			{
			case ks::eItem::Dark:
			{

			}
			break;
			case ks::eItem::Ice:
			{
				int a = 0;
			}
			break;
			case ks::eItem::Barrier:
			{
				int a = 0;
			}
			break;
			case ks::eItem::Lighting:
			{
				int a = 0;
			}
			break;
			}
		}



	}

	void SkilScript::loadSound()
	{
		std::shared_ptr<AudioClip> Void_Attack = Resources::Load<AudioClip>
			(L"Void_Attack", L"..\\Resources\\Sound\\Void_Attack.ogg");


		std::shared_ptr<AudioClip> Ice_Hit = Resources::Load<AudioClip>
			(L"Ice_Hit", L"..\\Resources\\Sound\\Ice_Hit.ogg");

	}

	void SkilScript::darkTickSound()
	{
		std::shared_ptr<AudioClip> sound = Resources::Find<AudioClip>(L"Void_Attack");
		sound->SetLoop(false);
		sound->Play();
	}

	void SkilScript::iceHitSound()
	{
		std::shared_ptr<AudioClip> sound = Resources::Find<AudioClip>(L"Ice_Hit");
		sound->SetLoop(false);
		sound->Play();
	}

}