#pragma once
#include "ksUIBase.h"

namespace ks
{
    class OnOff :
        public UIBase
    {

    public:

        OnOff();
        ~OnOff();


        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;


        bool GetOnOffCheak() { return m_bOnOffCheak; }
        void SetOnOffCheak(bool cheak) { m_bOnOffCheak = cheak; }
        void SetOnOffOneCheak(bool cheak) { m_bOnOffOneCheak = cheak; }


    private:



    private:

        Transform* mTransform;
      

        Vec3            mUiPos;
        Vec3            m_vUiFinalPos;


        bool            m_bOnOffCheak;
        bool            m_bOnOffOneCheak;



    };
}
