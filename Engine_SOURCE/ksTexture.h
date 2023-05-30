#pragma once
#include "..\External\DirectXTex\Include\DirectXTex.h"
#include "ksResource.h"
#include "ksGraphicDevice_DX11.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\External\\DirectXTex\\lib\\Debug\\DirectXTex.lib") 
#else 
#pragma comment(lib, "..\\External\\DirectXTex\\lib\\Release\\DirectXTex.lib") 
#endif




union Pixel
{
	struct
	{
		BYTE R;
		BYTE G;
		BYTE B;
		BYTE A;
	};
	DWORD Color;

	Pixel(BYTE r, BYTE g, BYTE b, BYTE a)
		:R(r), G(g), B(b), A(a)
	{

	}

	Pixel(COLORREF color)
		:Color(color)
	{

	}

};


using namespace ks::enums;
namespace ks::graphics
{
	class Texture : public Resource
	{
	public:
		Texture();
		virtual ~Texture();

		static void Clear(UINT startSlot);
		virtual HRESULT Load(const std::wstring& path) override;
		void BindShader(eShaderStage stage, UINT slot);
		void Clear();

		size_t GetHeight() { return mImage.GetMetadata().height; }
		size_t GetWidth() { return mImage.GetMetadata().width; }


		Pixel GetPixelColor(int x, int y, Vec3 pos);
		//Pixel GetPixelColor(std::shared_ptr<Texture> texture);
		void SetPixelColor(int x, int y, Pixel pixel);


	private:
		ScratchImage mImage;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		D3D11_TEXTURE2D_DESC mDesc;
		void* mBit;


	};

}
