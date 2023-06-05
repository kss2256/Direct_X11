#pragma once
#include "ksUIBase.h"
#include "ksPlayer.h"
#include "ksAnimation.h"
#include "ksAnimator.h"


namespace ks
{	
    class PlayerItem :
        public UIBase
    {

	public:
		PlayerItem();
		virtual ~PlayerItem();


		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		Player* GetTarget() { return mTarget; }
		eItem GetPlayerItem() { return mPlayerItem; }

		void SetTarget(Player* player) { mTarget = player; }
		void SetPlayerItem(eItem item) { mPlayerItem = item; }

	private:

		void loadAnimation();
		void CreateAnimation(const std::wstring& name, std::shared_ptr<Texture> texture, Animator* animaotr
			, Vec2 scale, Vector2 offset, std::vector<UINT> numbers, float duration);


	private:

		Transform*		mTransform;
		Animator*		mAnimator;
		Player*			mTarget;
		Vec3			mPlayerPos;
		Vec3			mUiPos;
		Vec3			mFinalPos;

		eItem			mPlayerItem;

		std::vector<Sprite>		mSprites;
		std::vector<Sprite>		mSvaeSprite;

		std::vector<UINT>       mNumbers;


    };
}
