#include "ksFadeEffect.h"
#include "ksTime.h"
#include "ksSpriteRenderer.h"
#include "ksMaterial.h"
#include "ksResources.h"
#include "ksGameObject.h"
#include "ksConstantBuffer.h"
#include "ksInput.h"
#include "ksTexture.h"
#include "ksMesh.h"
#include "ksTransform.h"


namespace ks
{


	//float FadeEffect::mAlphaTime = 0.f;
	//float FadeEffect::mEndTime = 1.5f;

	FadeEffect::FadeEffect()
		: Component(eComponentType::FadeEffect)
		, mAlphaTime(0.f)
		, mEndTime(1.5f)
	{
		

	}

	FadeEffect::~FadeEffect()
	{


	}

	void FadeEffect::Initalize()
	{
		SpriteRenderer* monmr = GetOwner()->GetComponent<SpriteRenderer>();

		

		std::shared_ptr<Material> monmateiral = Resources::Find<Material>(L"FadeEffectMaterial");
		//std::shared_ptr<Material> monmateiral = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr<Texture> fadeTexture = Resources::Load<Texture>(L"Fade", L"Fade.png");
		monmateiral->SetTexture(fadeTexture);		
		monmr->SetMaterial(monmateiral);
		//std::shared_ptr<Mesh> monmesh = Resources::Find<Mesh>(L"FadeEffectMesh");
		std::shared_ptr<Mesh> monmesh = Resources::Find<Mesh>(L"RectMesh");
		monmr->SetMesh(monmesh);		

	}

	void FadeEffect::Update()
	{
	
		mTransform = GetOwner()->GetComponent<Transform>();



		mTransform->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());


		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Fade_Effect];
		renderer::Fade data;

		data.time = mAlphaTime;
		data.EndTime = mEndTime;	


		cb->Bind(&data);
		cb->SetPipline(eShaderStage::VS);
		cb->SetPipline(eShaderStage::PS);



		//if (Input::GetKeyDown(eKeyCode::N_1))
		//{
		//	// ¾îµÎ¿öÁü
		//	mFadeEffect = true;
		//	mAlphaTime = 0.f;
		//}
		//if (Input::GetKeyDown(eKeyCode::N_2))
		//{
		//	// ¹à¾ÆÁü
		//	mFadeEffect = false;
		//	mAlphaTime = 1.f;
		//}

		switch (mFadeEffect)
		{
		//case ks::Fade::None:
		//	mAlphaTime = 0.f;
		//	break;
		case ks::Fade::Fade_In:
		{
			mAlphaTime -= Time::DeltaTime() / mEndTime;			
		}
			break;
		case ks::Fade::Fade_Out:
		{
			mAlphaTime += Time::DeltaTime() / mEndTime;			
		}
			break;
		case ks::Fade::Fade_In_Out:
		{
			mAlphaTime += Time::DeltaTime() / mEndTime;
			if (mAlphaTime > 1.5f)
			{
				mFadeEffect = Fade::Fade_In;
				mAlphaTime = 1.f;
			}
		}
			break;	
		}



	}

	void FadeEffect::FixedUpdate()
	{

	}

	void FadeEffect::Render()
	{


	}

	void FadeEffect::Fade_In()
	{
		mFadeEffect = Fade::Fade_In;
		mAlphaTime = 1.f;

	}

	void FadeEffect::Fade_Out()
	{	

		mFadeEffect = Fade::Fade_Out;
		mAlphaTime = 0.f;


	}

	void FadeEffect::Fade_In_Out()
	{
		mFadeEffect = Fade::Fade_In_Out;
		mAlphaTime = 0.f;

	}

}