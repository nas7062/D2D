#include  "framework.h"
#include  "S02_IntroScene.h"
#include  "Object/AObject.h"
#include  "Object/Rect.h"

////////////////////////////////////////////////////////////////////////
// ������ & �Ҹ���
///////////////////////////////////////////////////////////////////////
S02_IntroScene::S02_IntroScene()
{
	// Scene�� Active �� Name ����
	SetActive(false);                               //  �����忡�� ������ ����  false�� �д�
	SetSceneName("S02_IntroScene");                //  ���� �� Name
	SetNextSceneName("S03_LodingScene");           //  ���� �� Name

	// Object ����


	wstring  strImageFile = L"/helltaker/CutScene/CutScene (1).png";
	wstring  strShaderFile = L"00_Animation.fx";



	m_pAnimation = new Animation();     // image full�� �Ǿ� ����
	m_pAnimation->SetRotation(0.0f, 0.0f,0.0f);
	m_pAnimation->SetScale(0.8f, 0.8f);
	m_pAnimation->SetPosition(0.0f, 100.0f);
	Texture *pTexture = m_pAnimation->CreateTexture(strImageFile, strShaderFile);

	{
		AnimationClip *pClip = new AnimationClip(AnimationClip::eState::Once);
		m_pAnimation->AddAnimationClip(pClip);

		for (int i = 3; i < 6; i++)
		{
			strImageFile = L"/helltaker/CutScene/CutScene (" + to_wstring(i) +L").png";
			pClip->AddFrame(pTexture, strImageFile, 0.0f, 0.0f, 0.0f, 0.0f, 3.0f);

		}
	}
	
//m_cvMessage.push_back(L"��� �� ����� ������ ���� ������ �Ͼ���ϴ�.\n  ���Ǹ����� ������ �Ϸ��� ����� ������.");
//m_cvMessage.push_back(L"������,����� �� ���� ���� �ʴٴ� ���� �˰� �־����ϴ�.\n  �׸��� ����� ���� ���� ���·ο� ��Ȳ�� ��ĥ �͵���.");
//m_cvMessage.push_back(L"���Ǹ����� ���õ� ���̶��, �׸��� �񰡰� ���� �� �ۿ����� \n��� ���ϸ�,����� �������� ������ ������ �����մϴ�.");


	m_pRect = new Rect();
	Vector2 size = m_pAnimation->GetRealTextureSize();
	m_pRect->SetScale(size.x*0.8f, size.y*0.8f);
	m_pRect->SetPosition(0.0f, 100.0f);
	m_pRect->SetColor(Color(0.6f, 0.3f, 0.0f, 0.5f));
//	m_pRect->SetRotation(0.0f, 0.0f, 5.0f);

	// CAMERA �Ӽ��ο�

	//CAMERA->SetObject(m_pPlayer);    // Player�� �������� ī�޶� ��ġ�� ���Ѵ�

}

S02_IntroScene::~S02_IntroScene()
{
	SAFE_DELETE(m_pAnimation);
	SAFE_DELETE(m_pRect);
}
////////////////////////////////////////////////////////////////////////
// Scene Update
// 1. ī�޶� Update �� View, Projection Matrix ����
// 2. 
///////////////////////////////////////////////////////////////////////
void S02_IntroScene::Update()
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

	m_DelayTime = m_DelayTime + TIMEMANAGER->Delta();

	if (!m_pAnimation->IsPlay())
	{
	//	Scene *pScene = SCENEMANAGER->GetScene("S03_LoadingScene");
	//	pScene->SetNextSceneName("S01_IntroScene");

		if (SCENEMANAGER->IsLoadingEnd())
		{
			SCENEMANAGER->ChangeScene("S03_LoadingScene");
			return;
		}


	}

	CAMERA->Update(V,P);
	m_pAnimation->Update(V, P);
	m_pRect->Update(V, P);

}

void S02_IntroScene::Render()
{

	m_pRect->Render();
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

		// ����
	//	int  no = m_pAnimation->GetCurrentFrameNo();
	//	wstring  str2 = m_cvMessage[no];  // Animation->AnimationClip.m_nCurrent

		wstring str2;


	
		if(m_DelayTime <=3.0f)
		{
			str2 = L"��� �� ����� ������ ���� ������ �Ͼ���ϴ�.\n  ���Ǹ����� ������ �Ϸ��� ����� ������.";
			float x = -(str2.length() * 35.0f * 0.5f);
			Vector2   pos2 = Vector2(x, -200.0);
			CAMERA->VCtoWC(pos2);

			DirectWrite::RenderText(str2, pos2, 255, 255, 255, 35.0f);

		}
		if (m_DelayTime >= 3.0f and m_DelayTime  <=6.0f)
		{
			str2 = L"������,����� �� ���� ���� �ʴٴ� ���� �˰� �־����ϴ�.\n  �׸��� ����� ���� ���� ���·ο� ��Ȳ�� ��ĥ �͵���.";
			float x = -(str2.length() * 35.0f * 0.5f);
			Vector2   pos2 = Vector2(x, -200.0);
			CAMERA->VCtoWC(pos2);

			DirectWrite::RenderText(str2, pos2, 255, 255, 255, 35.0f);

		}
		if (m_DelayTime >= 6.0f and m_DelayTime <= 9.0f)
		{
			str2 = L"���Ǹ����� ���õ� ���̶��, �׸��� �񰡰� ���� �� �ۿ����� \n��� ���ϸ�,����� �������� ������ ������ �����մϴ�.";
			float x = -(str2.length() * 35.0f * 0.5f);
			Vector2   pos2 = Vector2(x, -200.0);
			CAMERA->VCtoWC(pos2);

			DirectWrite::RenderText(str2, pos2, 255, 255, 255, 35.0f);

		}



	}
	DirectWrite::GetDC()->EndDraw();
	
}
