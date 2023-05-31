#pragma once
#include "ksScene.h"
#include "ksAnimator.h"
#include "ksTexture.h"
#include "ksAnimation.h"

namespace ks
{
	class Boss_Ent;
	class Boss_Flime;
	class FadeEffect;
	class Snake_Green;
	class Slime_Green;
	class Forest_Fairy;
	class Stage1_1Move;
	class Stage1_1Parts;
	class Stage1_1Shadows;
	class Stage1_1;
	class Player;
	class Mouse;
	class GameObject;
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		virtual ~PlayScene();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;


	private:
		void loadAnimation();
		void loadGround(eLayerType layer, eGroundStage stage, const std::wstring name, Vec3 pos);
		void loadShadows(eLayerType layer, eGroundStage stage, const std::wstring name, Vec3 pos);
		void loadParts(eLayerType layer, eGroundStage stage, const std::wstring name, Vec3 pos);
		void CreateAnimation(const std::wstring& name, std::shared_ptr<Texture> texture, Animator* animaotr
			, Vec2 scale, Vector2 offset, std::vector<UINT> numbers, float duration);

		

	private:

		Player*					mPlayer;
		Mouse*					mMouse;
		Stage1_1*				mStage;
		Stage1_1Shadows*		mStageShadows;
		Stage1_1Parts*			mStageParts;
		Stage1_1Move*			mStageMove;
		Forest_Fairy*			mForest_Fairy;
		Slime_Green*			mSlime_Green;
		Slime_Green*			mSlime_Green_Two;
		Snake_Green*			mSnake_Green;
		Snake_Green*			mSnake_Green_Two;
		Boss_Flime*				mBoss_Flime;
		Boss_Ent*				mBoss_Ent;


		FadeEffect*				mFadeEffect;

		std::vector<UINT>       mNumbers;
		std::vector<Sprite>		mSprites;
		std::vector<Sprite>		mSvaeSprite;
	};
}