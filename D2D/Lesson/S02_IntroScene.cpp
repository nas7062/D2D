#include  "framework.h"
#include  "S02_IntroScene.h"
#include  "Object/AObject.h"
#include  "Object/Rect.h"

////////////////////////////////////////////////////////////////////////
// 생성자 & 소멸자
///////////////////////////////////////////////////////////////////////
S02_IntroScene::S02_IntroScene()
{
	// Scene의 Active 및 Name 설정
	SetActive(false);                               //  스레드에서 생성할 신은  false로 둔다
	SetSceneName("S02_IntroScene");                //  현재 신 Name
	SetNextSceneName("S03_LodingScene");           //  다음 신 Name

	// Object 생성


	wstring  strImageFile = L"/helltaker/CutScene/CutScene (1).png";
	wstring  strShaderFile = L"00_Animation.fx";



	m_pAnimation = new Animation();     // image full로 되어 있음
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
	
//m_cvMessage.push_back(L"어느 날 당신은 위대한 꿈을 가지고 일어났습니다.\n  여악마들이 가득한 하램을 만드는 꿈이죠.");
//m_cvMessage.push_back(L"하지만,당신은 이 꿈이 쉽지 않다는 것을 알고 있었습니다.\n  그리고 목숨을 잃을 만한 위태로운 상황을 닥칠 것도요.");
//m_cvMessage.push_back(L"여악마들이 관련된 일이라면, 그만한 댓가가 따를 수 밖에없지 \n라고 말하며,당신은 지옥으로 여정을 떠나기 시작합니다.");


	m_pRect = new Rect();
	Vector2 size = m_pAnimation->GetRealTextureSize();
	m_pRect->SetScale(size.x*0.8f, size.y*0.8f);
	m_pRect->SetPosition(0.0f, 100.0f);
	m_pRect->SetColor(Color(0.6f, 0.3f, 0.0f, 0.5f));
//	m_pRect->SetRotation(0.0f, 0.0f, 5.0f);

	// CAMERA 속성부여

	//CAMERA->SetObject(m_pPlayer);    // Player를 기준으로 카메라 위치기 변한다

}

S02_IntroScene::~S02_IntroScene()
{
	SAFE_DELETE(m_pAnimation);
	SAFE_DELETE(m_pRect);
}
////////////////////////////////////////////////////////////////////////
// Scene Update
// 1. 카메라 Update 및 View, Projection Matrix 생성
// 2. 
///////////////////////////////////////////////////////////////////////
void S02_IntroScene::Update()
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

		// Mouse의 Position : 윈도우의 좌표
		Vector2 pos = Mouse->GetPosition();
		CAMERA->WCtoVC(pos);
		Main->SetMousePosition(pos);

		rect.top += 20;
		rect.bottom += 20;
		str = L"Mouse(p) : " + to_wstring(pos.x);
		str = str + L", " + to_wstring(pos.y);
		DirectWrite::RenderText(str, rect);

		// 글자
	//	int  no = m_pAnimation->GetCurrentFrameNo();
	//	wstring  str2 = m_cvMessage[no];  // Animation->AnimationClip.m_nCurrent

		wstring str2;


	
		if(m_DelayTime <=3.0f)
		{
			str2 = L"어느 날 당신은 위대한 꿈을 가지고 일어났습니다.\n  여악마들이 가득한 하램을 만드는 꿈이죠.";
			float x = -(str2.length() * 35.0f * 0.5f);
			Vector2   pos2 = Vector2(x, -200.0);
			CAMERA->VCtoWC(pos2);

			DirectWrite::RenderText(str2, pos2, 255, 255, 255, 35.0f);

		}
		if (m_DelayTime >= 3.0f and m_DelayTime  <=6.0f)
		{
			str2 = L"하지만,당신은 이 꿈이 쉽지 않다는 것을 알고 있었습니다.\n  그리고 목숨을 잃을 만한 위태로운 상황을 닥칠 것도요.";
			float x = -(str2.length() * 35.0f * 0.5f);
			Vector2   pos2 = Vector2(x, -200.0);
			CAMERA->VCtoWC(pos2);

			DirectWrite::RenderText(str2, pos2, 255, 255, 255, 35.0f);

		}
		if (m_DelayTime >= 6.0f and m_DelayTime <= 9.0f)
		{
			str2 = L"여악마들이 관련된 일이라면, 그만한 댓가가 따를 수 밖에없지 \n라고 말하며,당신은 지옥으로 여정을 떠나기 시작합니다.";
			float x = -(str2.length() * 35.0f * 0.5f);
			Vector2   pos2 = Vector2(x, -200.0);
			CAMERA->VCtoWC(pos2);

			DirectWrite::RenderText(str2, pos2, 255, 255, 255, 35.0f);

		}



	}
	DirectWrite::GetDC()->EndDraw();
	
}
