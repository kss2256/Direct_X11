#pragma once
#include "ksGameObject.h"
#include "ksPlayer.h"
#include "ksStatus.h"

namespace ks
{

    class Animator;
    class Transform;
    class PlayerMissile :
        public GameObject
    {

    public:
        PlayerMissile();
        virtual ~PlayerMissile();


        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;



        GameObject* GetTarget() { return mPlayer; }
        Vec3 GetDirection() { return mDirection; }


        void SetTarget(GameObject* target) { mPlayer = (Player*)target; }
        void SetDirection(Vec3 dir) { mDirection = dir; }

    private:


        Transform*      mTransform;
        Animator*       mAnimator;
        Player*         mPlayer;
        s_PlayerInfo         mState;

        Vec3            mPos;
        Vec3            mDir;

        Vec3            mDirection;

        static float    mCooldownTime;

    };
}
