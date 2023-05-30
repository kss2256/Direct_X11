#pragma once
#include "ksComponent.h"

namespace ks
{
    enum class eDirection
    {
        None,
        Up,
        UpLeft,
        Left,
        DownLeft,
        Down,
        DownRight,
        Right,
        UpRight,
        BothX,
        BothY,
        End,
    };

    enum class eSituation
    {
        None,
        Idle,
        Run,
        Attack,
        Auto,
        Continue,
        Connect,
        Skil,
        Patrol,
        Hit,
        Sit,
        Item,
        Death,
    };

    struct tStateInfo
    {
        eDirection direction;
        eSituation situation;

    };


    class Status
        : public Component
    {




    public:
        Status();
        ~Status();


        virtual void Initalize();
        virtual void Update();
        virtual void FixedUpdate();
        virtual void Render();


        tStateInfo GetStateInfo() { return mState; }



        void SetStateInfo(tStateInfo state) { mState = state; }


    private:

        tStateInfo      mState;

    };
}
