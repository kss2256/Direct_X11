#pragma once
#include "ksGameObject.h"
#include "ksPlayer.h"
#include "ksAnimation.h"
#include "ksAnimator.h"
#include "ksSpriteRenderer.h"
#include "ksMaterial.h"
#include "ksMesh.h"
#include "ksResources.h"
#include "ksTransform.h"
#include "ksObject.h"
#include "ksTime.h"
#include "ksInput.h"




namespace ks
{
    class Transform;
    class CSkil :
        public GameObject
    {
    public:

        CSkil();
        virtual ~CSkil();


        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        Player* GetTarget() { return mTarget; }    

        void SetTarget(Player* player) { mTarget = player; }
     


    protected:
     
        void CreateAnimation(const std::wstring& name, std::shared_ptr<Texture> texture, Animator* animaotr
            , Vec2 scale, Vector2 offset, std::vector<UINT> numbers, float duration);


    protected:

        Transform*                  mTransform;
        Animator*                   mAnimator;
        Player*                     mTarget;
     

        float                       m_fTime;


        std::vector<Sprite>		    mSprites;
        std::vector<Sprite>		    mSvaeSprite;

        std::vector<UINT>			mNumbers;  

        bool                        m_bSkilStart;


    };
}
