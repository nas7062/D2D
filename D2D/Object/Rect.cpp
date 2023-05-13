#include  "framework.h"
#include  "Rect.h"
///////////////////////////////////////////////////////////
// ������
//////////////////////////////////////////////////////////
Rect::Rect()
{
	wstring  strFileName = L"./_Shaders/10_Rect.fx";
	m_pShader = new Shader(strFileName);
	CreateVertexBuffer();
}

Rect::~Rect()
{
	SAFE_DELETE(m_pShader);
	SAFE_RELEASE(m_pVertexBuffer);   // com interface 
	SAFE_RELEASE(m_pIndexBuffer);    // com interface 
}

//////////////////////////////////////////////////////////
//  ������ �ð�������� ����
//
//        1   |    3              0 : -0.5f,-0.5f, 0.0f
//            |                   1 : -0.5f,+0.5f, 0.0f
//     ------------------         2 : +0.5f,-0.5f, 0.0f
//        0   |    2              3 : +0.5f,+0.5f, 0.0f
//            |
//
//   Rectangle --> Triangle + Triangle
//                 (0,1,2)    (2,1,3)
//   UINT indices[] = { 0,1,2,2,1,3 };
////////////////////////////////////////////////////////
void Rect::CreateVertexBuffer()
{
	//1. ������ �����
	vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = Vector3(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = Vector3(+0.5f, -0.47f, 0.0f);
	vertices[3].Position = Vector3(+0.5f, +0.53f, 0.0f);

	vertices[0].Color    = Color(1.0f, 1.0f, 0.0f, 1.0f);
	vertices[1].Color    = Color(1.0f, 1.0f, 0.0f, 1.0f);
	vertices[2].Color    = Color(1.0f, 1.0f, 0.0f, 1.0f);
	vertices[3].Color    = Color(1.0f, 1.0f, 0.0f, 1.0f);

	m_nVertexCount = 4;

	//2. Device(CPU)�� �����͸� ����
	//   CPU�ڿ��� GPU�ܰ迡 �Ѱ� �ֱ� ���� �غ� �۾��� �Ѵ�

	{
		D3D11_BUFFER_DESC       desc;  // �׻������� ZeroMemory�̿��Ͽ� �ʱ�ȭ �Ͽ��� �Ѵ�
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

		desc.Usage          = D3D11_USAGE_DYNAMIC;      // Buffer�� �����Ҽ� �ְ� ��
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;   // CPU --> GPU
		desc.ByteWidth = sizeof(Vertex) * m_nVertexCount;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;      // ����,Constant(Matrix,float3 etc), ShaderResouce


		D3D11_SUBRESOURCE_DATA  data;
		ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
		data.pSysMem = vertices;

		HRESULT hr = Device->CreateBuffer(&desc, &data, &m_pVertexBuffer);
		assert(SUCCEEDED(hr));
	}
	
	// index
	{
		UINT indices[] = { 0,1,2,2,1,3 };

		D3D11_BUFFER_DESC       desc;                  // �׻������� ZeroMemory�̿��Ͽ� �ʱ�ȭ �Ͽ��� �Ѵ�
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

		desc.Usage = D3D11_USAGE_DYNAMIC;               // Buffer�� �����Ҽ� �ְ� ��
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;   // CPU --> GPU
		desc.ByteWidth = sizeof(UINT) * 6;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;       // ����,Constant(Matrix,float3 etc), ShaderResouce


		D3D11_SUBRESOURCE_DATA  data;
		ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
		data.pSysMem = indices;

		HRESULT hr = Device->CreateBuffer(&desc, &data, &m_pIndexBuffer);
		assert(SUCCEEDED(hr));
	}
}
////////////////////////////////////////////////////////////////
// Update(V,P) --> ���� ���α׷� ( View,Projection)
// World       --> �ڱ��ڽ��� Matrix
///////////////////////////////////////////////////////////////
void Rect::UpdateWorld()
{
	Matrix S, T, R, W;

	D3DXMatrixScaling(&S, m_Scale.x, m_Scale.y, 0.0f);
	D3DXMatrixTranslation(&T, m_Position.x, m_Position.y, 0.0f);
	D3DXMatrixRotationYawPitchRoll(&R, m_Rotation.y*3.141692f / 180.0f,
		m_Rotation.x*3.141692f / 180.0f,
		m_Rotation.z*3.141692f / 180.0f);
	
	W = S * R * T;
	m_pShader->AsMatrix("World")->SetMatrix(W);
}

void Rect::Update(Matrix V, Matrix P)
{
	m_pShader->AsMatrix("View")->SetMatrix(V);
	m_pShader->AsMatrix("Projection")->SetMatrix(P);
	UpdateWorld();
}
void Rect::Render()
{
	UINT  stride = sizeof(Vertex);
	UINT  offset = 0;

	m_pShader->AsVector("Color")->SetFloatVector(m_Color);
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	DeviceContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT,0);
	m_pShader->DrawIndexed(0, 0, 6);
}