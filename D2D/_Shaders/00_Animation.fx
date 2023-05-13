////////////////////////////////////////////////////////////////////////
//   Shader :  ��ü��  ����� ǥ�� ���¸� �������� �Ӽ�
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
//    �ؽ��İ� �ƴ� �Ϲ� ������ ���� �Ӽ���  x,y,z,w(����)�� ��������
//    ���� �Ҽ� �ִ�.  
//    CPU->GPU�� ������ �������� ����ü�� ���� 
//
//    Vertext Type Define
//       * High Level Shader Langauge ���� ���
//         HLSL ���α׷� ������ ���� ����, Ÿ�� ����, ���� , �ȼ�,
//         geometry shader�� ������ �� ���� 
//
//        IA->VS->RS->PS->OM
////////////////////////////////////////////////////////////////////////
cbuffer CB_PerFrame            // Constant Bufffer�� ��������� �����ü� �ִ�  
{
    matrix View;
    matrix Projection;
}
matrix World;
//=======================================================================
//   Texture Global 
//=======================================================================
float2  sprite_offset;
float2  sprite_size;
float2  texture_size;
float4  TextureColor;

Texture2D    DiffuseMap;                  //  �ؽ��� �ڿ����μ� �𵨿� �ؽ��ĸ� �׸��� ���, Shader Class���� ����
SamplerState PointSampler                 //  ���̵��� �̷���� �� ��� �ؽ����� �ȼ��� �������� ���� ������ ���ְ� ��.
{
    Filter = MIN_MAG_MIP_POINT;
    AddressU = Mirror;
    AddressV = Mirror;
};
SamplerState LinearSampler             //  ���̵��� �̷���� �� ��� �ؽ����� �ȼ��� �������� ���� ������ ���ְ� ��.
{
    Filter = MIN_MAG_MIP_LINEAR;
};

//=======================================================================
//   ����� ������ Type Define
//=======================================================================
struct VertexInput                     // DeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
{
    float4 Position : POSITION0;       // C���� ó�� Type�� �������Ͽ� ������ �����ڿ� GPU�� �˾� ���� �ֵ��� POSITION(����ƽ)�� �ο��Ѵ�
    float2 Uv : UV0;                   // Semantic(�ǹ�) : 
};

struct VertexOutput
{
    float4 Position : SV_POSITION0;
    float2 Uv : UV0;
};

//=======================================================================
//   VS Stage
//=======================================================================
VertexOutput VS(VertexInput input)
{
    VertexOutput output;

    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);

    output.Uv = input.Uv;
 //   output.Uv = output.Uv * sprite_size   / texture_size;
 //   output.Uv = output.Uv + sprite_offset / texture_size;

    return output;
}

//=======================================================================
//   PS Stage
//float4 color = DiffuseMap.Sample(PointSampler, input.Uv);

//if (color.r == 1.0f && color.b == 1.0f)
//discard;
//=======================================================================
float4 PS_Point(VertexOutput input) : SV_TARGET0
{
   float4 color = DiffuseMap.Sample(PointSampler, input.Uv);
    
  // if (color.r == 1.0f && color.b == 1.0f)
	//   discard;

	//if (color.a < 0.1f)
    //discard;
    
    return DiffuseMap.Sample(PointSampler, input.Uv);
}
float4 PS_Linear(VertexOutput input) : SV_TARGET0
{
    return DiffuseMap.Sample(LinearSampler, input.Uv);
}
float Time = 0.5;
float4 PS_Lerp(VertexOutput input) : SV_Target
{
    float4 diffuse = DiffuseMap.Sample(PointSampler, input.Uv);

    float4 red = float4(1, 0, 0, diffuse.a);
    float4 color = lerp(diffuse, red, Time);

    return color;
}
float4 PS_GreyLerp(VertexOutput input) : SV_Target
{
    float4 diffuse = DiffuseMap.Sample(PointSampler, input.Uv);

    float4 grey= float4(TextureColor.rgb, diffuse.a);
    float4 color = lerp(diffuse, grey, Time);

    return color;
}

