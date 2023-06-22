#pragma once
#include "ksUIBase.h"
#include "ksTitleScene.h"
#include <stdlib.h>

namespace ks
{
    class TitleUi :
        public UIBase
    {

    public:
        TitleUi();
        ~TitleUi();

        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        
        void SetTarget(TitleScene* title) { mTitle = title; }

    private:

        void loadSound();
        void selectMouseOnSound();


    private:

        Transform*      mTransform;    

        Vec3            m_vMousePos;
        Vec3            m_vUiScale;


        bool            m_bSoundUpdate;
        bool            m_bOneCheak1;
        bool            m_bOneCheak2;
        bool            m_bOneCheak3;
        bool            m_bOneCheak4;
        bool            m_bOneCheak5;
     
        TitleScene*         mTitle;


    };
}
