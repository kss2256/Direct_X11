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
        void tripleAttack();
        void multipleAttack();

    private:

     


    };
}
