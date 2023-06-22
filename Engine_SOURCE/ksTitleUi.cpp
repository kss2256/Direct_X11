#include "ksTitleUi.h"
#include "ksSpriteRenderer.h"
#include "ksMaterial.h"
#include "ksMesh.h"
#include "ksResources.h"
#include "ksTransform.h"
#include "ksAudioClip.h"
#include "ksSceneManager.h"


#include "ksInput.h"


namespace ks
{
	TitleUi::TitleUi()
	{
		mTransform = GetComponent<Transform>();



		SpriteRenderer* sr = AddComponent<SpriteRenderer>();


		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"TitleUIMaterial");
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Title_None", L"Title\\Title_None.png");
		mateiral->SetTexture(texture);
		sr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);


	}

	TitleUi::~TitleUi()
	{
	}

	void TitleUi::Initalize()
	{
		std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"Title_None");

		float height = (float)texture->GetHeight();
		float width = (float)texture->GetWidth();
		m_vUiScale = Vec3(width, height / 4, 1.0f);
		GameObject::Initalize();





	}

	void TitleUi::Update()
	{

		m_vMousePos = Input::GetMousWorldPosition();

		//처음 사운드 로드 작업
		if (!m_bSoundUpdate)
		{
			loadSound();
			m_bSoundUpdate = true;
		}

		//마우스가 위에 올라오면 소리 작업 (ok)
		//마우스가 위에 올라올때 위치마다 텍스트 바꿔주기 작업 중
		if (IsMouseOn())
		{					

			if (m_vMousePos.y <= 0.0f && m_vMousePos.y >= -1.11f)
			{				
				bool lbtn = Input::GetKeyDown(eKeyCode::LBTN);
				if (lbtn)
				{
					mTitle->SetChangeScene(true);
				}
				if(!m_bOneCheak1)
				{
					selectMouseOnSound();
					std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"TitleUIMaterial");
					std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Title_Start", L"Title\\Title_Start.png");
					mateiral->SetTexture(texture);
					m_bOneCheak1 = true;
					m_bOneCheak2 = false;
					m_bOneCheak3 = false;
					m_bOneCheak4 = false;
					m_bOneCheak5 = false;
				}
			}
			else if (m_vMousePos.y <= -1.12f && m_vMousePos.y >= -1.71f)
			{
				if(!m_bOneCheak2)
				{
					selectMouseOnSound();
					std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"TitleUIMaterial");
					std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Title_Continue", L"Title\\Title_Continue.png");
					mateiral->SetTexture(texture);
					m_bOneCheak1 = false;
					m_bOneCheak2 = true;
					m_bOneCheak3 = false;
					m_bOneCheak4 = false;
					m_bOneCheak5 = false;
				}
			}
			else if (m_vMousePos.y <= -1.72f && m_vMousePos.y >= -2.21f)
			{
				if(!m_bOneCheak3)
				{
					selectMouseOnSound();
					std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"TitleUIMaterial");
					std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Title_Option", L"Title\\Title_Option.png");
					mateiral->SetTexture(texture);
					m_bOneCheak1 = false;
					m_bOneCheak2 = false;
					m_bOneCheak3 = true;
					m_bOneCheak4 = false;
					m_bOneCheak5 = false;
				}
			}
			else if (m_vMousePos.y <= -2.22f && m_vMousePos.y >= -2.96f)
			{

				bool lbtn = Input::GetKeyDown(eKeyCode::LBTN);
				if (lbtn)
				{					
				
				}

				if(!m_bOneCheak4)
				{
					selectMouseOnSound();
					std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"TitleUIMaterial");
					std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Title_Exit", L"Title\\Title_Exit.png");
					mateiral->SetTexture(texture);
					m_bOneCheak1 = false;
					m_bOneCheak2 = false;
					m_bOneCheak3 = false;
					m_bOneCheak4 = true;
					m_bOneCheak5 = false;
				}
			}


		}
		else
		{
			if(!m_bOneCheak5)
			{
				std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"TitleUIMaterial");
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Title_None", L"Title\\Title_None.png");
				mateiral->SetTexture(texture);
				m_bOneCheak1 = false;
				m_bOneCheak2 = false;
				m_bOneCheak3 = false;
				m_bOneCheak4 = false;
				m_bOneCheak5 = true;
			}
			
		}

		UIBase::Update();
	}

	void TitleUi::FixedUpdate()
	{
		
		GameObject::FixedUpdate();
	}

	void TitleUi::Render()
	{
		
		GameObject::Render();
	}

	void TitleUi::loadSound()
	{
		std::shared_ptr<AudioClip> Select_MouseOn = Resources::Load<AudioClip>
			(L"Select_MouseOn", L"..\\Resources\\Sound\\Select_MouseOn.ogg");



	}

	void TitleUi::selectMouseOnSound()
	{
		std::shared_ptr<AudioClip> sound = Resources::Find<AudioClip>(L"Select_MouseOn");
		sound->SetLoop(false);
		sound->Play();
	}

}