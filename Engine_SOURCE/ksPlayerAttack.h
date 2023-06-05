#pragma once
#include "ksGameObject.h"
#include "ksPlayer.h"
#include "ksStatus.h"
#include "ksPlayerAttackScript.h"


namespace ks
{
    class Collider2D;
    class SpriteRenderer;
    class Player;
    class Animator;
    class Transform;
    class PlayerAttack :
        public GameObject
    {
    public:

        PlayerAttack();
        virtual ~PlayerAttack();


    public:

        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;


    public:

        GameObject* GetTarget() { return mPlayer; }
        float GetCooldownTime() { return mCooldownTime; }
        eDirection GetDirection() { return mDirection; }
        static float GetSphereScale() { return mSphereScale; }



        void SetTarget(GameObject* target) { mPlayer = (Player*)target; }
        void SetCooldownTime(float time) { mCooldownTime = time; }
        void SetDirection(eDirection dir) { mDirection = dir; }
        static void SetSphereScale(float scale) { mSphereScale = scale; }


    private:

        void deathTime(float time);
        void dirAnimation(float value = 0.f);
        void bulletAnipos(Vector3 Scale, float offset);
        void swordAnipos(Vector3 Scale, float offset);

    private:

        Player*         mPlayer;
        Transform*      mTransform;
        Animator*       mAnimator;
        Collider2D*     mCollider;
        s_PlayerInfo         mState;
        eDirection      mDirection;
        PlayerAttackScript* mPlayerScript;
       

        Vec3            mPos;
        Vec3            mDir;



        float          mCheakTime;
        float          mCooldownTime;
        static float   mSphereScale;

        friend class PlayerMissile;
    };
   
}
