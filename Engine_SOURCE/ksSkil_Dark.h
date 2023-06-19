#pragma once
#include "ksCSkil.h"

namespace ks
{
    class SkilScript;
    class Skil_Dark :
        public CSkil
    {
    public:
        Skil_Dark();
        ~Skil_Dark();



        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

		bool IsVoidAttack() { return m_bVoidAttack; }

    private:
        void loadAnimation();
        void loadSound();

        void darkStartSound();
        void darkVoidSound();
        void darkAttackSound();
        void darkEndSound();


    private:


        SkilScript* m_pSkilScript;

        bool        m_bVoidCheak;
        bool        m_bVoidEnd;
        bool        m_bVoidDeath;
        bool        m_bSoundCheak;

        bool        m_bVoidAttack;

    };
}
