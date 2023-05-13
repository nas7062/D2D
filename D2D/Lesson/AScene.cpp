#include  "framework.h"
#include  "AScene.h"
#include  "Object/AObject.h"

////////////////////////////////////////////////////////////////////////
// 생성자 & 소멸자
///////////////////////////////////////////////////////////////////////
AScene::AScene()
{
	// Scene의 Active 및 Name 설정
	SetActive(true);                      //  스레드에서 생성할 신은  false로 둔다
	SetSceneName("AScene");               //  현재 신 Name
	SetNextSceneName("AScene");           //  다음 신 Name

	// Object 생성
	wstring  strImageFile = L"/helltaker/Title/Title (16).png";
	wstring  strShaderFile = L"00_Animation.fx";

	m_pBackground = new Texture(strImageFile, strShaderFile);
	m_pPlayer = new AObject();

	// CAMERA 속성부여

	CAMERA->SetObject(m_pPlayer);    // Player를 기준으로 카메라 위치기 변한다

}

AScene::~AScene()
{
	SAFE_DELETE(m_pBackground);
}
////////////////////////////////////////////////////////////////////////
// Scene Update
// 1. 카메라 Update 및 View, Projection Matrix 생성
// 2. 
///////////////////////////////////////////////////////////////////////
void AScene::Update()
{
	Matrix V, P;

	// View, Projectiion Matrix
	CAMERA->Update();
	V = CAMERA->GetViewMatrix();
	P = CAMERA->GetProjectionMatrix();


	// Mouse의 Position : 윈도우의 좌표
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
