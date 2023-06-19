#pragma once
#include "ksUIBase.h"




namespace ks
{
    class Transform;
    class SkilSlot :
        public UIBase
    {

    public:

        SkilSlot();
        ~SkilSlot();

        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

    private:

        Transform*      mTransform;
        bool            m_bSlotOnOff;

        Vec3			mPlayerPos;
        Vec3			mUiPos;
        //Vec3			mUiScale;
        Vec3			mFinalPos;
        eItem           e_skil;


        friend class SkilUi;

    };
}
