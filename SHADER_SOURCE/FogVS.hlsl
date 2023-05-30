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

VSOut main(VSIn In)
{
    VSOut Out = (VSOut) 0.f;
    
    float4 worldPosition = mul(In.Pos, world);
    float4 viewPosition = mul(worldPosition, view);
    float4 ProjPosition = mul(viewPosition, projection);
    
    Out.Pos = ProjPosition;
    Out.Color = In.Color;
    Out.UV = In.UV;
    

    
    return Out;
    
    
    
    //// Calculate final UV value
    //float2 finalUV = In.UV + StartTime;
    
    //// Output final vertex attributes
    //Out.Pos = mul(float4(In.Pos.xyz, 1.0f), mul(world, mul(view, projection)));
    //Out.Color = In.Color;
    //Out.UV = finalUV;
    
    //return Out;
    
}