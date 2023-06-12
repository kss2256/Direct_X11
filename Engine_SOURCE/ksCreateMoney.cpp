#include "ksCreateMoney.h"
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

	CreateMoney::CreateMoney()
		: m_bMoneyChange(false)
	{

		mAnimator = AddComponent<Animator>();

		mTransform = GetComponent<Transform>();

		SpriteRenderer* sr = AddComponent<SpriteRenderer>();

		loadAnimation();


		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"MoneyUiMaterial");
		sr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);


	}

	CreateMoney::~CreateMoney()
	{
	}

	void CreateMoney::Initalize()
	{
		mUiPos = mTransform->GetPosition();

		
		playMoneyAnimaiton();


		GameObject::Initalize();
	}

	void CreateMoney::Update()
	{

		if (mTarget != nullptr)
		{
			//mPlayerPos = mTarget->GetComponent<Transform>()->GetPosition();

			Vec3 Pos = mTransform->GetPosition();

			mPlayerPos = mainCamera->GetOwner()->GetComponent<Transform>()->GetPosition();


			mFinalPos = mPlayerPos + mUiPos;

			mTransform->SetPosition(mFinalPos);

			if (m_bMoneyChange)
			{				
				playMoneyAnimaiton();
				m_bMoneyChange = false;
			}


		}



		UIBase::Update();
	}

	void CreateMoney::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void CreateMoney::Render()
	{
		GameObject::Render();
	}

	void CreateMoney::loadAnimation()
	{
		std::shared_ptr<Texture> Bronze = Resources::Load<Texture>(L"Money", L"UI\\Money.png");


		mNumbers.push_back(0);
		CreateAnimation(L"Money_0", Bronze, mAnimator, Vector2(14.0f, 20.0f), Vec2::Zero, mNumbers, 0.15f);
		mNumbers.clear();

		mNumbers.push_back(1);
		CreateAnimation(L"Money_1", Bronze, mAnimator, Vector2(14.0f, 20.0f), Vec2::Zero, mNumbers, 0.15f);
		mNumbers.clear();

		mNumbers.push_back(2);
		CreateAnimation(L"Money_2", Bronze, mAnimator, Vector2(14.0f, 20.0f), Vec2::Zero, mNumbers, 0.15f);
		mNumbers.clear();

		mNumbers.push_back(3);
		CreateAnimation(L"Money_3", Bronze, mAnimator, Vector2(14.0f, 20.0f), Vec2::Zero, mNumbers, 0.15f);
		mNumbers.clear();

		mNumbers.push_back(4);
		CreateAnimation(L"Money_4", Bronze, mAnimator, Vector2(14.0f, 20.0f), Vec2::Zero, mNumbers, 0.15f);
		mNumbers.clear();

		mNumbers.push_back(5);
		CreateAnimation(L"Money_5", Bronze, mAnimator, Vector2(14.0f, 20.0f), Vec2::Zero, mNumbers, 0.15f);
		mNumbers.clear();

		mNumbers.push_back(6);
		CreateAnimation(L"Money_6", Bronze, mAnimator, Vector2(14.0f, 20.0f), Vec2::Zero, mNumbers, 0.15f);
		mNumbers.clear();

		mNumbers.push_back(7);
		CreateAnimation(L"Money_7", Bronze, mAnimator, Vector2(14.0f, 20.0f), Vec2::Zero, mNumbers, 0.15f);
		mNumbers.clear();

		mNumbers.push_back(8);
		CreateAnimation(L"Money_8", Bronze, mAnimator, Vector2(14.0f, 20.0f), Vec2::Zero, mNumbers, 0.15f);
		mNumbers.clear();

		mNumbers.push_back(9);
		CreateAnimation(L"Money_9", Bronze, mAnimator, Vector2(14.0f, 20.0f), Vec2::Zero, mNumbers, 0.15f);
		mNumbers.clear();


	}

	void CreateMoney::CreateAnimation(const std::wstring& name, std::shared_ptr<Texture> texture, Animator* animaotr, Vec2 scale, Vector2 offset, std::vector<UINT> numbers, float duration)
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

	void CreateMoney::playMoneyAnimaiton()
	{		

		if (m_uMoneyValue == 0)
			mAnimator->Play(L"Money_0", true);
		else if (m_uMoneyValue == 1)
			mAnimator->Play(L"Money_1", true);
		else if (m_uMoneyValue == 2)
			mAnimator->Play(L"Money_2", true);
		else if (m_uMoneyValue == 3)
			mAnimator->Play(L"Money_3", true);
		else if (m_uMoneyValue == 4)
			mAnimator->Play(L"Money_4", true);
		else if (m_uMoneyValue == 5)
			mAnimator->Play(L"Money_5", true);
		else if (m_uMoneyValue == 6)
			mAnimator->Play(L"Money_6", true);
		else if (m_uMoneyValue == 7)
			mAnimator->Play(L"Money_7", true);
		else if (m_uMoneyValue == 8)
			mAnimator->Play(L"Money_8", true);
		else if (m_uMoneyValue == 9)
			mAnimator->Play(L"Money_9", true);

	}

}