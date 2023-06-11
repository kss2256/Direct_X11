#include "ksPlayerHP.h"
#include "ksPlayer.h"
#include "ksSpriteRenderer.h"
#include "ksMaterial.h"
#include "ksMesh.h"
#include "ksResources.h"
#include "ksTransform.h"
#include "ksObject.h"
#include "ksPlayerCreateHp.h"

#include "ksInput.h"



namespace ks
{

	UINT PlayerHP::mHpCount = 0;
	UINT PlayerHP::mFullMpCount = 0;
	UINT PlayerHP::mHalfMpCount = 0;

	PlayerHP::PlayerHP()
	{




	}

	PlayerHP::~PlayerHP()
	{


	}

	void PlayerHP::Initalize()
	{
		if (nullptr != mTarget)
		{
			mPlayerHp = mTarget->GetPlayerHp();
			mPlayerPrevHp = mTarget->GetPlayerHp();

			mPlayerFullMp = mTarget->GetPlayerFullMp();
			mPlayerFullPrevMp = mTarget->GetPlayerFullMp();

			mPlayerMp = mTarget->GetPlayerMp();
			mPlayerPrevMp = mTarget->GetPlayerMp();

			createHpSet();
			createMpSet();
			hpSetPos();
			mpSetPos();
		}


		GameObject::Initalize();
	}

	void PlayerHP::Update()
	{
		


		if (nullptr != mTarget)
		{
			mPlayerHp = mTarget->GetPlayerHp();
			if (mPlayerPrevHp != mPlayerHp)
			{
				
				hpSetPos();
				

				mPlayerPrevHp = mPlayerHp;
			}

			mPlayerFullMp = mTarget->GetPlayerFullMp();
			mPlayerMp = mTarget->GetPlayerMp();
			if (mPlayerPrevMp != mPlayerMp || mPlayerFullPrevMp != mPlayerFullMp)
			{

				mpSetPos();

				mPlayerFullPrevMp = mPlayerFullMp;
				mPlayerPrevMp = mPlayerMp;
			}


		}



		UIBase::Update();
	}

	void PlayerHP::FixedUpdate()
	{

		

		GameObject::FixedUpdate();
	}

	void PlayerHP::Render()
	{
		GameObject::Render();
	}

	void PlayerHP::createHpSet()
	{

		for (size_t i = 0; i < 10 ; i++)
		{
			PlayerCreateHp* playerhp = object::Instantiate<PlayerCreateHp>(eLayerType::UI);
			playerhp->SetName(L"Player_Full_Hp");
			playerhp->SetTarget(this);
			playerhp->SetFullHp(true);


			Transform* tr = playerhp->GetComponent<Transform>();			
			tr->SetPosition(Vector3(-100.0f, 0.0f, 0.0f));
			tr->SetScale(Vector3(0.5f, 0.5f, 1.0f));

			playerhp->Initalize();

			m_vCreateHps.push_back(playerhp);
		}
		
			PlayerCreateHp* playerhp = object::Instantiate<PlayerCreateHp>(eLayerType::UI);
			playerhp->SetName(L"Player_Half_Hp");
			playerhp->SetTarget(this);
			playerhp->SetHalfHp(true);

			Transform* tr = playerhp->GetComponent<Transform>();
			tr->SetPosition(Vector3(-100.0f, -3.5f, 0.0f));
			tr->SetScale(Vector3(0.5f, 0.5f, 1.0f));

			playerhp->Initalize();

			m_vCreateHps.push_back(playerhp);

	}


	

	void PlayerHP::hpSetPos()
	{

		mFullHp = mPlayerHp / 1;
		mHalfHp = fmodf(mPlayerHp, 1);
		mHpCount = 0;

		float playerhpuipos = -0.5f;
		for (size_t i = 0; i < mFullHp ; i++)
		{
			Transform* tr = m_vCreateHps[i]->GetComponent<Transform>();
			//tr->SetPosition(Vector3(-1.0f - (i / 2), -3.5f, 0.0f));
			m_vCreateHps[i]->SetUiPos(Vector3(playerhpuipos - 0.5f, -3.5f, 0.0f));
			tr->SetPosition(Vector3(playerhpuipos -=0.5f, -3.5f, 0.0f));
			tr->SetScale(Vector3(0.5f, 0.5f, 1.0f));	

			++mHpCount;
		}


		if (mHalfHp > 0.0f)
		{
			Transform* tr = m_vCreateHps[10]->GetComponent<Transform>();
			m_vCreateHps[10]->SetUiPos(Vector3(playerhpuipos - 0.5f, -3.5f, 0.0f));
			tr->SetPosition(Vector3(playerhpuipos -= 0.5f, -3.5f, 0.0f));
			tr->SetScale(Vector3(0.5f, 0.5f, 1.0f));				

			for (size_t i = mHpCount; i < 10; i++)
			{
				Transform* tr = m_vCreateHps[i]->GetComponent<Transform>();
				m_vCreateHps[i]->SetUiPos(Vector3(-100.0f, -3.5f, 0.0f));
				tr->SetPosition(Vector3(-100.0f, -3.5f, 0.0f));
				tr->SetScale(Vector3(0.5f, 0.5f, 1.0f));
			}

		}

		else
		{
			for (size_t i = mHpCount; i < 11; i++)
			{
				Transform* tr = m_vCreateHps[i]->GetComponent<Transform>();
				m_vCreateHps[i]->SetUiPos(Vector3(-100.0f, -3.5f, 0.0f));
				tr->SetPosition(Vector3(-100.0f, -3.5f, 0.0f));
				tr->SetScale(Vector3(0.5f, 0.5f, 1.0f));
			}
		}

	

	}

