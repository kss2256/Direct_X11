#include "ksSkilScript.h"
#include "ksSkil_Dark.h"
#include "ksSnake_Green.h"
#include "ksSlime_Green.h"
#include "ksForest_Fairy.h"
#include "ksTime.h"


namespace ks
{

	SkilScript::SkilScript()
	{

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
				if(skil->IsVoidAttack())
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
					Vec3 pos = fairy->GetComponent<Transform>()->GetPosition();

					pos += m_vNomal * 3.0f * Time::DeltaTime();

					fairy->GetComponent<Transform>()->SetPosition(pos);
				}
				
				if (m_bDarkAttackFinsh)
				{
					fairy->SetMonsterHp(25);					
					
				}

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

		if (dynamic_cast<Slime_Green*>(collider->GetOwner()))
		{
			switch (m_eSkil)
			{
			case ks::eItem::Dark:
			{
				Skil_Dark* skil = (Skil_Dark*)mSkilOwner;
				Slime_Green* slime = (Slime_Green*)collider->GetOwner();
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
					Vec3 pos = slime->GetComponent<Transform>()->GetPosition();

					pos += m_vNomal * 3.0f * Time::DeltaTime();

					slime->GetComponent<Transform>()->SetPosition(pos);
				}
				if (m_bDarkAttackFinsh)
				{
					slime->SetMonsterHp(25);	
					slime->SetIdleAnimation();
					
				}
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

		if (dynamic_cast<Snake_Green*>(collider->GetOwner()))
		{
			switch (m_eSkil)
			{
			case ks::eItem::Dark:
			{
				Skil_Dark* skil = (Skil_Dark*)mSkilOwner;
				Snake_Green* snake = (Snake_Green*)collider->GetOwner();
				if(snake)
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
					Vec3 pos = snake->GetComponent<Transform>()->GetPosition();

					pos += m_vNomal * 3.0f * Time::DeltaTime();

					snake->GetComponent<Transform>()->SetPosition(pos);
				}
				
				if (m_bDarkAttackFinsh)
				{
					snake->SetMonsterHp(25);					
					
				}

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

}