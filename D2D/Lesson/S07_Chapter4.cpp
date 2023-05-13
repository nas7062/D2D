#include  "framework.h"
#include  "S07_Chapter4.h"
#include  "Object/BackGround.h"
#include  "Object/HellTakerMap.h"
#include  "Object/AObject.h"
#include  "Object/Box.h"
#include  "Object/HellTaker.h"
#include  "Object/Mob.h"
#include  "Lesson/S03_DeathScene.h"
#include  "Object/Fire.h"
#include  "Object/Dust.h"
#include  "Base/ObjectManager.h"
#include  "Object/Bone.h"
#include  "Object/Trap.h"
#include  "Object/Pandemonica.h"

////////////////////////////////////////////////////////////////////////
// 생성자 & 소멸자
///////////////////////////////////////////////////////////////////////
S07_Chapter4::S07_Chapter4()
{

	// Scene의 Active 및 Name 설정
	SetActive(false);                               //  스레드에서 생성할 신은  false로 둔다
	SetSceneName("S07_Chapter4");                //  현재 신 Name
	SetNextSceneName("S04_LodingScene");           //  다음 신 Name

	// Object 생성
	wstring  strImageFile = L"/helltaker/Chapter/Chapter (4).png";
	wstring  strShaderFile = L"00_Animation.fx";

	m_pTexture    = new Texture(strImageFile, strShaderFile);
	m_pBackGround = new BackGround();

	
	// CAMERA 속성부여

	//CAMERA->SetObject(m_pPlayer);    // Player를 기준으로 카메라 위치기 변한다

	//ChangeScene();
}

S07_Chapter4::~S07_Chapter4()
{
	SAFE_DELETE(m_pTexture);
}
////////////////////////////////////////////////////////////////////////
// Scene Update
// 1. 카메라 Update 및 View, Projection Matrix 생성
// 2. 
///////////////////////////////////////////////////////////////////////
void S07_Chapter4::Update()
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

	for(int i = 0; i < 13; i++)
		OBJECTMANAGER->Update("Box" + to_string(i + 1) , V, P);

	OBJECTMANAGER->Update("Pandemonica1", V, P);
	OBJECTMANAGER->Update("Fire1", V, P);
	OBJECTMANAGER->Update("Fire2", V, P);
	OBJECTMANAGER->Update("Fire3", V, P);
	OBJECTMANAGER->Update("Fire4", V, P);

	

	
	OBJECTMANAGER->FindObject("Fire1")->SetPosition(-250.0f, 280.0f);
	OBJECTMANAGER->FindObject("Fire2")->SetPosition(455.0f, 130.0f);

	dynamic_cast<Fire*>(OBJECTMANAGER->FindObject("Fire3"))->SetState(0);
	OBJECTMANAGER->FindObject("Fire3")->SetPosition(155.0f, 330.0f);

	dynamic_cast<Fire*>(OBJECTMANAGER->FindObject("Fire4"))->SetState(0);
	OBJECTMANAGER->FindObject("Fire4")->SetPosition(355.0f, 330.0f);


	OBJECTMANAGER->Update("Trap1", V, P);
//	dynamic_cast<Trap*>(OBJECTMANAGER->FindObject("Trap1"))->SetState(0);
	OBJECTMANAGER->Update("Trap2", V, P);
//	dynamic_cast<Trap*>(OBJECTMANAGER->FindObject("Trap2"))->SetState(0);

	OBJECTMANAGER->Update("Key1", V, P);
	OBJECTMANAGER->Update("LockBox1", V, P);


	HellTaker *pHelltaker = (HellTaker*)OBJECTMANAGER->FindObject("Helltaker");


	if (pHelltaker->GetTry() < 0)
	{
		Scene *pScene = SCENEMANAGER->GetScene("S03_LoadingScene");
		pScene->SetNextSceneName("S07_Chapter4");

		pScene = SCENEMANAGER->GetScene("S03_DeathScene");
		pScene->SetNextSceneName("S03_LoadingScene");

		S03_DeathScene *pDepthScene = (S03_DeathScene*)pScene;
		pDepthScene->SetPoisition(pHelltaker->GetPosition());


		SCENEMANAGER->ChangeScene("S03_DeathScene");
		return;
	}

	
}

