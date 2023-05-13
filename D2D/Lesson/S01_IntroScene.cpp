#include  "framework.h"
#include  "S01_IntroScene.h"
#include  "Object/Button.h"
#include  "Base/ObjectManager.h"

void S01_IntroScene::OnButton1(int id)
{
	if (id == 1)
	{
		while(!SCENEMANAGER->IsLoadingEnd())
		SCENEMANAGER->ChangeScene("S04_Chapter1");
		return;
	}

	Button *pButton = (Button*)OBJECTMANAGER->FindObject("Button2");
	pButton->SetSelect(true);
	printf("1 %d \n",id);
}
void S01_IntroScene::OnButton2(int id)
{
	Button *pButton = (Button*)OBJECTMANAGER->FindObject("Button3");
	pButton->SetSelect(true);
	printf("2 %d \n", id);
}
void S01_IntroScene::OnButton3(int id)
{
	if (id == 1)
	{
		PostQuitMessage(0);
		return;
	}


	Button *pButton = (Button*)OBJECTMANAGER->FindObject("Button1");
	pButton->SetSelect(true);
	printf("3 %d \n", id);
}
////////////////////////////////////////////////////////////////////////
// 생성자 & 소멸자
///////////////////////////////////////////////////////////////////////
S01_IntroScene::S01_IntroScene()
{
//	Audio->AddSound("BGM", "./_Sounds/bgm.wav");
//	Audio->Play("BGM", 1.0f);
	// Scene의 Active 및 Name 설정
	SetActive(true);                      //  스레드에서 생성할 신은  false로 둔다
	SetSceneName("S01_IntroScene");               //  현재 신 Name
	SetNextSceneName("S02_IntroScene");           //  다음 신 Name

	for (int i = 0; i < 4; i++)
	{
		Button *pButton = new Button();
		string name = "Button" + to_string(i + 1);
		OBJECTMANAGER->AddObject(name, pButton);
	}


	// Object 생성
	wstring  strImageFile = L"/helltaker/Dialog/DialogBGAbyss.png";
	wstring  strShaderFile = L"00_Animation.fx";

	m_pBackground[0] = new Texture(strImageFile, strShaderFile);
	m_pBackground[1] = new Texture(strImageFile, strShaderFile);

	Vector2 size = m_pBackground[0]->GetRealTextureSize();
	m_pBackground[1]->SetPosition(size.x-2, 0.0f);
	
		strImageFile = L"/helltaker/Dialog/BeelFly.png";
		m_pBeelFly = new Texture(strImageFile, strShaderFile);
	
		size.y = 0.0f - size.y * 0.5f + m_pBeelFly->GetRealTextureSize().y * 0.5f;

		m_pBeelFly->SetPosition(0.0f, size.y);
	
	// CAMERA 속성부여

//	CAMERA->SetObject(m_pPlayer);    // Player를 기준으로 카메라 위치기 변한다

	Button *pButton1 = (Button*)OBJECTMANAGER->FindObject("Button1");
	pButton1->SetPosition(0,-200.0f);
	pButton1->SetScale(0.6f, 0.8f);
	pButton1->SetSelect(true);
	pButton1->SetButtonString(L"새 게임");
	pButton1->SetCallback(bind(&S01_IntroScene::OnButton1, this,placeholders::_1));
	


	Button *pButton2 = (Button*)OBJECTMANAGER->FindObject("Button2");
	pButton2->SetPosition(0, -270.0f);
	pButton2->SetScale(0.6f, 0.8f);
	pButton2->SetSelect(false);
	pButton2->SetButtonString(L"챕터 선택");
	pButton2->SetCallback(bind(&S01_IntroScene::OnButton2, this, placeholders::_1));





	Button *pButton3 = (Button*)OBJECTMANAGER->FindObject("Button3");
	pButton3->SetPosition(0, -340.0f);
	pButton3->SetScale(0.6f, 0.8f);
	pButton3->SetSelect(false);
	pButton3->SetButtonString(L"나가기 ");
	pButton3->SetCallback(bind(&S01_IntroScene::OnButton3, this, placeholders::_1));

	
}

