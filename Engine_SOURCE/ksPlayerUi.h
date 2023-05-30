#pragma once
#include "ksUIBase.h"


namespace ks
{
	class Transform;
	class PlayerUi :
		public UIBase
	{
	public:

		PlayerUi();
		virtual ~PlayerUi();


		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;



	private:

		Transform* mTransform;

	};


}
