#pragma once
#include "ksUIBase.h"
#include "ksPlayer.h"
#include "ksAnimation.h"
#include "ksAnimator.h"

enum class eCoin
{
	None,
	Bronze,
	Silver,
	Gold,
};

namespace ks
{
	class Animator;
	class Transform;
	class CCoin :
		public UIBase
	{
	public:



	public:

		CCoin();
		virtual ~CCoin();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		Player* GetTarget() { return mTarget; }



		void SetTarget(Player* player) { mTarget = player; }
		void SetCoin(eCoin coin, UINT value) { m_eCoin = coin, m_uCoinValue = value; }


	private:
		void loadAnimation();
		void CreateAnimation(const std::wstring& name, std::shared_ptr<Texture> texture, Animator* animaotr
			, Vec2 scale, Vector2 offset, std::vector<UINT> numbers, float duration);


	private:

		Transform*		mTransform;
		Animator*		mAnimator;
		Player*			mTarget;
		Vec3			mUiPos;
		Vec3			mJumpPos;
		Vec3			mNomarlizeUp;
		Vec3			mNomarlizeDown;
		//Vec3			mUiScale;
		Vec3			mFinalPos;
			
		eCoin			m_eCoin;
		UINT			m_uCoinValue;

		std::vector<Sprite>		mSprites;
		std::vector<Sprite>		mSvaeSprite;

		std::vector<UINT>			mNumbers;
		static std::wstring			mItemName;

		bool		m_bStartCheak;
		bool		m_bEndCheak;

	};
}
