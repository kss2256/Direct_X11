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


		


	private:
		void loadAnimation();

		void loadSound();


	private:


		SkilScript*			 m_pSkilScript;		


    };
}
