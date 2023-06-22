#include "ksVolume.h"
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

	Volume::Volume()
	{
		mTransform = GetComponent<Transform>();

		SpriteRenderer* sr = AddComponent<SpriteRenderer>();


		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"VolumeMaterial");
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"100", L"UI\\100.png");
		mateiral->SetTexture(texture);
		sr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);

	}

	Volume::~Volume()
	{
	}

	void Volume::Initalize()
	{
		mUiPos = mTransform->GetPosition();



		GameObject::Initalize();
	}

	void Volume::Update()
	{
		if(m_bChangeVolume)
		{
			switch (m_eVolume)
			{
			case e_Volume::Volume_100:
			{
				std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"VolumeMaterial");
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"100", L"UI\\100.png");
				mateiral->SetTexture(texture);
			}
			break;
			case e_Volume::Volume_0:
			{
				std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"VolumeMaterial");
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"0", L"UI\\0.png");
				mateiral->SetTexture(texture);
			}
			break;
			case e_Volume::Volume_20:
			{
				std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"VolumeMaterial");
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"20", L"UI\\20.png");
				mateiral->SetTexture(texture);
			}
			break;
			case e_Volume::Volume_40:
			{
				std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"VolumeMaterial");
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"40", L"UI\\40.png");
				mateiral->SetTexture(texture);
			}
			break;
			case e_Volume::Volume_60:
			{
				std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"VolumeMaterial");
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"60", L"UI\\60.png");
				mateiral->SetTexture(texture);
			}
			break;
			case e_Volume::Volume_80:
			{
				std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"VolumeMaterial");
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"80", L"UI\\80.png");
				mateiral->SetTexture(texture);
			}
			break;
			}
			m_bChangeVolume = false;
		}


		UIBase::Update();
	}

	void Volume::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void Volume::Render()
	{
		GameObject::Render();
	}

}