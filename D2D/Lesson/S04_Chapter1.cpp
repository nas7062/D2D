#include  "framework.h"
#include  "S04_Chapter1.h"
#include  "Object/BackGround.h"
#include  "Object/HellTakerMap.h"
#include  "Object/AObject.h"
#include  "Object/Box.h"
#include  "Object/HellTaker.h"
#include  "Object/Mob.h"
#include  "Lesson/S03_DeathScene.h"
#include  "Object/Pandemonica.h"
#include  "Object/Fire.h"
#include  "Object/Dust.h"
#include  "Base/ObjectManager.h"
#include  "Object/Bone.h"
#include  "Object/Trap.h"

////////////////////////////////////////////////////////////////////////
// 생성자 & 소멸자
///////////////////////////////////////////////////////////////////////
S04_Chapter1::S04_Chapter1()
{
	// Scene의 Active 및 Name 설정
	SetActive(false);                               //  스레드에서 생성할 신은  false로 둔다
	SetSceneName("S04_Chapter1");                //  현재 신 Name
	SetNextSceneName("S05_Chapter2");           //  다음 신 Name

	// Object 생성
	wstring  strImageFile = L"/helltaker/Chapter/Chapter (1).png";
	wstring  strShaderFile = L"00_Animation.fx";

	m_pTexture    = new Texture(strImageFile, strShaderFile);
	m_pBackGround = new BackGround();
	Audio->AddSound("BGM", "./_Sounds/bgm.wav");
	
	Audio->Play("BGM", 0.3f);
	// CAMERA 속성부여

	//CAMERA->SetObject(m_pPlayer);    // Player를 기준으로 카메라 위치기 변한다

	//ChangeScene();
}

S04_Chapter1::~S04_Chapter1()
{
	SAFE_DELETE(m_pTexture);
}
////////////////////////////////////////////////////////////////////////
// Scene Update
// 1. 카메라 Update 및 View, Projection Matrix 생성
// 2. 
///////////////////////////////////////////////////////////////////////
void S04_Chapter1::Update()
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
	m_pTexture->Update(V, P);
	m_pBackGround->Update(V, P);

	OBJECTMANAGER->Update("Helltaker", V, P);
	OBJECTMANAGER->Update("Mob1", V, P);
	OBJECTMANAGER->Update("Mob2", V, P);
	OBJECTMANAGER->Update("Mob3", V, P);

	OBJECTMANAGER->Update("Box1", V, P);
	OBJECTMANAGER->Update("Box2", V, P);
	OBJECTMANAGER->Update("Box3", V, P);
	OBJECTMANAGER->Update("Box4", V, P);

	OBJECTMANAGER->Update("Pandemonica1", V, P);
	OBJECTMANAGER->Update("Fire1", V, P);
	OBJECTMANAGER->Update("Fire2", V, P);


	OBJECTMANAGER->FindObject("Fire1")->SetPosition(-290.0f, 230.0f);
	OBJECTMANAGER->FindObject("Fire2")->SetPosition(300.0f, -10.0f);


	HellTaker *pHelltaker = (HellTaker*)OBJECTMANAGER->FindObject("Helltaker");


	if (pHelltaker->GetTry() < 0)
	{
		Scene *pScene = SCENEMANAGER->GetScene("S03_LoadingScene");
		pScene->SetNextSceneName("S04_Chapter1");

		pScene = SCENEMANAGER->GetScene("S03_DeathScene");
		pScene->SetNextSceneName("S03_LoadingScene");

		S03_DeathScene *pDepthScene = (S03_DeathScene*)pScene;
		pDepthScene->SetPoisition(pHelltaker->GetPosition());

		SCENEMANAGER->ChangeScene("S03_DeathScene");
		return;
	}

	
}

void S04_Chapter1::Render()
{
	HellTaker *pHelltaker = (HellTaker*)OBJECTMANAGER->FindObject("Helltaker");

	m_pTexture->Render();
	m_pBackGround->Render();

	OBJECTMANAGER->Render("Fire1");
	OBJECTMANAGER->Render("Fire2");

	OBJECTMANAGER->Render("Mob1");
	OBJECTMANAGER->Render("Mob2");
	OBJECTMANAGER->Render("Mob3");


	OBJECTMANAGER->Render("Box1");
	OBJECTMANAGER->Render("Box2");
	OBJECTMANAGER->Render("Box3");
	OBJECTMANAGER->Render("Box4");



	OBJECTMANAGER->Render("Pandemonica1");
	OBJECTMANAGER->Render("Helltaker");


//	pHelltaker->Render();

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

		//  Hit수 Stage
		wstring  str2 = to_wstring(pHelltaker->GetTry());  // Animation->AnimationClip.m_nCurrent
	
		if (str2 == L"0")
			str2 = L"X";
		if (pHelltaker->GetTry() < 10)
		{
			Vector2   pos2 = Vector2(100, 450);
			DirectWrite::RenderText(str2, pos2, 255, 255, 255, 180.0f);
		}
		else
		{
			Vector2   pos2 = Vector2(30, 450);
			DirectWrite::RenderText(str2, pos2, 255, 255, 255, 180.0f);
		}
		wstring   str3 = L"Ⅰ";
		Vector2   pos3 = Vector2(1250, 450);
		DirectWrite::RenderText(str3, pos3, 255, 255, 255, 180.0f);

		
		if (g_bVisibleMap)
		{
			int  Y = MAPMANAGER->GetRowSize();
			int  X = MAPMANAGER->GetColSize();

			for (int y = 0; y < MAPMANAGER->GetRowSize(); y++)
			{
				for (int x = 0; x < MAPMANAGER->GetColSize(); x++)
				{
					Vector2  position = MAPMANAGER->GetPosition(x, y);
					CAMERA->VCtoWC(position);
					wstring   str3 = to_wstring(MAPMANAGER->GetValue(x, y));
					DirectWrite::RenderText(str3, position, 255, 255, 255, 20.0f);

					position.y = position.y - 10;
					str3 = L"(" + to_wstring(x) + L"," + to_wstring(y) + L")";
					DirectWrite::RenderText(str3, position, 255, 0, 255, 20.0f);
				}
			}
		}
		
			


	}
	DirectWrite::GetDC()->EndDraw();
	
}

