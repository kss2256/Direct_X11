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

        
            float newAlphaValue = 0.5f; // ������ ���İ�
            float2 center = float2(0.5f, 0.5f); // ���� �߽� ��ǥ
            float radius = 0.5f; // ���� ������

         // �� ���ʿ��� ������ ������ ����
            float2 distance = In.UV - center; //���� �ȼ���ǥ�� ���� �߽���ǥ �� ��ǥ�� �Ÿ� ���
            float distSquared = dot(distance, distance); //dot = ����, (���Ϳ� �ڱ� �ڽ��� �����Ͽ� ������ �������� ���Ѵ�.
                                                        //�� ���� ���� �߽����κ��� �ȼ��� �Ÿ��� ������ ���ϴ°���.
            if (distSquared <= radius * radius)             //������ ���� ���� ���� ũ�⺸�� ���� ��쿡�� ������ ���� �ϴ°�
            {
                color = float4(1.0f, 0.0f, 0.0f, newAlphaValue);
            }
        
        }
    }
    
    return color;
    

    
}

