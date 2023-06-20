#pragma once
#include "ksScript.h"
#include "ksPlayer.h"
#include "ksMonster.h"
#include "ksCSkil.h"

namespace ks
{
	
    class SkilScript :
        public Script
    {
	public:

		SkilScript();
		virtual ~SkilScript();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		float GetPlayerStr() { return mStr; }
		Player* GetPlayer() { return mPlayer; }
		Monster* GetMonster() { return mMonster; }
		CSkil* GetSkilOwner() { return mSkilOwner; }
		

		void SetPlayerStr(float value) { mStr = value; }
		void SetPlayer(Player* player) { mPlayer = player; }		
		void SetMonster(Monster* monster) { mMonster = monster; }
		void SetSkilOwner(CSkil* monster) { mSkilOwner = monster; }
		void SetSkil(eItem skil) { m_eSkil = skil; }
		void SetSkilPos(Vec3 pos) { m_vPos = pos; }
		void SetDarkAttackFinsh(bool end) { m_bDarkAttackFinsh = end; }
		void SetDarkVoidEnd(bool end) { m_bDarkVoid = end; }

	private:


		float					mStr;
		float					m_fTime;
		Player*					mPlayer;		
		Monster*				mMonster;

		CSkil*					mSkilOwner;


		eItem					m_eSkil;

		Vec3					m_vPos;
		Vec3					m_vTargetPos;
		Vec3					m_vNomal;

		bool					m_bDarkVoid;		
		bool					m_bDarkAttackFinsh;
		bool					m_bNomalOneCheak;


    };
}
