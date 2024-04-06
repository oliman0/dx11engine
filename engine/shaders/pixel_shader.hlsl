struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float2 TexCoord : TEXCOORD;
};

Texture2D ObjTexture;
SamplerState ObjSamplerState;

float4 PSMain(VS_OUTPUT input) : SV_TARGET
{
    float4 colour = ObjTexture.Sample(ObjSamplerState, input.TexCoord);
    
    clip(colour.a - .25);
    
    return colour;
}