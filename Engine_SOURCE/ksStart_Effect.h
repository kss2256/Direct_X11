#pragma once
#include "ksGameObject.h"

namespace ks
{
    class Animator;
    class Start_Effect :
        public GameObject
    {

    public:
        Start_Effect();
        ~Start_Effect();


        virtual void Initalize();
        virtual void Update();
        virtual void FixedUpdate();
        virtual void Render();

    private:
        void loadanimation();


    private:

        Animator* mAnimator;


    };
}
