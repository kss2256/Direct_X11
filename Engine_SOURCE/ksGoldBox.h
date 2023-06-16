#pragma once
#include "ksUIBase.h"
#include "ksPlayer.h"
#include "ksAnimation.h"
#include "ksAnimator.h"

enum class e_BoxType
{
	Gold,
	Platinum,
};


namespace ks
{
	class Transform;
    class GoldBox :
        public UIBase
    {

	public:
		GoldBox();
		virtual ~GoldBox();


		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;


		Player* GetTarget() { return mTarget; }

		void SetTarget(Player* player) { mTarget = player; }

		void SetBoxType(e_BoxType type) { m_eBoxType = type; }
		void IsBoxOpen(bool change) { m_bBoxShake = change; }

		bool IsOpenFinsh() { return m_bOpenFinsh; }


	private:

		void loadAnimation();
		void CreateAnimation(const std::wstring& name, std::shared_ptr<Texture> texture, Animator* animaotr
			, Vec2 scale, Vector2 offset, std::vector<UINT> numbers, float duration);
		void loadSound();
		void boxOpenSound();
		void PlatinumSound();
		void goldSound();
		void boxStartShake();
		void createItem();


	private:

		Transform*				mTransform;
		Animator*				mAnimator;
		Player*					mTarget;		
		Vec3					mPlayerPos;
		Vec3					mUiPos;
		Vec3					mFinalPos;

		Vec3					mShakePos;
		Vec3					mFixPos;

		float					mShakeTime;
		float					m_fTime;

		std::vector<Sprite>		mSprites;
		std::vector<Sprite>		mSvaeSprite;

		std::vector<UINT>       mNumbers;

		e_BoxType				m_eBoxType;
		bool					m_bAniChange;
		bool					m_bBoxShake;
		bool					m_bOnceCheak;
		bool					m_bBoxItemCteate;

		bool					m_bOpenFinsh;


    };
}
