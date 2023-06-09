#pragma once
#include "ksPlayerHP.h"


namespace ks
{
	class SpriteRenderer;
	class Transform;
	class PlayerCreateHp :
		public PlayerHP
	{
	public:

		PlayerCreateHp();
		virtual ~PlayerCreateHp();


		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		PlayerHP* GetTarget() { return mTarget; }


		void SetTarget(PlayerHP* player) { mTarget = player; }
		void SetFullHp(bool hp) { m_bFullHp = hp; }
		void SetHalfHp(bool hp) { m_bHalfHp = hp; }
		void SetUiPos(Vec3 pos) { mUiPos = pos; }


	private:

		Transform*		mTransform;
		PlayerHP*		mTarget;
		Vec3			mPlayerPos;
		Vec3			mUiPos;
		//Vec3			mUiScale;
		Vec3			mFinalPos;

		SpriteRenderer* mSprite;


		bool			m_bFullHp;
		bool			m_bHalfHp;


	};



}
