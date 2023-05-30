#include "ksStart_Effect.h"
#include "ksResources.h"
#include "ksTransform.h"
#include "ksSpriteRenderer.h"
#include "ksMaterial.h"
#include "ksMesh.h"
#include "ksPlayer.h"
#include "ksAnimator.h"


namespace ks
{

	Start_Effect::Start_Effect()
	{
		mAnimator = AddComponent<Animator>();

		
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vec3(10.0f, 10.0f, 1.0f));
		tr->SetPosition(Vec3(35.f, 0.0f, 1.0f));

		SpriteRenderer* sr = AddComponent<SpriteRenderer>();

		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"SpriteMaterial");
		sr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);

		loadanimation();

		mAnimator->Play(L"Idle", true);
	}

	Start_Effect::~Start_Effect()
	{

	}

	void Start_Effect::Initalize()
	{
		GameObject::Initalize();
	}

	void Start_Effect::Update()
	{
		GameObject::Update();
	}

	void Start_Effect::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void Start_Effect::Render()
	{
		GameObject::Render();
	}

	void Start_Effect::loadanimation()
	{

		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"magic_circle", L"Map\\Effect\\magic_circle.png");


		mAnimator->Create(L"Idle", texture, Vector2(0.0f, 0.0f), Vector2(192.f, 192.0f), Vector2::Zero, 2, 1.0f);
		




	}

}