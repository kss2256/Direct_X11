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
    VSOut output;
    
    float4 worldPosition = mul(In.Pos, world);
    float4 viewPosition = mul(worldPosition, view);
    float4 ProjPosition = mul(viewPosition, projection);
    
    output.Pos = ProjPosition;
    output.Color = In.Color;
    
   
    float2 uv = In.UV;
    float monsterbarSize = 0.5;
    float monsterbarStart = 0.0;
    float monsterbarEnd = 0.5;
    
    
    monsterbarStart += monstermeter;
    monsterbarEnd += monstermeter;
    
    if (uv.x < monsterbarStart || uv.x > monsterbarEnd)
    {
        uv.x = clamp(uv.x, monsterbarStart, monsterbarEnd);
    }
    else if (uv.x >= monsterbarStart && uv.x <= monsterbarStart + monsterbarSize)
    {
        uv.x = lerp(monsterbarStart, monsterbarEnd, (uv.x - monsterbarStart) / monsterbarSize);
    }
    else if (uv.x >= monsterbarEnd - monsterbarSize && uv.x <= monsterbarEnd)
    {
        uv.x = lerp(monsterbarStart, monsterbarEnd, (uv.x - (monsterbarEnd - monsterbarSize)) / monsterbarSize);
    }
    
    output.UV = uv;
    
    return output;
}