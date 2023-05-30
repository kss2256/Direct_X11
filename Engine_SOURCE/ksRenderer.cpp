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
		// Input Layout ( ���� ���� ���� ) 
#pragma region Input layout

//Vertex ����ü ��� �ϳ��� �迭 �ϳ��� ���� �ؼ� ���� ���ָ��
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

		std::shared_ptr<Shader> afterimageShader = Resources::Find<Shader>(L"AfterimageShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, afterimageShader->GetVSBlobBufferPointer()
			, afterimageShader->GetVSBlobBufferSize()
			, afterimageShader->GetInputLayoutAddressOf());



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

		//After
		std::shared_ptr<Shader> afterimageShader = std::make_shared<Shader>();
		afterimageShader->Create(eShaderStage::VS, L"AfterimageVS.hlsl", "main");
		afterimageShader->Create(eShaderStage::PS, L"AfterimagePS.hlsl", "main");
		
		Resources::Insert<Shader>(L"AfterimageShader", afterimageShader);



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
		Resources::Insert<Material>(L"PlayerUiMaterial", spriteMaterial);
		
		//Afterimage
		std::shared_ptr<Shader> afterimageShader = Resources::Find<Shader>(L"AfterimageShader");
		std::shared_ptr<Material> afterimageMaterial = std::make_shared<Material>();
		afterimageMaterial->SetRenderingMode(eRenderingMode::Transparent);
		afterimageMaterial->SetShader(afterimageShader);

		Resources::Insert<Material>(L"AfterimageMaterial", afterimageMaterial);
				

		//Ground + Shadows + Parts �� 9���� 27��??
		//Ground1 , Ground2 �̷������� i���� ��ȣ�� �ٲ㼭 ���׸��� ����..

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