S01_IntroScene::~S01_IntroScene()
{
	SAFE_DELETE(m_pBackground[0]);
	SAFE_DELETE(m_pBackground[1]);
	SAFE_DELETE(m_pBeelFly);

//	if (m_pBackground[0])
//	{
//		delete m_pBackground[0];
//		m_pBackground[0] = nullptr;
//	}


}
////////////////////////////////////////////////////////////////////////
// Scene Update
// 1. 카메라 Update 및 View, Projection Matrix 생성
// 2. 
///////////////////////////////////////////////////////////////////////
void S01_IntroScene::Update()
{
	Matrix V, P;

	// 1. View, Projectiion Matrix
	CAMERA->Update();
	V = CAMERA->GetViewMatrix();
	P = CAMERA->GetProjectionMatrix();


	// 2. Object Update
	CAMERA->Update(V,P);

	// 3. 무한배경

	m_pBackground[0]->SetPosition(m_pBackground[0]->GetPosition().x -1.0f, 0.0f);
	m_pBackground[1]->SetPosition(m_pBackground[1]->GetPosition().x - 1.0f, 0.0f);

	for (int i = 0; i < 2; i++)
	{
		Vector2 pos  = m_pBackground[i]->GetPosition();
		Vector2 size = m_pBackground[i]->GetRealTextureSize();

		if (pos.x <= -size.x)  // 2Pixel이 겹치게끔
		{
			if( i == 0)
			 m_pBackground[0]->SetPosition(m_pBackground[1]->GetPosition().x+  size.x*0.5f - 2.0f, 0.0f);
			else
			 m_pBackground[1]->SetPosition(m_pBackground[0]->GetPosition().x + size.x*0.5f - 2.0f, 0.0f);
		}
	}

	// 4. DelayTime

	m_DelayTime = m_DelayTime + TIMEMANAGER->Delta();

	if (m_DelayTime >= 12.0f)
	{
		SCENEMANAGER->ChangeScene("S02_IntroScene");
		return;
	}

	
	m_pBackground[0]->Update(V, P);
	m_pBackground[1]->Update(V, P);
	if (m_DelayTime >= 2.5f)
	{
		m_pBeelFly->Update(V, P);
		
	}
	if (m_DelayTime >= 5.5f)
	{
		OBJECTMANAGER->Update("Button1", V, P);
		OBJECTMANAGER->Update("Button2", V, P);
		OBJECTMANAGER->Update("Button3", V, P);
	}
	
}
///////////////////////////////////////////////////////////
// Rendering
//////////////////////////////////////////////////////////
void S01_IntroScene::Render()
{
	m_pBackground[0]->Render();
	m_pBackground[1]->Render();

	CAMERA->Render();
	
	
	if (m_DelayTime >= 2.5f)
	{
		m_pBeelFly->Render();
		
	}
	if (m_DelayTime >= 5.5f)
	{
		OBJECTMANAGER->Render("Button1");
		OBJECTMANAGER->Render("Button2");
		OBJECTMANAGER->Render("Button3");
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

		// 글자

		wstring  str2;

		if (m_DelayTime <= 2.5f)
		{
			str2 = L"당신은 주변이 심연으로 \n 둘러싸인것을 알아차립니다";
			float x = -(str2.length() * 45.0f * 0.5f);
			Vector2   pos2 = Vector2(x, -200.0);
			CAMERA->VCtoWC(pos2);

			DirectWrite::RenderText(str2, pos2, 255, 255, 255, 45.0f);
			str2.clear();
		}

		if (m_DelayTime >= 2.5f && m_DelayTime <=5.5f)
		{
			
			str2 = L"환영하네 인간이여.너무 놀라지 말게나.\n 자네의 친구 베엘제붑일세";
			float x = -(str2.length() * 35.0f * 0.5f);
			Vector2   pos2 = Vector2(x, -150.0);
			CAMERA->VCtoWC(pos2);

			DirectWrite::RenderText(str2, pos2, 255, 255, 255, 35.0f);
			
			
		}

		if (m_DelayTime >= 2.5f)
			{

					str2 = L".위대한 파리, 베엘제붑.";
					float x = -(str2.length() * 35.0f * 0.5f);
					Vector2   pos2 = Vector2(x, -100.0);
					CAMERA->VCtoWC(pos2);

					DirectWrite::RenderText(str2, pos2, 255, 0, 0, 35.0f);
					
			}
				DirectWrite::GetDC()->EndDraw();
			
	}	
}
