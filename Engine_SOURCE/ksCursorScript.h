#pragma once
#include "ksScript.h"

namespace ks
{

	class CursorScript
		: public Script
	{

	public:
		CursorScript();
		~CursorScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;


	public:



	private:

		Vector2 mMousePos;


	};
}
