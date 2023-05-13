cbuffer CB_PerFrame
{
    matrix View;
    matrix Projection;
};

matrix World;

struct VertexOutput
{
    float4 Position : SV_POSITION0;
};

VertexOutput VS(float4 position : POSITION0)
{
    VertexOutput output;
    output.Position = mul(position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);

    return output;
}


float4 PS(VertexOutput input, uniform float4 color) : SV_TARGET0
{
    return color;
}

technique11 T0
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS(float4(0, 1, 0, 1))));
    }

    pass P1
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS(float4(1, 0, 0, 1))));
    }
}