#include "ksGridScript.h"
#include "ksTransform.h"
#include "ksGameObject.h"
#include "ksApplication.h"
#include "ksConstantBuffer.h"
#include "ksRenderer.h"
#include "ksSceneManager.h"

extern ks::Application application;

namespace ks
{
	GridScript::GridScript()
		: Script()
		, mCamera(nullptr)
	{

	}

	GridScript::~GridScript()
	{

	}

	void GridScript::Initalize()
	{
		eSceneType type = SceneManager::GetActiveScene()->GetSceneType();
		mCamera = renderer::cameras[(UINT)type][0];
	}

	void GridScript::Update()
	{
		//	CBUFFER(GridCB, CBSLOT_GRID)
		//{
		//	Vector4 cameraPosition;
		//	Vector2 cameraScale;
		//	Vector2 resolution;
		//};

		if (mCamera == nullptr)
			return;


		

		GameObject* gameObj = mCamera->GetOwner();
		Transform* tr = gameObj->GetComponent<Transform>();

		Vector3 cameraPos = tr->GetPosition();
		Vector4 position = Vector4(cameraPos.x, cameraPos.y, cameraPos.z, 1.0f);

		float scale = mCamera->GetScale();

		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);
		float width = float(winRect.right - winRect.left);
		float height = float(winRect.bottom - winRect.top);
		Vector2 resolution(width, height);

		// Constant buffer
		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Grid];
		renderer::GridCB data;
		data.cameraPosition = position;
		data.cameraScale = Vector2(scale, scale);
		data.resolution = resolution;

		cb->Bind(&data);
		cb->SetPipline(eShaderStage::VS);
		cb->SetPipline(eShaderStage::PS);
	}

	void GridScript::FixedUpdate()
	{
	}

	void GridScript::Render()
	{
	}

}
