#pragma once
#include "ksCSkil.h"

namespace ks
{
	class SkilScript;
    class Skil_Lighting :
        public CSkil
    {
	public:

		Skil_Lighting();
		~Skil_Lighting();
	
		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;


		void SetLightionRight(bool right) { m_bRight = right; }
		void SetLightionLeft(bool left) { m_bLeft = left; }


	private:
		void loadAnimation();

		void loadSound();
		void lightionStartSound();


	private:


		SkilScript*			 m_pSkilScript;		

		bool				m_bRight;
		bool				m_bLeft;


    };
}
