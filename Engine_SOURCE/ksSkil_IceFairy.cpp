#include "ksSkil_IceFairy.h"


namespace ks
{

	Skil_IceFairy::Skil_IceFairy()
	{
		mTransform = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>();

		loadAnimation();


		SpriteRenderer* sr = AddComponent<SpriteRenderer>();


		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"CoinMaterial");
		sr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);

	}

	Skil_IceFairy::~Skil_IceFairy()
	{
		

	}

	void Skil_IceFairy::Initalize()
	{
		if (mTarget != nullptr)
		{
			mAnimator->Play(L"Ice_Start", false);

			m_bSkilStart = true;
		}


		GameObject::Initalize();
	}

	void Skil_IceFairy::Update()
	{
		m_fTime += Time::DeltaTime();


		if (m_bSkilStart)
		{			
			if (m_fTime >= 1.5f)
			{
				mAnimator->Play(L"Ice_End", false);
				m_bSkilStart = false;
			}
		}

		if (m_fTime >= 1.8f)
		{
			this->Death();
		}


		GameObject::Update();
	}

	void Skil_IceFairy::FixedUpdate()
	{

		GameObject::FixedUpdate();
	}

	void Skil_IceFairy::Render()
	{

		GameObject::Render();
	}

	void Skil_IceFairy::loadAnimation()
	{

		std::shared_ptr<Texture> skil = Resources::Load<Texture>(L"skill_icefairy2", L"Skil\\skill_icefairy2.png");



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

		CreateAnimation(L"Ice_Start", skil, mAnimator, Vector2(192.0f, 192.0f), Vec2::Zero, mNumbers, 0.03f);
		mNumbers.clear();

		mNumbers.push_back(15);
		mNumbers.push_back(16);
		mNumbers.push_back(17);
		mNumbers.push_back(18);
		mNumbers.push_back(19);
		mNumbers.push_back(20);
		mNumbers.push_back(21);
		mNumbers.push_back(22);
		mNumbers.push_back(23);
		mNumbers.push_back(24);

		CreateAnimation(L"Ice_End", skil, mAnimator, Vector2(192.0f, 192.0f), Vec2::Zero, mNumbers, 0.03f);
		mNumbers.clear();


	}

}