#include "ksScene.h"


namespace ks
{
	Scene::Scene(eSceneType type)
		: mType(type)
	{
		mLayers.resize((UINT)eLayerType::End);
	}
	Scene::~Scene()
	{

	}
	void Scene::Initalize()
	{
		for (Layer& layer : mLayers)
		{
			layer.Initalize();
		}
	}
	void Scene::Update()
	{
		for (Layer& layer : mLayers)
		{
			layer.Update();
		}
	}
	void Scene::FixedUpdate()
	{
		for (Layer& layer : mLayers)
		{
			layer.FixedUpdate();
		}
	}
	void Scene::Render()
	{
		for (Layer& layer : mLayers)
		{
			layer.Render();
		}
	}
	void Scene::Destroy()
	{
		for (Layer& layer : mLayers)
		{
			layer.Destroy();
		}
	}
	void Scene::OnEnter()
	{

	}
	void Scene::OnExit()
	{
	}
	void Scene::AddGameObject(GameObject* gameObj, const eLayerType type)
	{
		mLayers[(UINT)type].AddGameObject(gameObj);
		gameObj->SetLayerType(type);
	}

	std::vector<GameObject*> Scene::GetDontDestroyGameObjects()
	{
		std::vector<GameObject*> gameObjects;
		for (Layer& layer : mLayers)
		{
			std::vector<GameObject*> dontGameObjs
				= layer.GetDontDestroyGameObjects();

			gameObjects.insert(gameObjects.end()
				, dontGameObjs.begin()
				, dontGameObjs.end());
		}

		return gameObjects;
	}
	const std::vector<GameObject*>& Scene::GetGameObjects(const eLayerType type)
	{
		return mLayers[(UINT)type].GetGameObjects();
	}
	void Scene::LayerObjectClear(const eLayerType type)
	{
		std::vector<GameObject*> obj = GetGameObjects(type);

		for (size_t i = 0; i < obj.size(); i++)
		{
			if (obj[i] != nullptr)
			{
				obj[i]->Death();
			}
		}


	}

}