void S07_Chapter4::Render()
{
	HellTaker *pHelltaker = (HellTaker*)OBJECTMANAGER->FindObject("Helltaker");

	m_pTexture->Render();
	m_pBackGround->Render();

	OBJECTMANAGER->Render("Fire1");
	OBJECTMANAGER->Render("Fire2");
	OBJECTMANAGER->Render("Fire3");
	OBJECTMANAGER->Render("Fire4");


	OBJECTMANAGER->Render("Trap1");
	OBJECTMANAGER->Render("Trap2");


	for (int i = 0; i < 13; i++)
		OBJECTMANAGER->Render("Box" + to_string(i + 1));



	OBJECTMANAGER->Render("Pandemonica1");
	OBJECTMANAGER->Render("Helltaker");

	OBJECTMANAGER->Render("Key1");
	OBJECTMANAGER->Render("LockBox1");

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

		wstring str3 = L"Ⅳ";
		Vector2 pos3 = Vector2(1250, 450);
		DirectWrite::RenderText(str3, pos3, 255, 255, 255, 180.0f);



//		wstring   str4 = L"Press '1' to move to Stage1";
//		Vector2   pos4 = Vector2(450, 900);
//		DirectWrite::RenderText(str4, pos4, 255, 255, 255, 30.0f);


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

void S07_Chapter4::ChangeScene()
{
	// 픞레이어, Box, Mob, Goal 위치를 초기화

	MAPMANAGER->Clear();
	MAPMANAGER->SetOffSet(-350.0f, 300.f);
	MAPMANAGER->SetSize(9, 7);

	int str_move[] = {01,   21,31,41,
					  02,12,22,32,42,52,62,
					  03,13,23,33,43,53,63,73,
					  04,14,24,34,44,54,64,74,
				       	 15,25,35,45,55       };

	for (auto a : str_move)
	{
		int x = a / 10;
		int y = a % 10;
		MAPMANAGER->SetValue(x, y, HellTakerMap::eState::Move, NULL);
	}

	Vector2 position; 

	HellTaker *pHelltaker = (HellTaker*)OBJECTMANAGER->FindObject("Helltaker");

	pHelltaker->Reset();
	MAPMANAGER->SetValue(0, 1, HellTakerMap::eState::Helltaker, pHelltaker);
	position = MAPMANAGER->GetPosition(0, 1);
	pHelltaker->SetPosition(position);
	pHelltaker->SetTry(23);




	//Malina

	Pandemonica *pPandemonica = (Pandemonica*)OBJECTMANAGER->FindObject("Pandemonica1");
	MAPMANAGER->SetValue(7, 3, HellTakerMap::eState::Goal, OBJECTMANAGER->FindObject("Pandemonica1"));
	position = MAPMANAGER->GetPosition(7, 3);
	OBJECTMANAGER->FindObject("Pandemonica1")->SetPosition(position);
	pPandemonica->SetSuccess(false);
	pPandemonica->SetState(Pandemonica::eState::MALINA);

	MAPMANAGER->SetValue(2, 2, HellTakerMap::eState::Trap, OBJECTMANAGER->FindObject("Trap1"));
	position = MAPMANAGER->GetPosition(2, 2);
	OBJECTMANAGER->FindObject("Trap1")->SetPosition(position);
	OBJECTMANAGER->FindObject("Trap1")->SetActive(false);
	dynamic_cast<Trap*>(OBJECTMANAGER->FindObject("Trap1"))->SetState(1);	
		
	MAPMANAGER->SetValue(3, 2, HellTakerMap::eState::Trap, OBJECTMANAGER->FindObject("Trap2"));
	position = MAPMANAGER->GetPosition(3, 2);
	OBJECTMANAGER->FindObject("Trap2")->SetPosition(position);
	OBJECTMANAGER->FindObject("Trap2")->SetActive(true);
	dynamic_cast<Trap*>(OBJECTMANAGER->FindObject("Trap2"))->SetState(1);


	MAPMANAGER->SetValue(4, 1, HellTakerMap::eState::BOX, OBJECTMANAGER->FindObject("Box1"));
	position = MAPMANAGER->GetPosition(4, 1);
	OBJECTMANAGER->FindObject("Box1")->SetPosition(position);

	MAPMANAGER->SetValue(1, 2, HellTakerMap::eState::BOX, OBJECTMANAGER->FindObject("Box2"));
	position = MAPMANAGER->GetPosition(1, 2);
	OBJECTMANAGER->FindObject("Box2")->SetPosition(position);

	MAPMANAGER->SetValue(3, 2, HellTakerMap::eState::BOX, OBJECTMANAGER->FindObject("Box3"));
	position = MAPMANAGER->GetPosition(3, 2);
	OBJECTMANAGER->FindObject("Box3")->SetPosition(position);

	MAPMANAGER->SetValue(2, 3, HellTakerMap::eState::BOX, OBJECTMANAGER->FindObject("Box4"));
	position = MAPMANAGER->GetPosition(2, 3);
	OBJECTMANAGER->FindObject("Box4")->SetPosition(position);

	MAPMANAGER->SetValue(4, 3, HellTakerMap::eState::BOX, OBJECTMANAGER->FindObject("Box5"));
	position = MAPMANAGER->GetPosition(4, 3);
	OBJECTMANAGER->FindObject("Box5")->SetPosition(position);

	MAPMANAGER->SetValue(5, 3, HellTakerMap::eState::BOX, OBJECTMANAGER->FindObject("Box6"));
	position = MAPMANAGER->GetPosition(5, 3);
	OBJECTMANAGER->FindObject("Box6")->SetPosition(position);

	MAPMANAGER->SetValue(1, 4, HellTakerMap::eState::BOX, OBJECTMANAGER->FindObject("Box7"));
	position = MAPMANAGER->GetPosition(1, 4);
	OBJECTMANAGER->FindObject("Box7")->SetPosition(position);

	MAPMANAGER->SetValue(3, 4, HellTakerMap::eState::BOX, OBJECTMANAGER->FindObject("Box8"));
	position = MAPMANAGER->GetPosition(3, 4);
	OBJECTMANAGER->FindObject("Box8")->SetPosition(position);

	MAPMANAGER->SetValue(5, 4, HellTakerMap::eState::BOX, OBJECTMANAGER->FindObject("Box9"));
	position = MAPMANAGER->GetPosition(5, 4);
	OBJECTMANAGER->FindObject("Box9")->SetPosition(position);

	MAPMANAGER->SetValue(6, 4, HellTakerMap::eState::BOX, OBJECTMANAGER->FindObject("Box10"));
	position = MAPMANAGER->GetPosition(6, 4);
	OBJECTMANAGER->FindObject("Box10")->SetPosition(position);

	MAPMANAGER->SetValue(0, 3, HellTakerMap::eState::BOX, OBJECTMANAGER->FindObject("Box11"));
	position = MAPMANAGER->GetPosition(0, 3);
	OBJECTMANAGER->FindObject("Box11")->SetPosition(position);

	MAPMANAGER->SetValue(2, 5, HellTakerMap::eState::BOX, OBJECTMANAGER->FindObject("Box12"));
	position = MAPMANAGER->GetPosition(2, 5);
	OBJECTMANAGER->FindObject("Box12")->SetPosition(position);

	MAPMANAGER->SetValue(4, 5, HellTakerMap::eState::BOX, OBJECTMANAGER->FindObject("Box13"));
	position = MAPMANAGER->GetPosition(4, 5);
	OBJECTMANAGER->FindObject("Box13")->SetPosition(position);



	MAPMANAGER->SetValue(2, 1, HellTakerMap::eState::Key, OBJECTMANAGER->FindObject("Key1"));
	position = MAPMANAGER->GetPosition(2, 1);
	OBJECTMANAGER->FindObject("Key1")->SetPosition(position);
	OBJECTMANAGER->FindObject("Key1")->SetActive(true);



	MAPMANAGER->SetValue(5, 2, HellTakerMap::eState::LockBox, OBJECTMANAGER->FindObject("LockBox1"));
	position = MAPMANAGER->GetPosition(5, 2);
	OBJECTMANAGER->FindObject("LockBox1")->SetPosition(position);
	OBJECTMANAGER->FindObject("LockBox1")->SetActive(true);


}
