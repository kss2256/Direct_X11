#pragma once
#include "ksComponent.h"

using namespace ks::math;
namespace ks
{
	class Transform : public Component
	{
	public:
		Transform();
		virtual ~Transform();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void SetConstantBuffer();

		void SetParent(Transform* parent) { mParent = parent; }
		Transform* GetParent() { return mParent; }

		Vector3 GetPosition() { return mPosition; };
		Vector3 GetmViewPos() { return mViewPos; };
		Vector3 GetRotation() { return mRotation; };
		Vector3 GetScale() { return mScale; };
		Vector3 GetDirection() { return mDirection; }
		float GetAngle() { return mAngle; }


		void SetPosition(Vector3 position) { mPosition = position; };
		void SetRotation(Vector3 rotation) { mRotation = rotation; };
		void SetScale(Vector3 scale) { mScale = scale; };
		void SetDirection(Vector3 dir) { mDirection = dir; }
		void SetAngle(float angle) { mAngle = angle; }



		Vector3 Foward() { return mFoward; }
		Vector3 Right() { return mRight; }
		Vector3 Up() { return mUp; }

		Matrix& GetWorldMatrix() { return mWorld; }

	private:
		Transform* mParent;
		Vector3 mFoward;
		Vector3 mRight;
		Vector3 mUp;
		Vector3 mPosition;
		Vector3 mViewPos;
		Vector3 mRotation;
		Vector3 mScale;
		Vector3 mDirection;
		Matrix	mWorld;
		float	mAngle;


	};
}
