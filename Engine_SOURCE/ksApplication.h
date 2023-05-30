#pragma once
#include "ksEngine.h"
#include "ksGraphics.h"
#include "ksGraphicDevice_DX11.h"

namespace ks
{
	class Application
	{
	public:
		Application();
		~Application();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
		virtual void Destroy();

		// Running main engine loop
		void Run();
		void Present();
		void Release();


		void SetWindow(HWND hwnd, UINT width, UINT height);
		void SetHwnd(HWND hwnd) { mHwnd = hwnd; }
		HWND GetHwnd() { return mHwnd; }
		HDC GetWindowDC() { return mHdc; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

	private:
		bool initialized = false;
		std::unique_ptr<graphics::GraphicDevice_DX11> graphicDevice;

		HWND mHwnd;
		HDC mHdc;
		UINT mHeight;
		UINT mWidth;
	};
}
