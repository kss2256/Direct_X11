#include "ksPlayerCreateHp.h"
#include "ksPlayer.h"
#include "ksSpriteRenderer.h"
#include "ksMaterial.h"
#include "ksMesh.h"
#include "ksResources.h"
#include "ksTransform.h"
#include "ksObject.h"

#include "ksInput.h"

namespace ks
{

	PlayerCreateHp::PlayerCreateHp()
	{

		mTransform = GetComponent<Transform>();



		mSprite = AddComponent<SpriteRenderer>();


		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"FullHpMaterial");
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"FullHp", L"Player_UI\\FullHp.png");
		mateiral->SetTexture(texture);

		std::shared_ptr<Material> mateiral1 = Resources::Find<Material>(L"HalfHpMaterial");
		std::shared_ptr<Texture> texture1 = Resources::Load<Texture>(L"HalfHp", L"Player_UI\\HalfHp.png");
		mateiral1->SetTexture(texture1);


		mSprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		mSprite->SetMesh(mesh);


	}

	PlayerCreateHp::~PlayerCreateHp()
	{
	}

	void PlayerCreateHp::Initalize()
	{
		mUiPos = mTransform->GetPosition();

		if (m_bFullHp)
		{
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"FullHpMaterial");
			mSprite->SetMaterial(mateiral);
		}

		if (m_bHalfHp)
		{
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"HalfHpMaterial");
			mSprite->SetMaterial(mateiral);
		}


		GameObject::Initalize();
	}

	void PlayerCreateHp::Update()
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

	void PlayerCreateHp::FixedUpdate()
	{



		GameObject::FixedUpdate();
	}

	void PlayerCreateHp::Render()
	{

		GameObject::Render();
	}

}