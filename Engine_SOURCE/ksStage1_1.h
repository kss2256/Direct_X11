#pragma once
#include "ksGameObject.h"
#include "ksTexture.h"
#include "ksMonster.h"


typedef void(ks::Monster::*SetMonster)(void);




namespace ks
{
    class Slime_Green;
    class Snake_Green;
    class Forest_Fairy;
    class Boss_Ent;
    class Boss_Flime;
    class Collider2D;
    class Stage1_1 :
        public GameObject
    {

    public:
        Stage1_1();
        virtual ~Stage1_1();

        virtual void Initalize();
        virtual void Update();
        virtual void FixedUpdate();
        virtual void Render();


        static GameObject* GetTarget() { return mTarget; }
        static UINT GetKeyCount() { return mKeyCount; }
        std::wstring GetTextureName() { return mName; }
        eGroundStage GetGroundStage() { return mGroundStage; }

        static void SetTarget(GameObject* target) { mTarget = target; }
        static void SetKey(bool key) { mKey = key; }
        static void SetKeyCheak(bool key) { mKeyCheak = key; }
        static void KeyCount_Up() 
        {
            ++mKeyCount;
        }
        void SetTextureName(std::wstring name) { mName = name; }
        void SetGroundStage(eGroundStage stage) { mGroundStage = stage; }
       
        void SetDelegate(Monster* _pInst, SetMonster _Func)
        {
            test = _pInst;
            TEST = _Func;
        }

        void SetEnt(Boss_Ent* ent) { mEnt = ent; }
		void SetFlime(Boss_Flime* flime) { mFlime = flime; }
        void SetFairy(Forest_Fairy* fairy) {mFairy = fairy; }
        void SetSlime(Slime_Green* flime) { mSlime = flime; }
        void SetSlime_Two(Slime_Green* flime) { mSlime_Two = flime; }
        void SetSnake(Snake_Green* snake) { mSnake = snake; }
        void SetSnake_Two(Snake_Green* snake) { mSnake_Two = snake; }



    private:
        template<typename T>
        void createGround(const std::wstring& name, std::shared_ptr<T> texture);
        void createDiary();
       
        void range_In(Vector4 pos);
        void range_Out(Vector4 pos);

    private:


        static UINT         mKeyCount;
        static bool         mKey;
        static bool         mKeyCheak;
        static GameObject*  mTarget;
        std::wstring        mName;
        eGroundStage        mGroundStage;
        Collider2D*         mCollider;

        Vec3                mPrevPos;

        Monster*            test;
        SetMonster          TEST;

        Boss_Ent*           mEnt;
        Boss_Flime*         mFlime;
        Forest_Fairy*       mFairy;
        Slime_Green*        mSlime;
        Slime_Green*        mSlime_Two;
        Snake_Green*        mSnake;
        Snake_Green*        mSnake_Two;

       

    };
}
