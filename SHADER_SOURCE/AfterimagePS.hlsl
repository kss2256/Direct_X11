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
        
        
        //파랑색으로 텍스쳐 이미지 변경 
        //float4 texcolor = atlasTexture.Sample(pointSampler, UV); 
        //float blue = texcolor.b;
        //color = float4(0.1f, 0.1f, blue, texcolor.a); 알파값은 UV 제외시키는거 받고 rgb값만 새로 팜       
        
        //color = float4(0.1f, 0.1f, color.b, color.a);
        
        
        
        //color = float4(color.r, 0.1f, color.b, color.a);
        
        if (color.a == 1.0f)
        {
            float newAlphaValue = 0.6f; // 변경할 알파값
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