#include "ksOnOff.h"
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
#include "ksObject.h"

#include "ksInput.h"


namespace ks
{

	//bool OnOff::m_bOnOffCheak = false;

	OnOff::OnOff()
	{

		mTransform = GetComponent<Transform>();

		SpriteRenderer* sr = AddComponent<SpriteRenderer>();


		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"OnOffMaterial");
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"OFF", L"UI\\OFF.png");
		mateiral->SetTexture(texture);
		sr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);

	}

	OnOff::~OnOff()
	{
	}

	void OnOff::Initalize()
	{
		mUiPos = mTransform->GetPosition();



		GameObject::Initalize();
	}

	void OnOff::Update()
	{



		if (m_bOnOffCheak)
		{
			if(m_bOnOffOneCheak)
			{

				std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"OnOffMaterial");
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"ON", L"UI\\ON.png");
				mateiral->SetTexture(texture);
				m_bOnOffOneCheak = false;
			}
		}
		else
		{
			if (m_bOnOffOneCheak)
			{
				std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"OnOffMaterial");
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"OFF", L"UI\\OFF.png");
				mateiral->SetTexture(texture);
				m_bOnOffOneCheak = false;
			}
		}


		UIBase::Update();
	}

	void OnOff::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void OnOff::Render()
	{
		GameObject::Render();
	}

}
