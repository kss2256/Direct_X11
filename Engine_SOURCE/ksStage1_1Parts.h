#pragma once
#include "ksGameObject.h"
#include "ksTexture.h"

namespace ks
{
    class Stage1_1Parts :
        public GameObject
    {

    public:
        Stage1_1Parts();
        virtual ~Stage1_1Parts();

        virtual void Initalize();
        virtual void Update();
        virtual void FixedUpdate();
        virtual void Render();


        static GameObject* GetTarget() { return mTarget; }
        std::wstring GetTextureName() { return mName; }
        eGroundStage GetGroundStage() { return mGroundStage; }

        static void SetTarget(GameObject* target) { mTarget = target; }
        void SetTextureName(std::wstring name) { mName = name; }
        void SetGroundStage(eGroundStage stage) { mGroundStage = stage; }


    private:
        template <typename T>
        void createGround(const std::wstring& name, std::shared_ptr<T> texture);


    private:

        static GameObject*      mTarget;
        std::wstring            mName;
        eGroundStage            mGroundStage;


    };
}
