#pragma once
#include "ksGameObject.h"
#include "ksPlayer.h"
#include "ksStatus.h"


namespace ks
{

    class Transform;
    class Animator;
    class PlayerEffect
        : public GameObject
    {

    public:
        PlayerEffect();
        virtual ~PlayerEffect();


    public:

        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;



        GameObject* GetTarget() { return mPlayer; }
        sPlayer GetPlayer() { return mState;}



        void SetTarget(GameObject* target) { mPlayer = (Player*)target; }
		void SetPlayer(sPlayer player) { mState = player; }


    private:

        Player* mPlayer;
        Transform* mTransform;
        Animator* mAnimator;

        sPlayer         mState;
        eDirection      mDirection;


    };
}
