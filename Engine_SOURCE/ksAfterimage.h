#pragma once
#include "ksGameObject.h"
#include "ksPlayer.h"
#include "ksAnimation.h"
#include "ksTexture.h"

namespace ks
{
    
    enum class progress
    {
        Start,
        Step_1,
        Step_2,
        Step_3,
        Step_4,
        Step_5,
        End,
    };


    class Animator;
    class Transform;
    class Afterimage :
        public GameObject
    {

    public:
        Afterimage();
       virtual ~Afterimage();

        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        void PlayAfterimage(Sprite sprite, Vec3 pos);



        GameObject* GetTarget() { return mPlayer; }

        void SetTarget(GameObject* target) { mPlayer = (Player*)target; }


    private:

        Transform*                  mTransform;
        Animator*                   mAnimator;
        Player*                     mPlayer;
        std::vector<Sprite>         mSprite;        
        std::shared_ptr<Texture>    mTexture;

        progress                    mprogress;
        Sprite                      msprite;

        static float                mTime;
        static float                mDelayTime;

    };
}
