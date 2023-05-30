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

    
    //float2 diff = (atlasSize - spriteSize) / 2.0f;
    //float2 UV = (leftTop - diff - offset) + (atlasSize * In.UV);
        
    //if (UV.x < leftTop.x || UV.y < leftTop.y 
    //        || UV.x > leftTop.x + spriteSize.x 
    //        || UV.y > leftTop.y + spriteSize.y)
    //    discard;
    
    
      
    
    float4 color = (float) 0.0f;
    color = defaultTexture.Sample(pointSampler, In.UV);
        
    if (color.a == 1.0f)
    {
        float newAlphaValue = 0.3f; // 변경할 알파값
        color = float4(color.rgb, newAlphaValue);
    }
  
   
    return color;
}