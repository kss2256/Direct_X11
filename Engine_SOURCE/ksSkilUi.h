#pragma once
#include "ksUIBase.h"
#include "ksPlayer.h"
#include "ksAnimation.h"
#include "ksAnimator.h"
#include "ksSkilSlot.h"

namespace ks
{

	class Transform;
    class SkilUi :
        public UIBase
    {

	public:

		SkilUi();
		virtual ~SkilUi();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		Player* GetTarget() { return mTarget; }

		eItem GetActiveSkil() { return m_pActiveSlot->e_skil; }


		bool IsActiveSlot()
		{ 
			if (m_pActiveSlot == nullptr)
				return false;
			else
			return true;
		}
		void SetTarget(Player* player) { mTarget = player; }

		void CreateSkillbook(eItem skil);
		

	private:
		void loadAnimation();
		void CreateAnimation(const std::wstring& name, std::shared_ptr<Texture> texture, Animator* animaotr
			, Vec2 scale, Vector2 offset, std::vector<UINT> numbers, float duration);
		void slotCheak(eItem skil);
		void createSkilSlot(eItem skil, Vec3 pos);
		void changeAnimation();

	private:

		Transform*		mTransform;
		Animator*		mAnimator;
		Player*			mTarget;
		Vec3			mPlayerPos;
		Vec3			mUiPos;
		//Vec3			mUiScale;
		Vec3			mFinalPos;


		SkilSlot*		m_pSkilSlot_1;
		SkilSlot*		m_pSkilSlot_2;
		SkilSlot*		m_pSkilSlot_3;
		SkilSlot*		m_pSkilSlot_4;
		SkilSlot*		m_pActiveSlot;
		

		std::vector<Sprite>		mSprites;
		std::vector<Sprite>		mSvaeSprite;

		std::vector<UINT>			mNumbers;



    };
}
