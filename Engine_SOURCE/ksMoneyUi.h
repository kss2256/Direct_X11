#pragma once
#include "ksUIBase.h"
#include "ksPlayer.h"
#include "ksAnimation.h"
#include "ksAnimator.h"

enum class eMoneyCheak
{
	Money_1,
	Money_10,
	Money_100,
};


namespace ks
{
	class CreateMoney;
	class Animator;
	class Transform;
	class MoneyUi :
		public UIBase
	{
	public:

		MoneyUi();
		virtual ~MoneyUi();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		Player* GetTarget() { return mTarget; }



		void SetTarget(Player* player) { mTarget = player; }
		void SetMoney(UINT value) { m_uMoneyValue = value; }

	private:

		void createMoney(eMoneyCheak value);



	private:

		Transform*				mTransform;
		Animator*				mAnimator;
		Player*					mTarget;
		Vec3					mUiPos;
		//Vec3					mUiScale;
		Vec3					mFinalPos;

		UINT					m_uMoneyValue;
		UINT					m_uPrevMoney;

		std::vector<Sprite>		mSprites;
		std::vector<Sprite>		mSvaeSprite;

		std::vector<UINT>		mNumbers;
		static std::wstring		mItemName;

		bool					m_bStartCheak;
		bool					m_bEndCheak;

		CreateMoney*			m_pMoney_1;
		CreateMoney*			m_pMoney_10;
		CreateMoney*			m_pMoney_100;
		UINT					m_uMoney_1;
		UINT					m_uMoney_10;
		UINT					m_uMoney_100;

		eMoneyCheak				m_eMoneyCheak;

	};
}
