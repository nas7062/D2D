#include  "framework.h"
#include  "S03_DeathScene.h"

////////////////////////////////////////////////////////////////////////
// ������ & �Ҹ���
///////////////////////////////////////////////////////////////////////
S03_DeathScene::S03_DeathScene()
{
	// Scene�� Active �� Name ����
	SetActive(false);                               //  �����忡�� ������ ����  false�� �д�
	SetSceneName("S03_DeathScene");                //  ���� �� Name
	SetNextSceneName(SCENEMANAGER->GetStartSceneName());           //  ���� �� Name

	// Object ����
	wstring  strImageFile = L"/helltaker/Depth/Depth (1).png";
	wstring  strShaderFile = L"00_Animation.fx";

	m_pAnimation = new Animation();     // image full�� �Ǿ� ����
	Texture *pTexture = m_pAnimation->CreateTexture(strImageFile, strShaderFile);

	{
		AnimationClip *pClip = new AnimationClip(AnimationClip::eState::Once);
		m_pAnimation->AddAnimationClip(pClip);

		for (int i = 1; i < 19; i++)
		{
			strImageFile = L"/helltaker/Depth/Depth (" + to_wstring(i) +L").png";
			pClip->AddFrame(pTexture, strImageFile, 0.0f, 0.0f, 0.0f, 0.0f, 0.1f);
		}
	}


	// CAMERA �Ӽ��ο�

	//CAMERA->SetObject(m_pPlayer);    // Player�� �������� ī�޶� ��ġ�� ���Ѵ�

}

S03_DeathScene::~S03_DeathScene()
{
	SAFE_DELETE(m_pAnimation);
}
void S03_DeathScene::ChangeScene()
{
	m_pAnimation->SetPosition(m_Position);
	m_pAnimation->SetPlay(0);
}

////////////////////////////////////////////////////////////////////////
// Scene Update
// 1. ī�޶� Update �� View, Projection Matrix ����
// 2. 
///////////////////////////////////////////////////////////////////////
void S03_DeathScene::Update()
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

	if (!m_pAnimation->IsPlay())
	{
		SCENEMANAGER->ChangeScene(this->GetNextSceneName());
		return;
	}

	CAMERA->Update(V,P);
	m_pAnimation->Update(V, P);


}

void S03_DeathScene::Render()
{
	m_pAnimation->Render();
//	CAMERA->Render();


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

		// Mouse�� Position : �������� ��ǥ
		Vector2 pos = Mouse->GetPosition();
		CAMERA->WCtoVC(pos);
		Main->SetMousePosition(pos);

		rect.top += 20;
		rect.bottom += 20;
		str = L"Mouse(p) : " + to_wstring(pos.x);
		str = str + L", " + to_wstring(pos.y);
		DirectWrite::RenderText(str, rect);
	}
	DirectWrite::GetDC()->EndDraw();
	
}


