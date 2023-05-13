#include  "framework.h"
#include  "S06_Chapter3.h"
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
S06_Chapter3::S06_Chapter3()
{
	// Scene의 Active 및 Name 설정
	SetActive(false);                               //  스레드에서 생성할 신은  false로 둔다
	SetSceneName("S06_Chapter3");                //  현재 신 Name
	SetNextSceneName("S07_Chapter4");           //  다음 신 Name

	// Object 생성
	wstring  strImageFile = L"/helltaker/Chapter/Chapter (3).png";
	wstring  strShaderFile = L"00_Animation.fx";

	m_pTexture    = new Texture(strImageFile, strShaderFile);
	m_pBackGround = new BackGround();

	m_nTry = 32;
	// CAMERA 속성부여

	//CAMERA->SetObject(m_pPlayer);    // Player를 기준으로 카메라 위치기 변한다

	//ChangeScene();
}

S06_Chapter3::~S06_Chapter3()
{
	SAFE_DELETE(m_pTexture);
}
////////////////////////////////////////////////////////////////////////
// Scene Update
// 1. 카메라 Update 및 View, Projection Matrix 생성
// 2. 
///////////////////////////////////////////////////////////////////////
void S06_Chapter3::Update()
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


	OBJECTMANAGER->Update("Pandemonica1", V, P);
	OBJECTMANAGER->Update("Pandemonica2", V, P);
	OBJECTMANAGER->Update("Pandemonica3", V, P);

	OBJECTMANAGER->Update("Fire1", V, P);
	OBJECTMANAGER->Update("Fire2", V, P);


	OBJECTMANAGER->FindObject("Fire1")->SetPosition(-250.0f, -60.0f);
	OBJECTMANAGER->FindObject("Fire2")->SetPosition(350.0f, 290.0f);


	OBJECTMANAGER->Update("Trap1", V, P);
	OBJECTMANAGER->Update("Trap2", V, P);
	OBJECTMANAGER->Update("Trap3", V, P);
	OBJECTMANAGER->Update("Trap4", V, P);
	OBJECTMANAGER->Update("Trap5", V, P);
	OBJECTMANAGER->Update("Trap6", V, P);
	OBJECTMANAGER->Update("Trap7", V, P);
	OBJECTMANAGER->Update("Trap8", V, P);


	OBJECTMANAGER->Update("Key1", V, P);
	OBJECTMANAGER->Update("LockBox1", V, P);

	HellTaker *pHelltaker = (HellTaker*)OBJECTMANAGER->FindObject("Helltaker");


	if (pHelltaker->GetTry() < 0)
	{
		Scene *pScene = SCENEMANAGER->GetScene("S03_LoadingScene");
		pScene->SetNextSceneName("S06_Chapter3");

		pScene = SCENEMANAGER->GetScene("S03_DeathScene");
		pScene->SetNextSceneName("S03_LoadingScene");

		S03_DeathScene *pDepthScene = (S03_DeathScene*)pScene;
		pDepthScene->SetPoisition(pHelltaker->GetPosition());

		SCENEMANAGER->ChangeScene("S03_DeathScene");
		return;
	}

	
}

