#include "Light.hlsli"
cbuffer Transform : register(b0)
{
    row_major matrix world;
    row_major matrix view;
    row_major matrix projection;
}

cbuffer MaterialData : register(b1)
{
    int cbiData;
    float cbfData;
    float2 cbxy;
    float3 cbxyz;
    float4 cbxyzw;
    matrix cbmat;
}

cbuffer Grid : register(b2)
{
    float4 cameraPosition;
    float2 cameraScale;
    float2 resolution;
}

cbuffer Animation : register(b3)
{
    float2 leftTop;
    float2 spriteSize;
    float2 offset;
    float2 atlasSize;

    uint animationType;
}


cbuffer Fade : register(b4)
{
    
    float time;
    float StartTime;
    float EndTime;
    float dumi;
    
}

cbuffer Trap : register(b5)
{
    
    float   linecolor;
    float   alpha;
    float2  linesize;
    
}


cbuffer Meter : register(b6)
{    
    float metertime;
    float meterendtime;
    float2 metersize;
}

cbuffer MONSTERMeter : register(b7)
{
    float   monstermeter;
    float   monstermeterend;
    float2  monstermetersize;
}


cbuffer PLAYEREFFECT : register(b8)
{
    float   playerhit;
    float   playerhittime;
    float2  player;   
}




SamplerState pointSampler : register(s0);
SamplerState linearSampler : register(s1);
SamplerState anisotropicSampler : register(s2);

StructuredBuffer<LightAttribute> lightAttributes : register(t13);

Texture2D defaultTexture : register(t0);
//Texture2D defaultTexture2 : register(t1);
//Texture2D defaultTexture3 : register(t2);

//Atlas texture
Texture2D atlasTexture : register(t12);