#include  "framework.h"
#include  "S00_DialogSucces.h"
#include  "Base/ObjectManager.h"
#include  "Object/Pandemonica.h"
#include  "Object/AObject.h"
#include  "Object/HellTaker.h"
#include  "Object/Button.h"
#include  "Lesson/S03_LoadingScene.h"

// Succes
void S00_DialogSucces::OnButtonSuccess(int id)
{
	if (id == 1)
	{
		Pandemonica *pObject = (Pandemonica*)OBJECTMANAGER->FindObject("Pandemonica1");
		pObject->SetSuccess(true);

		HellTaker *pObject2 = (HellTaker*)OBJECTMANAGER->FindObject("Helltaker");
		pObject2->SetState(HellTaker::eState::GOAL);
		SetActive(false);
		SCENEMANAGER->SetSceneState();
		return;
	}

	Button *pButton = (Button*)OBJECTMANAGER->FindObject("Button2");
	pButton->SetSelect(true);
}
// Fail
void S00_DialogSucces::OnButtonFail(int id)
{
	if (id == 1)
	{
		S03_LoadingScene *pScene = (S03_LoadingScene*)SCENEMANAGER->GetScene("S03_LoadingScene");
		pScene->SetNextSceneName(m_strNoSuccessScene);
		pScene->m_nState = 0;
		SCENEMANAGER->ChangeScene("S03_LoadingScene");
		SCENEMANAGER->SetSceneState();
		return;
	}

	Button *pButton = (Button*)OBJECTMANAGER->FindObject("Button1");
	pButton->SetSelect(true);


}
////////////////////////////////////////////////////////////////////////
// 생성자 & 소멸자
///////////////////////////////////////////////////////////////////////
S00_DialogSucces::S00_DialogSucces()
{
	// Scene의 Active 및 Name 설정
	SetActive(false);                      //  스레드에서 생성할 신은  false로 둔다
	SetSceneName("S00_DialogSucces");               //  현재 신 Name
	SetNextSceneName("S03_LoadingScene");           //  다음 신 Name

	// Object 생성
	wstring  strImageFile = L"/helltaker/Pandemonica/pand_idle.png";
	wstring  strShaderFile = L"00_Animation.fx";

	m_pPandAnimation1 = new Animation();		// Pandemonica의 초상화를 담기위한 Animation, Pandemonica의 각각 다른 포즈를 클립마다 담는다.
	Texture *pTextrue = m_pPandAnimation1->CreateTexture(strImageFile, strShaderFile);
	
	m_pPandAnimation1->SetScale(0.8f, 0.8f);
	m_pPandAnimation1->SetPosition(0.0f, 100.0f);
	
	

	// Pandemonica 생성
	{
		AnimationClip *pClip = new AnimationClip(AnimationClip::eState::Once);
		m_pPandAnimation1->AddAnimationClip(pClip);
		for (int i = 0; i < 6; i++)
		{
			strImageFile = L"/helltaker/pandemonica/pand_idle.png";	//idle포즈를 저장
			pClip->AddFrame(pTextrue, strImageFile, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f);
		}

		pClip = new AnimationClip(AnimationClip::eState::Loop);
		m_pPandAnimation1->AddAnimationClip(pClip);
		strImageFile = L"/helltaker/pandemonica/pand_flust.png";	//idle포즈를 저장
		pClip->AddFrame(pTextrue, strImageFile, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f);
	
	}

	

		strImageFile = L"/helltaker/Demon1/PanS (1).png";
		
		
		m_pPandAnimation2 = new Animation();		// Pandemonica의 초상화를 담기위한 Animation, Pandemonica의 각각 다른 포즈를 클립마다 담는다.
		pTextrue = m_pPandAnimation2->CreateTexture(strImageFile, strShaderFile);
		
		m_pPandAnimation2->SetScale(0.8f, 0.8f);
		m_pPandAnimation2->SetPosition(0.0f, 100.0f);





	// Pandemonica 생성
	{
		AnimationClip *pClip = new AnimationClip(AnimationClip::eState::Once);
		m_pPandAnimation2->AddAnimationClip(pClip);
		for (int i = 0; i < 6; i++)
		{
			strImageFile = L"/helltaker/Modeus/mod_idle.png";	//idle포즈를 저장
			pClip->AddFrame(pTextrue, strImageFile, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f);
			
			
		}

		pClip = new AnimationClip(AnimationClip::eState::Loop);
		m_pPandAnimation2->AddAnimationClip(pClip);
		strImageFile = L"/helltaker/Modeus/mod_close.png"; 	//idle포즈를 저장
		pClip->AddFrame(pTextrue, strImageFile, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f);
	}


	m_pPandAnimation = m_pPandAnimation1;


	strImageFile = L"/helltaker/kerber.jpg";


	m_pPandAnimation3 = new Animation();		// Pandemonica의 초상화를 담기위한 Animation, Pandemonica의 각각 다른 포즈를 클립마다 담는다.
	pTextrue = m_pPandAnimation3->CreateTexture(strImageFile, strShaderFile);

	m_pPandAnimation3->SetScale(1.2f, 1.2f);
	m_pPandAnimation3->SetPosition(0.0f, 100.0f);
	




	// Pandemonica 생성
	{
		AnimationClip* pClip = new AnimationClip(AnimationClip::eState::Once);
		m_pPandAnimation3->AddAnimationClip(pClip);
		
			strImageFile = L"/helltaker/kerber.jpg";	//idle포즈를 저장
			pClip->AddFrame(pTextrue, strImageFile, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f);

			
		

		pClip = new AnimationClip(AnimationClip::eState::Loop);
		m_pPandAnimation3->AddAnimationClip(pClip);
		strImageFile = L"/helltaker/kerber.jpg"; 	//idle포즈를 저장
		pClip->AddFrame(pTextrue, strImageFile, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f);
	}

	strImageFile = L"/helltaker/Malina/Malina_idle.png";


	m_pPandAnimation4 = new Animation();		// Pandemonica의 초상화를 담기위한 Animation, Pandemonica의 각각 다른 포즈를 클립마다 담는다.
	pTextrue = m_pPandAnimation4->CreateTexture(strImageFile, strShaderFile);

	m_pPandAnimation4->SetScale(1.2f, 1.2f);
	m_pPandAnimation4->SetPosition(0.0f, 100.0f);





	// Pandemonica 생성
	{
		AnimationClip* pClip = new AnimationClip(AnimationClip::eState::Once);
		m_pPandAnimation4->AddAnimationClip(pClip);

		strImageFile = L"/helltaker/Malina/Malina_idle.png";	//idle포즈를 저장
		pClip->AddFrame(pTextrue, strImageFile, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);




		pClip = new AnimationClip(AnimationClip::eState::Once);
		m_pPandAnimation4->AddAnimationClip(pClip);
		strImageFile = L"/helltaker/Malina/Malina_idle.png";	//idle포즈를 저장
		pClip->AddFrame(pTextrue, strImageFile, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	}

	strImageFile = L"/helltaker/Zdrada/Zdrada_idle.png";


	m_pPandAnimation5 = new Animation();		// Pandemonica의 초상화를 담기위한 Animation, Pandemonica의 각각 다른 포즈를 클립마다 담는다.
	pTextrue = m_pPandAnimation5->CreateTexture(strImageFile, strShaderFile);

	m_pPandAnimation5->SetScale(1.2f, 1.2f);
	m_pPandAnimation5->SetPosition(0.0f, 100.0f);





	// Pandemonica 생성
	{
		AnimationClip* pClip = new AnimationClip(AnimationClip::eState::Once);
		m_pPandAnimation5->AddAnimationClip(pClip);

		strImageFile = L"/helltaker/Zdrada/Zdrada_idle.png";	//idle포즈를 저장
		pClip->AddFrame(pTextrue, strImageFile, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);




		pClip = new AnimationClip(AnimationClip::eState::Once);
		m_pPandAnimation5->AddAnimationClip(pClip);
		strImageFile = L"/helltaker/Zdrada/Zdrada_idle.png";	//idle포즈를 저장
		pClip->AddFrame(pTextrue, strImageFile, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	}

	strImageFile = L"/helltaker/Azazel/azazel_idle.jpg";


	m_pPandAnimation6 = new Animation();		// Pandemonica의 초상화를 담기위한 Animation, Pandemonica의 각각 다른 포즈를 클립마다 담는다.
	pTextrue = m_pPandAnimation6->CreateTexture(strImageFile, strShaderFile);

	m_pPandAnimation6->SetScale(2.0f, 2.0f);
	m_pPandAnimation6->SetPosition(0.0f, 100.0f);





	// Pandemonica 생성
	{
		AnimationClip* pClip = new AnimationClip(AnimationClip::eState::Once);
		m_pPandAnimation6->AddAnimationClip(pClip);

		strImageFile = L"/helltaker/Azazel/azazel_idle.jpg";	//idle포즈를 저장
		pClip->AddFrame(pTextrue, strImageFile, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);




		pClip = new AnimationClip(AnimationClip::eState::Once);
		m_pPandAnimation6->AddAnimationClip(pClip);
		strImageFile = L"/helltaker/Azazel/azazel_idle.jpg";	//idle포즈를 저장
		pClip->AddFrame(pTextrue, strImageFile, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	}


	strImageFile = L"/helltaker/justice.png";
	m_pPandAnimation7 = new Animation();		// Pandemonica의 초상화를 담기위한 Animation, Pandemonica의 각각 다른 포즈를 클립마다 담는다.
	pTextrue = m_pPandAnimation->CreateTexture(strImageFile, strShaderFile);

	m_pPandAnimation7->SetScale(1.0f, 1.0f);
	m_pPandAnimation7->SetPosition(0.0f, 100.0f);





	// Pandemonica 생성
	{
		AnimationClip* pClip = new AnimationClip(AnimationClip::eState::Once);
		m_pPandAnimation7->AddAnimationClip(pClip);

		strImageFile = L"/helltaker/justice.png";	//idle포즈를 저장
		pClip->AddFrame(pTextrue, strImageFile, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);




		pClip = new AnimationClip(AnimationClip::eState::Once);
		m_pPandAnimation7->AddAnimationClip(pClip);
		strImageFile = L"/helltaker/justice.png";	//idle포즈를 저장
		pClip->AddFrame(pTextrue, strImageFile, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	}

	Button *pButton1 = (Button*)OBJECTMANAGER->FindObject("Button1");
	pButton1->SetPosition(0, -300.0f);
	pButton1->SetScale(1.0f, 0.8f);
	pButton1->SetSelect(true);
	pButton1->SetButtonString(L"");
	pButton1->SetCallback(bind(&S00_DialogSucces::OnButtonSuccess, this, placeholders::_1));
	


	Button *pButton2 = (Button*)OBJECTMANAGER->FindObject("Button2");
	pButton2->SetPosition(0, -370.0f);
	pButton2->SetScale(1.0f, 0.8f);
	pButton2->SetSelect(false);
	pButton2->SetButtonString(L"Select Game");
	pButton2->SetCallback(bind(&S00_DialogSucces::OnButtonFail, this, placeholders::_1));




	// CAMERA 속성부여

	//CAMERA->SetObject(m_pPlayer);    // Player를 기준으로 카메라 위치기 변한다
}

S00_DialogSucces::~S00_DialogSucces()
{
	SAFE_DELETE(m_pPandAnimation1);
	SAFE_DELETE(m_pPandAnimation2);
}
////////////////////////////////////////////////////////////////////////
// Scene Update
// 1. 카메라 Update 및 View, Projection Matrix 생성
// 2. 
///////////////////////////////////////////////////////////////////////
void S00_DialogSucces::Update()
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

	OBJECTMANAGER->Update("Button1", V, P);
	OBJECTMANAGER->Update("Button2", V, P);




	if (m_nState == eState::DIALOG)
	{
		if (!m_pPandAnimation->IsPlay())
			m_nState = eState::FADE_IN;
	}


//	// 페이드가 끝난 상태라면 화면을 조작할 수 있다. Space 또는 Enter를 눌러 넘어간다.
	if (m_nState == eState::FADE_IN)
	{
		// 13:Enter, ' ':Space
		if (KEYMANAGER->Down(13) || KEYMANAGER->Down(' '))
			m_nState = eState::FADE_OUT;
		else
			;
	}


	if ( m_nState == eState::FADE_OUT)
	{
		Pandemonica *pObject = (Pandemonica*)OBJECTMANAGER->FindObject("Pandemonica1");
		pObject->SetSuccess(true);

		HellTaker *pObject2  = (HellTaker*)OBJECTMANAGER->FindObject("Helltaker");
		pObject2->SetState(HellTaker::eState::GOAL);
		SetActive(false);
		SCENEMANAGER->SetSceneState();
		return;
	}

	if (m_nState == eState::DIALOG)
	{
		m_pPandAnimation->SetPass(5);	// 애니메이션의 투명도를 변화시키는 Pass (0에서 1로 갈수록 투명해진다)
		m_pPandAnimation->SetFloatConstant("Time", 1.0f - F(m_Time / MAX_TIME));
	//	printf("%f\n", 1.0f - F(m_Time / MAX_TIME));
	}

	m_Time = m_Time + TIMEMANAGER->Delta();
	//m_pPandAnimation->SetFloatConstant("Time", 0.0f);

	m_pPandAnimation->SetPlay((UINT)m_nState);
	CAMERA->Update(V, P);
	m_pPandAnimation->Update(V, P);

}

void S00_DialogSucces::Render()
{
	DirectWrite::GetDC()->BeginDraw();
	{
		RECT rect = { 0,0,Main->GetWidth(),Main->GetHeight() };
		D2D1::ColorF color = { 0.0f,0.0f,0.0f,F(m_Time / MAX_TIME) };
		if (m_nState == eState::FADE_OUT)
			color = { 0.0f,0.0f,0.0f,1.0f - F(m_Time / MAX_TIME) };
		DirectWrite::SkewRectangle(rect, color, 0.0f, 0.0f);
	}
	DirectWrite::GetDC()->EndDraw();
	if (m_nState == eState::DIALOG) m_pPandAnimation->Render();
	//CAMERA->Render();

	m_pPandAnimation->Render();

	if (m_nState != eState::DIALOG)
	{
		OBJECTMANAGER->Render("Button1");
		OBJECTMANAGER->Render("Button2");
	}


	//2D Render
	DirectWrite::GetDC()->BeginDraw();
	{
		RECT rect = { 0,0,500,200 };
		wstring  str = L"FPS(ImGui) : " + to_wstring(ImGui::GetIO().Framerate);
		DirectWrite::RenderText(str, rect);

		rect.top += 20;
		rect.bottom += 20;
		str = L"Camera(p) : " + to_wstring(CAMERA->GetPosition().x);
		str = str + L", " + to_wstring(CAMERA->GetPosition().y);
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
		

		
		
	
	
	}
	DirectWrite::GetDC()->EndDraw();

}

void S00_DialogSucces::ChangeScene()
{
	m_nState = eState::DIALOG;
	m_Time = 0.0f;
	str_num = 0;
	page = 0;

	if (m_strNoSuccessScene == "S04_Chapter1")
		m_pPandAnimation = m_pPandAnimation1;
	
	if (m_strNoSuccessScene == "S05_Chapter2")
		m_pPandAnimation = m_pPandAnimation2;
	if (m_strNoSuccessScene == "S06_Chapter3")
		m_pPandAnimation = m_pPandAnimation3;
	if (m_strNoSuccessScene == "S07_Chapter4")
		m_pPandAnimation = m_pPandAnimation4;
	if (m_strNoSuccessScene == "S08_Chapter5")
		m_pPandAnimation = m_pPandAnimation5;
	if (m_strNoSuccessScene == "S09_Chapter6")
		m_pPandAnimation = m_pPandAnimation6;
	if (m_strNoSuccessScene == "S10_Chapter7")
		m_pPandAnimation = m_pPandAnimation7;
	m_pPandAnimation->SetPlay((UINT)m_nState);

	
	Button *pButton1 = (Button*)OBJECTMANAGER->FindObject("Button1");
	pButton1->SetButtonString(m_strButtonName1);

	Button *pButton2 = (Button*)OBJECTMANAGER->FindObject("Button2");
	pButton2->SetButtonString(m_strButtonName2);


	m_cvMessage.clear();
	m_cvMessage.push_back(m_strBanner);

	

}