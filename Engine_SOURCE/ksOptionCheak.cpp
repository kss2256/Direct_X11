#include "ksOptionCheak.h"
#include "ksSpriteRenderer.h"
#include "ksMaterial.h"
#include "ksMesh.h"
#include "ksResources.h"
#include "ksTransform.h"
#include "ksAudioClip.h"
#include "ksSceneManager.h"
#include "ksPlayerScript.h"
#include "ksInventory.h"
#include "ksOptionCheak.h"

#include "ksInput.h"

namespace ks
{

	bool OptionCheak::m_bOptionCheakOnOff = false;

	OptionCheak::OptionCheak()
	{
		mTransform = GetComponent<Transform>();

		loadSound();

		SpriteRenderer* sr = AddComponent<SpriteRenderer>();


		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"OptionCheakMaterial");
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"OptionCheak", L"UI\\OptionCheak.png");
		mateiral->SetTexture(texture);
		sr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);

	}

	OptionCheak::~OptionCheak()
	{
	}

	void OptionCheak::Initalize()
	{
		mUiPos = mTransform->GetPosition();



		GameObject::Initalize();
	}

	void OptionCheak::Update()
	{
		
		if (m_bOneCheak1)
		{
			mTransform->SetPosition(mUiPos);
			m_bOneCheak1 = false;
			
		}
		else if (m_bOneCheak2)
		{

			mTransform->SetPosition(m_vUiFinalPos);			
			m_bOneCheak2 = false;
			

		}
		else if (m_bOneCheak3)
		{
			mTransform->SetPosition(m_vUiFinalPos);		
			m_bOneCheak3 = false;
		
		}
		else if (m_bOneCheak4)
		{
			mTransform->SetPosition(m_vUiFinalPos);		
			m_bOneCheak4 = false;
		
		}
		else if (m_bOneCheak5)
		{
			mTransform->SetPosition(m_vUiFinalPos);			
			m_bOneCheak5 = false;
		}

		


		UIBase::Update();
	}

	void OptionCheak::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void OptionCheak::Render()
	{
		GameObject::Render();
	}

	void OptionCheak::loadSound()
	{
	}

}