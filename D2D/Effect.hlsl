///////////////////////////////////////////////////////
//    Vertext Type Define
//    * High Level Shader Langauge ���� ���
//    HLSL ���α׷� ������ ���� ����, Ÿ�� ����, ���� , �ȼ�,
//    geometry shader�� ������ �� ���� 
//
//    IA->VS->RS->PS->OM
///////////////////////////////////////////////////////


///////////// // GLOBALS // ///////////// 
// cbuffer MatrixBuffer
// { 
// 	matrix worldMatrix; 
// 	matrix viewMatrix; 
// 	matrix projectionMatrix;
// };

////////////////////////////////////////////////////////
// Vertex input typedefine
// float4         : x,y,z,w�� ������ shader���Ǵ� ����
// POSITION,COLOR : GPU�� �� ������ ����� ���� ���� (SemanticName)
// ���� Type�� �� ����Ϸ��� 0,1,2...�� ����Ѵ� 
////////////////////////////////////////////////////////
struct VertexInput
{
    float4 Position : POSITION0;     
    float4 Color :    COLOR0;
};
struct PixelInput
{
    float4 Position : SV_POSITION0;
    float4 Color :    COLOR0;
};
////////////////////////////////////////////////////////
//  Vertex Shader ��� ���α׷�
////////////////////////////////////////////////////////
PixelInput VS(VertexInput input)
{
    PixelInput output;

	// ����� ����ȭ�� ��ǥ���� ����ϱ� ������ �Ʒ� function�� (��) �� �����ݴϴ�.
	{
		// �ùٸ��� ��� ������ �ϱ� ���Ͽ� position ���͸� w���� �ִ� 4������ �ִ� ������ ����մϴ�. 
	//	input.position.w = 1.0f;
		// ������ ��ġ�� ����, ��, ������ ������ ����մϴ�. 
	//	output.position = mul(input.position, worldMatrix);
	//	output.position = mul(output.position, viewMatrix);
	//	output.position = mul(output.position, projectionMatrix);
	}

	output.Position = input.Position;
	output.Color = input.Color;
    return output;
}
////////////////////////////////////////////////////////
// Pixel Shader ��� ���α׷�
////////////////////////////////////////////////////////
float4 PS(PixelInput input) : SV_TARGET0
{
	//return float4(1, 1, 0, 1);
    return input.Color;
}