void S06_Chapter3::Render()
{
	HellTaker *pHelltaker = (HellTaker*)OBJECTMANAGER->FindObject("Helltaker");

	m_pTexture->Render();
	m_pBackGround->Render();

	OBJECTMANAGER->Render("Fire1");
	OBJECTMANAGER->Render("Fire2");

	OBJECTMANAGER->Render("Mob1");
	OBJECTMANAGER->Render("Mob2");


	OBJECTMANAGER->Render("Trap1");
	OBJECTMANAGER->Render("Trap2");
	OBJECTMANAGER->Render("Trap3");
	OBJECTMANAGER->Render("Trap4");
	OBJECTMANAGER->Render("Trap5");
	OBJECTMANAGER->Render("Trap6");
	OBJECTMANAGER->Render("Trap7");
	OBJECTMANAGER->Render("Trap8");


	OBJECTMANAGER->Render("Key1");
	OBJECTMANAGER->Render("LockBox1");


	OBJECTMANAGER->Render("Pandemonica1");
	OBJECTMANAGER->Render("Pandemonica2");
	OBJECTMANAGER->Render("Pandemonica3");
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

		wstring str3 = L"Ⅲ";
		Vector2 pos3 = Vector2(1250, 450);
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

void S06_Chapter3::ChangeScene()
{
	// 픞레이어, Box, Mob, Goal 위치를 초기화

	MAPMANAGER->Clear();
	MAPMANAGER->SetSize(9, 7);
	MAPMANAGER->SetOffSet(-360.0f, 310.0f);

	MAPMANAGER->SetValue(3, 0, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(4, 0, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(5, 0, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(6, 0, HellTakerMap::eState::Move, NULL);

	MAPMANAGER->SetValue(6, 1, HellTakerMap::eState::Move, NULL);

	for(int i=2; i<=7; i++)
	  MAPMANAGER->SetValue(i, 2, HellTakerMap::eState::Move, NULL);

	MAPMANAGER->SetValue(2, 3, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(4, 3, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(6, 3, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(7, 3, HellTakerMap::eState::Move, NULL);

	for (int i = 2; i <= 6; i++)
		MAPMANAGER->SetValue(i, 4, HellTakerMap::eState::Move, NULL);

	MAPMANAGER->SetValue(0, 5, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(2, 5, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(4, 5, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(6, 5, HellTakerMap::eState::Move, NULL);

	for (int i = 0; i <= 6; i++)
		MAPMANAGER->SetValue(i, 6, HellTakerMap::eState::Move, NULL);


	Vector2 position; 

	HellTaker *pHelltaker = (HellTaker*)OBJECTMANAGER->FindObject("Helltaker");

	pHelltaker->Reset();
	MAPMANAGER->SetValue(7, 2, HellTakerMap::eState::Helltaker, pHelltaker);
	position = MAPMANAGER->GetPosition(7, 2);
	pHelltaker->SetPosition(position);
	pHelltaker->SetTry(32);

	
	// mob

	MAPMANAGER->SetValue(4, 4, HellTakerMap::eState::Mob, OBJECTMANAGER->FindObject("Mob1"));
	position = MAPMANAGER->GetPosition(4, 4);
	OBJECTMANAGER->FindObject("Mob1")->SetPosition(position);
	OBJECTMANAGER->FindObject("Mob1")->SetActive(true);

	MAPMANAGER->SetValue(5, 6, HellTakerMap::eState::Mob, OBJECTMANAGER->FindObject("Mob2"));
	position = MAPMANAGER->GetPosition(5, 6);
	OBJECTMANAGER->FindObject("Mob2")->SetPosition(position);
	OBJECTMANAGER->FindObject("Mob2")->SetActive(true);



	//Pandemonica

	Pandemonica *pPandemonica = (Pandemonica*)OBJECTMANAGER->FindObject("Pandemonica1");
	MAPMANAGER->SetValue(3, 0, HellTakerMap::eState::Goal, OBJECTMANAGER->FindObject("Pandemonica1"));
	position = MAPMANAGER->GetPosition(3, 0);
	OBJECTMANAGER->FindObject("Pandemonica1")->SetPosition(position);
	pPandemonica->SetSuccess(false);
	pPandemonica->SetState(Pandemonica::eState::DEMON7);

	Pandemonica *pPandemonica2 = (Pandemonica*)OBJECTMANAGER->FindObject("Pandemonica2");
	MAPMANAGER->SetValue(4, 0, HellTakerMap::eState::Goal, OBJECTMANAGER->FindObject("Pandemonica2"));
	position = MAPMANAGER->GetPosition(4, 0);
	OBJECTMANAGER->FindObject("Pandemonica2")->SetPosition(position);
	pPandemonica2->SetSuccess(false);
	pPandemonica2->SetState(Pandemonica::eState::DEMON7);

	Pandemonica *pPandemonica3 = (Pandemonica*)OBJECTMANAGER->FindObject("Pandemonica3");
	MAPMANAGER->SetValue(5, 0, HellTakerMap::eState::Goal, OBJECTMANAGER->FindObject("Pandemonica3"));
	position = MAPMANAGER->GetPosition(5, 0);
	OBJECTMANAGER->FindObject("Pandemonica3")->SetPosition(position);
	pPandemonica3->SetSuccess(false);
	pPandemonica3->SetState(Pandemonica::eState::DEMON7);


	MakeTrap(1, 3, 2, 0);
	MakeTrap(2, 4, 2, 0);
	MakeTrap(3, 2, 3, 0);
	MakeTrap(4, 4, 3, 0);
	MakeTrap(5, 5, 4, 0);
	MakeTrap(6, 6, 4, 0);
	MakeTrap(7, 2, 5, 0);
	MakeTrap(8, 4, 5, 0);


	MAPMANAGER->SetValue(0, 5, HellTakerMap::eState::Key, OBJECTMANAGER->FindObject("Key1"));
	position = MAPMANAGER->GetPosition(0, 5);
	OBJECTMANAGER->FindObject("Key1")->SetPosition(position);

	MAPMANAGER->SetValue(6, 1, HellTakerMap::eState::LockBox, OBJECTMANAGER->FindObject("LockBox1"));
	position = MAPMANAGER->GetPosition(6, 1);
	OBJECTMANAGER->FindObject("LockBox1")->SetPosition(position);


}

void S06_Chapter3::MakeTrap(int id, int x, int y, int state)
{
	string name = "Trap" + to_string(id);
	MAPMANAGER->SetValue(x, y, HellTakerMap::eState::Trap, OBJECTMANAGER->FindObject(name));
	Vector2 position = MAPMANAGER->GetPosition(x, y);
	OBJECTMANAGER->FindObject(name)->SetPosition(position);
	OBJECTMANAGER->FindObject(name)->SetActive(true);
	dynamic_cast<Trap*>(OBJECTMANAGER->FindObject(name))->SetState(state);
}


//Trap(Active)
//{
//	int str_trap[] = { 23,42,52,53,63,64 };
//	for (unsigned int i = 0; i < (sizeof(str_trap) / sizeof(str_trap[0])); i++)
//	{
//		int x = str_trap[i] / 10;
//		int y = str_trap[i] % 10;
//		string name = "Trap" + to_string(i + 1);
//		MAPMANAGER->SetValue(x, y, HellTakerMap::eState::Trap, OBJECTMANAGER->FindObject(name));
//		position = MAPMANAGER->GetPosition(x, y);
//		OBJECTMANAGER->FindObject(name)->SetPosition(position);
//		OBJECTMANAGER->FindObject(name)->SetActive(true);
//		dynamic_cast<Trap*>(OBJECTMANAGER->FindObject(name))->SetState(0);
//	}
//}