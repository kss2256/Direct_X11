#include "ksCSkil.h"




namespace ks
{

	CSkil::CSkil()
	{
	}

	CSkil::~CSkil()
	{
	}

	void CSkil::Initalize()
	{
		GameObject::Initalize();
	}

	void CSkil::Update()
	{
		GameObject::Update();
	}

	void CSkil::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void CSkil::Render()
	{
		GameObject::Render();
	}
	

	void CSkil::CreateAnimation(const std::wstring& name, std::shared_ptr<Texture> texture, Animator* animaotr, Vec2 scale, Vector2 offset, std::vector<UINT> numbers, float duration)
	{
		// ���� ���� 		
		Vec2 value = Vec2(texture->GetWidth() / scale.x, texture->GetHeight() / scale.y);
		UINT Col = (UINT)value.x;					//3��?
		UINT Row = (UINT)value.y;					//10��?

		UINT textureeLegth = (UINT)(value.x * value.y);		//�� ���� 30��

		//���� ���� �̰� 10��
		for (UINT i = 0; i < Row; i++)
		{
			//���� ���� �̰� 3��
			for (UINT j = 0; j < Col; j++)
			{
				Sprite animation;

				animation.AnimationName = name;
				animation.atlasSize = scale;
				animation.duration = duration;
				animation.leftTop = Vec2(j * scale.x, i * scale.y);
				animation.offset = offset;
				//animation.pos = mTransform->GetPosition(); // �̰� �ʿ� ���µ� ? �ʿ��ҋ� ��뿹�� �������� �޾ƿ;���
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