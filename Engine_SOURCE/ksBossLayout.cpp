#include "ksBossLayout.h"
#include "ksMonster.h"
#include "ksSpriteRenderer.h"
#include "ksMaterial.h"
#include "ksMesh.h"
#include "ksResources.h"
#include "ksTransform.h"


#include "ksInput.h"


namespace ks
{

	BossLayout::BossLayout()
	{

		mTransform = GetComponent<Transform>();



		SpriteRenderer* sr = AddComponent<SpriteRenderer>();


		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"BossUIMaterial");
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"boss_Frame", L"Monster\\boss_Frame.png");
		mateiral->SetTexture(texture);
		sr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);

	}

	BossLayout::~BossLayout()
	{
	}

	void BossLayout::Initalize()
	{

	

		mUiPos = mTransform->GetPosition();


		GameObject::Initalize();

	}

	void BossLayout::Update()
	{		

			mPlayerPos = mainCamera->GetOwner()->GetComponent<Transform>()->GetPosition();


			mFinalPos = mPlayerPos + mUiPos;

			mTransform->SetPosition(mFinalPos);





		UIBase::Update();

	}

	void BossLayout::FixedUpdate()
	{

		GameObject::FixedUpdate();
	}

	void BossLayout::Render()
	{

		GameObject::Render();
	}

}