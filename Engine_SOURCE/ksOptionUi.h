#pragma once
#include "ksUIBase.h"
#include "ksPlayer.h"
#include "ksVolume.h"



namespace ks
{
    class Volume;
    class OnOff;
    class OptionCheak;
    class OptionUi :
        public UIBase
    {
    public:

        OptionUi();
        ~OptionUi();

  

        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        Player* GetTarget() { return mTarget; }
        static bool    GetOption() { return m_bOptionOnOff; }

        void SetTarget(Player* player) { mTarget = player; }
        static void SetOption(bool option) { m_bOptionOnOff = option; }

  

    private:

        void loadSound();
        void optionSelectSound();

        void optionCheakCreate();
        void onOffCreate();
        void volumeCreate();
        void soundVolume(float volume);

    private:

        Transform*      mTransform;
        Player*         mTarget;
        OptionCheak*    mOptionCheak;
        OnOff*          mOnOff;
        Volume*         mVolume;
        Vec3            m_vMousePos;
        Vec3            m_vUiScale;
        Vec3            mUiPos;
        Vec3            mUiPrevPos;
        Vec3            mUiPrevMousePos;


        static bool     m_bOptionOnOff;
        bool            m_bOptionCheak;
        bool            m_bOptionDrag;



    };
}
