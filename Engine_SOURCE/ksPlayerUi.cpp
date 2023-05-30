#include "ksPlayerUi.h"
#include "ksSpriteRenderer.h"
#include "ksMaterial.h"
#include "ksMesh.h"
#include "ksResources.h"
#include "ksTransform.h"


namespace ks
{

	PlayerUi::PlayerUi()
	{

		mTransform = GetComponent<Transform>();

		SpriteRenderer* sr = AddComponent<SpriteRenderer>();

		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Layout", L"Player_UI\\Layout.png");

		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"PlayerUiMaterial");
		//std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"SpriteMaterial");
		mateiral->SetTexture(texture);
		sr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);

	}

	PlayerUi::~PlayerUi()
	{
	}

	void PlayerUi::Initalize()
	{

		GameObject::Initalize();
	}

	void PlayerUi::Update()
	{

		GameObject::Update();
	}

	void PlayerUi::FixedUpdate()
	{

		GameObject::FixedUpdate();
	}

	void PlayerUi::Render()
	{

		GameObject::Render();
	}

}