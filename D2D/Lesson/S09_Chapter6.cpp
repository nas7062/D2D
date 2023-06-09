#include  "framework.h"
#include  "S09_Chapter6.h"
#include  "Object/BackGround.h"
#include  "Object/HellTakerMap.h"
#include  "Object/AObject.h"
#include  "Object/Box.h"
#include  "Object/LockBox.h"
#include  "Object/HellTaker.h"
#include  "Object/Mob.h"
#include  "Lesson/S03_DeathScene.h"
#include  "Object/Azazel.h"
#include  "Object/Fire.h"
#include  "Object/Dust.h"
#include  "Base/ObjectManager.h"
#include  "Object/Bone.h"
#include  "Object/Trap.h"
#include  "Object/Key.h"
#include  "Object/Pandemonica.h"


////////////////////////////////////////////////////////////////////////
// 생성자 & 소멸자
///////////////////////////////////////////////////////////////////////
S09_Chapter6::S09_Chapter6()
{
	// Scene의 Active 및 Name 설정
	SetActive(false);                               //  스레드에서 생성할 신은  false로 둔다
	SetSceneName("S09_Chapter6");                //  현재 신 Name
	SetNextSceneName("S06_Chapter6");           //  다음 신 Name

	// Object 생성
	wstring  strImageFile = L"/helltaker/Chapter/Chapter (6).png";
	wstring  strShaderFile = L"00_Animation.fx";

	m_pTexture    = new Texture(strImageFile, strShaderFile);
	m_pBackGround = new BackGround();
	
	// CAMERA 속성부여

	//CAMERA->SetObject(m_pPlayer);    // Player를 기준으로 카메라 위치기 변한다

	//ChangeScene();
}

S09_Chapter6::~S09_Chapter6()
{
	SAFE_DELETE(m_pTexture);
}
////////////////////////////////////////////////////////////////////////
// Scene Update
// 1. 카메라 Update 및 View, Projection Matrix 생성
// 2. 
///////////////////////////////////////////////////////////////////////
void S09_Chapter6::Update()
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

	OBJECTMANAGER->Update("Box1", V, P);
	OBJECTMANAGER->Update("Box2", V, P);
	OBJECTMANAGER->Update("Box3", V, P);
	OBJECTMANAGER->Update("Box4", V, P);
	OBJECTMANAGER->Update("Box5", V, P);
	OBJECTMANAGER->Update("Box6", V, P);
	OBJECTMANAGER->Update("Box7", V, P);
	OBJECTMANAGER->Update("Box8", V, P);

	OBJECTMANAGER->Update("LockBox1", V, P);
		
	OBJECTMANAGER->Update("Fire1", V, P);
	OBJECTMANAGER->Update("Fire2", V, P);

	OBJECTMANAGER->Update("Trap1", V, P);
	OBJECTMANAGER->Update("Trap2", V, P);

	OBJECTMANAGER->FindObject("Fire1")->SetPosition(-305.0f, 330.0f);
	OBJECTMANAGER->FindObject("Fire2")->SetPosition(205.0f, 275.0f);

	OBJECTMANAGER->Update("Key1", V, P);

	OBJECTMANAGER->Update("Pandemonica1", V, P);

	HellTaker *pHelltaker = (HellTaker*)OBJECTMANAGER->FindObject("Helltaker");


	if (pHelltaker->GetTry() < 0 || KEYMANAGER->Down('R'))
	{
		Scene *pScene = SCENEMANAGER->GetScene("S03_LoadingScene");
		pScene->SetNextSceneName("S09_Chapter6");

		pScene = SCENEMANAGER->GetScene("S03_DeathScene");
		pScene->SetNextSceneName("S03_LoadingScene");

		S03_DeathScene *pDepthScene = (S03_DeathScene*)pScene;
		pDepthScene->SetPoisition(pHelltaker->GetPosition());


		SCENEMANAGER->ChangeScene("S03_DeathScene");
		return;
	}

	
}

