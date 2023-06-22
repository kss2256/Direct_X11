#pragma once
#include "ksUIBase.h"

namespace ks
{
    class Player;
    class OptionCheak :
        public UIBase
    {

    public:

        OptionCheak();
        ~OptionCheak();


        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        Player* GetTarget() { return mTarget; }        

        void SetTarget(Player* player) { mTarget = player; }
     
        static void SetOptionCheakOnOff(bool cheak) { m_bOptionCheakOnOff = cheak; }
        void SetOptionCheakUiPos(Vec3 pos)  { m_vUiFinalPos = pos; }

        void SetOptionCheak1(bool cheak) { m_bOneCheak1 = cheak; }
        void SetOptionCheak2(bool cheak) { m_bOneCheak2 = cheak; }
        void SetOptionCheak3(bool cheak) { m_bOneCheak3 = cheak; }
        void SetOptionCheak4(bool cheak) { m_bOneCheak4 = cheak; }
        void SetOptionCheak5(bool cheak) { m_bOneCheak5 = cheak; }

    private:

        void loadSound();
        void optionSound();



    private:

        Transform*      mTransform;
        Player*         mTarget;

        Vec3            mUiPos;
        Vec3            m_vUiFinalPos;
     

        static bool     m_bOptionCheakOnOff;

        bool            m_bOneCheak1;
        bool            m_bOneCheak2;
        bool            m_bOneCheak3;
        bool            m_bOneCheak4;
        bool            m_bOneCheak5;

        


    };
}
