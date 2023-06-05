#include "ksPlayerSlot.h"
#include "ksSpriteRenderer.h"
#include "ksMaterial.h"
#include "ksMesh.h"
#include "ksResources.h"
#include "ksTransform.h"


#include "ksInput.h"




namespace ks
{

	PlayerSlot::PlayerSlot()
	{

		mTransform = GetComponent<Transform>();



		SpriteRenderer* sr = AddComponent<SpriteRenderer>();


		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"SlotUIMaterial");
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"weaponSlotA", L"Player_UI\\weaponSlotA.png");
		mateiral->SetTexture(texture);
		sr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);

	}
	PlayerSlot::~PlayerSlot()
	{



	}


	void PlayerSlot::Initalize()
	{

		mUiPos = mTransform->GetPosition();


		GameObject::Initalize();
	}

	void PlayerSlot::Update()
	{
		if (mTarget != nullptr)
		{
			//mPlayerPos = mTarget->GetComponent<Transform>()->GetPosition();

			Vec3 Pos = mTransform->GetPosition();
			mPlayerWeaponSlot = mTarget->GetPlayerInfo().weapon_Slot;

			mPlayerPos = mainCamera->GetOwner()->GetComponent<Transform>()->GetPosition();


			mFinalPos = mPlayerPos + mUiPos;

			mTransform->SetPosition(mFinalPos);
		}
		

		switch (mPlayerWeaponSlot)
		{
		case ks::eSlot::Slot_1:
		{
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"SlotUIMaterial");
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"weaponSlotA", L"Player_UI\\weaponSlotA.png");
			mateiral->SetTexture(texture);
		}
			break;
		case ks::eSlot::Slot_2:
		{
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"SlotUIMaterial");
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"weaponSlotB", L"Player_UI\\weaponSlotB.png");
			mateiral->SetTexture(texture);
		}
			break;		
		}



		UIBase::Update();
	}

	void PlayerSlot::FixedUpdate()
	{

		



		GameObject::FixedUpdate();
	}

	void PlayerSlot::Render()
	{

		GameObject::Render();
	}

}