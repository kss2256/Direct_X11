#pragma once
#include "ksMonster.h"

namespace ks
{
    class Collider2D;
    class Animator;
    class Diary :
        public Monster
    {

	public:

        Diary();
        virtual ~Diary();

        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;
      
        void SetCheak(bool cheak) { mCheak = cheak; }

    private:
        void loadanimation();


    private:

        Animator*       mAnimator;
        Collider2D*     mCollider;



        eStep           mDiaryStep;
        float           mTime;
        bool     mCheak;


    };
}
