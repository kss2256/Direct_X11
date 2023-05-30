#pragma once
#include "ksGameObject.h"

namespace ks
{
	class Mouse
		: public GameObject
	{
	public:

		Mouse();
		virtual ~Mouse();


		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;




	private:

	};
}