float4 PS_AlphaLerp(VertexOutput input) : SV_Target
{
	float4 diffuse = DiffuseMap.Sample(PointSampler, input.Uv);

	float4 alpha = float4(diffuse.rgb, 0);
	float4 color = lerp(diffuse, alpha, Time);

	return color;
}

float4 PS_TextureColor(VertexOutput input) : SV_Target
{
    float4 diffuse = DiffuseMap.Sample(PointSampler, input.Uv);
    float4 final = float4(TextureColor.r,TextureColor.g,TextureColor.b,diffuse.a);

    return final;
}


//=======================================================================
//   OM Stage
//   DestBlend  :  �̹� �׷��� �ִ� �ȼ��� ����
//   SrcBlend   :  ����׷����ϴ� �ȼ�
//    blendStateDescription.RenderTarget[0].BlendEnable = TRUE; 
//    blendStateDescription.RenderTarget[0].SrcBlend =D3D11_BLEND_SRC_ALPHA; 
//    blendStateDescription.RenderTarget[0].DestBlend =D3D11_BLEND_INV_SRC_ALPHA; 
//    blendStateDescription.RenderTarget[0].BlendOp =D3D11_BLEND_OP_ADD; 
//    blendStateDescription.RenderTarget[0].SrcBlendAlpha =D3D11_BLEND_ONE; 
//    blendStateDescription.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO; 
//    blendStateDescription.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD; 
//    blendStateDescription.RenderTarget[0].RenderTargetWriteMask = 0x0f;
//=======================================================================
BlendState AlphaBlend     // https://docs.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_blend
{
    BlendEnable[0] = true;
    DestBlend[0] = INV_SRC_ALPHA;      // �ҽ��� a ���� ���� ��Ų�� ( 1-a )  �������� ���� Pixel�� a ���� �۰���
    SrcBlend[0] = SRC_ALPHA;           // �� Image�� a �� ���
    BlendOp[0] = ADD;                  

    SrcBlendAlpha[0] = ONE;
    DestBlendAlpha[0] = ONE;
    RenderTargetWriteMask[0] = 0x0F;
};

BlendState AlphaBlend_AlphaToCoverage
{
    AlphaToCoverageEnable = true;

    BlendEnable[0] = true;
    DestBlend[0] = INV_SRC_ALPHA;
    SrcBlend[0] = SRC_ALPHA;
    BlendOp[0] = Add;

    SrcBlendAlpha[0] = One;
    DestBlendAlpha[0] = One;
    RenderTargetWriteMask[0] = 0x0F;
};
RasterizerState CullMode_None
{
    CullMode = None;
    DepthClipEnable = false;
};
//=======================================================================
//   Pipe Line
//=======================================================================
technique11 T0
{
    pass P0
    {
        SetRasterizerState(CullMode_None);
        SetBlendState(AlphaBlend, float4(0, 0, 0, 0), 0xFF);
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS_Point()));
    }

    pass P1
    {
        SetRasterizerState(CullMode_None);
        SetBlendState(AlphaBlend, float4(0, 0, 0, 0), 0xFF);
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS_Lerp()));
    }

    pass P2
    {
        SetBlendState(AlphaBlend_AlphaToCoverage, float4(0, 0, 0, 0), 0xFF);
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS_Linear()));
    }

    pass P3
    {
        SetRasterizerState(CullMode_None);
        SetBlendState(AlphaBlend, float4(0, 0, 0, 0), 0xFF);
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS_GreyLerp()));
    }

    pass P4
    {
        SetRasterizerState(CullMode_None);
        SetBlendState(AlphaBlend, float4(0, 0, 0, 0), 0xFF);
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS_TextureColor()));
    }

	pass P5
	{
		SetRasterizerState(CullMode_None);
		SetBlendState(AlphaBlend, float4(0, 0, 0, 0), 0xFF);
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS_AlphaLerp()));
	}
}