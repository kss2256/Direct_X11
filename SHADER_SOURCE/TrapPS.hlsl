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


float4 main(VSOut In) : SV_Target
{
    float4 color = float(0.f);
    
    if (animationType == 1) // 2D
    {
        float2 diff = (atlasSize - spriteSize) / 2.0f;
        float2 UV = (leftTop - diff - offset) + (atlasSize * In.UV);
        
        if (UV.x < leftTop.x || UV.y < leftTop.y 
            || UV.x > leftTop.x + spriteSize.x 
            || UV.y > leftTop.y + spriteSize.y)
            discard;
        
        
        //color = atlasTexture.Sample(anisotropicSampler, UV);
        color = atlasTexture.Sample(pointSampler, UV);
        //color = atlasTexture.Sample(, UV);
    }
    else
    {
    
        color = defaultTexture.Sample(pointSampler, In.UV);
    
        color = float4(1.0f, linecolor, linecolor, color.a);
    
        if (color.a == 0.0f)
        {

        
            float newAlphaValue = 0.5f; // 변경할 알파값
            float2 center = float2(0.5f, 0.5f); // 원의 중심 좌표
            float radius = 0.5f; // 원의 반지름

         // 원 안쪽에만 투명한 빨강색 적용
            float2 distance = In.UV - center; //현재 픽셀좌표와 원의 중심좌표 두 좌표의 거리 계산
            float distSquared = dot(distance, distance); //dot = 내적, (벡터와 자기 자신을 내적하여 길이의 제곱값을 구한다.
                                                        //이 값은 원의 중심으로부터 픽셀의 거리의 제곱을 구하는것임.
            if (distSquared <= radius * radius)             //위에서 구한 값이 원의 크기보다 작은 경우에만 투명값을 적용 하는것
            {
                color = float4(1.0f, 0.0f, 0.0f, newAlphaValue);
            }
        
        }
    }
    
    return color;
    

    
}

