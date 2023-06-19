#include "ksSkilUi.h"
#include "ksSpriteRenderer.h"
#include "ksMaterial.h"
#include "ksMesh.h"
#include "ksResources.h"
#include "ksTransform.h"
#include "ksObject.h"
#include "ksPlayerItem.h"

#include "ksInput.h"



namespace ks
{

	SkilUi::SkilUi()
	{
		mTransform = GetComponent<Transform>();

		mAnimator = AddComponent<Animator>();

		SpriteRenderer* sr = AddComponent<SpriteRenderer>();

		loadAnimation();

		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"CoinMaterial");
		sr->SetMaterial(mateiral);

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);

		
		{
			m_pSkilSlot_1 = object::Instantiate<SkilSlot>(eLayerType::Gold_Ui);
			m_pSkilSlot_1->SetName(L"Skil_Slot1");


			Transform* tr = m_pSkilSlot_1->GetComponent<Transform>();
			tr->SetPosition(Vector3(-1.1f, -2.8f, 0.0f));
			tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));

			m_pSkilSlot_1->Initalize();
		}

		{
			m_pSkilSlot_2 = object::Instantiate<SkilSlot>(eLayerType::Gold_Ui);
			m_pSkilSlot_2->SetName(L"Skil_Slot2");


			Transform* tr = m_pSkilSlot_2->GetComponent<Transform>();
			tr->SetPosition(Vector3(-0.5f, -2.2f, 0.0f));
			tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));

			m_pSkilSlot_2->Initalize();
		}

		{
			m_pSkilSlot_3 = object::Instantiate<SkilSlot>(eLayerType::Gold_Ui);
			m_pSkilSlot_3->SetName(L"Skil_Slot3");


			Transform* tr = m_pSkilSlot_3->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.3f, -2.2f, 0.0f));
			tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));

			m_pSkilSlot_3->Initalize();
		}

		{
			m_pSkilSlot_4 = object::Instantiate<SkilSlot>(eLayerType::Gold_Ui);
			m_pSkilSlot_4->SetName(L"Skil_Slot4");


			Transform* tr = m_pSkilSlot_4->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.9f, -2.8f, 0.0f));
			tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));

			m_pSkilSlot_4->Initalize();
		}
	}

	SkilUi::~SkilUi()
	{
	}

	void SkilUi::Initalize()
	{
	


		mUiPos = mTransform->GetPosition();

		GameObject::Initalize();
	}

	void SkilUi::Update()
	{
		if (mTarget != nullptr)
		{
			//mPlayerPos = mTarget->GetComponent<Transform>()->GetPosition();			

			mPlayerPos = mainCamera->GetOwner()->GetComponent<Transform>()->GetPosition();


			mFinalPos = mPlayerPos + mUiPos;

			mTransform->SetPosition(mFinalPos);
		}

		if (Input::GetKeyDown(eKeyCode::N_1))
		{
			if(m_pSkilSlot_1->m_bSlotOnOff)
			{
				m_pActiveSlot = m_pSkilSlot_1;
				changeAnimation();
			}
		}		
		if (Input::GetKeyDown(eKeyCode::N_2))
		{
			if (m_pSkilSlot_2->m_bSlotOnOff)
			{
				m_pActiveSlot = m_pSkilSlot_2;
				changeAnimation();
			}
		}
		if (Input::GetKeyDown(eKeyCode::N_3))
		{
			if (m_pSkilSlot_3->m_bSlotOnOff)
			{
				m_pActiveSlot = m_pSkilSlot_3;
				changeAnimation();
			}
		}		
		if (Input::GetKeyDown(eKeyCode::N_4))
		{
			if (m_pSkilSlot_4->m_bSlotOnOff)
			{
				m_pActiveSlot = m_pSkilSlot_4;
				changeAnimation();
			}
		}





		UIBase::Update();
	}

	void SkilUi::FixedUpdate()
	{

		GameObject::FixedUpdate();
	}

	void SkilUi::Render()
	{

		GameObject::Render();
	}

	void SkilUi::CreateSkillbook(eItem skil)
	{
		

		slotCheak(skil);

		



	}

	void SkilUi::loadAnimation()
	{
		std::shared_ptr<Texture> skil = Resources::Load<Texture>(L"Skil", L"Skil\\item_magic.png");

		mNumbers.push_back(21);
		
		CreateAnimation(L"Ice_Skil", skil, mAnimator, Vector2(32.0f, 32.0f), Vec2::Zero, mNumbers, 0.15f);
		mNumbers.clear();

		mNumbers.push_back(17);

		CreateAnimation(L"Dark_Skil", skil, mAnimator, Vector2(32.0f, 32.0f), Vec2::Zero, mNumbers, 0.15f);
		mNumbers.clear();


		mNumbers.push_back(13);

		CreateAnimation(L"Barrier_Skil", skil, mAnimator, Vector2(32.0f, 32.0f), Vec2::Zero, mNumbers, 0.15f);
		mNumbers.clear();


		mNumbers.push_back(16);

		CreateAnimation(L"Lighting_Skil", skil, mAnimator, Vector2(32.0f, 32.0f), Vec2::Zero, mNumbers, 0.15f);
		mNumbers.clear();

	}

	void SkilUi::CreateAnimation(const std::wstring& name, std::shared_ptr<Texture> texture, Animator* animaotr, Vec2 scale, Vector2 offset, std::vector<UINT> numbers, float duration)
	{
		// 이중 포문 		
		Vec2 value = Vec2(texture->GetWidth() / scale.x, texture->GetHeight() / scale.y);
		UINT Col = (UINT)value.x;					//3개?
		UINT Row = (UINT)value.y;					//10개?

		UINT textureeLegth = (UINT)(value.x * value.y);		//총 개수 30개

		//이중 포문 이건 10행
		for (UINT i = 0; i < Row; i++)
		{
			//이중 포문 이건 3열
			for (UINT j = 0; j < Col; j++)
			{
				Sprite animation;

				animation.AnimationName = name;
				animation.atlasSize = scale;
				animation.duration = duration;
				animation.leftTop = Vec2(j * scale.x, i * scale.y);
				animation.offset = offset;
				//animation.pos = mTransform->GetPosition(); // 이건 필요 없는듯 ? 필요할떄 사용예정 포지션을 받아와야함
				animation.size = scale;


				mSvaeSprite.push_back(animation);
			}
		}

		for (size_t i = 0; i < numbers.size(); i++)
		{
			std::vector<UINT>::iterator iter = numbers.begin();

			mSprites.push_back(mSvaeSprite[iter[i]]);
		}


		for (size_t i = 0; i < mSprites.size(); i++)
		{
			mSprites[i].leftTop = Vector2((mSprites[i].leftTop.x / texture->GetWidth()), (mSprites[i].leftTop.y) / texture->GetHeight());
			mSprites[i].size = Vector2(mSprites[i].size.x / texture->GetWidth(), mSprites[i].size.y / texture->GetHeight());
			mSprites[i].offset = mSprites[i].offset;
			mSprites[i].duration = mSprites[i].duration;
			mSprites[i].atlasSize = Vector2(400.0f / texture->GetWidth(), 400.0f / texture->GetHeight());
			mSprites[i].AnimationName = mSprites[i].AnimationName;
		}



		animaotr->CreateAfter(mSprites, texture);
		mSvaeSprite.clear();
		mSprites.clear();
	}

	void SkilUi::slotCheak(eItem skil)
	{
		if (!m_pSkilSlot_1->m_bSlotOnOff)
		{			
			createSkilSlot(skil, m_pSkilSlot_1->mUiPos);
			m_pSkilSlot_1->m_bSlotOnOff = true;
			m_pSkilSlot_1->e_skil = skil;
		}
		else if (!m_pSkilSlot_2->m_bSlotOnOff)
		{
			createSkilSlot(skil, m_pSkilSlot_2->mUiPos);
			m_pSkilSlot_2->m_bSlotOnOff = true;
			m_pSkilSlot_2->e_skil = skil;
		}
		else if (!m_pSkilSlot_3->m_bSlotOnOff)
		{
			createSkilSlot(skil, m_pSkilSlot_3->mUiPos);
			m_pSkilSlot_3->m_bSlotOnOff = true;
			m_pSkilSlot_3->e_skil = skil;
		}
		else if (!m_pSkilSlot_4->m_bSlotOnOff)
		{
			createSkilSlot(skil, m_pSkilSlot_4->mUiPos);
			m_pSkilSlot_4->m_bSlotOnOff = true;
			m_pSkilSlot_4->e_skil = skil;
		}

		

	}

	void SkilUi::createSkilSlot(eItem skil, Vec3 pos)
	{

		PlayerItem* Legendmp = object::Instantiate<PlayerItem>(eLayerType::Skil_Ui);
		Legendmp->SetName(L"Skil_Book");
		Legendmp->SetTarget(mTarget);

		Legendmp->SetPlayerItem(skil);

		
	


		switch (skil)
		{		
		case ks::eItem::Dark:
		{
			Transform* mptr = Legendmp->GetComponent<Transform>();			
			mptr->SetPosition(pos);
			mptr->SetScale(Vec3(7.5f, 7.8f, 1.0f));
		}
			break;
		case ks::eItem::Ice:
		{
			Transform* mptr = Legendmp->GetComponent<Transform>();
			//pos.x -= -5.0f;
			mptr->SetPosition(pos);
			mptr->SetScale(Vec3(9.0f, 9.0f, 1.0f));
		}
			break;
		case ks::eItem::Barrier:
		{
			Transform* mptr = Legendmp->GetComponent<Transform>();
			mptr->SetPosition(pos);
			mptr->SetScale(Vec3(8.9f, 8.9f, 1.0f));
		}
			break;
		case ks::eItem::Lighting:
		{
			Transform* mptr = Legendmp->GetComponent<Transform>();
			mptr->SetPosition(pos);
			mptr->SetScale(Vec3(6.5f, 6.8f, 1.0f));
		}
			break;
		}

		Legendmp->SetSkilSlot(true);
		Legendmp->Initalize();

	}

	void SkilUi::changeAnimation()
	{
		switch (m_pActiveSlot->e_skil)
		{
		case ks::eItem::Dark:
		{
			mAnimator->Play(L"Dark_Skil", false);
			mTransform->SetScale(Vec3(8.5f, 8.8f, 1.0f));
		}
			break;
		case ks::eItem::Ice:
		{		
			mAnimator->Play(L"Ice_Skil", false);
			mTransform->SetScale(Vec3(10.0f, 10.0f, 1.0f));
		}
			break;
		case ks::eItem::Barrier:
		{
			mAnimator->Play(L"Barrier_Skil", false);
			mTransform->SetScale(Vec3(9.9f, 9.9f, 1.0f));
		}
			break;
		case ks::eItem::Lighting:
		{	
			mAnimator->Play(L"Lighting_Skil", false);
			mTransform->SetScale(Vec3(7.5f, 7.8f, 1.0f));
		}
			break;
		}


	}

}