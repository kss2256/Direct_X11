#pragma once
#include "ksGameObject.h"


namespace ks
{
	class DebugObject : public GameObject
	{
	public:
		DebugObject();
		virtual ~DebugObject();

		virtual void FixedUpdate() override;
	
	private:
	};
}
