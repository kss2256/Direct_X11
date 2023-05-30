#pragma once
#include "ksScript.h"
#include "ksCamera.h"

namespace ks
{
	class GridScript : public Script
	{
	public:
		GridScript();
		virtual ~GridScript();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void SetCamera(Camera* camera) { mCamera = camera; }

	private:
		Camera* mCamera;
	};
}
