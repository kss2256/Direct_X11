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
		void loadSound();
		void soundDeath();
		void soundAttack1();
		void soundAttack2();
		void skillBookSound();

		

	private:

		bool        m_bSoundDeathCheak;
		bool        m_bSkillCheak;


	};
}