void S04_Chapter1::ChangeScene()
{
	// 픞레이어, Box, Mob, Goal 위치를 초기화

	MAPMANAGER->Clear();
	MAPMANAGER->SetSize(9, 7);
	MAPMANAGER->SetOffSet(-400.0f, 350.0f);

	MAPMANAGER->SetValue(5, 1, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(6, 1, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(2, 2, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(3, 2, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(4, 2, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(5, 2, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(6, 2, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(2, 3, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(3, 3, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(4, 3, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(5, 3, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(1, 4, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(2, 4, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(1, 5, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(2, 5, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(3, 5, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(4, 5, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(5, 5, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(6, 5, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(1, 6, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(2, 6, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(3, 6, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(4, 6, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(5, 6, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(6, 6, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(7, 6, HellTakerMap::eState::Move, NULL);
	Vector2 position; 

	HellTaker *pHelltaker = (HellTaker*)OBJECTMANAGER->FindObject("Helltaker");

	pHelltaker->Reset();
	MAPMANAGER->SetValue(6, 1, HellTakerMap::eState::Helltaker, pHelltaker);
	position = MAPMANAGER->GetPosition(6, 1);
	pHelltaker->SetPosition(position);
	pHelltaker->SetTry(23);

	// Box

	MAPMANAGER->SetValue(5, 5, HellTakerMap::eState::BOX, OBJECTMANAGER->FindObject("Box1"));
	position = MAPMANAGER->GetPosition(5, 5);
	OBJECTMANAGER->FindObject("Box1")->SetPosition(position);

	MAPMANAGER->SetValue(2, 5, HellTakerMap::eState::BOX, OBJECTMANAGER->FindObject("Box2"));
	position = MAPMANAGER->GetPosition(2, 5);
	OBJECTMANAGER->FindObject("Box2")->SetPosition(position);

	MAPMANAGER->SetValue(2, 6, HellTakerMap::eState::BOX, OBJECTMANAGER->FindObject("Box3"));
	position = MAPMANAGER->GetPosition(2, 6);
	OBJECTMANAGER->FindObject("Box3")->SetPosition(position);

	MAPMANAGER->SetValue(4, 6, HellTakerMap::eState::BOX, OBJECTMANAGER->FindObject("Box4"));
	position = MAPMANAGER->GetPosition(4, 6);
	OBJECTMANAGER->FindObject("Box4")->SetPosition(position);

	// mob

	MAPMANAGER->SetValue(4, 2, HellTakerMap::eState::Mob, OBJECTMANAGER->FindObject("Mob1"));
	position = MAPMANAGER->GetPosition(4, 2);
	OBJECTMANAGER->FindObject("Mob1")->SetPosition(position);
	OBJECTMANAGER->FindObject("Mob1")->SetActive(true);

	MAPMANAGER->SetValue(3, 3, HellTakerMap::eState::Mob, OBJECTMANAGER->FindObject("Mob2"));
	position = MAPMANAGER->GetPosition(3, 3);
	OBJECTMANAGER->FindObject("Mob2")->SetPosition(position);
	OBJECTMANAGER->FindObject("Mob2")->SetActive(true);

	MAPMANAGER->SetValue(5, 3, HellTakerMap::eState::Mob, OBJECTMANAGER->FindObject("Mob3"));
	position = MAPMANAGER->GetPosition(5, 3);
	OBJECTMANAGER->FindObject("Mob3")->SetPosition(position);
	OBJECTMANAGER->FindObject("Mob3")->SetActive(true);


	//Pandemonica

	Pandemonica *pPandemonica = (Pandemonica*)OBJECTMANAGER->FindObject("Pandemonica1");
	MAPMANAGER->SetValue(7, 6, HellTakerMap::eState::Goal, OBJECTMANAGER->FindObject("Pandemonica1"));
	position = MAPMANAGER->GetPosition(7, 6);
	OBJECTMANAGER->FindObject("Pandemonica1")->SetPosition(position);
	pPandemonica->SetSuccess(false);
	pPandemonica->SetState(Pandemonica::eState::PANDEMONICA);

}
