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

			if (m_fTime >= 1.02f)
			{
				barrierSound();
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
			scale.x += Time::DeltaTime() * 7 ;
			scale.y += Time::DeltaTime() * 7 ;

			mTransform->SetScale(scale);
		
			if (m_fTime >= 3.0f)
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

		std::shared_ptr<Texture> skil = Resources::Load<Texture>(L"60FPS_AC2Q017_Barrier", L"Skil\\60FPS_AC2Q017_Barrier.png");
		
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
		CreateAnimation(L"Barrier_Start", skil, mAnimator, Vector2(192.0f, 192.0f), Vec2::Zero, mNumbers, 0.03f);
		mNumbers.clear();


	
		mNumbers.push_back(38);
		mNumbers.push_back(39);
		mNumbers.push_back(40);
		mNumbers.push_back(41);
		mNumbers.push_back(42);
		mNumbers.push_back(43);
		mNumbers.push_back(44);
		mNumbers.push_back(45);
		mNumbers.push_back(46);
		mNumbers.push_back(47);
		mNumbers.push_back(48);
		mNumbers.push_back(49);
		mNumbers.push_back(50);
		mNumbers.push_back(51);
		mNumbers.push_back(52);
		mNumbers.push_back(53);
		mNumbers.push_back(54);
		mNumbers.push_back(55);
		mNumbers.push_back(56);
		mNumbers.push_back(57);
		mNumbers.push_back(58);
		mNumbers.push_back(59);
		mNumbers.push_back(60);
		mNumbers.push_back(61);
		mNumbers.push_back(62);
		mNumbers.push_back(63);
		mNumbers.push_back(64);
		mNumbers.push_back(65);
		mNumbers.push_back(66);
		mNumbers.push_back(67);
		mNumbers.push_back(68);
		mNumbers.push_back(69);
		mNumbers.push_back(70);
		mNumbers.push_back(71);
		mNumbers.push_back(72);
		mNumbers.push_back(73);
		mNumbers.push_back(74);
		mNumbers.push_back(75);
		mNumbers.push_back(76);
		mNumbers.push_back(77);
		mNumbers.push_back(78);
		mNumbers.push_back(79);
		mNumbers.push_back(80);
		mNumbers.push_back(81);
		mNumbers.push_back(82);
		mNumbers.push_back(83);
		mNumbers.push_back(84);
		mNumbers.push_back(85);
		mNumbers.push_back(86);
		mNumbers.push_back(87);

		CreateAnimation(L"Barrier_End", skil, mAnimator, Vector2(192.0f, 192.0f), Vec2::Zero, mNumbers, 0.06f);
		mNumbers.clear();



	

	}

	void Skil_Barrier::loadSound()
	{

		std::shared_ptr<AudioClip> Barrier = Resources::Load<AudioClip>
			(L"Barrier", L"..\\Resources\\Sound\\Barrier.ogg");


	}

	void Skil_Barrier::barrierSound()
	{
		std::shared_ptr<AudioClip> sound = Resources::Find<AudioClip>(L"Barrier");
		sound->SetLoop(false);
		sound->Play();
	}

}