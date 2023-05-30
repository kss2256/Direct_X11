#include "ksMonsterMissile.h"
#include "ksTransform.h"
#include "ksSpriteRenderer.h"
#include "ksResources.h"
#include "ksTexture.h"
#include "ksMaterial.h"
#include "ksMesh.h"
#include "ksAnimator.h"
#include "ksTime.h"
#include "ksCollider2D.h"

#include "ksScene.h"
#include "ksSceneManager.h"


#define PI 3.1415926535f

namespace ks
{	

	MonsterMissile::MonsterMissile()
		: mSpeed(3.0f)
		, mCollider(nullptr)
	{

		mTransform = GetComponent<Transform>();

		std::shared_ptr<Texture> bow1 = Resources::Load<Texture>(L"Monster_Tan", L"Attack\\Monster_Tan.png");

		



		SpriteRenderer* sr = AddComponent<SpriteRenderer>();


		std::shared_ptr<Material> mr = Resources::Find<Material>(L"MonsterMaterial");
		
		mr->SetTexture(bow1);
		sr->SetMaterial(mr);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);


	}

	MonsterMissile::~MonsterMissile()
	{
	}

	void MonsterMissile::Initalize()
	{

		

		GameObject::Initalize();
	}

	void MonsterMissile::Update()
	{
		Vec3 pos = mTransform->GetPosition();		

		float fRadian = (mDegree * PI) / 180.f;

		pos.x += mSpeed * cosf(fRadian) * Time::DeltaTime();
		pos.y -= mSpeed * sinf(fRadian) * Time::DeltaTime();

		mTransform->SetPosition(pos);
				
		
		

		mCooldownTime += Time::DeltaTime();
		if (mCooldownTime >= 5.0f)
		{

			this->Death();
			mCooldownTime = 0.f;



			//Scene* scene = SceneManager::GetActiveScene();

			//const std::vector<GameObject*>& obj = scene->GetGameObjects(eLayerType::Monster_Attack);

			//for (size_t i = 0; i < obj.size(); i++)
			//{
			//	if (obj[i] != nullptr)
			//	{
			//		obj[i]->Death();
			//	}
			//	//scene->Destroy();
			//}
		
		}




		GameObject::Update();
	}

	void MonsterMissile::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void MonsterMissile::Render()
	{
		GameObject::Render();
	}

}