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
		WireframeNone,		//���� �׷����� (Mesh ���·� �׷����ٰ� �����)
		End,
	};

	enum class eDSType
	{
		Less,				//���� ������ �׷�����. 1 > 2;
		Greater,			//���� ũ��(�ڿ� ������) �׷�����. 1 < 2;
		NoWrite,			//���� �� ��� X ���̾� ������� API �� ��� �ϴ� ���
		None,
		End,
	};

	enum class eBSType
	{
		Default,			// Blend �ɼ� X
		AlphaBlend,			// Blend �ɼ� O
		OneOne,				// ���� ȥ��?( ������ ���ؼ� ���)
		End,
	};

	enum class eRenderingMode
	{
		Opaque,				//������
		CutOut,				//����
		Transparent,		//����
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