#pragma once
#include "ksComponent.h"


namespace ks
{


    enum class Fade
    {
        None,
        Fade_In,
        Fade_Out,
        Fade_In_Out,
        End,

    };

    class Transform;
    class FadeEffect :
        public Component
    {
    public:
        FadeEffect();
        ~FadeEffect();


        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;


        void Fade_In();
        void Fade_Out();
        void Fade_In_Out();

        void SetEffect(Fade effect) { mFadeEffect = effect; }
        

    private:

        Transform*      mTransform;
        Fade            mFadeEffect;

        float    mAlphaTime;
        float    mEndTime;        
        



    };
}
