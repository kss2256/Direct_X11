#include "ksSkil_Barrier.h"
#include "ksSkilScript.h"
#include "ksAudioClip.h"


namespace ks
{
	Skil_Barrier::Skil_Barrier()
	{

		mTransform = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>();

		m_pSkilScript = AddComponent<SkilScript>();
		m_pSkilScript->SetSkil(eItem::Barrier);

		m_pSkilScript->SetSkilOwner(this);

		loadAnimation();
		loadSound();

		SpriteRenderer* sr = AddComponent<SpriteRenderer>();


		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"CoinMaterial");
		sr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);

		mAnimator->Play(L"Barrier_Start", false);

	}

	Skil_Barrier::~Skil_Barrier()
	{
	}

	void Skil_Barrier::Initalize()
	{
		if (mTarget != nullptr)
		{
			//mAnimator->Play(L"Ice_Start", false);
			//iceStartSound();


			m_bSkilStart = true;
		}


		GameObject::Initalize();
	}

	void Skil_Barrier::Update()
	{
		if (m_bSkilStart)
		{
			m_fTime += Time::DeltaTime();
			if (m_fTime >= 0.51f)
			{
				m_bBarrier = true;
				mAnimator->Play(L"Barrier_End", false);
				m_bSkilStart = false;
				m_bBarrierScale = true;
				m_fTime = 0.f;
			}
		}

		if (m_bBarrierScale)
		{
			m_fTime += Time::DeltaTime();
			Vec3 scale = mTransform->GetScale();
			scale.x += Time::DeltaTime() * 10 ;
			scale.y += Time::DeltaTime() * 10 ;

			mTransform->SetScale(scale);
			if (m_fTime >= 1.5f)
			{
				Vec3 scale = mTransform->GetScale();
				m_bBarrierScale = false;
				m_fTime = 0.f;
				this->Death();
			}
		}

		if (m_bBarrierEnd)
		{


			m_bBarrierEnd = false;
		}


		if (mTarget != nullptr)
		{
			mTransform->SetPosition(mTarget->GetComponent<Transform>()->GetPosition());
		}



		GameObject::Update();
	}

	void Skil_Barrier::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void Skil_Barrier::Render()
	{
		GameObject::Render();
	}

	void Skil_Barrier::loadAnimation()
	{
		std::shared_ptr<Texture> skil = Resources::Load<Texture>(L"30FPS_AC2Q017_Barrier", L"Skil\\30FPS_AC2Q017_Barrier.png");
		//43
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
		CreateAnimation(L"Barrier_Start", skil, mAnimator, Vector2(192.0f, 192.0f), Vec2::Zero, mNumbers, 0.03f);
		mNumbers.clear();

		mNumbers.push_back(19);
		mNumbers.push_back(20);
		mNumbers.push_back(21);
		mNumbers.push_back(22);
		mNumbers.push_back(23);
		mNumbers.push_back(24);
		mNumbers.push_back(25);
		mNumbers.push_back(26);
		mNumbers.push_back(27);
		mNumbers.push_back(28);
		mNumbers.push_back(29);
		mNumbers.push_back(30);
		mNumbers.push_back(31);
		mNumbers.push_back(32);
		mNumbers.push_back(33);
		mNumbers.push_back(34);
		mNumbers.push_back(35);
		mNumbers.push_back(36);
		mNumbers.push_back(37);
		mNumbers.push_back(38);
		mNumbers.push_back(39);
		mNumbers.push_back(40);
		mNumbers.push_back(41);
		mNumbers.push_back(42);
		mNumbers.push_back(43);

		CreateAnimation(L"Barrier_End", skil, mAnimator, Vector2(192.0f, 192.0f), Vec2::Zero, mNumbers, 0.06f);
		mNumbers.clear();





	

	}

	void Skil_Barrier::loadSound()
	{

		/*std::shared_ptr<AudioClip> Ice_Spear = Resources::Load<AudioClip>
			(L"Ice_Spear", L"..\\Resources\\Sound\\Ice_Spear.ogg");*/
	}

}