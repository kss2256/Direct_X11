#include "ksGoldUi.h"
#include "ksPlayer.h"
#include "ksSpriteRenderer.h"
#include "ksMaterial.h"
#include "ksMesh.h"
#include "ksResources.h"
#include "ksTransform.h"


#include "ksInput.h"


namespace ks
{

	GoldUi::GoldUi()
	{
		mTransform = GetComponent<Transform>();



		SpriteRenderer* sr = AddComponent<SpriteRenderer>();


		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"GoldUiMaterial");
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Gold_Ui", L"UI\\Gold_Ui.png");
		mateiral->SetTexture(texture);
		sr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);

	}

	GoldUi::~GoldUi()
	{
	}

	void GoldUi::Initalize()
	{

		mUiPos = mTransform->GetPosition();

		//GameObject::Initalize();
	}

	void GoldUi::Update()
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

	void GoldUi::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void GoldUi::Render()
	{
		GameObject::Render();
	}

}
