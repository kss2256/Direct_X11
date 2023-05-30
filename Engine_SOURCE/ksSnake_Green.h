#pragma once
#include "ksMonster.h"


namespace ks
{
	class Snake_Green :
		public Monster
	{
	public:
		Snake_Green();
		virtual ~Snake_Green();


		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void resurrection();

	private:

		void loadAnimation();
		void doubleAttack();
		void tripleAttack();



	private:




	};
}
