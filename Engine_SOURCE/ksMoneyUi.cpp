#include "ksMoneyUi.h"
#include "ksSpriteRenderer.h"
#include "ksMaterial.h"
#include "ksMesh.h"
#include "ksResources.h"
#include "ksTransform.h"
#include "ksObject.h"
#include "ksTime.h"
#include "ksCreateMoney.h"


#include "ksInput.h"


namespace ks
{

	MoneyUi::MoneyUi()
	{

		mTransform = GetComponent<Transform>();

		SpriteRenderer* sr = AddComponent<SpriteRenderer>();


		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"MoneyUiMaterial");
		sr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);


	}

	MoneyUi::~MoneyUi()
	{
	}

	void MoneyUi::Initalize()
	{

		if (nullptr != mTarget)
		{
			UINT coin = mTarget->GetPlayerCoin();
			m_uPrevMoney = coin;
			m_uMoney_10 = UINT(coin * 0.1);

			m_uMoney_1 = coin % 10;
			m_uMoney_10 = m_uMoney_10 % 10;
			m_uMoney_100 = coin / 100;
			
			


			createMoney(eMoneyCheak::Money_1);			
			createMoney(eMoneyCheak::Money_10);			
			createMoney(eMoneyCheak::Money_100);



			//createMoney(eMoneyCheak::Money_1);
			//if (m_uMoney_10 > 0)
			//{
			//	createMoney(eMoneyCheak::Money_10);
			//}
			//if (m_uMoney_100 > 0)
			//{
			//	createMoney(eMoneyCheak::Money_100);
			//}

		}

		GameObject::Initalize();

	}

	void MoneyUi::Update()
	{
		if (mTarget->GetPlayerCoin() != m_uPrevMoney)
		{
			UINT coin = mTarget->GetPlayerCoin();
			m_uPrevMoney = coin;
			m_uMoney_10 = UINT(coin * 0.1);

			m_uMoney_1 = coin % 10;
			m_uMoney_10 = m_uMoney_10 % 10;
			m_uMoney_100 = coin / 100;


			if (m_pMoney_1)
			{
				m_pMoney_1->SetMoney(m_uMoney_1);
				m_pMoney_1->SetMoneyChange(true);	
			}
			if (m_pMoney_10)
			{
				m_pMoney_10->SetMoney(m_uMoney_10);
				m_pMoney_10->SetMoneyChange(true);	
			}
			if (m_pMoney_100)
			{
				m_pMoney_100->SetMoney(m_uMoney_100);
				m_pMoney_100->SetMoneyChange(true);
			}
			

			m_uPrevMoney = mTarget->GetPlayerCoin();
		}



		UIBase::Update();
	}

	void MoneyUi::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void MoneyUi::Render()
	{
		GameObject::Render();
	}

	void MoneyUi::createMoney(eMoneyCheak value)
	{

		switch (value)
		{
		case eMoneyCheak::Money_1:
		{

			m_pMoney_1 = object::Instantiate<CreateMoney>(eLayerType::Gold_Ui);
			m_pMoney_1->SetName(L"Money_1");
			m_pMoney_1->SetTarget(mTarget);
			m_pMoney_1->SetMoney(m_uMoney_1);

			Transform* tr = m_pMoney_1->GetComponent<Transform>();
			tr->SetPosition(Vector3(8.5f, 4.7f, 0.0f));
			tr->SetScale(Vector3(10.0f, 10.0f, 1.0f));

			m_pMoney_1->Initalize();

		}
			break;
		case eMoneyCheak::Money_10:
		{
			m_pMoney_10 = object::Instantiate<CreateMoney>(eLayerType::Gold_Ui);
			m_pMoney_10->SetName(L"Money_10");
			m_pMoney_10->SetTarget(mTarget);
			m_pMoney_10->SetMoney(m_uMoney_10);

			Transform* tr = m_pMoney_10->GetComponent<Transform>();
			tr->SetPosition(Vector3(8.2f, 4.7f, 0.0f));
			tr->SetScale(Vector3(10.0f, 10.0f, 1.0f));

			m_pMoney_10->Initalize();
		}
			break;
		case eMoneyCheak::Money_100:
		{
			m_pMoney_100 = object::Instantiate<CreateMoney>(eLayerType::Gold_Ui);
			m_pMoney_100->SetName(L"Money_100");
			m_pMoney_100->SetTarget(mTarget);
			m_pMoney_100->SetMoney(m_uMoney_100);

			Transform* tr = m_pMoney_100->GetComponent<Transform>();
			tr->SetPosition(Vector3(7.9f, 4.7f, 0.0f));
			tr->SetScale(Vector3(10.0f, 10.0f, 1.0f));

			m_pMoney_100->Initalize();
		}
			break;		
		}





	}



}