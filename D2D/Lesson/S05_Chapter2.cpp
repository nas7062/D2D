#include  "framework.h"
#include  "S05_Chapter2.h"
#include  "Object/BackGround.h"
#include  "Object/HelltakerMap.h"
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
S05_Chapter2::S05_Chapter2()
{
	// Scene의 Active 및 Name 설정
	SetActive(false);                      //  스레드에서 생성할 신은  false로 둔다
	SetSceneName("S05_Chapter2");               //  현재 신 Name
	SetNextSceneName("S06_Chapter3");           //  다음 신 Name

	// Object 생성
	wstring  strImageFile = L"/helltaker/Chapter/Chapter (2).png";
	wstring  strShaderFile = L"00_Animation.fx";

	m_pTexture = new Texture(strImageFile, strShaderFile);
	m_pBackground = new BackGround();

	m_nTry = 24;
	// CAMERA 속성부여

	//CAMERA->SetObject(m_pPlayer);    // Player를 기준으로 카메라 위치기 변한다

	//ChangeScene();
}

S05_Chapter2::~S05_Chapter2()
{
	SAFE_DELETE(m_pTexture);
}
////////////////////////////////////////////////////////////////////////
// Scene Update
// 1. 카메라 Update 및 View, Projection Matrix 생성
// 2. 
///////////////////////////////////////////////////////////////////////
void S05_Chapter2::Update()
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
	m_pBackground->Update(V, P);

	OBJECTMANAGER->Update("Helltaker", V, P);
	OBJECTMANAGER->Update("Mob1", V, P);
	OBJECTMANAGER->Update("Mob2", V, P);
	OBJECTMANAGER->Update("Mob3", V, P);

	OBJECTMANAGER->Update("Box1", V, P);
	OBJECTMANAGER->Update("Box2", V, P);
	OBJECTMANAGER->Update("Box3", V, P);

	OBJECTMANAGER->Update("Trap1", V, P);
	OBJECTMANAGER->Update("Trap2", V, P);
	OBJECTMANAGER->Update("Trap3", V, P);
	OBJECTMANAGER->Update("Trap4", V, P);
	OBJECTMANAGER->Update("Trap5", V, P);
	OBJECTMANAGER->Update("Trap6", V, P);

	OBJECTMANAGER->Update("Pandemonica1", V, P);
	OBJECTMANAGER->Update("Fire1", V, P);
	OBJECTMANAGER->Update("Fire2", V, P);
	OBJECTMANAGER->Update("Fire3", V, P);


	OBJECTMANAGER->FindObject("Fire1")->SetPosition(-305.0f, 330.0f);
	OBJECTMANAGER->FindObject("Fire2")->SetPosition(205.0f, 385.0f);
	dynamic_cast<Fire*>(OBJECTMANAGER->FindObject("Fire2"))->SetState(0);
	OBJECTMANAGER->FindObject("Fire3")->SetPosition(410.0f, -15.0f);

	HellTaker *pHelltaker = (HellTaker*)OBJECTMANAGER->FindObject("Helltaker");

	if (pHelltaker->GetTry() < 0)
	{
		Scene *pScene = SCENEMANAGER->GetScene("S03_LoadingScene");
		pScene->SetNextSceneName("S05_Chapter2");

		pScene = SCENEMANAGER->GetScene("S03_DeathScene");
		pScene->SetNextSceneName("S03_LoadingScene");

		S03_DeathScene *pDeathScene = (S03_DeathScene*)pScene;
		pDeathScene->SetPoisition(pHelltaker->GetPosition());


		SCENEMANAGER->ChangeScene("S03_DeathScene");
		return;
	}

	OBJECTMANAGER->Update("Trap7",V,P);
	OBJECTMANAGER->Update("Box4",V,P);

}

