#pragma once
#include "ksGameObject.h"
#include "ksPlayer.h"
#include "ksStatus.h"


namespace ks
{
    class Collider2D;
    class Animator;
    class Transform;
    class MonsterMissile :
        public GameObject
    {

    public:
        MonsterMissile();
        virtual ~MonsterMissile();

        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;



        GameObject* GetTarget() { return mPlayer; }
        Vec3 GetDirection() { return mDirection; }
        float GetSpeed() { return mSpeed; }
        float GetDegree() { return mDegree; }

        void SetTarget(GameObject* target) { mPlayer = (Player*)target; }
        void SetDirection(Vec3 dir) { mDirection = dir; }

        void SetSpeed(float speed) { mSpeed = speed; }
        void SetDegree(float degree) { mDegree = degree; }


    private:


        Transform*      mTransform;
        Animator*       mAnimator;
        Player*         mPlayer;
        sPlayer         mState;

        Collider2D*     mCollider;

        Vec3            mPos;
        Vec3            mDir;
        Vec3            mDirection;

        float           mSpeed;
        float           mDegree;

        float    mCooldownTime;

    };
}
