#pragma once
#include "ksUIBase.h"
#include "ksPlayer.h"
#include "ksAnimation.h"
#include "ksAnimator.h"

namespace ks
{
	class Animator;
	class Transform;
    class CreateMoney :
        public UIBase
    {
	public:
		CreateMoney();
		virtual ~CreateMoney();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		Player* GetTarget() { return mTarget; }



		void SetTarget(Player* player) { mTarget = player; }
		void SetMoney(UINT value) { m_uMoneyValue = value; }
		void SetMoneyChange(bool change) { m_bMoneyChange = change; }


	private:
		void loadAnimation();
		void CreateAnimation(const std::wstring& name, std::shared_ptr<Texture> texture, Animator* animaotr
			, Vec2 scale, Vector2 offset, std::vector<UINT> numbers, float duration);
		void playMoneyAnimaiton();

	private:

		Transform*				mTransform;
		Animator*				mAnimator;
		Player*					mTarget;
		Vec3					mUiPos;
		Vec3					mPlayerPos;
		Vec3					mFinalPos;

		UINT					m_uMoneyValue;

		std::vector<Sprite>		mSprites;
		std::vector<Sprite>		mSvaeSprite;

		std::vector<UINT>		mNumbers;
		static std::wstring		mItemName;

		bool					m_bMoneyChange;





    };
}
