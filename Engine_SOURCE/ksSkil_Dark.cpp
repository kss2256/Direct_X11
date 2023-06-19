#include "ksSkil_Dark.h"
#include "ksAudioClip.h"
#include "ksSkilScript.h"

namespace ks
{

	Skil_Dark::Skil_Dark()
	{

		mTransform = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>();
		
		m_pSkilScript = AddComponent<SkilScript>();
		m_pSkilScript->SetSkil(eItem::Dark);
		
		m_pSkilScript->SetSkilOwner(this);

		loadAnimation();
		loadSound();

		SpriteRenderer* sr = AddComponent<SpriteRenderer>();


		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"CoinMaterial");
		sr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);

	}

	Skil_Dark::~Skil_Dark()
	{
	}

	void Skil_Dark::Initalize()
	{
		if (mTarget != nullptr)
		{
			mTransform->GetPosition();

			

			darkStartSound();
			mAnimator->Play(L"Dark_Start", false);
			
			m_bSkilStart = true;
		}


		GameObject::Initalize();
	}

	void Skil_Dark::Update()
	{
		m_fTime += Time::DeltaTime();


		if (m_bSkilStart)
		{
			if (m_fTime >= 0.7f)
			{
				darkVoidSound();
				mAnimator->Play(L"Dark_Void", true);
				m_bVoidAttack = true;
				m_bSkilStart = false;
				m_bVoidCheak = true;
				m_fTime = 0.f;
			}
		}

		if (m_bVoidCheak)
		{
			if (m_fTime >= 1.2f)
			{
				m_bVoidAttack = false;
				m_pSkilScript->SetDarkVoidEnd(false);
				mAnimator->Play(L"Dark_End", false);				
				m_bVoidCheak = false;				
				m_bVoidEnd = true;
				m_bSoundCheak = true;
				m_fTime = 0.f;
			}
		}

		if (m_bVoidEnd)
		{
			if (m_fTime >= 0.2f)
			{
				if (m_bSoundCheak)
				{
					mAnimator->Play(L"Dark_Attack", false);
					m_bSoundCheak = false;
				}
			}
			if (m_fTime >= 0.4f)
			{

				
				darkAttackSound();							
				m_bVoidEnd = false;
				m_bVoidDeath = true;
				m_bSoundCheak = true;
				m_fTime = 0.f;
			}		
		}

		if (m_bVoidDeath)
		{
			if (m_fTime >= 0.4f)
			{
				if(m_bSoundCheak)
				{
					m_pSkilScript->SetDarkAttackFinsh(true);
					darkEndSound();
					m_bSoundCheak = false;
				}
			}

			if (m_fTime >= 0.8f)
			{				
				this->Death();
				m_pSkilScript->SetDarkAttackFinsh(false);
				m_bVoidDeath = false;
				m_fTime = 0.f;
			}

		}
		





		GameObject::Update();
	}

	void Skil_Dark::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void Skil_Dark::Render()
	{
		GameObject::Render();
	}

	void Skil_Dark::loadAnimation()
	{
		std::shared_ptr<Texture> skil = Resources::Load<Texture>(L"card_dark", L"Skil\\card_dark.png");
	
		//mNumbers.push_back(0);
		//mNumbers.push_back(1);
		//mNumbers.push_back(2);
		//mNumbers.push_back(3);
		//mNumbers.push_back(4);
		//mNumbers.push_back(5);
		//mNumbers.push_back(6);
		//CreateAnimation(L"Dark_Start", skil, mAnimator, Vector2(192.0f, 192.0f), Vec2::Zero, mNumbers, 0.1f);
		//mNumbers.clear();


		mNumbers.push_back(26);
		mNumbers.push_back(25);
		mNumbers.push_back(24);
		mNumbers.push_back(23);
		mNumbers.push_back(22);
		mNumbers.push_back(21);
		mNumbers.push_back(20);

		CreateAnimation(L"Dark_Start", skil, mAnimator, Vector2(192.0f, 192.0f), Vec2::Zero, mNumbers, 0.1f);
		mNumbers.clear();

		mNumbers.push_back(19);
		mNumbers.push_back(18);
		mNumbers.push_back(17);
		mNumbers.push_back(16);
		mNumbers.push_back(15);
		mNumbers.push_back(14);
		mNumbers.push_back(13);
		mNumbers.push_back(12);

	
		CreateAnimation(L"Dark_Void", skil, mAnimator, Vector2(192.0f, 192.0f), Vec2::Zero, mNumbers, 0.15f);
		mNumbers.clear();


		mNumbers.push_back(11);
		mNumbers.push_back(10);
		mNumbers.push_back(9);
		mNumbers.push_back(8);

		CreateAnimation(L"Dark_End", skil, mAnimator, Vector2(192.0f, 192.0f), Vec2::Zero, mNumbers, 0.1f);
		mNumbers.clear();


		mNumbers.push_back(7);
		mNumbers.push_back(6);
		mNumbers.push_back(5);
		mNumbers.push_back(4);
		mNumbers.push_back(3);
		mNumbers.push_back(2);
		mNumbers.push_back(1);
		mNumbers.push_back(0);
		CreateAnimation(L"Dark_Attack", skil, mAnimator, Vector2(192.0f, 192.0f), Vec2::Zero, mNumbers, 0.1f);
		mNumbers.clear();	
		
	}

	void Skil_Dark::loadSound()
	{
		std::shared_ptr<AudioClip> Dark_Void = Resources::Load<AudioClip>
			(L"Dark_Void", L"D:\\50\\Resources\\Sound\\Dark_Void.ogg");

		std::shared_ptr<AudioClip> Dark_Attack = Resources::Load<AudioClip>
			(L"Dark_Attack", L"D:\\50\\Resources\\Sound\\Dark_Attack.ogg");

		std::shared_ptr<AudioClip> Dark_End = Resources::Load<AudioClip>
			(L"Dark_End", L"D:\\50\\Resources\\Sound\\Dark_End.ogg");

		std::shared_ptr<AudioClip> Dark_Start = Resources::Load<AudioClip>
			(L"Dark_Start", L"D:\\50\\Resources\\Sound\\Dark_Start.ogg");

	}

	void Skil_Dark::darkStartSound()
	{
		std::shared_ptr<AudioClip> sound = Resources::Find<AudioClip>(L"Dark_Start");
		sound->SetLoop(false);
		sound->Play();
	}

	void Skil_Dark::darkVoidSound()
	{
		std::shared_ptr<AudioClip> sound = Resources::Find<AudioClip>(L"Dark_Void");
		sound->SetLoop(false);
		sound->Play();
	}

	void Skil_Dark::darkAttackSound()
	{
		std::shared_ptr<AudioClip> sound = Resources::Find<AudioClip>(L"Dark_Attack");
		sound->SetLoop(false);
		sound->Play();
	}

	void Skil_Dark::darkEndSound()
	{
		std::shared_ptr<AudioClip> sound = Resources::Find<AudioClip>(L"Dark_End");
		sound->SetLoop(false);
		sound->Play();
	}

}