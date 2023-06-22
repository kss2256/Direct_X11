#pragma once
#include "ksGameObject.h"
#include "ksTexture.h"
#include "ksMonster.h"


typedef void(ks::Monster::*SetMonster)(void);

enum class Stage_Step
{

    None,
    Stet_1,
    Stet_2,
    Stet_3,
    Stet_4,
    Stet_5,
    Stet_6,
    End,
};


namespace ks
{



    class BossTpMeter;
    class BossLayout;
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
        static void SetSoundCheak(bool sound) { m_bSoundCheak = sound; }
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

        static void stage_1Sound();
        static void stage_1SoundStop();
        static void flime_BattleSound();
        static void flime_BattleSoundStop();
        static void ent_BattleSound();
        static void ent_BattleSoundStop();

    private:
        template<typename T>
        void createGround(const std::wstring& name, std::shared_ptr<T> texture);
        void createDiary();
        void createSkilBook(Vec3 pos);

        void range_In(Vector4 pos);
        void range_Out(Vector4 pos);

        void flime_Start();
        void ent_Start();

        void loadSound();
        void ent_StartSound1();
        void ent_StartSound2();
        void ent_StartSound3();




    private:


        static UINT         mKeyCount;
        static bool         mKey;
        static bool         mKeyCheak;
        static bool         m_bSoundCheak;
        static bool         m_bOneSound;
        static GameObject*  mTarget;
        std::wstring        mName;
        eGroundStage        mGroundStage;
        Collider2D*         mCollider;
        float               mFlimeTime;
        float               mEntTime;
        float               m_fTime;

        static Stage_Step                mStep;

        Vec3                mPrevPos;
       static Vec3                mMoveCam;
       static Vec3                mEndCam;

        Monster*            test;
        SetMonster          TEST;

        Boss_Ent*           mEnt;
        Boss_Flime*         mFlime;
        Forest_Fairy*       mFairy;
        Slime_Green*        mSlime;
        Slime_Green*        mSlime_Two;
        Snake_Green*        mSnake;
        Snake_Green*        mSnake_Two;
        BossLayout*         mBossLayout;
        BossTpMeter*        mBossMeter;
       

    };
}
