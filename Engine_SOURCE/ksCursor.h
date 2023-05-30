#pragma once
#include "ksScript.h"

namespace ks
{
	class Input;
	class Transform;
	class Cursor
		: public Script
	{

	public:

		Cursor();
		virtual ~Cursor();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		static Vector3 GetCursorPos() { return mMousePos; }
		static GameObject* GetTarget() { return mTarget; }


		static void SetCursorPos(Vector3 pos) { mMousePos = pos; }
		static void SetTarget(GameObject* target) { mTarget = target; }

	private:

		static Vector3		mMousePos;
		static Transform* mTransform;
		static GameObject* mTarget;

	};
}
