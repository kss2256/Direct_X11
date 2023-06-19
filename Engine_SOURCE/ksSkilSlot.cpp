#include "ksSkilSlot.h"
#include "ksPlayer.h"
#include "ksSpriteRenderer.h"
#include "ksMaterial.h"
#include "ksMesh.h"
#include "ksResources.h"
#include "ksTransform.h"
#include "ksSkilSlot.h"

#include "ksInput.h"

namespace ks
{
	SkilSlot::SkilSlot()
	{
		mTransform = GetComponent<Transform>();


		SpriteRenderer* sr = AddComponent<SpriteRenderer>();


		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"SkilUiMaterial");
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"skillSlot", L"Player_UI\\skillSlot.png");
		mateiral->SetTexture(texture);
		sr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);

	}

	SkilSlot::~SkilSlot()
	{
	}

	void SkilSlot::Initalize()
	{
		mUiPos = mTransform->GetPosition();

		GameObject::Initalize();

	}

	void SkilSlot::Update()
	{
		mPlayerPos = mainCamera->GetOwner()->GetComponent<Transform>()->GetPosition();


		mFinalPos = mPlayerPos + mUiPos;

		mTransform->SetPosition(mFinalPos);



		UIBase::Update();
	}

	void SkilSlot::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void SkilSlot::Render()
	{
		GameObject::Render();
	}

}
