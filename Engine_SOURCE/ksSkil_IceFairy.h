#pragma once
#include "ksCSkil.h"


namespace ks
{
    class Skil_IceFairy :
        public CSkil
    {
    public:

        Skil_IceFairy();
        virtual ~Skil_IceFairy();

        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;
        


    private:
       void loadAnimation();


    private:




    };
}
