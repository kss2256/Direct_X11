#include "ksStage1_1Parts.h"
#include "ksResources.h"
#include "ksTransform.h"
#include "ksMeshRenderer.h"
#include "ksMaterial.h"
#include "ksMesh.h"


using namespace ks::graphics;

namespace ks
{

	GameObject* Stage1_1Parts::mTarget = nullptr;

	Stage1_1Parts::Stage1_1Parts()
	{
	
	}

	Stage1_1Parts::~Stage1_1Parts()
	{
	}

	void Stage1_1Parts::Initalize()
	{

		std::shared_ptr<Texture> ground1 = Resources::Load<Texture>(L"Ground1_Parts", L"Map\\Parts\\Ground1.png");
		std::shared_ptr<Texture> ground2 = Resources::Load<Texture>(L"Ground2_Parts", L"Map\\Parts\\Ground2.png");
		std::shared_ptr<Texture> ground3 = Resources::Load<Texture>(L"Ground3_Parts", L"Map\\Parts\\Ground3.png");
		std::shared_ptr<Texture> ground4 = Resources::Load<Texture>(L"Ground4_Parts", L"Map\\Parts\\Ground4.png");
		std::shared_ptr<Texture> ground5 = Resources::Load<Texture>(L"Ground5_Parts", L"Map\\Parts\\Ground5.png");
		std::shared_ptr<Texture> ground6 = Resources::Load<Texture>(L"Ground6_Parts", L"Map\\Parts\\Ground6.png");
		std::shared_ptr<Texture> ground7 = Resources::Load<Texture>(L"Ground7_Parts", L"Map\\Parts\\Ground7.png");
		std::shared_ptr<Texture> ground8 = Resources::Load<Texture>(L"Ground8_Parts", L"Map\\Parts\\Ground8.png");
		std::shared_ptr<Texture> ground9 = Resources::Load<Texture>(L"Ground9_Parts", L"Map\\Parts\\Ground9.png");
		std::shared_ptr<Texture> start = Resources::Load<Texture>(L"StartParts", L"Map\\Parts\\Start.png");


		switch (mGroundStage)
		{
		case ks::enums::eGroundStage::Ground1:
			createGround(L"GroundParts1", ground1);
		break;
		case ks::enums::eGroundStage::Ground2:
			createGround(L"GroundParts2", ground2);	
		break;
		case ks::enums::eGroundStage::Ground3:
			createGround(L"GroundParts3", ground3);
			break;
		case ks::enums::eGroundStage::Ground4:
			createGround(L"GroundParts4", ground4);
			break;
		case ks::enums::eGroundStage::Ground5:
			createGround(L"GroundParts5", ground5);
			break;
		case ks::enums::eGroundStage::Ground6:
			createGround(L"GroundParts6", ground1);
			break;
		case ks::enums::eGroundStage::Ground7:
			createGround(L"GroundParts7", ground7);
			break;
		case ks::enums::eGroundStage::Ground8:
			createGround(L"GroundParts8", ground8);
			break;
		case ks::enums::eGroundStage::Ground9:
			createGround(L"GroundParts9", ground9);
			break;
		case ks::enums::eGroundStage::Start:
		{
			createGround(L"StartParts", start);
			Transform* tr = GetComponent<Transform>();
			tr->SetScale(Vec3(37.f, 35.f, 1.0f));
		}
			break;
		}

		GameObject::Initalize();
	}

	void Stage1_1Parts::Update()
	{
		GameObject::Update();
	}

	void Stage1_1Parts::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void Stage1_1Parts::Render()
	{
		GameObject::Render();
	}

	template <typename T>
	void Stage1_1Parts::createGround(const std::wstring& name, std::shared_ptr<T> texture)
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vec3(30.5f, 22.95f, 1.0f));

		std::wstring finshname = name + L"Material";

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(finshname);

		mateiral->SetTexture(texture);

		mr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->SetMesh(mesh);

	}

}