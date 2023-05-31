#pragma once
#include "CommonInclude.h"
#include "ksMath.h"
#include "ksGraphicDevice_DX11.h"

#include "ksMesh.h"
#include "ksShader.h"
#include "ksConstantBuffer.h"
#include "ksCamera.h"
#include "ksLight.h"

using namespace ks::math;
using namespace ks::graphics;

namespace ks::renderer
{
	struct Vertex
	{
		Vector4 pos;
		Vector4 color;
		Vector2 uv;
	};

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Matrix world;
		Matrix view;
		Matrix projection;
	};

	CBUFFER(MaterialCB, CBSLOT_MATERIAL)
	{
		int iData;
		float fData;
		Vector2 xy;
		Vector3 xyz;
		Vector4 xyzw;
		Matrix matrix;
	};

	CBUFFER(GridCB, CBSLOT_GRID)
	{
		Vector4 cameraPosition;
		Vector2 cameraScale;
		Vector2 resolution;
	};

	CBUFFER(AnimationCB, CBSLOT_ANIMATION)
	{
		Vector2 leftTop;
		Vector2 size;
		Vector2 offset;
		Vector2 atlasSize;

		UINT type;
	};

	CBUFFER(Fade, CBSLOT_FADEEFFECT)
	{
		float	time;
		float	StartTime;
		float	EndTime;
		float	dumi;
	};

	CBUFFER(Trap, CBSLOT_FADEEFFECT)
	{
		float		linecolor;
		float		alpha;
		Vector2		linesize;
	};

	CBUFFER(Meter, CBSLOT_FADEEFFECT)
	{
		float		metertime;
		float		meterendtime;
		Vector2		metersize;
	};


	extern Vertex vertexes[4];
	extern Vertex fadeeffect[4];
	extern Camera* mainCamera;
	extern ConstantBuffer* constantBuffers[];
	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthstencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];

	extern std::vector<Camera*> cameras[];
	extern std::vector<DebugMesh> debugMeshes;
	extern std::vector<LightAttribute> lights;

	void Initialize();
	void Render();
	void Release();

	void InitInputLayout(const std::wstring& name);
	void CreateShader(const std::wstring& name);
	void CreateShadowShader(const std::wstring& name);
	void CreateMaterial(const std::wstring& name);

	//Renderer


}

