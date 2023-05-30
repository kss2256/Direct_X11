#include "ksPlayerMissile.h"
#include "ksTransform.h"
#include "ksSpriteRenderer.h"
#include "ksResources.h"
#include "ksTexture.h"
#include "ksMaterial.h"
#include "ksMesh.h"
#include "ksAnimator.h"
#include "ksTime.h"



#include "ksScene.h"
#include "ksSceneManager.h"

#include "ksInput.h"


namespace ks
{
	float PlayerMissile::mCooldownTime = 0.f;

	PlayerMissile::PlayerMissile()
	{

		mTransform = GetComponent<Transform>();
		
		std::shared_ptr<Texture> bow1 = Resources::Load<Texture>(L"bow1", L"Attack\\bow1.png");
		
		
		
		SpriteRenderer* sr = AddComponent<SpriteRenderer>();
				
		
		std::shared_ptr<Material> mr = Resources::Find<Material>(L"SpriteMaterial");
		mr->SetTexture(bow1);
		sr->SetMaterial(mr);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);


	}

	PlayerMissile::~PlayerMissile()
	{
	}

	void PlayerMissile::Initalize()
	{
		


	}

	void PlayerMissile::Update()
	{

		//if (mPlayer)
		//{
		//	mState = mPlayer->GetPlayer();			
		//}

		//if (mState.progress == eProgress::Step_1)
		//{			
		//	mState.progress = eProgress::Step_2;
		//	mPlayer->SetPlayer(mState);

		//	mDir = GetDirection();
		//	mDir.Normalize();
		//}

		//if (mState.progress == eProgress::Step_2)
		//{
		//	mPos = mTransform->GetPosition();

		//	mCooldownTime += Time::DeltaTime();
		//	mPos.x += mDir.x * 3.f * Time::DeltaTime();
		//	mPos.y += mDir.y * 3.f * Time::DeltaTime();

		//	mTransform->SetPosition(mPos);
		//	if (mCooldownTime >= 2.2f)
		//	{
		//		mState.progress = eProgress::End;
		//		mPlayer->SetPlayer(mState);
		//		mCooldownTime = 0.f;
		//	}			
		//}	

		//if (mState.progress == eProgress::End)
		//{

		//	Scene* scene = SceneManager::GetActiveScene();

		//	const std::vector<GameObject*>& obj = scene->GetGameObjects(eLayerType::Player_Effect);

		//	for (size_t i = 0; i < obj.size(); i++)
		//	{
		//		if (obj[i] != nullptr)
		//		{
		//			obj[i]->Death();
		//		}
		//		scene->Destroy();
		//	}

		//}

		Vec3 pos = mTransform->GetPosition();
		
		pos.y += 3.0f * Time::DeltaTime();
		
		mTransform->SetPosition(pos);


		mCooldownTime += Time::DeltaTime();
		if (mCooldownTime >= 2.2f)
		{
			Scene* scene = SceneManager::GetActiveScene();

			const std::vector<GameObject*>& obj = scene->GetGameObjects(eLayerType::Player_Effect);

			for (size_t i = 0; i < obj.size(); i++)
			{
				if (obj[i] != nullptr)
				{
					obj[i]->Death();
				}
				//scene->Destroy();
			}
			mCooldownTime = 0.f;
		}

		


		GameObject::Update();
	}

	void PlayerMissile::FixedUpdate()
	{

		GameObject::FixedUpdate();
	}

	void PlayerMissile::Render()
	{

		GameObject::Render();
	}

}