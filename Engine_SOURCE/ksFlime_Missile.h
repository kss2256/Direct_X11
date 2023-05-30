#pragma once
#include "ksGameObject.h"


namespace ks
{

    enum class Flime_Step
    {
        None,
        Step_1,
        Step_2,
        Step_3,
        Step_4,
        Step_5,
        Step_6,
        Step_7,
        Step_8,
        Step_9,
        End,
    };

    class Transform;
    class Flime_Missile :
        public GameObject
    {
    public:

        Flime_Missile();
        virtual ~Flime_Missile();

        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        void Lineinterval(float interval);



        float GetDegree() { return mDegree; }
        Flime_Step GetStep() { return mStep; }
        bool GetMissile() { return mMissile; }

        void SetDegree(float degree) { mDegree = degree; }
        void SetStep(Flime_Step step) { mStep = step; }
        void SetMissile(bool missile) { mMissile = missile; }

    private:


        Transform*          mTransform;
        Vec3                mScale;
        float               mDegree;
        float               mSpeed;
        float               mTime;
        Flime_Step          mStep;
        bool                mMissile;

    };
}
