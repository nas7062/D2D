#include  "framework.h"
#include  "AScene.h"
#include  "Object/AObject.h"

////////////////////////////////////////////////////////////////////////
// ������ & �Ҹ���
///////////////////////////////////////////////////////////////////////
AScene::AScene()
{
	// Scene�� Active �� Name ����
	SetActive(true);                      //  �����忡�� ������ ����  false�� �д�
	SetSceneName("AScene");               //  ���� �� Name
	SetNextSceneName("AScene");           //  ���� �� Name

	// Object ����
	wstring  strImageFile = L"/helltaker/Title/Title (16).png";
	wstring  strShaderFile = L"00_Animation.fx";

	m_pBackground = new Texture(strImageFile, strShaderFile);
	m_pPlayer = new AObject();

	// CAMERA �Ӽ��ο�

	CAMERA->SetObject(m_pPlayer);    // Player�� �������� ī�޶� ��ġ�� ���Ѵ�

}

AScene::~AScene()
{
	SAFE_DELETE(m_pBackground);
}
////////////////////////////////////////////////////////////////////////
// Scene Update
// 1. ī�޶� Update �� View, Projection Matrix ����
// 2. 
///////////////////////////////////////////////////////////////////////
void AScene::Update()
{
	Matrix V, P;

	// View, Projectiion Matrix
	CAMERA->Update();
	V = CAMERA->GetViewMatrix();
	P = CAMERA->GetProjectionMatrix();


	// Mouse�� Position : �������� ��ǥ
	Vector2 pos = Mouse->GetPosition();
	CAMERA->WCtoVC(pos);
	Main->SetMousePosition(pos);

	// Object Update

	CAMERA->Update(V,P);
	m_pBackground->Update(V, P);
	m_pPlayer->Update(V, P);

}

void AScene::Render()
{
	m_pBackground->Render();
	m_pPlayer->Render();
	CAMERA->Render();

	

	//2D Render
	DirectWrite::GetDC()->BeginDraw();
	{
		RECT rect = { 0,0,500,200 };
		wstring  str = L"FPS(ImGui) : " + to_wstring(ImGui::GetIO().Framerate);
		DirectWrite::RenderText(str, rect);

		rect.top    += 20;
		rect.bottom += 20;
		str = L"Camera(p) : " + to_wstring(CAMERA->GetPosition().x);
		str = str + L", "     + to_wstring(CAMERA->GetPosition().y);
		DirectWrite::RenderText(str, rect);
	}
	DirectWrite::GetDC()->EndDraw();
	
}
