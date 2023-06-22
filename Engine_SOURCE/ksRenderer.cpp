#include "ksRenderer.h"
#include "ksResources.h"
#include "ksMaterial.h"
#include "ksSceneManager.h"


namespace ks::renderer
{
	Vertex vertexes[4] = {};
	Vertex fadeeffect[4] = {};
	ConstantBuffer* constantBuffers[(UINT)eCBType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[(UINT)eSamplerType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthstencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};

	Camera* mainCamera = nullptr;
	std::vector<Camera*> cameras[(UINT)eSceneType::End];
	std::vector<DebugMesh> debugMeshes;
	std::vector<LightAttribute> lights;

	void LoadMesh()
	{
		//RECT
		vertexes[0].pos = Vector4(-0.5f, 0.5f, 0.0f, 1.0f);
		vertexes[0].color = Vector4(0.f, 1.f, 0.f, 1.f);
		vertexes[0].uv = Vector2(0.f, 0.f);

		vertexes[1].pos = Vector4(0.5f, 0.5f, 0.0f, 1.0f);
		vertexes[1].color = Vector4(1.f, 1.f, 1.f, 1.f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector4(0.5f, -0.5f, 0.0f, 1.0f);
		vertexes[2].color = Vector4(1.f, 0.f, 0.f, 1.f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector4(-0.5f, -0.5f, 0.0f, 1.0f);
		vertexes[3].color = Vector4(0.f, 0.f, 1.f, 1.f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		// Crate Mesh
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"RectMesh", mesh);
		mesh->CreateVertexBuffer(vertexes, 4);

		std::vector<UINT> indexes;
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);
		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);
		indexes.push_back(0);
		mesh->CreateIndexBuffer(indexes.data(), (UINT)indexes.size());

		// 
		vertexes[0].pos = Vector4(-0.5f, 0.5f, -0.00001f, 1.0f);
		vertexes[0].color = Vector4(0.f, 1.f, 0.f, 1.f);
		vertexes[0].uv = Vector2(0.f, 0.f);

		vertexes[1].pos = Vector4(0.5f, 0.5f, -0.00001f, 1.0f);
		vertexes[1].color = Vector4(1.f, 1.f, 1.f, 1.f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector4(0.5f, -0.5f, -0.00001f, 1.0f);
		vertexes[2].color = Vector4(1.f, 0.f, 0.f, 1.f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector4(-0.5f, -0.5f, -0.00001f, 1.0f);
		vertexes[3].color = Vector4(0.f, 0.f, 1.f, 1.f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		// Crate Mesh
		std::shared_ptr<Mesh> debugmesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"DebugRectMesh", debugmesh);
		debugmesh->CreateVertexBuffer(vertexes, 4);
		debugmesh->CreateIndexBuffer(indexes.data(), (UINT)indexes.size());

		// Circle Mesh
		std::vector<Vertex> circleVtxes;
		Vertex center = {};
		center.pos = Vector4(0.0f, 0.0f, -0.00001f, 1.0f);
		center.color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		center.uv = Vector2::Zero;

		circleVtxes.push_back(center);

		int iSlice = 80;
		float fRadius = 0.5f;
		float fTheta = XM_2PI / (float)iSlice;


		for (size_t i = 0; i < iSlice; i++)
		{
			Vertex vtx = {};
			vtx.pos = Vector4
			(
				fRadius * cosf(fTheta * (float)i)
				, fRadius * sinf(fTheta * (float)i)
				, -0.00001f, 1.0f
			);
			vtx.color = center.color;

			circleVtxes.push_back(vtx);
		}
		indexes.clear();
		for (size_t i = 0; i < iSlice - 2; i++)
		{
			indexes.push_back(i + 1);
		}
		indexes.push_back(1);

		// Crate Mesh
		std::shared_ptr<Mesh> cirlceMesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"CircleMesh", cirlceMesh);
		cirlceMesh->CreateVertexBuffer(circleVtxes.data(), (UINT)circleVtxes.size());
		cirlceMesh->CreateIndexBuffer(indexes.data(), (UINT)indexes.size());

		
		//Fade 
		fadeeffect[0].pos = Vector4(-1.0f, 1.0f, 0.0f, 1.0f);
		fadeeffect[0].color = Vector4(0.f, 0.f, 0.f, 1.f);
		fadeeffect[0].uv = Vector2(0.f, 0.f);
		
		fadeeffect[1].pos = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		fadeeffect[1].color = Vector4(0.f, 0.f, 0.f, 1.f);
		fadeeffect[1].uv = Vector2(1.f, 0.f);
		
		fadeeffect[2].pos = Vector4(1.0f, -1.0f, 0.0f, 1.0f);
		fadeeffect[2].color = Vector4(0.f, 0.f, 0.f, 1.f);
		fadeeffect[2].uv = Vector2(1.f, 1.f);
		
		fadeeffect[3].pos = Vector4(-1.0f, -1.0f, 0.0f, 1.0f);
		fadeeffect[3].color = Vector4(0.f, 0.f, 0.f, 1.f);
		fadeeffect[3].uv = Vector2(0.f, 1.f);
		
		std::shared_ptr<Mesh> fademesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"FedeEffectMesh", fademesh);
		fademesh->CreateVertexBuffer(fadeeffect, 4);
		
	}

	void SetUpState()
	{
		// Input Layout ( 정점 구조 정보 ) 
#pragma region Input layout

//Vertex 구조체 멤버 하나당 배열 하나씩 증가 해서 설명 해주면됨
		D3D11_INPUT_ELEMENT_DESC arrLayoutDesc[3] = {};

		arrLayoutDesc[0].AlignedByteOffset = 0;
		arrLayoutDesc[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayoutDesc[0].InputSlot = 0;
		arrLayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[0].SemanticName = "POSITION";
		arrLayoutDesc[0].SemanticIndex = 0;

		arrLayoutDesc[1].AlignedByteOffset = 16;
		arrLayoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayoutDesc[1].InputSlot = 0;
		arrLayoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[1].SemanticName = "COLOR";
		arrLayoutDesc[1].SemanticIndex = 0;

		arrLayoutDesc[2].AlignedByteOffset = 32;
		arrLayoutDesc[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		arrLayoutDesc[2].InputSlot = 0;
		arrLayoutDesc[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[2].SemanticName = "TEXCOORD";
		arrLayoutDesc[2].SemanticIndex = 0;


		std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"RectShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, shader->GetVSBlobBufferPointer()
			, shader->GetVSBlobBufferSize()
			, shader->GetInputLayoutAddressOf());


		std::shared_ptr<Shader> fadeshader = Resources::Find<Shader>(L"FadeEffectShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, fadeshader->GetVSBlobBufferPointer()
			, fadeshader->GetVSBlobBufferSize()
			, fadeshader->GetInputLayoutAddressOf());


		std::shared_ptr<Shader> TitleShader = Resources::Find<Shader>(L"TitleShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, TitleShader->GetVSBlobBufferPointer()
			, TitleShader->GetVSBlobBufferSize()
			, TitleShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, spriteShader->GetVSBlobBufferPointer()
			, spriteShader->GetVSBlobBufferSize()
			, spriteShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> playerShader = Resources::Find<Shader>(L"PlayerShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, playerShader->GetVSBlobBufferPointer()
			, playerShader->GetVSBlobBufferSize()
			, playerShader->GetInputLayoutAddressOf());


		std::shared_ptr<Shader> afterimageShader = Resources::Find<Shader>(L"AfterimageShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, afterimageShader->GetVSBlobBufferPointer()
			, afterimageShader->GetVSBlobBufferSize()
			, afterimageShader->GetInputLayoutAddressOf());


		std::shared_ptr<Shader> titleuiShader = Resources::Find<Shader>(L"TitleUIShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, titleuiShader->GetVSBlobBufferPointer()
			, titleuiShader->GetVSBlobBufferSize()
			, titleuiShader->GetInputLayoutAddressOf());



		for (size_t i = 1; i < 10; i++)
		{
			InitInputLayout(std::wstring(L"Ground" + std::to_wstring(i)));
			InitInputLayout(std::wstring(L"GroundShadows" + std::to_wstring(i)));
			InitInputLayout(std::wstring(L"GroundParts" + std::to_wstring(i)));
		}

		InitInputLayout(std::wstring(L"Start"));
		InitInputLayout(std::wstring(L"StartShadows"));
		InitInputLayout(std::wstring(L"StartParts"));

		std::shared_ptr<Shader> fogShader = Resources::Find<Shader>(L"FogShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, fogShader->GetVSBlobBufferPointer()
			, fogShader->GetVSBlobBufferSize()
			, fogShader->GetInputLayoutAddressOf());


		std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, uiShader->GetVSBlobBufferPointer()
			, uiShader->GetVSBlobBufferSize()
			, uiShader->GetInputLayoutAddressOf());


		std::shared_ptr<Shader> bossuiShader = Resources::Find<Shader>(L"BossUIShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, bossuiShader->GetVSBlobBufferPointer()
			, bossuiShader->GetVSBlobBufferSize()
			, bossuiShader->GetInputLayoutAddressOf());


		std::shared_ptr<Shader> weaponuiShader = Resources::Find<Shader>(L"WeaponUIShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, weaponuiShader->GetVSBlobBufferPointer()
			, weaponuiShader->GetVSBlobBufferSize()
			, weaponuiShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> slotuiShader = Resources::Find<Shader>(L"SlotUIShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, slotuiShader->GetVSBlobBufferPointer()
			, slotuiShader->GetVSBlobBufferSize()
			, slotuiShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> inventoryuiShader = Resources::Find<Shader>(L"InventoryUIShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, inventoryuiShader->GetVSBlobBufferPointer()
			, inventoryuiShader->GetVSBlobBufferSize()
			, inventoryuiShader->GetInputLayoutAddressOf());


		std::shared_ptr<Shader> inventoryslotuiShader = Resources::Find<Shader>(L"InventorySlotUIShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, inventoryslotuiShader->GetVSBlobBufferPointer()
			, inventoryslotuiShader->GetVSBlobBufferSize()
			, inventoryslotuiShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> inventoryslot_1uiShader = Resources::Find<Shader>(L"InventorySlot_1UIShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, inventoryslot_1uiShader->GetVSBlobBufferPointer()
			, inventoryslot_1uiShader->GetVSBlobBufferSize()
			, inventoryslot_1uiShader->GetInputLayoutAddressOf());


		std::shared_ptr<Shader> bossmeteruiShader = Resources::Find<Shader>(L"BossMeterShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, bossmeteruiShader->GetVSBlobBufferPointer()
			, bossmeteruiShader->GetVSBlobBufferSize()
			, bossmeteruiShader->GetInputLayoutAddressOf());


		std::shared_ptr<Shader> meterShader = Resources::Find<Shader>(L"MeterShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, meterShader->GetVSBlobBufferPointer()
			, meterShader->GetVSBlobBufferSize()
			, meterShader->GetInputLayoutAddressOf());


		std::shared_ptr<Shader> gridShader = Resources::Find<Shader>(L"GridShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, gridShader->GetVSBlobBufferPointer()
			, gridShader->GetVSBlobBufferSize()
			, gridShader->GetInputLayoutAddressOf());


		std::shared_ptr<Shader> debugShader = Resources::Find<Shader>(L"DebugShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, debugShader->GetVSBlobBufferPointer()
			, debugShader->GetVSBlobBufferSize()
			, debugShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> TrapShader = Resources::Find<Shader>(L"TrapShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, TrapShader->GetVSBlobBufferPointer()
			, TrapShader->GetVSBlobBufferSize()
			, TrapShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> flimeShader = Resources::Find<Shader>(L"FlimeShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, flimeShader->GetVSBlobBufferPointer()
			, flimeShader->GetVSBlobBufferSize()
			, flimeShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> fullhpShader = Resources::Find<Shader>(L"FullHpShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, fullhpShader->GetVSBlobBufferPointer()
			, fullhpShader->GetVSBlobBufferSize()
			, fullhpShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> halfhpShader = Resources::Find<Shader>(L"HalfHpShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, halfhpShader->GetVSBlobBufferPointer()
			, halfhpShader->GetVSBlobBufferSize()
			, halfhpShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> fullmpShader = Resources::Find<Shader>(L"FullMpShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, fullmpShader->GetVSBlobBufferPointer()
			, fullmpShader->GetVSBlobBufferSize()
			, fullmpShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> halfmpShader = Resources::Find<Shader>(L"HalfMpShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, halfmpShader->GetVSBlobBufferPointer()
			, halfmpShader->GetVSBlobBufferSize()
			, halfmpShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> coinShader = Resources::Find<Shader>(L"CoinShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, coinShader->GetVSBlobBufferPointer()
			, coinShader->GetVSBlobBufferSize()
			, coinShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> golduiShader = Resources::Find<Shader>(L"GoldUiShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, golduiShader->GetVSBlobBufferPointer()
			, golduiShader->GetVSBlobBufferSize()
			, golduiShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> moneyuiShader = Resources::Find<Shader>(L"MoneyUiShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, moneyuiShader->GetVSBlobBufferPointer()
			, moneyuiShader->GetVSBlobBufferSize()
			, moneyuiShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> skiluiShader = Resources::Find<Shader>(L"SkilUiShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, skiluiShader->GetVSBlobBufferPointer()
			, skiluiShader->GetVSBlobBufferSize()
			, skiluiShader->GetInputLayoutAddressOf());



#pragma endregion
		// Sampler State
#pragma region sampler state
		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		//D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR = 0x5,
		//D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT = 0x10,
		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;


		GetDevice()->CreateSamplerState
		(
			&samplerDesc
			, samplerStates[(UINT)eSamplerType::Point].GetAddressOf()
		);

		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
		GetDevice()->CreateSamplerState
		(
			&samplerDesc
			, samplerStates[(UINT)eSamplerType::Linear].GetAddressOf()
		);

		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSamplerState
		(
			&samplerDesc
			, samplerStates[(UINT)eSamplerType::Anisotropic].GetAddressOf()
		);

		GetDevice()->BindsSamplers((UINT)eSamplerType::Point
			, 1, samplerStates[(UINT)eSamplerType::Point].GetAddressOf());

		GetDevice()->BindsSamplers((UINT)eSamplerType::Linear
			, 1, samplerStates[(UINT)eSamplerType::Linear].GetAddressOf());

		GetDevice()->BindsSamplers((UINT)eSamplerType::Anisotropic
			, 1, samplerStates[(UINT)eSamplerType::Anisotropic].GetAddressOf());
#pragma endregion
		// Rasterlizer State
#pragma region Rasterizer state
		D3D11_RASTERIZER_DESC rsDesc = {};
		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;

		GetDevice()->CreateRasterizerState(&rsDesc
			, rasterizerStates[(UINT)eRSType::SolidBack].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;

		GetDevice()->CreateRasterizerState(&rsDesc
			, rasterizerStates[(UINT)eRSType::SolidFront].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;

		GetDevice()->CreateRasterizerState(&rsDesc
			, rasterizerStates[(UINT)eRSType::SolidNone].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;

		GetDevice()->CreateRasterizerState(&rsDesc
			, rasterizerStates[(UINT)eRSType::WireframeNone].GetAddressOf());


#pragma endregion
		// Depth Stencil State
#pragma region Depth Stencil State
		D3D11_DEPTH_STENCIL_DESC dsDesc = {};
		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&dsDesc
			, depthstencilStates[(UINT)eDSType::Less].GetAddressOf());

		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&dsDesc
			, depthstencilStates[(UINT)eDSType::Greater].GetAddressOf());

		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
		dsDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&dsDesc
			, depthstencilStates[(UINT)eDSType::NoWrite].GetAddressOf());

		dsDesc.DepthEnable = false;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
		dsDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&dsDesc
			, depthstencilStates[(UINT)eDSType::None].GetAddressOf());

#pragma endregion
		// Blend State
#pragma region Blend State

		blendStates[(UINT)eBSType::Default] = nullptr;

		D3D11_BLEND_DESC bsDesc = {};
		bsDesc.AlphaToCoverageEnable = false;
		bsDesc.IndependentBlendEnable = false;
		bsDesc.RenderTarget[0].BlendEnable = true;
		bsDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		bsDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		bsDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		bsDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

		bsDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&bsDesc, blendStates[(UINT)eBSType::AlphaBlend].GetAddressOf());

		bsDesc.AlphaToCoverageEnable = false;
		bsDesc.IndependentBlendEnable = false;

		bsDesc.RenderTarget[0].BlendEnable = true;
		bsDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		bsDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		bsDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&bsDesc, blendStates[(UINT)eBSType::OneOne].GetAddressOf());

#pragma endregion

	}

	void LoadBuffer()
	{
		constantBuffers[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffers[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));

		constantBuffers[(UINT)eCBType::Material] = new ConstantBuffer(eCBType::Material);
		constantBuffers[(UINT)eCBType::Material]->Create(sizeof(MaterialCB));

		constantBuffers[(UINT)eCBType::Grid] = new ConstantBuffer(eCBType::Grid);
		constantBuffers[(UINT)eCBType::Grid]->Create(sizeof(GridCB));

		constantBuffers[(UINT)eCBType::Animation] = new ConstantBuffer(eCBType::Animation);
		constantBuffers[(UINT)eCBType::Animation]->Create(sizeof(AnimationCB));

		constantBuffers[(UINT)eCBType::Fade_Effect] = new ConstantBuffer(eCBType::Fade_Effect);
		constantBuffers[(UINT)eCBType::Fade_Effect]->Create(sizeof(Fade));

		constantBuffers[(UINT)eCBType::Trap_Line] = new ConstantBuffer(eCBType::Trap_Line);
		constantBuffers[(UINT)eCBType::Trap_Line]->Create(sizeof(Trap));

		constantBuffers[(UINT)eCBType::Meter] = new ConstantBuffer(eCBType::Meter);
		constantBuffers[(UINT)eCBType::Meter]->Create(sizeof(Meter));

		constantBuffers[(UINT)eCBType::Monster_Meter] = new ConstantBuffer(eCBType::Monster_Meter);
		constantBuffers[(UINT)eCBType::Monster_Meter]->Create(sizeof(MONSTERMeter));

	}

	void LoadShader()
	{
		// Default
		std::shared_ptr<Shader> shader = std::make_shared<Shader>();
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");

		Resources::Insert<Shader>(L"RectShader", shader);

		//Fade
		std::shared_ptr<Shader> fadeshader = std::make_shared<Shader>();
		fadeshader->Create(eShaderStage::VS, L"FadeEffectVS.hlsl", "main");
		fadeshader->Create(eShaderStage::PS, L"FadeEffectPS.hlsl", "main");
		
		Resources::Insert<Shader>(L"FadeEffectShader", fadeshader);


		//Title
		std::shared_ptr<Shader> Cursorshader = std::make_shared<Shader>();
		Cursorshader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		Cursorshader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");

		Resources::Insert<Shader>(L"TitleShader", Cursorshader);


		// Sprite
		std::shared_ptr<Shader> spriteShader = std::make_shared<Shader>();
		spriteShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		spriteShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");
		Resources::Insert<Shader>(L"SpriteShader", spriteShader);

		// Player
		std::shared_ptr<Shader> playerShader = std::make_shared<Shader>();
		playerShader->Create(eShaderStage::VS, L"PlayerVS.hlsl", "main");
		playerShader->Create(eShaderStage::PS, L"PlayerPS.hlsl", "main");
		Resources::Insert<Shader>(L"PlayerShader", playerShader);

		//After
		std::shared_ptr<Shader> afterimageShader = std::make_shared<Shader>();
		afterimageShader->Create(eShaderStage::VS, L"AfterimageVS.hlsl", "main");
		afterimageShader->Create(eShaderStage::PS, L"AfterimagePS.hlsl", "main");
		
		Resources::Insert<Shader>(L"AfterimageShader", afterimageShader);



		std::shared_ptr<Shader> titleuiShader = std::make_shared<Shader>();
		titleuiShader->Create(eShaderStage::VS, L"UserInterfaceVS.hlsl", "main");
		titleuiShader->Create(eShaderStage::PS, L"UserInterfacePS.hlsl", "main");

		Resources::Insert<Shader>(L"TitleUIShader", titleuiShader);


		// Ground + Shadows + Parts
		for (size_t i = 1; i < 10; i++)
		{
			CreateShader(std::wstring(L"Ground" + std::to_wstring(i)));
			CreateShadowShader(std::wstring(L"GroundShadows" + std::to_wstring(i)));
			CreateShader(std::wstring(L"GroundParts" + std::to_wstring(i)));
		}

		CreateShader(std::wstring(L"Start"));
		CreateShadowShader(std::wstring(L"StartShadows"));
		CreateShader(std::wstring(L"StartParts"));


		//Fogs
		std::shared_ptr<Shader> fogsShader = std::make_shared<Shader>();
		fogsShader->Create(eShaderStage::VS, L"FogVS.hlsl", "main");
		fogsShader->Create(eShaderStage::PS, L"FogPS.hlsl", "main");		
		fogsShader->SetBSState(eBSType::AlphaBlend);
		

		Resources::Insert<Shader>(L"FogShader", fogsShader);


		// UI
		std::shared_ptr<Shader> uiShader = std::make_shared<Shader>();
		uiShader->Create(eShaderStage::VS, L"UserInterfaceVS.hlsl", "main");
		uiShader->Create(eShaderStage::PS, L"UserInterfacePS.hlsl", "main");

		Resources::Insert<Shader>(L"UIShader", uiShader);

		// UI
		std::shared_ptr<Shader> bossuiShader = std::make_shared<Shader>();
		bossuiShader->Create(eShaderStage::VS, L"UserInterfaceVS.hlsl", "main");
		bossuiShader->Create(eShaderStage::PS, L"UserInterfacePS.hlsl", "main");

		Resources::Insert<Shader>(L"BossUIShader", bossuiShader);

		// player_weapon
		std::shared_ptr<Shader> weaponuiShader = std::make_shared<Shader>();
		weaponuiShader->Create(eShaderStage::VS, L"UserInterfaceVS.hlsl", "main");
		weaponuiShader->Create(eShaderStage::PS, L"UserInterfacePS.hlsl", "main");

		Resources::Insert<Shader>(L"WeaponUIShader", weaponuiShader);

		// Player_Slot
		std::shared_ptr<Shader> slotuiShader = std::make_shared<Shader>();
		slotuiShader->Create(eShaderStage::VS, L"UserInterfaceVS.hlsl", "main");
		slotuiShader->Create(eShaderStage::PS, L"UserInterfacePS.hlsl", "main");

		Resources::Insert<Shader>(L"SlotUIShader", slotuiShader);

		// Inventory
		std::shared_ptr<Shader> inventoryuiShader = std::make_shared<Shader>();
		inventoryuiShader->Create(eShaderStage::VS, L"UserInterfaceVS.hlsl", "main");
		inventoryuiShader->Create(eShaderStage::PS, L"UserInterfacePS.hlsl", "main");
		

		Resources::Insert<Shader>(L"InventoryUIShader", inventoryuiShader);

		// Inventory Slot
		std::shared_ptr<Shader> inventoryslotuiShader = std::make_shared<Shader>();
		inventoryslotuiShader->Create(eShaderStage::VS, L"UserInterfaceVS.hlsl", "main");
		inventoryslotuiShader->Create(eShaderStage::PS, L"UserInterfacePS.hlsl", "main");


		Resources::Insert<Shader>(L"InventorySlotUIShader", inventoryslotuiShader);

		// Inventory Slot
		std::shared_ptr<Shader> inventoryslot_1uiShader = std::make_shared<Shader>();
		inventoryslot_1uiShader->Create(eShaderStage::VS, L"UserInterfaceVS.hlsl", "main");
		inventoryslot_1uiShader->Create(eShaderStage::PS, L"UserInterfacePS.hlsl", "main");


		Resources::Insert<Shader>(L"InventorySlot_1UIShader", inventoryslot_1uiShader);


		// FullHp
		std::shared_ptr<Shader> fullhpShader = std::make_shared<Shader>();
		fullhpShader->Create(eShaderStage::VS, L"UserInterfaceVS.hlsl", "main");
		fullhpShader->Create(eShaderStage::PS, L"UserInterfacePS.hlsl", "main");


		Resources::Insert<Shader>(L"FullHpShader", fullhpShader);

		//// HalfHp
		std::shared_ptr<Shader> halfhpShader = std::make_shared<Shader>();
		halfhpShader->Create(eShaderStage::VS, L"UserInterfaceVS.hlsl", "main");
		halfhpShader->Create(eShaderStage::PS, L"UserInterfacePS.hlsl", "main");


		Resources::Insert<Shader>(L"HalfHpShader", halfhpShader);

		// FullMp
		std::shared_ptr<Shader> fullmpShader = std::make_shared<Shader>();
		fullmpShader->Create(eShaderStage::VS, L"UserInterfaceVS.hlsl", "main");
		fullmpShader->Create(eShaderStage::PS, L"UserInterfacePS.hlsl", "main");


		Resources::Insert<Shader>(L"FullMpShader", fullmpShader);

		//// HalfMp
		std::shared_ptr<Shader> halfmpShader = std::make_shared<Shader>();
		halfmpShader->Create(eShaderStage::VS, L"UserInterfaceVS.hlsl", "main");
		halfmpShader->Create(eShaderStage::PS, L"UserInterfacePS.hlsl", "main");


		Resources::Insert<Shader>(L"HalfMpShader", halfmpShader);


		std::shared_ptr<Shader> coinShader = std::make_shared<Shader>();
		coinShader->Create(eShaderStage::VS, L"UserInterfaceVS.hlsl", "main");
		coinShader->Create(eShaderStage::PS, L"UserInterfacePS.hlsl", "main");


		Resources::Insert<Shader>(L"CoinShader", coinShader);

		std::shared_ptr<Shader> golduiShader = std::make_shared<Shader>();
		golduiShader->Create(eShaderStage::VS, L"UserInterfaceVS.hlsl", "main");
		golduiShader->Create(eShaderStage::PS, L"UserInterfacePS.hlsl", "main");

		Resources::Insert<Shader>(L"GoldUiShader", golduiShader);

		std::shared_ptr<Shader> moneyuiShader = std::make_shared<Shader>();
		moneyuiShader->Create(eShaderStage::VS, L"UserInterfaceVS.hlsl", "main");
		moneyuiShader->Create(eShaderStage::PS, L"UserInterfacePS.hlsl", "main");

		Resources::Insert<Shader>(L"MoneyUiShader", moneyuiShader);


		std::shared_ptr<Shader> skiluiShader = std::make_shared<Shader>();
		skiluiShader->Create(eShaderStage::VS, L"UserInterfaceVS.hlsl", "main");
		skiluiShader->Create(eShaderStage::PS, L"UserInterfacePS.hlsl", "main");

		Resources::Insert<Shader>(L"SkilUiShader", skiluiShader);

		std::shared_ptr<Shader> meterShader = std::make_shared<Shader>();
		meterShader->Create(eShaderStage::VS, L"MeterVS.hlsl", "main");
		meterShader->Create(eShaderStage::PS, L"MeterPS.hlsl", "main");

		Resources::Insert<Shader>(L"MeterShader", meterShader);


		std::shared_ptr<Shader> bossmeterShader = std::make_shared<Shader>();
		bossmeterShader->Create(eShaderStage::VS, L"BossMeterVS.hlsl", "main");
		bossmeterShader->Create(eShaderStage::PS, L"BossMeterPS.hlsl", "main");

		Resources::Insert<Shader>(L"BossMeterShader", bossmeterShader);


		

		// Grid Shader
		std::shared_ptr<Shader> gridShader = std::make_shared<Shader>();
		gridShader->Create(eShaderStage::VS, L"GridVS.hlsl", "main");
		gridShader->Create(eShaderStage::PS, L"GridPS.hlsl", "main");
		gridShader->SetRSState(eRSType::SolidNone);
		gridShader->SetDSState(eDSType::NoWrite);
		gridShader->SetBSState(eBSType::AlphaBlend);

		Resources::Insert<Shader>(L"GridShader", gridShader);

		// Debug Shader
		std::shared_ptr<Shader> debugShader = std::make_shared<Shader>();
		debugShader->Create(eShaderStage::VS, L"DebugVS.hlsl", "main");
		debugShader->Create(eShaderStage::PS, L"DebugPS.hlsl", "main");
		debugShader->SetRSState(eRSType::SolidNone);
		debugShader->SetDSState(eDSType::None);
		debugShader->SetBSState(eBSType::AlphaBlend);
		debugShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

		Resources::Insert<Shader>(L"DebugShader", debugShader);


		// Trap
		std::shared_ptr<Shader> trapShader = std::make_shared<Shader>();
		trapShader->Create(eShaderStage::VS, L"TrapVS.hlsl", "main");
		trapShader->Create(eShaderStage::PS, L"TrapPS.hlsl", "main");
		Resources::Insert<Shader>(L"TrapShader", trapShader);

		//Flime_Missile
		std::shared_ptr<Shader> flimeShader = std::make_shared<Shader>();
		flimeShader->Create(eShaderStage::VS, L"FlimeVS.hlsl", "main");
		flimeShader->Create(eShaderStage::PS, L"FlimePS.hlsl", "main");
		Resources::Insert<Shader>(L"FlimeShader", flimeShader);





	}

	void LoadTexture()
	{
		Resources::Load<Texture>(L"PlayerTexture", L"Player.png");
		Resources::Load<Texture>(L"DefaultSprite", L"Light.png");
		Resources::Load<Texture>(L"HPBarTexture", L"HPBar.png");
		Resources::Load<Texture>(L"TitleTexture", L"Title\\Title.png");
		Resources::Load<Texture>(L"layer1", L"Title\\layer1.png");
		Resources::Load<Texture>(L"layer2", L"Title\\layer2.png");
		Resources::Load<Texture>(L"layer3", L"Title\\layer3.png");
		Resources::Load<Texture>(L"Logo", L"Title\\Logo.png");
		Resources::Load<Texture>(L"Cursor", L"Cursor.png");



	}

	void LoadMaterial()
	{

		// Default
		std::shared_ptr <Texture> texture = Resources::Find<Texture>(L"PlayerTexture");
		std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"RectShader");
		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		Resources::Insert<Material>(L"RectMaterial", material);



		//FadeEffect
		std::shared_ptr<Shader> fadeshader = Resources::Find<Shader>(L"FadeEffectShader");
		std::shared_ptr<Material> fadematerial = std::make_shared<Material>();
		fadematerial->SetRenderingMode(eRenderingMode::Transparent);
		fadematerial->SetShader(fadeshader);
		
		Resources::Insert<Material>(L"FadeEffectMaterial", fadematerial);


		//Title
		std::shared_ptr <Texture> Titletexture = Resources::Find<Texture>(L"TitleTexture");
		std::shared_ptr<Shader> Titleshader = Resources::Find<Shader>(L"TitleShader");
		std::shared_ptr<Material> Titlematerial = std::make_shared<Material>();
		Titlematerial->SetShader(Titleshader);
		Titlematerial->SetTexture(Titletexture);
		Resources::Insert<Material>(L"TitleMaterial", Titlematerial);

		//Layer1
		std::shared_ptr <Texture> Layer1texture = Resources::Find<Texture>(L"layer1");
		std::shared_ptr<Shader> Layer1shader = Resources::Find<Shader>(L"TitleShader");
		std::shared_ptr<Material> Layer1material = std::make_shared<Material>();
		Layer1material->SetShader(Layer1shader);
		Layer1material->SetTexture(Layer1texture);
		Resources::Insert<Material>(L"Layer1Material", Layer1material);

		//Layer2
		std::shared_ptr <Texture> Layer2texture = Resources::Find<Texture>(L"layer2");
		std::shared_ptr<Shader> Layer2shader = Resources::Find<Shader>(L"TitleShader");
		std::shared_ptr<Material> Layer2material = std::make_shared<Material>();
		Layer2material->SetShader(Layer2shader);
		Layer2material->SetTexture(Layer2texture);
		Resources::Insert<Material>(L"Layer2Material", Layer2material);

		//Layer3
		std::shared_ptr <Texture> Layer3texture = Resources::Find<Texture>(L"layer3");
		std::shared_ptr<Shader> Layer3shader = Resources::Find<Shader>(L"TitleShader");
		std::shared_ptr<Material> Layer3material = std::make_shared<Material>();
		Layer3material->SetShader(Layer3shader);
		Layer3material->SetTexture(Layer3texture);
		Resources::Insert<Material>(L"Layer3Material", Layer3material);


		////Logo
		std::shared_ptr <Texture> Logotexture = Resources::Find<Texture>(L"Logo");
		std::shared_ptr<Shader> Logoshader = Resources::Find<Shader>(L"TitleShader");
		std::shared_ptr<Material> Logomaterial = std::make_shared<Material>();
		Logomaterial->SetShader(Logoshader);
		Logomaterial->SetTexture(Logotexture);
		Resources::Insert<Material>(L"LogoMaterial", Logomaterial);

		//Cursor
		std::shared_ptr <Texture> Cursortexture = Resources::Find<Texture>(L"Cursor");
		std::shared_ptr<Shader> Cursorshader = Resources::Find<Shader>(L"TitleShader");
		std::shared_ptr<Material> Cursormaterial = std::make_shared<Material>();

		Cursormaterial->SetRenderingMode(eRenderingMode::Transparent);

		Cursormaterial->SetShader(Cursorshader);
		Cursormaterial->SetTexture(Cursortexture);
		Resources::Insert<Material>(L"CursorMaterial", Cursormaterial);


		// Sprite
		//std::shared_ptr <Texture> spriteTexture= Resources::Find<Texture>(L"DefaultSprite");
		//std::shared_ptr <Texture> spriteTexture = Resources::Find<Texture>(L"DefaultSprite");
		std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
		spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
		spriteMaterial->SetShader(spriteShader);
		//spriteMaterial->SetTexture(spriteTexture);

		Resources::Insert<Material>(L"SpriteMaterial", spriteMaterial);
		Resources::Insert<Material>(L"MonsterMaterial", spriteMaterial);
		

		//Player
		std::shared_ptr<Shader> playerShader = Resources::Find<Shader>(L"PlayerShader");
		std::shared_ptr<Material> playerMaterial = std::make_shared<Material>();
		playerMaterial->SetRenderingMode(eRenderingMode::Transparent);
		playerMaterial->SetShader(playerShader);

		Resources::Insert<Material>(L"PlayerMaterial", playerMaterial);


		//Afterimage
		std::shared_ptr<Shader> afterimageShader = Resources::Find<Shader>(L"AfterimageShader");
		std::shared_ptr<Material> afterimageMaterial = std::make_shared<Material>();
		afterimageMaterial->SetRenderingMode(eRenderingMode::Transparent);
		afterimageMaterial->SetShader(afterimageShader);

		Resources::Insert<Material>(L"AfterimageMaterial", afterimageMaterial);
				

		//Ground + Shadows + Parts 총 9개씩 27개??
		//Ground1 , Ground2 이런식으로 i값에 번호만 바꿔서 메테리얼 생성..

		for (size_t i = 1; i < 10; i++)
		{
			CreateMaterial(std::wstring(L"Ground"+ std::to_wstring(i)));
			CreateMaterial(std::wstring(L"GroundShadows" + std::to_wstring(i)));
			CreateMaterial(std::wstring(L"GroundParts" + std::to_wstring(i)));
		}

		CreateMaterial(std::wstring(L"Start"));
		CreateMaterial(std::wstring(L"StartShadows"));
		CreateMaterial(std::wstring(L"StartParts"));



		//Fog
		std::shared_ptr<Shader> fogshader = Resources::Find<Shader>(L"FogShader");
		std::shared_ptr<Material> fogMaterial = std::make_shared<Material>();
		fogMaterial->SetRenderingMode(eRenderingMode::Transparent);
		fogMaterial->SetShader(fogshader);

		Resources::Insert<Material>(L"FogMaterial", fogMaterial);



		// UI
		//std::shared_ptr <Texture> uiTexture = Resources::Find<Texture>(L"HPBarTexture");
		std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
		std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
		uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
		uiMaterial->SetShader(uiShader);
		//uiMaterial->SetTexture(uiTexture);
		Resources::Insert<Material>(L"UIMaterial", uiMaterial);

		std::shared_ptr<Shader> bossuiShader = Resources::Find<Shader>(L"BossUIShader");
		std::shared_ptr<Material> bossuiMaterial = std::make_shared<Material>();
		bossuiMaterial->SetRenderingMode(eRenderingMode::Transparent);
		bossuiMaterial->SetShader(bossuiShader);
		//uiMaterial->SetTexture(uiTexture);
		Resources::Insert<Material>(L"BossUIMaterial", bossuiMaterial);


		std::shared_ptr<Shader> weaponuiShader = Resources::Find<Shader>(L"WeaponUIShader");
		std::shared_ptr<Material> weaponuiMaterial = std::make_shared<Material>();
		weaponuiMaterial->SetRenderingMode(eRenderingMode::Transparent);
		weaponuiMaterial->SetShader(weaponuiShader);
		Resources::Insert<Material>(L"WeaponUIMaterial", weaponuiMaterial);


		std::shared_ptr<Shader> slotuiShader = Resources::Find<Shader>(L"SlotUIShader");
		std::shared_ptr<Material> slotuiMaterial = std::make_shared<Material>();
		slotuiMaterial->SetRenderingMode(eRenderingMode::Transparent);
		slotuiMaterial->SetShader(slotuiShader);
		Resources::Insert<Material>(L"SlotUIMaterial", slotuiMaterial);


		std::shared_ptr<Shader> inventoryuiShader = Resources::Find<Shader>(L"InventoryUIShader");
		std::shared_ptr<Material> inventoryuiMaterial = std::make_shared<Material>();
		inventoryuiMaterial->SetRenderingMode(eRenderingMode::Transparent);
		inventoryuiMaterial->SetShader(inventoryuiShader);
		Resources::Insert<Material>(L"InventoryUIMaterial", inventoryuiMaterial);


		std::shared_ptr<Shader> inventoryslotuiShader = Resources::Find<Shader>(L"InventorySlotUIShader");
		std::shared_ptr<Material> inventoryslotuiMaterial = std::make_shared<Material>();
		inventoryslotuiMaterial->SetRenderingMode(eRenderingMode::Transparent);
		inventoryslotuiMaterial->SetShader(inventoryslotuiShader);
		Resources::Insert<Material>(L"InventorySlotUIMaterial", inventoryslotuiMaterial);	
		
		std::shared_ptr<Shader> inventoryslot_1uiShader = Resources::Find<Shader>(L"InventorySlot_1UIShader");
		std::shared_ptr<Material> inventoryslot_1uiMaterial = std::make_shared<Material>();
		inventoryslot_1uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
		inventoryslot_1uiMaterial->SetShader(inventoryslot_1uiShader);
		Resources::Insert<Material>(L"InventorySlot_1UIMaterial", inventoryslot_1uiMaterial);


		std::shared_ptr<Shader> titleuiShader = Resources::Find<Shader>(L"TitleUIShader");
		std::shared_ptr<Material> titleuiMaterial = std::make_shared<Material>();
		titleuiMaterial->SetRenderingMode(eRenderingMode::Transparent);
		titleuiMaterial->SetShader(titleuiShader);
		Resources::Insert<Material>(L"TitleUIMaterial", titleuiMaterial);



		std::shared_ptr<Shader> fullhpShader = Resources::Find<Shader>(L"FullHpShader");
		std::shared_ptr<Material> fullhpMaterial = std::make_shared<Material>();
		fullhpMaterial->SetRenderingMode(eRenderingMode::Transparent);
		fullhpMaterial->SetShader(fullhpShader);
		Resources::Insert<Material>(L"FullHpMaterial", fullhpMaterial);

		std::shared_ptr<Shader> halfhpShader = Resources::Find<Shader>(L"HalfHpShader");
		std::shared_ptr<Material> halfhpMaterial = std::make_shared<Material>();
		halfhpMaterial->SetRenderingMode(eRenderingMode::Transparent);
		halfhpMaterial->SetShader(halfhpShader);
		Resources::Insert<Material>(L"HalfHpMaterial", halfhpMaterial);

		std::shared_ptr<Shader> fullmpShader = Resources::Find<Shader>(L"FullMpShader");
		std::shared_ptr<Material> fullmpMaterial = std::make_shared<Material>();
		fullmpMaterial->SetRenderingMode(eRenderingMode::Transparent);
		fullmpMaterial->SetShader(fullmpShader);
		Resources::Insert<Material>(L"FullMpMaterial", fullmpMaterial);

		std::shared_ptr<Shader> halfmpShader = Resources::Find<Shader>(L"HalfMpShader");
		std::shared_ptr<Material> halfmpMaterial = std::make_shared<Material>();
		halfmpMaterial->SetRenderingMode(eRenderingMode::Transparent);
		halfmpMaterial->SetShader(halfmpShader);
		Resources::Insert<Material>(L"HalfMpMaterial", halfmpMaterial);


		std::shared_ptr<Shader> coinShader = Resources::Find<Shader>(L"CoinShader");
		std::shared_ptr<Material> coinMaterial = std::make_shared<Material>();
		coinMaterial->SetRenderingMode(eRenderingMode::Transparent);
		coinMaterial->SetShader(coinShader);
		Resources::Insert<Material>(L"CoinMaterial", coinMaterial);


		std::shared_ptr<Shader> golduiShader = Resources::Find<Shader>(L"GoldUiShader");
		std::shared_ptr<Material> golduiMaterial = std::make_shared<Material>();
		golduiMaterial->SetRenderingMode(eRenderingMode::Transparent);
		golduiMaterial->SetShader(golduiShader);
		Resources::Insert<Material>(L"GoldUiMaterial", golduiMaterial);


		std::shared_ptr<Shader> moneyShader = Resources::Find<Shader>(L"MoneyUiShader");
		std::shared_ptr<Material> moneyMaterial = std::make_shared<Material>();
		moneyMaterial->SetRenderingMode(eRenderingMode::Transparent);
		moneyMaterial->SetShader(moneyShader);
		Resources::Insert<Material>(L"MoneyUiMaterial", moneyMaterial);


		std::shared_ptr<Shader> skilShader = Resources::Find<Shader>(L"SkilUiShader");
		std::shared_ptr<Material> skilMaterial = std::make_shared<Material>();
		skilMaterial->SetRenderingMode(eRenderingMode::Transparent);
		skilMaterial->SetShader(skilShader);
		Resources::Insert<Material>(L"SkilUiMaterial", skilMaterial);


		std::shared_ptr<Shader> meterShader = Resources::Find<Shader>(L"MeterShader");
		std::shared_ptr<Material> meterMaterial = std::make_shared<Material>();
		meterMaterial->SetRenderingMode(eRenderingMode::Transparent);
		meterMaterial->SetShader(meterShader);
		//uiMaterial->SetTexture(uiTexture);
		Resources::Insert<Material>(L"MeterMaterial", meterMaterial);


		std::shared_ptr<Shader> bossmeterShader = Resources::Find<Shader>(L"BossMeterShader");
		std::shared_ptr<Material> bossmeterMaterial = std::make_shared<Material>();
		bossmeterMaterial->SetRenderingMode(eRenderingMode::Transparent);
		bossmeterMaterial->SetShader(bossmeterShader);
		//uiMaterial->SetTexture(uiTexture);
		Resources::Insert<Material>(L"BossMeterMaterial", bossmeterMaterial);


		// Grid
		std::shared_ptr<Shader> gridShader = Resources::Find<Shader>(L"GridShader");
		std::shared_ptr<Material> gridMaterial = std::make_shared<Material>();
		gridMaterial->SetShader(gridShader);
		Resources::Insert<Material>(L"GridMaterial", gridMaterial);

		// Debug
		std::shared_ptr<Shader> debugShader = Resources::Find<Shader>(L"DebugShader");
		std::shared_ptr<Material> debugMaterial = std::make_shared<Material>();
		debugMaterial->SetRenderingMode(eRenderingMode::Transparent);
		debugMaterial->SetShader(debugShader);
		Resources::Insert<Material>(L"DebugMaterial", debugMaterial);

		// Trap
		std::shared_ptr<Shader> trapShader = Resources::Find<Shader>(L"TrapShader");
		std::shared_ptr<Material> trapMaterial = std::make_shared<Material>();
		trapMaterial->SetRenderingMode(eRenderingMode::Transparent);
		trapMaterial->SetShader(trapShader);

		Resources::Insert<Material>(L"TrapMaterial", trapMaterial);


		//Flime_Missile
		std::shared_ptr<Shader> flimeShader = Resources::Find<Shader>(L"FlimeShader");
		std::shared_ptr<Material> flimeMaterial = std::make_shared<Material>();
		flimeMaterial->SetRenderingMode(eRenderingMode::Transparent);
		flimeMaterial->SetShader(flimeShader);

		Resources::Insert<Material>(L"FlimeMaterial", flimeMaterial);

	
		std::shared_ptr<Shader> optionshader = Resources::Find<Shader>(L"TitleShader");
		std::shared_ptr<Material> optionsmaterial = std::make_shared<Material>();
		optionsmaterial->SetRenderingMode(eRenderingMode::Transparent);
		optionsmaterial->SetShader(optionshader);
		Resources::Insert<Material>(L"OptionMaterial", optionsmaterial);

		std::shared_ptr<Shader> optioncheakshader = Resources::Find<Shader>(L"TitleShader");
		std::shared_ptr<Material> optioncheakmaterial = std::make_shared<Material>();
		optioncheakmaterial->SetRenderingMode(eRenderingMode::Transparent);
		optioncheakmaterial->SetShader(optioncheakshader);
		Resources::Insert<Material>(L"OptionCheakMaterial", optioncheakmaterial);

		std::shared_ptr<Shader> onoffshader = Resources::Find<Shader>(L"TitleShader");
		std::shared_ptr<Material> onoffmaterial = std::make_shared<Material>();
		onoffmaterial->SetRenderingMode(eRenderingMode::Transparent);
		onoffmaterial->SetShader(onoffshader);
		Resources::Insert<Material>(L"OnOffMaterial", onoffmaterial);

		
		std::shared_ptr<Shader> volumeshader = Resources::Find<Shader>(L"TitleShader");
		std::shared_ptr<Material> volumematerial = std::make_shared<Material>();
		volumematerial->SetRenderingMode(eRenderingMode::Transparent);
		volumematerial->SetShader(volumeshader);
		Resources::Insert<Material>(L"VolumeMaterial", volumematerial);

	}

	void Initialize()
	{
		LoadMesh();
		LoadShader();
		SetUpState();
		LoadBuffer();
		LoadTexture();
		LoadMaterial();
	}

	void Release()
	{
		for (size_t i = 0; i < (UINT)eCBType::End; i++)
		{
			delete constantBuffers[i];
			constantBuffers[i] = nullptr;
		}
	}



	void Render()
	{
		//std::vector<Camera*> cameras[(UINT)eSceneType::End];
		eSceneType type = SceneManager::GetActiveScene()->GetSceneType();
		for (Camera* cam : cameras[(UINT)type])
		{
			if (cam == nullptr)
				continue;

			cam->Render();
		}

		cameras[(UINT)type].clear();
	}


	void InitInputLayout(const std::wstring& name)
	{

		D3D11_INPUT_ELEMENT_DESC arrLayoutDesc[3] = {};

		arrLayoutDesc[0].AlignedByteOffset = 0;
		arrLayoutDesc[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayoutDesc[0].InputSlot = 0;
		arrLayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[0].SemanticName = "POSITION";
		arrLayoutDesc[0].SemanticIndex = 0;

		arrLayoutDesc[1].AlignedByteOffset = 16;
		arrLayoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayoutDesc[1].InputSlot = 0;
		arrLayoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[1].SemanticName = "COLOR";
		arrLayoutDesc[1].SemanticIndex = 0;

		arrLayoutDesc[2].AlignedByteOffset = 32;
		arrLayoutDesc[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		arrLayoutDesc[2].InputSlot = 0;
		arrLayoutDesc[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[2].SemanticName = "TEXCOORD";
		arrLayoutDesc[2].SemanticIndex = 0;


		std::wstring Name = name + L"Shader";

		std::shared_ptr<Shader> groundShader = Resources::Find<Shader>(Name);
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, groundShader->GetVSBlobBufferPointer()
			, groundShader->GetVSBlobBufferSize()
			, groundShader->GetInputLayoutAddressOf());

	}

	void CreateShader(const std::wstring& name)
	{

		std::wstring Name = name + L"Shader";

		std::shared_ptr<Shader> partsShader = std::make_shared<Shader>();
		partsShader->Create(eShaderStage::VS, L"PartsVS.hlsl", "main");
		partsShader->Create(eShaderStage::PS, L"PartsPS.hlsl", "main");

		Resources::Insert<Shader>(Name, partsShader);


	}

	void CreateShadowShader(const std::wstring& name)
	{
		std::wstring Name = name + L"Shader";

		std::shared_ptr<Shader> partsShader = std::make_shared<Shader>();
		partsShader->Create(eShaderStage::VS, L"FogVS.hlsl", "main");
		partsShader->Create(eShaderStage::PS, L"FogPS.hlsl", "main");

		Resources::Insert<Shader>(Name, partsShader);


	}



	void CreateMaterial(const std::wstring& name)
	{

		std::wstring Name = name + L"Material";
		std::wstring Shadername = name + L"Shader";

		//Ground
		std::shared_ptr<Shader> shader = Resources::Find<Shader>(Shadername);
		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->SetRenderingMode(eRenderingMode::Transparent);
		material->SetShader(shader);
		
		Resources::Insert<Material>(Name, material);


	}

}