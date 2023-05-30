#include "ksCloud.h"
#include "ksTransform.h"
#include "ksSpriteRenderer.h"
#include "ksTime.h"
#include "ksResources.h"
#include "ksApplication.h"
#include "ksPlayer.h"

#pragma comment(lib, "msimg32.lib")




extern ks::Application application;


namespace ks
{

	float Cloud::mHoldingTime = 0.f;
	Player* Cloud::mTarget = nullptr;

	Cloud::Cloud()
	{


	}

	Cloud::~Cloud()
	{

	}

	void Cloud::Initalize()
	{

		std::shared_ptr <Texture> texture;

		texture = Resources::Load<Texture>(L"Fogs_1", L"Map\\Fogs\\Fogs.png");

		Transform* tr = GetComponent<Transform>();
		tr->SetPosition(Vector3(35.f, 0.f, 2.0f));
		mStartPos = tr->GetPosition();
		


		SpriteRenderer* mr = AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"FogMaterial");
		mateiral->SetTexture(texture);
		
		mr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->SetMesh(mesh);

		mStartPos = GetComponent<Transform>()->GetPosition();


		GameObject::Initalize();
	}

	void Cloud::Update()
	{

		if (mTarget != nullptr)
			mGroundStage = mTarget->GetGroundStage();


		switch (mGroundStage)
		{
		case ks::enums::eGroundStage::Ground1:
			mStartPos = Vector3(35.f, 0.f, 2.0f);
			break;
		case ks::enums::eGroundStage::Ground2:
			mStartPos = Vector3(70.f, 0.f, 2.0f);
			break;
		case ks::enums::eGroundStage::Ground3:
			mStartPos = Vector3(105.f, 0.f, 2.0f);
			break;
		case ks::enums::eGroundStage::Ground4:
			mStartPos = Vector3(140.f, 0.f, 2.0f);
			break;
		case ks::enums::eGroundStage::Ground5:
			mStartPos = Vector3(175.f, 0.f, 2.0f);
			break;
		case ks::enums::eGroundStage::Ground6:
			mStartPos = Vector3(210.f, 0.f, 2.0f);
			break;
		case ks::enums::eGroundStage::Ground7:
			mStartPos = Vector3(245.f, 0.f, 2.0f);
			break;
		case ks::enums::eGroundStage::Ground8:
			mStartPos = Vector3(280.f, 0.f, 2.0f);
			break;
		case ks::enums::eGroundStage::Ground9:
			mStartPos = Vector3(315.f, 0.f, 2.0f);
			break;
		}

		mHoldingTime += Time::DeltaTime();
		if (mHoldingTime >= 50.f)
		{
			Transform* tr = GetComponent<Transform>();
			tr->SetPosition(mStartPos);
			mHoldingTime = 0.f;
		}

		Transform* tr = GetComponent<Transform>();
		Vec3 pos = tr->GetPosition();
		pos.x += 0.5f * Time::DeltaTime();
		pos.y += 0.2f * Time::DeltaTime();

		tr->SetPosition(pos);


		
		
		//Vec3 pos;

		//pos.x += 0.1f * Time::DeltaTime();
		//pos.y += 0.1f * Time::DeltaTime();

		//if (pos.x >= 1.0f)
		//{
		//	pos.x = 0.f;
		//	pos.y = 0.f;
		//}

		//ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Fade_Effect];
		//renderer::Fade data;

		//data.StartTime = pos.x;
		//data.dumi = pos.y;


		//cb->Bind(&data);
		//cb->SetPipline(eShaderStage::VS);
		//cb->SetPipline(eShaderStage::PS);




		GameObject::Update();
	}

	void Cloud::FixedUpdate()
	{

		GameObject::FixedUpdate();
	}

	void Cloud::Render()
	{


		//알파블렌드 ??로하면되나
		//BLENDFUNCTION func = {};
		//func.BlendOp = AC_SRC_OVER;
		//func.BlendFlags = 0;
		//func.AlphaFormat = 0;
		//func.SourceConstantAlpha = 1.0f;

		//
		//


		//AlphaBlend(application.GetWindowDC(), 0, 0
		//	, mTexture->GetWidth() , mTexture->GetHeight()
		//	, application.GetWindowDC(), 0, 0
		//	, mTexture->GetWidth() , mTexture->GetHeight()
		//	, func);


		GameObject::Render();
	}

}