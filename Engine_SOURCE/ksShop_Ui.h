#pragma once
#include "ksUIBase.h"
#include "ksPlayer.h"
#include "ksAnimation.h"
#include "ksAnimator.h"
#include "ksCCoin.h"


namespace ks
{
    class Shop_Ui :
        public UIBase
    {

    public:
		Shop_Ui();
		~Shop_Ui();


		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		Player* GetTarget() { return mTarget; }

		UINT GetCoinValue() { return m_uCoinValue; }

		void SetTarget(Player* player) { mTarget = player; }

		void SetCoinValue(UINT value) { m_uCoinValue = value; }
		void ItemLoot(bool loot) { m_bItemLoot = loot; }


	private:
		void loadAnimation();
		void CreateAnimation(const std::wstring& name, std::shared_ptr<Texture> texture, Animator* animaotr
			, Vec2 scale, Vector2 offset, std::vector<UINT> numbers, float duration);


	private:

		Transform*					mTransform;
		Animator*					mAnimator;
		Player*						mTarget;
		Vec3						mUiPos;
		//Vec3						mUiScale;
		Vec3						mFinalPos;


		UINT						m_uCoinValue;

		std::vector<Sprite>			mSprites;
		std::vector<Sprite>			mSvaeSprite;

		std::vector<UINT>			mNumbers;


		bool						m_bStartCheak;
		bool						m_bEndCheak;
		bool						m_bItemLoot;




    };
}
