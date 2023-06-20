#include "ksApplication.h"
#include "ksRenderer.h"
#include "ksTime.h"
#include "ksInput.h"
#include "ksSceneManager.h"
#include "ksResources.h"
#include "ksCollisionManager.h"
#include "ksUiMgr.h"
#include "ksFmod.h"
#include "ksFontWrapper.h"


namespace ks
{
	using namespace graphics;

	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Initalize()
	{
		Time::Initialize();
		Input::Initialize();
		CollisionManager::Initialize();
		renderer::Initialize();
		SceneManager::Initalize();
		Fmod::Initialize();
		FontWrapper::Initialize();

	}

	// ���� ���� ĳ���� �̵� ��� 
	// CPU UPDATE
	void Application::Update()
	{
		Time::Update();
		Input::Update();
		UiMgr::Update();
		CollisionManager::Update();
		SceneManager::Update();
	}

	// GPU update
	void Application::FixedUpdate()
	{
		CollisionManager::FixedUpdate();
		SceneManager::FixedUpdate();
	}

	void Application::Render()
	{
	

		graphicDevice->Clear();
		graphicDevice->AdjustViewPorts();

		//SceneManager::Render();
		Time::Render(mHdc);
		renderer::Render();
		CollisionManager::Render();
		//graphicDevice->Render();
		//graphicDevice->Present();


	}

	void Application::Destroy()
	{
		SceneManager::Destroy();
	}

	// Running main engine loop
	void Application::Run()
	{
		Update();
		FixedUpdate();
		Render();
		Destroy();
	}

	void Application::Present()
	{
		graphicDevice->Present();
	}

	void Application::Release()
	{
		Resources::deleteTest();
		Fmod::Release();
		FontWrapper::Release();
	}

	void Application::SetWindow(HWND hwnd, UINT width, UINT height)
	{
		if (graphicDevice == nullptr)
		{
			mHwnd = hwnd;
			mHdc = GetDC(mHwnd);
			mWidth = width;
			mHeight = height;


			eValidationMode vaildationMode = eValidationMode::Disabled;
			graphicDevice = std::make_unique<GraphicDevice_DX11>();
			graphics::GetDevice() = graphicDevice.get();
		}

		RECT rt = { 0, 0, (LONG)width , (LONG)height };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(mHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
		ShowWindow(mHwnd, true);
		UpdateWindow(mHwnd);
	}

}
