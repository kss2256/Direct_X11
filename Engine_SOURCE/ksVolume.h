#pragma once
#include "ksUIBase.h"

enum class e_Volume
{
    Volume_100,
    Volume_0,
    Volume_20,
    Volume_40,
    Volume_60,
    Volume_80,
};


namespace ks
{
    class Volume :
        public UIBase
    {
    public:
        Volume();
        ~Volume();

        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        e_Volume GetVolume() { return m_eVolume; }

        void SetVolume(e_Volume volume) { m_eVolume = volume; }
        void SetChangeVolume(bool change) { m_bChangeVolume = change; }

    private:

        Transform*      mTransform;


        Vec3            mUiPos;
        Vec3            m_vUiFinalPos;

        e_Volume        m_eVolume;
        bool            m_bChangeVolume;

    };
}
