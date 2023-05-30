#pragma once
#include "ksMonster.h"

namespace ks
{
    class Boss_Flime :
        public Monster
    {

    public:


        Boss_Flime();
        ~Boss_Flime();



        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

    private:
        void loadAnimation();
        void multipleAttack(float dir, UINT count);
        void directionTrap(UINT count, float interval, bool missil);
        void TrapAttack(UINT count, float interval, bool missil);



    private:


        UINT        mTrapCount;
        float       mInterval;
        int         mMaxTrapCount;


    };
}
