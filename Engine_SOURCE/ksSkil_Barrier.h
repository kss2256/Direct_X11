#pragma once
#include "ksCSkil.h"

namespace ks
{
	class SkilScript;
	class Skil_Barrier
		: public CSkil
	{
	public:

		Skil_Barrier();
		~Skil_Barrier();
		
		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;


		bool IsBarrier() { return m_bBarrier; }


	private:
		void loadAnimation();

		void loadSound();


	private:


		SkilScript*			m_pSkilScript;
		bool				m_bBarrierScale;
		bool				m_bBarrierEnd;
		bool				m_bBarrier;

	};
}
