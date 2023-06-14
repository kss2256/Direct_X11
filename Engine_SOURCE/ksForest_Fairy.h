#pragma once
#include "ksMonster.h"


namespace ks
{
    class Forest_Fairy :
        public Monster
    {

    public:
        Forest_Fairy();
        ~Forest_Fairy();

        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        void resurrection();


    private:

        void loadAnimation();
        void multipleAttack(std::vector<UINT> missileCounts, std::vector<float> missileAngle);
        void loadSound();
        void soundDeath();
        void soundAttack();



    private:


        bool        m_bSoundDeathCheak;

    };
}