void S09_Chapter6::Render()
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

	OBJECTMANAGER->Render("Key1");

	OBJECTMANAGER->Render("Box1");
	OBJECTMANAGER->Render("Box2");
	OBJECTMANAGER->Render("Box3");
	OBJECTMANAGER->Render("Box4");
	OBJECTMANAGER->Render("Box5");
	OBJECTMANAGER->Render("Box6");
	OBJECTMANAGER->Render("Box7");
	OBJECTMANAGER->Render("Box8");



	OBJECTMANAGER->Render("LockBox1");



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

		wstring str3 = L"Ⅵ";
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
					DirectWrite::RenderText(str3, position, 0, 0, 255, 20.0f);

					position.y = position.y - 10;
					str3 = L"(" + to_wstring(x) + L"," + to_wstring(y) + L")";
					DirectWrite::RenderText(str3, position, 255, 0, 255, 20.0f);
				}
			}
		}
		
			


	}
	DirectWrite::GetDC()->EndDraw();
	
}

void S09_Chapter6::ChangeScene()
{
	// 픞레이어, Box, Mob, Goal 위치를 초기화
	
	MAPMANAGER->Clear();
	MAPMANAGER->SetOffSet(-300.0f, 350.0f);
	MAPMANAGER->SetSize(7, 8);
	
	
	MAPMANAGER->SetValue(1, 0, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(2, 0, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(3, 0, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(1, 1, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(2, 1, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(3, 1, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(0, 2, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(1, 2, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(2, 2, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(3, 2, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(1, 3, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(2, 3, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(3, 3, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(4, 3, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(1, 4, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(3, 4, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(4, 4, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(5, 4, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(6, 4, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(1, 5, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(2, 5, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(3, 5, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(4, 5, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(5, 5, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(4, 6, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(5, 6, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(6, 6, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(4, 7, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(5, 7, HellTakerMap::eState::Move, NULL);


	Vector2 position; 

	HellTaker *pHelltaker = (HellTaker*)OBJECTMANAGER->FindObject("Helltaker");

	pHelltaker->Reset();
	MAPMANAGER->SetValue(2, 0, HellTakerMap::eState::Helltaker, pHelltaker);
	position = MAPMANAGER->GetPosition(2, 0);
	pHelltaker->SetPosition(position);
	pHelltaker->SetTry(43);
	
	// Box

	MAPMANAGER->SetValue(1, 1, HellTakerMap::eState::BOX, OBJECTMANAGER->FindObject("Box1"));
	position = MAPMANAGER->GetPosition(1, 1);
	OBJECTMANAGER->FindObject("Box1")->SetPosition(position);

	MAPMANAGER->SetValue(2, 1, HellTakerMap::eState::BOX, OBJECTMANAGER->FindObject("Box2"));
	position = MAPMANAGER->GetPosition(2, 1);
	OBJECTMANAGER->FindObject("Box2")->SetPosition(position);

	MAPMANAGER->SetValue(3, 1, HellTakerMap::eState::BOX, OBJECTMANAGER->FindObject("Box3"));
	position = MAPMANAGER->GetPosition(3, 1);
	OBJECTMANAGER->FindObject("Box3")->SetPosition(position);

	MAPMANAGER->SetValue(2, 3, HellTakerMap::eState::BOX, OBJECTMANAGER->FindObject("Box4"));
	position = MAPMANAGER->GetPosition(2, 3);
	OBJECTMANAGER->FindObject("Box4")->SetPosition(position);

	MAPMANAGER->SetValue(3, 4, HellTakerMap::eState::BOX, OBJECTMANAGER->FindObject("Box5"));
	position = MAPMANAGER->GetPosition(3, 4);
	OBJECTMANAGER->FindObject("Box5")->SetPosition(position);

	MAPMANAGER->SetValue(4, 4, HellTakerMap::eState::BOX, OBJECTMANAGER->FindObject("Box6"));
	position = MAPMANAGER->GetPosition(4, 4);
	OBJECTMANAGER->FindObject("Box6")->SetPosition(position);

	MAPMANAGER->SetValue(3, 5, HellTakerMap::eState::BOX, OBJECTMANAGER->FindObject("Box7"));
	position = MAPMANAGER->GetPosition(3, 5);
	OBJECTMANAGER->FindObject("Box7")->SetPosition(position);
	
	MAPMANAGER->SetValue(5, 6, HellTakerMap::eState::BOX, OBJECTMANAGER->FindObject("Box8"));
	position = MAPMANAGER->GetPosition(5, 6);
	OBJECTMANAGER->FindObject("Box8")->SetPosition(position);
	
	// LockBox
	MAPMANAGER->SetValue(4, 6, HellTakerMap::eState::LockBox, OBJECTMANAGER->FindObject("LockBox1"));
	position = MAPMANAGER->GetPosition(4, 6);
	OBJECTMANAGER->FindObject("LockBox1")->SetPosition(position);
	OBJECTMANAGER->FindObject("LockBox1")->SetActive(true);
	
	// mob

	MAPMANAGER->SetValue(1, 4, HellTakerMap::eState::Mob, OBJECTMANAGER->FindObject("Mob1"));
	position = MAPMANAGER->GetPosition(1, 4);
	OBJECTMANAGER->FindObject("Mob1")->SetPosition(position);
	OBJECTMANAGER->FindObject("Mob1")->SetActive(true);

	MAPMANAGER->SetValue(5, 5, HellTakerMap::eState::Mob, OBJECTMANAGER->FindObject("Mob2"));
	position = MAPMANAGER->GetPosition(5, 5);
	OBJECTMANAGER->FindObject("Mob2")->SetPosition(position);
	OBJECTMANAGER->FindObject("Mob2")->SetActive(true);
	
	// Key
	MAPMANAGER->SetValue(3, 2, HellTakerMap::eState::Key, OBJECTMANAGER->FindObject("Key1"));
	position = MAPMANAGER->GetPosition(3, 2);
	OBJECTMANAGER->FindObject("Key1")->SetPosition(position);
	OBJECTMANAGER->FindObject("Key1")->SetActive(true);
	
	
	//Azazel
	Pandemonica *pPandemonica = (Pandemonica*)OBJECTMANAGER->FindObject("Pandemonica1");
	MAPMANAGER->SetValue(5, 7, HellTakerMap::eState::Goal, OBJECTMANAGER->FindObject("Pandemonica1"));
	position = MAPMANAGER->GetPosition(5, 7);
	OBJECTMANAGER->FindObject("Pandemonica1")->SetPosition(position);
	pPandemonica->SetSuccess(false);
	pPandemonica->SetState(Pandemonica::eState::AZAZEL);





	// Trap
	MAPMANAGER->SetValue(2, 3, HellTakerMap::eState::Trap, OBJECTMANAGER->FindObject("Trap1"));
	position = MAPMANAGER->GetPosition(2, 3);
	OBJECTMANAGER->FindObject("Trap1")->SetPosition(position);
	OBJECTMANAGER->FindObject("Trap1")->SetActive(true);
	dynamic_cast<Trap*>(OBJECTMANAGER->FindObject("Trap1"))->SetState(1);


	MAPMANAGER->SetValue(1, 3, HellTakerMap::eState::Trap, OBJECTMANAGER->FindObject("Trap2"));
	position = MAPMANAGER->GetPosition(1, 3);
	OBJECTMANAGER->FindObject("Trap2")->SetPosition(position);
	OBJECTMANAGER->FindObject("Trap2")->SetActive(true);
	dynamic_cast<Trap*>(OBJECTMANAGER->FindObject("Trap2"))->SetState(1);

}