	void PlayerHP::createMpSet()
	{

		for (size_t i = 0; i < 10; i++)
		{
			PlayerCreateHp* playermp = object::Instantiate<PlayerCreateHp>(eLayerType::UI);
			playermp->SetName(L"Player_Full_Mp");
			playermp->SetTarget(this);
			playermp->SetFullMp(true);


			Transform* tr = playermp->GetComponent<Transform>();
			tr->SetPosition(Vector3(-100.0f, 0.0f, 0.0f));
			tr->SetScale(Vector3(0.5f, 0.5f, 1.0f));

			playermp->Initalize();

			m_vCreateFullMps.push_back(playermp);
		}


		for (size_t i = 0; i < 10; i++)
		{
			PlayerCreateHp* playermp = object::Instantiate<PlayerCreateHp>(eLayerType::UI);
			playermp->SetName(L"Player_Half_Mp");
			playermp->SetTarget(this);
			playermp->SetHalfMp(true);

			Transform* tr = playermp->GetComponent<Transform>();
			tr->SetPosition(Vector3(-100.0f, 0.0f, 0.0f));
			tr->SetScale(Vector3(0.5f, 0.5f, 1.0f));

			playermp->Initalize();

			m_vCreateHalfMps.push_back(playermp);
		}


	}

	void PlayerHP::mpSetPos()
	{
		
		mFullMp = mPlayerFullMp / 1;
		mFullMpCount = 0;
		mHalfMpCount = 0;

	
		
		float playerfullmpuipos = 0.5f;
		for (size_t i = 0; i < mFullMp; i++)
		{
			if (mFullMpCount >= mPlayerMp)
				break;
			Transform* tr = m_vCreateFullMps[i]->GetComponent<Transform>();
			m_vCreateFullMps[i]->SetUiPos(Vector3(playerfullmpuipos + 0.5f, -3.5f, 0.0f));
			tr->SetPosition(Vector3(playerfullmpuipos += 0.5f, -3.5f, 0.0f));
			tr->SetScale(Vector3(0.5f, 0.5f, 1.0f));
			++mFullMpCount;
		}		

		for (size_t i = 0; i < mFullMp - mFullMpCount; i++)
		{

			Transform* tr = m_vCreateHalfMps[i]->GetComponent<Transform>();
			m_vCreateHalfMps[i]->SetUiPos(Vector3(playerfullmpuipos + 0.5f, -3.5f, 0.0f));
			tr->SetPosition(Vector3(playerfullmpuipos += 0.5f, -3.5f, 0.0f));
			tr->SetScale(Vector3(0.5f, 0.5f, 1.0f));
			++mHalfMpCount;
		}
		for (size_t i = mHalfMpCount; i < mFullMp; i++)
		{
			Transform* tr = m_vCreateHalfMps[i]->GetComponent<Transform>();
			m_vCreateHalfMps[i]->SetUiPos(Vector3(-100.0f, 0.0f, 0.0f));
			tr->SetPosition(Vector3(-100.0f, 0.0f, 0.0f));
			tr->SetScale(Vector3(0.5f, 0.5f, 1.0f));
		}




		//float playermpuipos = 0.5f;
		//for (size_t i = 0; i < mFullMp; i++)
		//{

		//	Transform* tr = m_vCreateHalfMps[i]->GetComponent<Transform>();
		//	m_vCreateHalfMps[i]->SetUiPos(Vector3(playermpuipos + 0.5f, -3.5f, 0.0f));
		//	tr->SetPosition(Vector3(playermpuipos += 0.5f, -3.5f, 0.0f));
		//	tr->SetScale(Vector3(0.5f, 0.5f, 1.0f));
		//}




	}

}