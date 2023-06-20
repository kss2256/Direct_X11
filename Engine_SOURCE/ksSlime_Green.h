#pragma once
#include "ksMonster.h"

namespace ks
{
    class Slime_Green :
        public Monster
    {
    public:
        Slime_Green();
        virtual ~Slime_Green();


        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        void resurrection();


    private:

        void loadAnimation();
        void loadSound();
        void tripleAttack();
        void multipleAttack();

        void soundDeath();
        void soundtripleAttack();
        void soundMultipleJump();
        void soundMultipleAttack();
        void skillBookSound();

        void DarkSkil();
        void BarrierSkil();

    private:

        bool        m_bSoundCheak;
        bool        m_bSoundOneCheak;
        bool        m_bSoundDeathCheak;
        bool        m_bDarkSkillCheak;
        bool        m_bBarrierSkillCheak;


    };
}
