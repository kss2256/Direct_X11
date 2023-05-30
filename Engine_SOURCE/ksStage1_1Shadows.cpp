#include "ksStage1_1Shadows.h"
#include "ksResources.h"
#include "ksTransform.h"
#include "ksMeshRenderer.h"
#include "ksMaterial.h"
#include "ksMesh.h"

using namespace ks::graphics;

namespace ks
{
	GameObject* Stage1_1Shadows::mTarget = nullptr;

	Stage1_1Shadows::Stage1_1Shadows()
	{

		


	}

	Stage1_1Shadows::~Stage1_1Shadows()
	{
	}

	void Stage1_1Shadows::Initalize()
	{

		std::shared_ptr<Texture> ground1 = Resources::Load<Texture>(L"Ground1_Shadows", L"Map\\Shadows\\Ground1.png");
		std::shared_ptr<Texture> ground2 = Resources::Load<Texture>(L"Ground2_Shadows", L"Map\\Shadows\\Ground2.png");
		std::shared_ptr<Texture> ground3 = Resources::Load<Texture>(L"Ground3_Shadows", L"Map\\Shadows\\Ground3.png");
		std::shared_ptr<Texture> ground4 = Resources::Load<Texture>(L"Ground4_Shadows", L"Map\\Shadows\\Ground4.png");
		std::shared_ptr<Texture> ground5 = Resources::Load<Texture>(L"Ground5_Shadows", L"Map\\Shadows\\Ground5.png");
		std::shared_ptr<Texture> ground6 = Resources::Load<Texture>(L"Ground6_Shadows", L"Map\\Shadows\\Ground6.png");
		std::shared_ptr<Texture> ground7 = Resources::Load<Texture>(L"Ground7_Shadows", L"Map\\Shadows\\Ground7.png");
		std::shared_ptr<Texture> ground8 = Resources::Load<Texture>(L"Ground8_Shadows", L"Map\\Shadows\\Ground8.png");
		std::shared_ptr<Texture> ground9 = Resources::Load<Texture>(L"Ground9_Shadows", L"Map\\Shadows\\Ground9.png");
		std::shared_ptr<Texture> start = Resources::Load<Texture>(L"StartShadows", L"Map\\Shadows\\Start.png");


		switch (mGroundStage)
		{
		case ks::enums::eGroundStage::Ground1:
			createGround(L"GroundShadows1", ground1);
			break;
		case ks::enums::eGroundStage::Ground2:
			createGround(L"GroundShadows2", ground2);
			break;
		case ks::enums::eGroundStage::Ground3:
			createGround(L"GroundShadows3", ground3);
			break;
		case ks::enums::eGroundStage::Ground4:
			createGround(L"GroundShadows4", ground4);
			break;
		case ks::enums::eGroundStage::Ground5:
			createGround(L"GroundShadows5", ground5);
			break;
		case ks::enums::eGroundStage::Ground6:
			createGround(L"GroundShadows6", ground1);
			break;
		case ks::enums::eGroundStage::Ground7:
			createGround(L"GroundShadows7", ground7);
			break;
		case ks::enums::eGroundStage::Ground8:
			createGround(L"GroundShadows8", ground8);
			break;
		case ks::enums::eGroundStage::Ground9:
			createGround(L"GroundShadows9", ground9);
			break;
		case ks::enums::eGroundStage::Start:
		{
			createGround(L"StartShadows", start);
			Transform* tr = GetComponent<Transform>();
			tr->SetScale(Vec3(37.f, 35.f, 1.0f));
		}
			break;
		}


		GameObject::Initalize();
	}

	void Stage1_1Shadows::Update()
	{
		GameObject::Update();
	}

	void Stage1_1Shadows::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void Stage1_1Shadows::Render()
	{
		GameObject::Render();
	}

	template <typename T>
	void Stage1_1Shadows::createGround(const std::wstring& name, std::shared_ptr<T> texture)
	{

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vec3(30.5f, 22.95f, 1.0f));

		std::wstring finshname = name + L"Material";

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(finshname);

		mateiral->SetRenderingMode(eRenderingMode::Transparent);
		mateiral->SetTexture(texture);

		mr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->SetMesh(mesh);

	}

}