void S05_Chapter2::Render()
{
	HellTaker *pHelltaker = (HellTaker*)OBJECTMANAGER->FindObject("Helltaker");

	m_pTexture->Render();
	m_pBackground->Render();
	//CAMERA->Render();



	OBJECTMANAGER->Render("Trap1");
	OBJECTMANAGER->Render("Trap2");
	OBJECTMANAGER->Render("Trap3");
	OBJECTMANAGER->Render("Trap4");
	OBJECTMANAGER->Render("Trap5");
	OBJECTMANAGER->Render("Trap6");


	OBJECTMANAGER->Render("Fire1");
	OBJECTMANAGER->Render("Fire2");
	OBJECTMANAGER->Render("Fire3");


	OBJECTMANAGER->Render("Trap7");
	OBJECTMANAGER->Render("Box4");

	OBJECTMANAGER->Render("Mob1");
	OBJECTMANAGER->Render("Mob2");
	OBJECTMANAGER->Render("Mob3");

	OBJECTMANAGER->Render("Box1");
	OBJECTMANAGER->Render("Box2");
	OBJECTMANAGER->Render("Box3");
	OBJECTMANAGER->Render("Pandemonica1");
	OBJECTMANAGER->Render("Helltaker");


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

		// Hit수 Stage
		wstring str2 = to_wstring(pHelltaker->GetTry());	// Animation->AnimationClip.m_nCurrent

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

		wstring str3 = L"Ⅱ";
		Vector2 pos3 = Vector2(1250, 450);
		DirectWrite::RenderText(str3, pos3, 255, 255, 255, 180.0f);


		if (g_bVisibleMap) {
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

void S05_Chapter2::ChangeScene()
{
	// 플레이어, Box, Mob, Goal 위치 초기화

	MAPMANAGER->Clear();
	MAPMANAGER->SetSize(9, 8);
	MAPMANAGER->SetOffSet(-400.0f, 350.0f);

	int str_move[] = {	   21,31,41,51,
						   22,   42,52,62,72,
						13,23,      53,63,73,
						14,24,      54,64,74,
						15,25,      55,65,75,
						            56,66,76 };

	for (auto a : str_move)
	{
		int x = a / 10;
		int y = a % 10;
		MAPMANAGER->SetValue(x, y, HellTakerMap::eState::Move, NULL);
	}
	
	Vector2 position;

	//Helltaker
	{
		int str_ht = { 15 };
		int x = str_ht / 10;
		int y = str_ht % 10;
		string name = "Helltaker";

		HellTaker *pHelltaker = (HellTaker*)OBJECTMANAGER->FindObject(name);
		pHelltaker->Reset();


		MAPMANAGER->SetValue(x, y, HellTakerMap::eState::Helltaker, pHelltaker);
		position = MAPMANAGER->GetPosition(x, y);
		pHelltaker->SetPosition(position);
		pHelltaker->SetTry(25);
	}





	//Box
	{
		int str_box[] = { 53,63,73 };
		for (unsigned int i = 0; i < (sizeof(str_box) / sizeof(str_box[0])); i++)
		{
			int x = str_box[i] / 10;
			int y = str_box[i] % 10;
			string name = "Box" + to_string(i + 1);
			MAPMANAGER->SetValue(x, y, HellTakerMap::eState::BOX, OBJECTMANAGER->FindObject(name));
			position = MAPMANAGER->GetPosition(x, y);
			OBJECTMANAGER->FindObject(name)->SetPosition(position);
		}
	}
	
	//Mob
	{
		int str_mob[] = { 22,65,76 };
		for (unsigned int i = 0; i < (sizeof(str_mob) / sizeof(str_mob[0])); i++)
		{
			int x = str_mob[i] / 10;
			int y = str_mob[i] % 10;
			string name = "Mob" + to_string(i + 1);
			MAPMANAGER->SetValue(x, y, HellTakerMap::eState::Mob, OBJECTMANAGER->FindObject(name));
			position = MAPMANAGER->GetPosition(x, y);
			OBJECTMANAGER->FindObject(name)->SetPosition(position);
			OBJECTMANAGER->FindObject(name)->SetActive(true);
		}
	}

	
	//Pandemonica
	{
		int str_goal[] = { 56 };
		for (unsigned int i = 0; i < (sizeof(str_goal) / sizeof(str_goal[0])); i++)
		{
			int x = str_goal[i] / 10;
			int y = str_goal[i] % 10;
			string name = "Pandemonica" + to_string(i + 1);
			Pandemonica *pPandemonica = (Pandemonica*)OBJECTMANAGER->FindObject(name);
			MAPMANAGER->SetValue(x, y, HellTakerMap::eState::Goal, OBJECTMANAGER->FindObject(name));
			position = MAPMANAGER->GetPosition(x, y);
			OBJECTMANAGER->FindObject(name)->SetPosition(position);
			pPandemonica->SetSuccess(false);
			pPandemonica->SetState(Pandemonica::eState::MODEUS);
		}
	}
	
	//Trap(Active)
	{
		int str_trap[] = { 23,42,52,53,63,64 };
		for (unsigned int i = 0; i < (sizeof(str_trap) / sizeof(str_trap[0])); i++)
		{
			int x = str_trap[i] / 10;
			int y = str_trap[i] % 10;
			string name = "Trap" + to_string(i + 1);
			MAPMANAGER->SetValue(x, y, HellTakerMap::eState::Trap, OBJECTMANAGER->FindObject(name));
			position = MAPMANAGER->GetPosition(x, y);
			OBJECTMANAGER->FindObject(name)->SetPosition(position);
			OBJECTMANAGER->FindObject(name)->SetActive(true);
			dynamic_cast<Trap*>(OBJECTMANAGER->FindObject(name))->SetState(0);
		}
	}






	MAPMANAGER->SetValue(2, 4, HellTakerMap::eState::Trap, OBJECTMANAGER->FindObject("Trap7"));
	position = MAPMANAGER->GetPosition(2, 4);
	OBJECTMANAGER->FindObject("Trap7")->SetPosition(position);
	OBJECTMANAGER->FindObject("Trap7")->SetActive(true);
	dynamic_cast<Trap*>(OBJECTMANAGER->FindObject("Trap7"))->SetState(0);

	string name = "Box" + to_string(4);
	MAPMANAGER->SetValue(2, 4, HellTakerMap::eState::BOX, OBJECTMANAGER->FindObject(name));
	position = MAPMANAGER->GetPosition(2, 4);
	OBJECTMANAGER->FindObject(name)->SetPosition(position);

}
