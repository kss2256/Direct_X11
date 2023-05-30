#pragma once
#include "ksScript.h"


namespace ks
{
	class CameraScript : public Script
	{
	public:
		CameraScript();
		~CameraScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

	private:

	};
}
