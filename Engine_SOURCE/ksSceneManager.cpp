#include "ksSceneManager.h"
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
#include "ksTitleScene.h"
#include "ksPlayScene.h"

namespace ks
{
	std::vector<Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initalize()
	{
		mScenes.resize((UINT)eSceneType::End);

		mScenes[(UINT)eSceneType::Tilte] = new TitleScene();
		mScenes[(UINT)eSceneType::Play] = new PlayScene();

		mActiveScene = mScenes[(UINT)eSceneType::Tilte];


		mActiveScene->Initalize();

		/*for (Scene* scene : mScenes)
		{
			scene->Initalize();
		}*/
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::FixedUpdate()
	{
		mActiveScene->FixedUpdate();
	}

	void SceneManager::Render()
	{
		mActiveScene->Render();
	}

	void SceneManager::Destroy()
	{
		mActiveScene->Destroy();
	}

	void SceneManager::Release()
	{
		for (Scene* scene : mScenes)
		{
			delete scene;
			scene = nullptr;
		}
	}
	void SceneManager::LoadScene(eSceneType type)
	{
		if (mActiveScene)
			mActiveScene->OnExit();

		// �ٲ� dontDestory ������Ʈ�� ���������� ���� �Ѱ�����Ѵ�.
		std::vector<GameObject*> gameObjs
			= mActiveScene->GetDontDestroyGameObjects();
		mActiveScene = mScenes[(UINT)type];

		for (GameObject* obj : gameObjs)
		{
			eLayerType type = obj->GetLayerType();
			mActiveScene->AddGameObject(obj, type);
		}


		//mActiveScene = mScenes[(UINT)type];

		mActiveScene->OnEnter();

	}
}