#include "ksSkil_Lighting.h"
#include "ksSkilScript.h"
#include "ksAudioClip.h"


namespace ks
{

	Skil_Lighting::Skil_Lighting()
	{

		mTransform = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>();

		m_pSkilScript = AddComponent<SkilScript>();
		m_pSkilScript->SetSkil(eItem::Lighting);

		m_pSkilScript->SetSkilOwner(this);

		loadAnimation();
		loadSound();

		SpriteRenderer* sr = AddComponent<SpriteRenderer>();


		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"CoinMaterial");
		sr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);

		mAnimator->Play(L"Right_Attack", false);

	}

	Skil_Lighting::~Skil_Lighting()
	{
	}

	void Skil_Lighting::Initalize()
	{
		if (mTarget != nullptr)
		{
			//mAnimator->Play(L"Ice_Start", false);
			//iceStartSound();


			m_bSkilStart = true;
		}


		GameObject::Initalize();

	}

	void Skil_Lighting::Update()
	{
		GameObject::Update();
	}

	void Skil_Lighting::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void Skil_Lighting::Render()
	{
		GameObject::Render();
	}

	void Skil_Lighting::loadAnimation()
	{
		std::shared_ptr<Texture> skil = Resources::Load<Texture>(L"actor1_ilsum_thunder", L"Skil\\actor1_ilsum_thunder.png");

		mNumbers.push_back(0);
		mNumbers.push_back(1);
		mNumbers.push_back(2);
		mNumbers.push_back(3);
		mNumbers.push_back(4);
		mNumbers.push_back(5);
		mNumbers.push_back(6);
		mNumbers.push_back(7);
		mNumbers.push_back(8);
		mNumbers.push_back(9);
		mNumbers.push_back(10);
		mNumbers.push_back(11);
		mNumbers.push_back(12);
		mNumbers.push_back(13);
		mNumbers.push_back(14);
		mNumbers.push_back(15);
		mNumbers.push_back(16);
		mNumbers.push_back(17);
		mNumbers.push_back(18);
		mNumbers.push_back(19);
		mNumbers.push_back(20);
		mNumbers.push_back(21);
		mNumbers.push_back(22);

		CreateAnimation(L"Right_Attack", skil, mAnimator, Vector2(192.0f, 192.0f), Vec2::Zero, mNumbers, 0.03f);
		mNumbers.clear();




		mNumbers.push_back(29);
		mNumbers.push_back(28);
		mNumbers.push_back(27);
		mNumbers.push_back(26);
		mNumbers.push_back(25);
		mNumbers.push_back(34);
		mNumbers.push_back(33);
		mNumbers.push_back(32);
		mNumbers.push_back(31);
		mNumbers.push_back(30);
		mNumbers.push_back(39);
		mNumbers.push_back(38);
		mNumbers.push_back(37);
		mNumbers.push_back(36);
		mNumbers.push_back(35);			
		mNumbers.push_back(44);
		mNumbers.push_back(43);
		mNumbers.push_back(42);
		mNumbers.push_back(41);
		mNumbers.push_back(40);			
		mNumbers.push_back(49);
		mNumbers.push_back(48);
		mNumbers.push_back(47);

		CreateAnimation(L"Left_Attack", skil, mAnimator, Vector2(192.0f, 192.0f), Vec2::Zero, mNumbers, 0.03f);
		mNumbers.clear();


	}

	void Skil_Lighting::loadSound()
	{

		//std::shared_ptr<AudioClip> Barrier = Resources::Load<AudioClip>
		//	(L"Barrier", L"..\\Resources\\Sound\\Barrier.ogg");
		//
		//std::shared_ptr<AudioClip> sound = Resources::Find<AudioClip>(L"Barrier");
		//sound->SetLoop(false);
		//sound->Play();
	}

}