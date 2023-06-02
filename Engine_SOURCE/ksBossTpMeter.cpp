#include "ksBossTpMeter.h"
#include "ksMonster.h"
#include "ksBoss_Flime.h"
#include "ksBoss_Ent.h"
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

	float BossTpMeter::mFlimeHp = 0.f;

	BossTpMeter::BossTpMeter()
	{
		mTransform = GetComponent<Transform>();



		SpriteRenderer* sr = AddComponent<SpriteRenderer>();


		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"BossMeterMaterial");
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Monster_Meter", L"Monster\\Monster_Meter.png");
		mateiral->SetTexture(texture);
		sr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);


	}

	BossTpMeter::~BossTpMeter()
	{
	}

	void BossTpMeter::Initalize()
	{
		
		
		mUiPos = mTransform->GetPosition();



		GameObject::Initalize();
	}

	void BossTpMeter::Update()
	{




		if (mTarget != nullptr)
		{

			

			mPlayerPos = mainCamera->GetOwner()->GetComponent<Transform>()->GetPosition();

			mFinalPos = mPlayerPos + mUiPos;

			mTransform->SetPosition(mFinalPos);

		

			if (dynamic_cast<Boss_Flime*>(mTarget))
			{
				
				float flimehp = STAMINA_PERCENTAGE / MAX_FLIME_HP;
				mFlimeHp = STAMINA_PERCENTAGE - (flimehp * mTarget->GetMonsterHp());

			}

			if (dynamic_cast<Boss_Ent*>(mTarget))
			{

				float flimehp = STAMINA_PERCENTAGE / MAX_ENT_HP;
				mFlimeHp = STAMINA_PERCENTAGE - (flimehp * mTarget->GetMonsterHp());

			}

		}



		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Monster_Meter];
		renderer::MONSTERMeter data;

		data.monstermeter = mFlimeHp;


		cb->Bind(&data);
		cb->SetPipline(eShaderStage::VS);
		cb->SetPipline(eShaderStage::PS);


		UIBase::Update();
	}

	void BossTpMeter::FixedUpdate()
	{

		GameObject::FixedUpdate();
	}

	void BossTpMeter::Render()
	{

		GameObject::Render();
	}

}