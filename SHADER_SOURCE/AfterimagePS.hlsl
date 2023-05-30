#include "globals.hlsli"
struct VSIn
{
    float4 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

//cbuffer time
//int 0

float4 main(VSOut In) : SV_Target
{
    float4 color = (float) 0.0f;
        
    //color.a += time;
    
    if (animationType == 1) // 2D
    {
        float2 diff = (atlasSize - spriteSize) / 2.0f;
        float2 UV = (leftTop - diff - offset) + (atlasSize * In.UV);
        
        if (UV.x < leftTop.x || UV.y < leftTop.y 
            || UV.x > leftTop.x + spriteSize.x 
            || UV.y > leftTop.y + spriteSize.y)
            discard;
        
        color = atlasTexture.Sample(pointSampler, UV);
        
        
        //�Ķ������� �ؽ��� �̹��� ���� 
        //float4 texcolor = atlasTexture.Sample(pointSampler, UV); 
        //float blue = texcolor.b;
        //color = float4(0.1f, 0.1f, blue, texcolor.a); ���İ��� UV ���ܽ�Ű�°� �ް� rgb���� ���� ��       
        
        //color = float4(0.1f, 0.1f, color.b, color.a);
        
        
        
        //color = float4(color.r, 0.1f, color.b, color.a);
        
        if (color.a == 1.0f)
        {
            float newAlphaValue = 0.6f; // ������ ���İ�
            color = float4(color.r, 0.1f, 0.1f, newAlphaValue);
        }
        

    }
    else
    {
        color = defaultTexture.Sample(anisotropicSampler, In.UV);
    }
    
    
   
    //color = defaultTexture.Sample(anisotropicSampler, In.UV);
    return color;
}