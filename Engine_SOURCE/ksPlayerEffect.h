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
        s_PlayerInfo GetPlayer() { return mState;}



        void SetTarget(GameObject* target) { mPlayer = (Player*)target; }
		void SetPlayer(s_PlayerInfo player) { mState = player; }


    private:

        Player* mPlayer;
        Transform* mTransform;
        Animator* mAnimator;

        s_PlayerInfo         mState;
        eDirection      mDirection;


    };
}
