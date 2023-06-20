#include "ksTitleScene.h"
#include "ksTransform.h"
#include "ksMeshRenderer.h"
#include "ksRenderer.h"
#include "ksResources.h"
#include "ksTexture.h"
#include "ksPlayerScript.h"
#include "ksCamera.h"
#include "ksCameraScript.h"
#include "ksSpriteRenderer.h"
#include "ksGridScript.h"
#include "ksObject.h"
#include "ksInput.h"
#include "ksCollider2D.h"
#include "ksCursor.h"
#include "ksCursorScript.h"
#include "ksPlayer.h"
#include "ksMonster.h"
#include "ksCollisionManager.h"
#include "ksAnimator.h"
#include "ksAudioClip.h"
#include "ksAudioListener.h"
#include "ksFontWrapper.h"


#include "ksApplication.h"

extern ks::Application application;

namespace ks
{
	TitleScene::TitleScene()
		: Scene(eSceneType::Tilte)
		, m_BgmSound(false)
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initalize()
	{
		// Main Camera Game Object
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		//cameraObj->AddComponent<CameraScript>();
		mainCamera = cameraComp;

		//object::DontDestroyOnLoad(layer2obj);
		//monobj->AddComponent<PlayerScript>();


		//std::shared_ptr<AudioClip> titlesound = Resources::Load<AudioClip>
		//	(L"TiTle", L"D:\\50\\Resources\\Sound\\TiTle.ogg");

		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);

		float width = (float)(winRect.right - winRect.left);
		float height = (float)(winRect.bottom - winRect.top);

		{
			Player* obj = object::Instantiate<Player>(eLayerType::Player);
			obj->SetName(L"TITLE");

			Transform* tr = obj->GetComponent<Transform>();


			//tr->SetPosition(Vector3(1.0, 1.0, 1.0f));
			tr->SetScale(Vector3(width / 100.f, height / 100.f, 0.0f));

			MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
			//SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();

			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"TitleMaterial");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

			mr->SetMesh(mesh);
		}

		{
			Player* monobj = object::Instantiate<Player>(eLayerType::Mouse);
			monobj->SetName(L"CURSOR");
			monobj->AddComponent<Cursor>()->SetTarget(monobj);
			Transform* montr = monobj->GetComponent<Transform>();
			montr->SetScale(Vector3(0.7f, 0.7f, 1.0f));
			//montr->SetPosition(Vector3(0.f, 0.f, 0.9f));
			SpriteRenderer* monmr = monobj->AddComponent<SpriteRenderer>();

			std::shared_ptr<Material> monmateiral = Resources::Find<Material>(L"CursorMaterial");
			monmr->SetMaterial(monmateiral);
			std::shared_ptr<Mesh> monmesh = Resources::Find<Mesh>(L"RectMesh");
			monmr->SetMesh(monmesh);
			//monobj->DontDestroy(false);
		}


		{
			Player* monobj = object::Instantiate<Player>(eLayerType::Player);
			monobj->SetName(L"LAYER1");
			Transform* montr = monobj->GetComponent<Transform>();
			montr->SetScale(Vector3(10.f, 10.f, 1.0f));
			montr->SetPosition(Vector3(1.f, 0.f, 2.0f));
			MeshRenderer* monmr = monobj->AddComponent<MeshRenderer>();

			std::shared_ptr<Material> monmateiral = Resources::Find<Material>(L"Layer1Material");
			monmr->SetMaterial(monmateiral);
			std::shared_ptr<Mesh> monmesh = Resources::Find<Mesh>(L"RectMesh");
			monmr->SetMesh(monmesh);

		}

		{
			Player* layer2obj = object::Instantiate<Player>(eLayerType::Player);
			layer2obj->SetName(L"LAYER2");
			Transform* montr = layer2obj->GetComponent<Transform>();
			montr->SetScale(Vector3(10.f, 10.f, 1.0f));
			montr->SetPosition(Vector3(-4.0f, 0.f, 2.0f));
			MeshRenderer* monmr = layer2obj->AddComponent<MeshRenderer>();

			std::shared_ptr<Material> monmateiral = Resources::Find<Material>(L"Layer2Material");
			monmr->SetMaterial(monmateiral);
			std::shared_ptr<Mesh> monmesh = Resources::Find<Mesh>(L"RectMesh");
			monmr->SetMesh(monmesh);


		}

		{
			Player* layer2obj = object::Instantiate<Player>(eLayerType::Player);
			layer2obj->SetName(L"LAYER3");
			Transform* montr = layer2obj->GetComponent<Transform>();
			montr->SetScale(Vector3(10.f, 10.f, 1.0f));
			montr->SetPosition(Vector3(6.0f, 0.f, 2.0f));
			MeshRenderer* monmr = layer2obj->AddComponent<MeshRenderer>();

			std::shared_ptr<Material> monmateiral = Resources::Find<Material>(L"Layer3Material");
			monmr->SetMaterial(monmateiral);
			std::shared_ptr<Mesh> monmesh = Resources::Find<Mesh>(L"RectMesh");
			monmr->SetMesh(monmesh);

		}

		{
			Player* layer2obj = object::Instantiate<Player>(eLayerType::Player);
			layer2obj->SetName(L"LOGO");
			Transform* montr = layer2obj->GetComponent<Transform>();
			montr->SetScale(Vector3(10.f, 10.f, 1.0f));
			montr->SetPosition(Vector3(1.0f, 1.f, 2.0f));
			MeshRenderer* monmr = layer2obj->AddComponent<MeshRenderer>();

			std::shared_ptr<Material> monmateiral = Resources::Find<Material>(L"LogoMaterial");
			monmr->SetMaterial(monmateiral);
			std::shared_ptr<Mesh> monmesh = Resources::Find<Mesh>(L"RectMesh");
			monmr->SetMesh(monmesh);

		}


	



		Scene::Initalize();

	}
	void TitleScene::Update()
	{

		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Play);
		}

		Scene::Update();
	}
	void TitleScene::FixedUpdate()
	{
		if(!m_BgmSound)
		{
			std::shared_ptr<AudioClip> titlesound = Resources::Load<AudioClip>
				(L"TiTle", L"..\\Resources\\Sound\\TiTle.ogg");
			titlesound->SetLoop(false);
			titlesound->Play();
			m_BgmSound = true;	
			

		}

		Scene::FixedUpdate();
	}
	void TitleScene::Render()
	{
		Scene::Render();
	}
	void TitleScene::OnEnter()
	{
		Destroy();
		Initalize();
		m_BgmSound = false;

	}
	void TitleScene::OnExit()
	{
		std::shared_ptr<AudioClip> titlesound = Resources::Find<AudioClip>(L"TiTle");
		titlesound->Stop();

		//LayerObjectClear(eLayerType::Camera);
		LayerObjectClear(eLayerType::Player);
		LayerObjectClear(eLayerType::Mouse);

		Destroy();
	}
}
