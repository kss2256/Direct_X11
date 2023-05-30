#include "ksEnt_Poison.h"
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

	Ent_Poison::Ent_Poison()
		: mSpeed(2.0f)
	{

		mTransform = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>();

		loadAnimation();
		


		mAnimator->Play(L"Attack_Poison", true);


		SpriteRenderer* sr = AddComponent<SpriteRenderer>();


		std::shared_ptr<Material> mr = Resources::Find<Material>(L"MonsterMaterial");
		
		sr->SetMaterial(mr);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);

	}

	Ent_Poison::~Ent_Poison()
	{
	}

	void Ent_Poison::Initalize()
	{

		GameObject::Initalize();
	}

	void Ent_Poison::Update()
	{

		mCollider = GetComponent<Collider2D>();
		mCollider->SetType(eColliderType::Rect);
		mCollider->SetSize(Vec2(0.2f, 0.2f));
		Initalize();

		Vec3 pos = mTransform->GetPosition();

		float fRadian = (mDegree * PI) / 180.f;

		pos.x += mSpeed * cosf(fRadian) * Time::DeltaTime();
		pos.y -= mSpeed * sinf(fRadian) * Time::DeltaTime();

		mTransform->SetPosition(pos);




		mCooldownTime += Time::DeltaTime();
		if (mCooldownTime >= 15.0f)
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

	void Ent_Poison::FixedUpdate()
	{

		GameObject::FixedUpdate();
	}

	void Ent_Poison::Render()
	{

		GameObject::Render();
	}

	void Ent_Poison::loadAnimation()
	{

		std::shared_ptr<Texture> bow1 = Resources::Load<Texture>(L"skill_ent2@[30-6]", L"Attack\\skill_ent2@[30-6].png");

		mNumbers.push_back(0);
		mNumbers.push_back(1);
		mNumbers.push_back(2);
		mNumbers.push_back(3);
		mNumbers.push_back(4);
		mNumbers.push_back(5);
		mNumbers.push_back(6);
		mNumbers.push_back(7);
		mNumbers.push_back(8);
		mNumbers.push_back(9);
		mNumbers.push_back(10);
		mNumbers.push_back(11);
		mNumbers.push_back(12);
		mNumbers.push_back(13);
		mNumbers.push_back(14);
		mNumbers.push_back(15);
		mNumbers.push_back(16);
		mNumbers.push_back(17);
		mNumbers.push_back(18);
		mNumbers.push_back(19);
		mNumbers.push_back(20);
		mNumbers.push_back(21);
		mNumbers.push_back(22);
		mNumbers.push_back(23);
		mNumbers.push_back(24);
		mNumbers.push_back(25);
		mNumbers.push_back(26);
		mNumbers.push_back(27);
		mNumbers.push_back(28);
		mNumbers.push_back(29);

		CreateAnimation(L"Attack_Poison", bow1, mAnimator, Vector2(160.0f, 160.0f), Vec2::Zero, mNumbers, 0.25f);
		mNumbers.clear();

	}

}