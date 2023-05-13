#include  "framework.h"
#include  "S03_LoadingScene.h"

////////////////////////////////////////////////////////////////////////
// ������ & �Ҹ���
///////////////////////////////////////////////////////////////////////
S03_LoadingScene::S03_LoadingScene()
{
	// Scene�� Active �� Name ����
	SetActive(false);                               //  �����忡�� ������ ����  false�� �д�
	SetSceneName("S03_LoadingScene");                //  ���� �� Name
	SetNextSceneName(SCENEMANAGER->GetStartSceneName());           //  ���� �� Name

	// Object ����
	wstring  strImageFile = L"/helltaker/Title/DialogGameOver (1).png";
	wstring  strShaderFile = L"00_Animation.fx";

	m_pAnimation = new Animation();     // image full�� �Ǿ� ����
	Texture *pTexture = m_pAnimation->CreateTexture(strImageFile, strShaderFile);

	{
		AnimationClip *pClip = new AnimationClip(AnimationClip::eState::Once);
		m_pAnimation->AddAnimationClip(pClip);

		for (int i = 1; i < 10; i++)
		{	
			strImageFile = L"/helltaker/Title/DialogGameOver (" + to_wstring(i) + L").png";
			pClip->AddFrame(pTexture, strImageFile, 0.0f, 0.0f, 0.0f, 0.0f, 0.1f);
		}
	}


	{
		AnimationClip *pClip = new AnimationClip(AnimationClip::eState::Once);
		m_pAnimation->AddAnimationClip(pClip);

		for (int i = 1; i < 17; i++)
		{
			strImageFile = L"/helltaker/Title/Title (" + to_wstring(i) +L").png";
			pClip->AddFrame(pTexture, strImageFile, 0.0f, 0.0f, 0.0f, 0.0f, 0.1f);
		}
	}


	// CAMERA �Ӽ��ο�

	//CAMERA->SetObject(m_pPlayer);    // Player�� �������� ī�޶� ��ġ�� ���Ѵ�

}

S03_LoadingScene::~S03_LoadingScene()
{
	SAFE_DELETE(m_pAnimation);
}
void S03_LoadingScene::ChangeScene()
{
	m_pAnimation->SetPlay(m_nState);
}

////////////////////////////////////////////////////////////////////////
// Scene Update
// 1. ī�޶� Update �� View, Projection Matrix ����
// 2. 
///////////////////////////////////////////////////////////////////////
void S03_LoadingScene::Update()
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

	switch (m_nState)
	{
	case 0:
		m_pAnimation->GetTexture()->SetImageSize(Vector2(1568.0f,480.0f));
		break;
	case 1:
		m_pAnimation->GetTexture()->SetImageSize(Vector2(1924.0f, 1084.0f));
		break;
	}



	// Object Update

	if (!m_pAnimation->IsPlay())
	{
		m_nState++;
		if (m_nState == 2)
		{
			SCENEMANAGER->ChangeScene(this->GetNextSceneName());
			m_nState = 1;
			return;
		}

	}

	m_pAnimation->SetPlay(m_nState);
	CAMERA->Update(V,P);
	m_pAnimation->Update(V, P);


}

void S03_LoadingScene::Render()
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


