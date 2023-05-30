#pragma once
#include <wrl.h>
#include "ksMath.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")


#define CB_GETBINDSLOT(name) __CBUFFERBINDSLOT__##name##__
#define CBUFFER(name, slot) static const int CB_GETBINDSLOT(name) = slot; struct alignas(16) name

#define CBSLOT_TRANSFORM 0
#define CBSLOT_MATERIAL 1
#define CBSLOT_GRID 2
#define CBSLOT_ANIMATION 3
#define CBSLOT_FADEEFFECT 4


using namespace ks::math;
namespace ks::graphics
{
	enum class eValidationMode
	{
		Disabled,
		Enabled,
		GPU,
	};

	enum class eShaderStage
	{
		VS,
		HS,
		DS,
		GS,
		PS,
		CS,
		Count,
	};

	enum class eSamplerType
	{
		Point,
		Linear,
		Anisotropic,
		End,
	};

	enum class eRSType
	{
		SolidBack,			//default (curling Back)
		SolidFront,
		SolidNone,			//curling Of
		WireframeNone,		//선만 그려지는 (Mesh 상태로 그려진다고 보면됨)
		End,
	};

	enum class eDSType
	{
		Less,				//값이 작으면 그려진다. 1 > 2;
		Greater,			//값이 크면(뒤에 있으면) 그려진다. 1 < 2;
		NoWrite,			//깊이 값 사용 X 레이어 순서대로 API 때 사용 하던 방법
		None,
		End,
	};

	enum class eBSType
	{
		Default,			// Blend 옵션 X
		AlphaBlend,			// Blend 옵션 O
		OneOne,				// 색상 혼합?( 색상을 더해서 사용)
		End,
	};

	enum class eRenderingMode
	{
		Opaque,				//불투명
		CutOut,				//차단
		Transparent,		//투명
		End,
	};


	struct GpuBuffer
	{
		enum class eType
		{
			Buffer,
			Texture,
			UnknownType,
		} type = eType::UnknownType;

		D3D11_BUFFER_DESC desc;
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;

		GpuBuffer() = default;
		virtual ~GpuBuffer() = default;
	};

	enum class eCBType
	{
		Transform,
		Material,
		Grid,
		Animation,
		Fade_Effect,
		Trap_Line,
		End,
	};

	enum class eGPUParam
	{
		Int,
		Float,
		Vector2,
		Vector3,
		Vector4,
		Matrix,
	};

	enum class eSRVType
	{
		None,
		End,
	};

	struct DebugMesh
	{
		enums::eColliderType type;
		math::Vector3 position;
		math::Vector3 rotatation;
		math::Vector3 scale;

		float radius;
		float duration;
		float time;
	};

	struct LightAttribute
	{
		Vector4 diffuse;
		Vector4 specular;
		Vector4 ambient;
		Vector4 emissive;
		Vector4 position;
		Vector4 direction;

		enums::eLightType type;
		float radius;
		float angle;
		int padding;
	};
}