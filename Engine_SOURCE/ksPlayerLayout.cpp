#include "ksPlayerLayout.h"
#include "ksPlayer.h"
#include "ksSpriteRenderer.h"
#include "ksMaterial.h"
#include "ksMesh.h"
#include "ksResources.h"
#include "ksTransform.h"


#include "ksInput.h"


namespace ks
{

	PlayerLayout::PlayerLayout()
	{

		mTransform = GetComponent<Transform>();
		
		

		SpriteRenderer* sr = AddComponent<SpriteRenderer>();


		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"UIMaterial");
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Layout", L"Player_UI\\Layout.png");
		mateiral->SetTexture(texture);
		sr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);

	}

	PlayerLayout::~PlayerLayout()
	{
	}

	void PlayerLayout::Initalize()
	{

		mUiPos = mTransform->GetPosition();
		



		GameObject::Initalize();
	}

	void PlayerLayout::Update()
	{

		if (mTarget != nullptr)
		{
			//mPlayerPos = mTarget->GetComponent<Transform>()->GetPosition();

			Vec3 Pos = mTransform->GetPosition();

			mPlayerPos = mainCamera->GetOwner()->GetComponent<Transform>()->GetPosition();
			

			mFinalPos = mPlayerPos + mUiPos;

			mTransform->SetPosition(mFinalPos);
		}
		



		UIBase::Update();
	}

	void PlayerLayout::FixedUpdate()
	{

	


		GameObject::FixedUpdate();
	}

	void PlayerLayout::Render()
	{

		GameObject::Render();
	}

}