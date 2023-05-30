#include "ksAnimation.h"
#include "ksTime.h"
#include "ksRenderer.h"

namespace ks
{
	Animation::Animation()
		: mAnimator(nullptr)
		, mAtlas(nullptr)
		, mSpriteSheet{}
		, mIndex(-1)
		, mTime(0.0f)
		, mbComplete(false)
	{
		
	}

	Animation::~Animation()
	{
	}

	UINT Animation::Update()
	{
		if (mbComplete)
			return -1;

		// �ð� üũ
		mTime += Time::DeltaTime();

		// ���� �ð��� �ش� �������� �����ð��� �Ѿ�� �������������� �̵�
		if (mSpriteSheet[mIndex].duration < mTime)
		{
			mTime = 0.0f;
			++mIndex;
			if (mSpriteSheet.size() <= mIndex)
			{
				mbComplete = true;
				mIndex = (int)mSpriteSheet.size() - 1;
			}

			return mIndex;
		}

		return -1;
	}

	void Animation::FixedUpdate()
	{

	}

	void Animation::Render()
	{
	}

	void Animation::Create(const std::wstring& name
		, std::shared_ptr<Texture> atlas
		, Vector2 leftTop, Vector2 size, Vector2 offset
		, UINT spriteLegth, float duration)
	{
		mAnimationName = name;

		mAtlas = atlas;
		float width = (float)atlas->GetWidth();
		float height = (float)atlas->GetHeight();

		for (size_t i = 0; i < spriteLegth; i++)
		{
			// API �ʹ� �ٸ��� 0~1 ������ ������ǥ�� ��ġ�� ǥ���ؾ��Ѵ�.
			Sprite sprite = {};
			sprite.leftTop = Vector2((leftTop.x + (size.x * (float)i)) / width
				, (leftTop.y) / height);
			sprite.size = Vector2(size.x / width, size.y / height);
			sprite.offset = offset;
			sprite.duration = duration;
			sprite.atlasSize = Vector2(400.0f / width, 400.0f / height);
			sprite.AnimationName = name;

			mSpriteSheet.push_back(sprite);
		}

	}

	void Animation::CreateAfter(std::vector<Sprite> sprites, std::shared_ptr<Texture> atlas)
	{

		mAtlas = atlas;
		float width = (float)atlas->GetWidth();
		float height = (float)atlas->GetHeight();

		for (size_t i = 0; i < sprites.size(); i++)
		{
			mAnimationName = sprites[i].AnimationName;
			// API �ʹ� �ٸ��� 0~1 ������ ������ǥ�� ��ġ�� ǥ���ؾ��Ѵ�.
			Sprite sprite = {};
			sprite.leftTop = sprites[i].leftTop;
			sprite.size = sprites[i].size;
			sprite.offset = sprites[i].offset;
			sprite.duration = sprites[i].duration;
			sprite.atlasSize = sprites[i].atlasSize;
			sprite.AnimationName = sprites[i].AnimationName;

			mSpriteSheet.push_back(sprite);
		}


	}

	void Animation::BindShader()
	{
		mAtlas->BindShader(eShaderStage::PS, 12);

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Animation];

		renderer::AnimationCB info = {};
		info.type = (UINT)eAnimationType::SecondDimension;
		info.leftTop = mSpriteSheet[mIndex].leftTop;
		info.offset = mSpriteSheet[mIndex].offset;
		info.size = mSpriteSheet[mIndex].size;
		info.atlasSize = mSpriteSheet[mIndex].atlasSize;

		cb->Bind(&info);
		cb->SetPipline(eShaderStage::PS);
	}

	void Animation::Reset()
	{
		mTime = 0.0f;
		mIndex = 0;
		mbComplete = false;
	}

	void Animation::Clear()
	{
		//Texture clear
		Texture::Clear(12);

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Animation];
		renderer::AnimationCB info = {};
		info.type = (UINT)eAnimationType::None;

		cb->Bind(&info);
		cb->SetPipline(eShaderStage::PS);
	}

}