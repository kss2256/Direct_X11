#pragma once
#include "ksGameObject.h"


namespace ks
{
    class Collider2D;
    class Player;
    class Animator;
    class Transform;
    class Stage1_1Move :
        public GameObject
    {

    public:

        Stage1_1Move();
        virtual ~Stage1_1Move();

        virtual void Initalize();
        virtual void Update();
        virtual void FixedUpdate();
        virtual void Render();


        static Player* GetTarget() { return mTarget; }
        eGroundStage GetGroundStage() { return mGroundStage; }
        static bool GetFadeEffect() { return mFadeEffect; }


        static void SetTarget(Player* target) { mTarget = target; }
        static void SetFedeEffect(bool fade) { mFadeEffect = fade; }
        void SetGroundStage(eGroundStage stage) { mGroundStage = stage; }




    private:

        Transform*                  mTransform;
        Collider2D*                 mCollider;

        static Player*              mTarget;
        static bool                 mFadeEffect;
        static bool                 mFadeEffectCheak;
        static bool                 mGroundExecuted;

        float                       mTime;

        eGroundStage                mGroundStage;


    };
}
