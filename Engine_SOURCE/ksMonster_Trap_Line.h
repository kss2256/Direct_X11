#pragma once
#include "ksMonster.h"
#include "ksPlayer.h"
#include "ksStatus.h"

enum class Monster_Line
{
    None,
    Flime_Missile,
    Flime_Trap,
    Ent_Trap,
    Ent_Earthquake,

    End,
};


namespace ks
{
    class Collider2D;
    class Animator;
    class Transform;
    class Monster_Trap_Line :
        public Monster
    {
    public:
        Monster_Trap_Line();
        virtual ~Monster_Trap_Line();

        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;



        GameObject* GetTarget() { return mPlayer; }
        Vec3 GetDirection() { return mDirection; }
        float GetSpeed() { return mSpeed; }
        float GetDegree() { return mDegree; }
        float GetDistance() { return mDistance; }
        Monster_Line GetMonsterLine() { return mMonLine; }

        void SetTarget(GameObject* target) { mPlayer = (Player*)target; }
        void SetDirection(Vec3 dir) { mDirection = dir; }
        void SetDistance(float distance) { mDistance = distance; }

        void SetSpeed(float speed) { mSpeed = speed; }
        void SetDegree(float degree) { mDegree = degree; }
        void SetMonsterLine(Monster_Line line) { mMonLine = line; }


        void Lineinterval(float interval);
    private:

        void loadAnimation();
        void loadSound();
        void soundTrapAttack();


    private:


        Transform*      mTransform;
        Animator*       mAnimator;
        Player*         mPlayer;
        s_PlayerInfo         mState;

        Collider2D*     mCollider;

        Vec3            mPos;
        Vec3            mDir;
        Vec3            mDirection;

        float           mSpeed;
        float           mDegree;
        float           mDistance;

        float    mCooldownTime;

        Monster_Line    mMonLine;
        

    };
}
