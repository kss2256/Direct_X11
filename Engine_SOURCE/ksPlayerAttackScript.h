#pragma once
#include "ksScript.h"


namespace ks
{
	class Player;
	class PlayerAttackScript :
		public Script
	{
	public:
		PlayerAttackScript();
		~PlayerAttackScript();


		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;



		float GetPlayerStr() { return mStr; }
		Player* GetPlayer() { return mPlayer; }

       
        void SetPlayerStr(float value) { mStr = value; }
		void SetPlayer(Player* player) { mPlayer = player; }

    private:

        float					mStr;
        Player*                 mPlayer;


    };
}
