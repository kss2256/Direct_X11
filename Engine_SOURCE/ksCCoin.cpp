#include "ksCCoin.h"
#include "ksSpriteRenderer.h"
#include "ksMaterial.h"
#include "ksMesh.h"
#include "ksResources.h"
#include "ksTransform.h"
#include "ksObject.h"
#include "ksTime.h"


#include "ksInput.h"


namespace ks
{

	CCoin::CCoin()
		: m_bStartCheak(false)
		, m_bEndCheak(false)
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

	CCoin::~CCoin()
	{

	

	}

	void CCoin::Initalize()
	{

		switch (m_eCoin)
		{		
		case eCoin::Bronze:
		{
			mAnimator->Play(L"Bronze",true);
		}
			break;
		case eCoin::Silver:
		{
			mAnimator->Play(L"Sliver", true);
		}
			break;
		case eCoin::Gold:
		{
			mAnimator->Play(L"Gold", true);
		}
			break;		
		}
		mUiPos = mTransform->GetPosition();
		mFinalPos = mUiPos;
		mJumpPos = mUiPos;
		mJumpPos.y += 1.0f;

		mNomarlizeUp = mJumpPos - mFinalPos;
		mNomarlizeUp.Normalize();

		mNomarlizeDown = mFinalPos - mJumpPos;
		mNomarlizeDown.Normalize();



		GameObject::Initalize();
	}

	void CCoin::Update()
	{
		if(!m_bStartCheak)
		{
			if (mFinalPos.y <= mJumpPos.y)
			{
				mFinalPos += mNomarlizeUp * Time::DeltaTime() * 6.0f;
				mTransform->SetPosition(mFinalPos);
			}
			else 
			{
				m_bStartCheak = true;
				m_bEndCheak = true;
			}
		}
		if(m_bEndCheak)
		{
			if (mFinalPos.y >= mUiPos.y)
			{
				mFinalPos += mNomarlizeDown * Time::DeltaTime() * 6.0f;
				mTransform->SetPosition(mFinalPos);
			}
			else
				m_bEndCheak = false;

		}

		GameObject::Update();
	}

	void CCoin::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void CCoin::Render()
	{
		GameObject::Render();
	}

	void CCoin::loadAnimation()
	{

		std::shared_ptr<Texture> Bronze = Resources::Load<Texture>(L"Bronze", L"UI\\Bronze.png");
		std::shared_ptr<Texture> Sliver = Resources::Load<Texture>(L"Sliver", L"UI\\Sliver.png");
		std::shared_ptr<Texture> Gold = Resources::Load<Texture>(L"Gold", L"UI\\Gold.png");



		mNumbers.push_back(0);
		mNumbers.push_back(1);
		mNumbers.push_back(2);
		mNumbers.push_back(3);
		mNumbers.push_back(4);
		mNumbers.push_back(5);
		mNumbers.push_back(6);
		mNumbers.push_back(7);
		CreateAnimation(L"Bronze", Bronze, mAnimator, Vector2(16.0f, 16.0f), Vec2::Zero, mNumbers, 0.15f);
		mNumbers.clear();


		mNumbers.push_back(0);
		mNumbers.push_back(1);
		mNumbers.push_back(2);
		mNumbers.push_back(3);
		mNumbers.push_back(4);
		mNumbers.push_back(5);
		mNumbers.push_back(6);
		mNumbers.push_back(7);
		CreateAnimation(L"Sliver", Sliver, mAnimator, Vector2(16.0f, 16.0f), Vec2::Zero, mNumbers, 0.15f);
		mNumbers.clear();


		mNumbers.push_back(0);
		mNumbers.push_back(1);
		mNumbers.push_back(2);
		mNumbers.push_back(3);
		mNumbers.push_back(4);
		mNumbers.push_back(5);
		mNumbers.push_back(6);
		mNumbers.push_back(7);
		CreateAnimation(L"Gold", Gold, mAnimator, Vector2(16.0f, 16.0f), Vec2::Zero, mNumbers, 0.15f);
		mNumbers.clear();



	}

	void CCoin::CreateAnimation(const std::wstring& name, std::shared_ptr<Texture> texture, Animator* animaotr, Vec2 scale, Vector2 offset, std::vector<UINT> numbers, float duration)
	{

		// 이중 포문 		
		Vec2 value = Vec2(texture->GetWidth() / scale.x, texture->GetHeight() / scale.y);
		UINT Col = (UINT)value.x;					//3개?
		UINT Row = (UINT)value.y;					//10개?

		UINT textureeLegth = (UINT)(value.x * value.y);		//총 개수 30개

		//이중 포문 이건 10행
		for (UINT i = 0; i < Row; i++)
		{
			//이중 포문 이건 3열
			for (UINT j = 0; j < Col; j++)
			{
				Sprite animation;

				animation.AnimationName = name;
				animation.atlasSize = scale;
				animation.duration = duration;
				animation.leftTop = Vec2(j * scale.x, i * scale.y);
				animation.offset = offset;
				//animation.pos = mTransform->GetPosition(); // 이건 필요 없는듯 ? 필요할떄 사용예정 포지션을 받아와야함
				animation.size = scale;


				mSvaeSprite.push_back(animation);
			}
		}

		for (size_t i = 0; i < numbers.size(); i++)
		{
			std::vector<UINT>::iterator iter = numbers.begin();

			mSprites.push_back(mSvaeSprite[iter[i]]);
		}


		for (size_t i = 0; i < mSprites.size(); i++)
		{
			mSprites[i].leftTop = Vector2((mSprites[i].leftTop.x / texture->GetWidth()), (mSprites[i].leftTop.y) / texture->GetHeight());
			mSprites[i].size = Vector2(mSprites[i].size.x / texture->GetWidth(), mSprites[i].size.y / texture->GetHeight());
			mSprites[i].offset = mSprites[i].offset;
			mSprites[i].duration = mSprites[i].duration;
			mSprites[i].atlasSize = Vector2(400.0f / texture->GetWidth(), 400.0f / texture->GetHeight());
			mSprites[i].AnimationName = mSprites[i].AnimationName;
		}



		animaotr->CreateAfter(mSprites, texture);
		mSvaeSprite.clear();
		mSprites.clear();


	}



}