#pragma once
#include "ksEntity.h"
#include "ksTexture.h"

using namespace ks::math;
using namespace ks::graphics;
namespace ks
{

	struct Sprite
	{
		Vector2 leftTop;	// ���� ��� ��ǥ
		Vector2 size;		// ������ܺ��� �߶� ���� ������ �ȼ� ����
		Vector2 offset;		// ������ ��ġ �����ϱ����� ��ǥ
		Vector2 atlasSize;  // �ؽ�ó �̹����� ũ��
		float duration;		// �����Ӱ��� �ð� ����

		std::wstring AnimationName;
		Vec3	pos;

		Sprite()
			: leftTop(0.0f, 0.0f)
			, size(0.0f, 0.0f)
			, offset(0.0f, 0.0f)
			, atlasSize(0.0f)
			, duration(0.1f)
		{

		}
	};
	class Animation : public Entity
	{
	public:


		Animation();
		~Animation();

		UINT Update();
		void FixedUpdate();
		void Render();

		void Create(const std::wstring& name, std::shared_ptr<Texture> atlas
			, Vector2 leftTop, Vector2 size, Vector2 offset
			, UINT spriteLegth, float duration);

		void CreateAfter(std::vector<Sprite> sprites, std::shared_ptr<Texture> atlas);

		void BindShader();
		void Reset();
		void Clear();

		bool IsComplete() { return mbComplete; }
		std::wstring& AnimationName() { return mAnimationName; }


		void SetSpriteSheet(Sprite sheet) { mSpriteSheet.push_back(sheet); }
		std::vector<Sprite> GetSpriteSheet() { return mSpriteSheet; }

		int GetIndex() { return mIndex; }

	private:
		class Animator* mAnimator;
		std::wstring mAnimationName;
		std::shared_ptr<Texture> mAtlas;
		std::vector<Sprite> mSpriteSheet;
		int mIndex;
		float mTime;
		bool mbComplete;
	};
}
