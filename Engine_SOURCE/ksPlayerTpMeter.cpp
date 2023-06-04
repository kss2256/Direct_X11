#include "ksPlayerTpMeter.h"
#include "ksPlayer.h"
#include "ksSpriteRenderer.h"
#include "ksMaterial.h"
#include "ksMesh.h"
#include "ksResources.h"
#include "ksTransform.h"

#include "ksTime.h"
#include "ksInput.h"
#include "ksConstantBuffer.h"




namespace ks
{

	float PlayerTpMeter::mStnamina = 0.f;


	PlayerTpMeter::PlayerTpMeter()
		
	{
		mTransform = GetComponent<Transform>();



		SpriteRenderer* sr = AddComponent<SpriteRenderer>();


		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"MeterMaterial");
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"TP_Meter", L"Player_UI\\TP_Meter.png");
		mateiral->SetTexture(texture);
		sr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);

	}

	PlayerTpMeter::~PlayerTpMeter()
	{
	}

	void PlayerTpMeter::Initalize()
	{
		mUiPos = mTransform->GetPosition();




		GameObject::Initalize();
	}

	void PlayerTpMeter::Update()
	{

		//mStnamina += 0.1 *  Time::DeltaTime();
		//if (mStnamina >= 0.5f)
		//	mStnamina = 0.0f;


		if (mTarget != nullptr)
		{
			//mPlayerPos = mTarget->GetComponent<Transform>()->GetPosition();
			mPlayerPos = mainCamera->GetOwner()->GetComponent<Transform>()->GetPosition();

			mFinalPos = mPlayerPos + mUiPos;

			mTransform->SetPosition(mFinalPos);

			float stamina = (float)STAMINA_PERCENTAGE / (float)MAX_STAMINA;
			mStnamina = (float)STAMINA_PERCENTAGE - (stamina * (float)mTarget->GetStamina());
			

		}

	
		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Meter];
		renderer::Meter data;

		data.meterendtime = mStnamina;


		cb->Bind(&data);
		cb->SetPipline(eShaderStage::VS);
		cb->SetPipline(eShaderStage::PS);


		UIBase::Update();
	}

	void PlayerTpMeter::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void PlayerTpMeter::Render()
	{
		GameObject::Render();
	}

}
