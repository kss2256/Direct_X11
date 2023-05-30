#pragma once
#include "ksGameObject.h"
#include "ksTexture.h"



namespace ks
{
    class Player;
    class Cloud :
        public GameObject
    {

    public:
        Cloud();
        ~Cloud();
        
        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        eGroundStage GetGroundStage() { return mGroundStage; }
        static Player* GetTarget() { return mTarget; }



        void SetGroundStage(eGroundStage stage) { mGroundStage = stage; }
        static void SetTarget(Player* target) { mTarget = target; }

    private:

        eGroundStage                    mGroundStage;
   
     

        Vec3                            mStartPos;

        static float                    mHoldingTime;
        static Player*                  mTarget;

    };
}
