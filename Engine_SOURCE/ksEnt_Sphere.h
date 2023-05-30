#pragma once
#include "ksMonster.h"

namespace ks
{

	enum class Sphere_Type
	{
		Direction_3,
		Direction_8,	
	};

	enum class Step
	{
		Step_1,
		Step_2,
		Step_3,


	};


	class Ent_Sphere
		: public Monster
	{
	public:
		Ent_Sphere();
		~Ent_Sphere();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	public:

		GameObject* GetTarget() { return mPlayer; }
		float GetSpeed() { return mSpeed; }
		float GetDegree() { return mDegree; }
		Sphere_Type GetSphereType() { return mSphereType; }


		void SetTarget(GameObject* target) { mPlayer = (Player*)target; }
		void SetSpeed(float speed) { mSpeed = speed; }
		void SetDegree(float degree) { mDegree = degree; }
		void SetSphereType(Sphere_Type type) { mSphereType = type; }
		

	private:

		void loadAnimation();

	private:

		float           mSpeed;
		float           mDegree;
		Sphere_Type		mSphereType;
		Step			mSphereStep;

		float			mCooldownTime;


	};
}
