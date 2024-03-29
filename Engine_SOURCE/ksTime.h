#pragma once
#include "ksEngine.h"

namespace ks
{
	class Time
	{
	public:
		static __forceinline float DeltaTime() { return mDeltaTime; }

		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

	private:
		static LARGE_INTEGER	mCpuFrequency;
		static LARGE_INTEGER   mPrevFrequency;
		static LARGE_INTEGER	mCurFrequency;

		static float			mDeltaTime;
		static float			mOneSecond;
	};
}


