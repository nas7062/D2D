#include  "framework.h"
#include  "S10_Chapter7.h"
#include  "Object/AObject.h"
#include "Object/BackGround.h"
#include "Object/HellTaker.h"
#include "Object/Mob.h"
#include "Object/Box.h"
//#include "Object/Thorn.h"
#include "Object/Fire.h"
#include "Object/Key.h"
#include "Object/LockBox.h"
#include "Base/ObjectManager.h"
#include "Object/HellTakerMap.h"
#include "Object/Pandemonica.h"
#include "Object/Trap.h"
#include "Lesson/S03_DeathScene.h"

////////////////////////////////////////////////////////////////////////
// 생성자 & 소멸자
///////////////////////////////////////////////////////////////////////
S10_Chapter7::S10_Chapter7()
{
	// Scene의 Active 및 Name 설정
	SetActive(false);                      //  스레드에서 생성할 신은  false로 둔다
	SetSceneName("S10_Chapter7");               //  현재 신 Name
	SetNextSceneName("S11_Chapter8");           //  다음 신 Name

	// Object 생성
	wstring  strImageFile = L"/helltaker/Chapter/Chapter (7).png";			// 배경
	wstring  strShaderFile = L"00_Animation.fx";

	m_pTexture = new Texture(strImageFile, strShaderFile);
	m_pBackground = new BackGround();

}

S10_Chapter7::~S10_Chapter7()
{
	SAFE_DELETE(m_pTexture);
	SAFE_DELETE(m_pBackground);

}
////////////////////////////////////////////////////////////////////////
// Scene Update
// 1. 카메라 Update 및 View, Projection Matrix 생성
// 2. 
///////////////////////////////////////////////////////////////////////
void S10_Chapter7::Update()
{
	Matrix V, P;

	// View, Projectiion Matrix
	CAMERA->Update();
	V = CAMERA->GetViewMatrix();
	P = CAMERA->GetProjectionMatrix();

	// Object Update
	m_pTexture->Update(V, P);
	m_pBackground->Update(V, P);



	OBJECTMANAGER->Update("Helltaker", V, P);
	for (int i = 0; i < 3; i++)
	{
		string  name = "Mob" + to_string(i+1);
		OBJECTMANAGER->Update(name, V, P);
	}

	for (int i = 0; i < 5; i++)
		{
			string  name = "Box" + to_string(i+1);
			OBJECTMANAGER->Update(name, V, P);
		}
		
	for (int i = 0; i < 6; i++)
		{
			string  name = "Trap" + to_string(i+1);
			OBJECTMANAGER->Update(name, V, P);
		}

	for (int i = 0; i < 3; i++)
	{
		string  name = "Fire" + to_string(i+1);
		OBJECTMANAGER->Update(name, V, P);
	}

	
	OBJECTMANAGER->Update("Key1", V, P);
	OBJECTMANAGER->Update("LockBox1", V, P);
	OBJECTMANAGER->Update("Pandemonica1", V, P);
	
	HellTaker *pHelltaker = (HellTaker*)OBJECTMANAGER->FindObject("Helltaker");

	if (pHelltaker->GetTry() < 0)
	{
		Scene *pScene = SCENEMANAGER->GetScene("S03_LoadingScene");
		pScene->SetNextSceneName("S10_Chapter7");

		pScene = SCENEMANAGER->GetScene("S03_DeathScene");
		pScene->SetNextSceneName("S03_LoadingScene");

		S03_DeathScene *pDepthScene = (S03_DeathScene*)pScene;
		pDepthScene->SetPoisition(pHelltaker->GetPosition());

		SCENEMANAGER->ChangeScene("S03_DeathScene");
		return;
	}









	
	//CAMERA Update
	CAMERA->Update(V,P);
}

/*=============================================================*/
// Render
void S10_Chapter7::Render()
{
	HellTaker *pHelltaker = (HellTaker*)OBJECTMANAGER->FindObject("Helltaker");

	//Object Render 
	m_pTexture->Render();
	m_pBackground->Render();


	for (int i = 0; i < 3; i++)
	{
		string  name = "Fire" + to_string(i+1);
		OBJECTMANAGER->Render(name);
	}

	
	for (int i = 0; i < 5; i++)
	{
		string  name = "Box" + to_string(i+1);
		OBJECTMANAGER->Render(name);
	}

	for (int i = 0; i < 6; i++)
	{
		string  name = "Trap" + to_string(i+1);
		OBJECTMANAGER->Render(name);
	}

	for (int i = 0; i < 3; i++)
	{
		string  name = "Mob" + to_string(i+1);
		OBJECTMANAGER->Render(name);
	}

	OBJECTMANAGER->Render("Helltaker");
	OBJECTMANAGER->Render("Key1");
	OBJECTMANAGER->Render("LockBox1");
	OBJECTMANAGER->Render("Pandemonica1");



	//Camera Render
	CAMERA->Render();

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

		/*================================== CAMERA position ====================================*/
		Vector2 pos = Mouse->GetPosition();
		CAMERA->WCtoVC(pos);
		Main->SetMousePosition(pos);

		rect.top += 20;
		rect.bottom += 20;
		str = L"Camera(p) : " + to_wstring(pos.x);
		str = str + L", " + to_wstring(pos.y);
		DirectWrite::RenderText(str, rect);

		/*================================== print str ===============================================*/
		wstring str2;
		str2 = to_wstring(pHelltaker->GetTry()); // Animation->AnimationClip.m_nCurrent

		if (pHelltaker->GetTry() <= 0)
			str2 = 'X';

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

		wstring str3 = L"VII";
		Vector2 pos3 = Vector2(1150, 500);
		DirectWrite::RenderText(str3, pos3, 255, 255, 255, 120.0f);

		

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
/*================================================== ChangeScene =============================================================*/
// 세로줄이 x, 가로줄이 y
void S10_Chapter7::ChangeScene()
{
	// 플레이어, 박스, Mob, Goal등등을 초기화
	MAPMANAGER->Clear();
	MAPMANAGER->SetOffSet(-350.0f, 400.f);
//	MAPMANAGER->SetOffSet(-300.0f, 350.0f);
	MAPMANAGER->SetSize(9, 9);

	// Move
	SetMoveValue(4, 5, 1);
	SetMoveValue(4, 6, 2);
	SetMoveValue(1, 2, 3);
	SetMoveValue(4, 6, 3);
	SetMoveValue(1, 6, 4);

	MAPMANAGER->SetValue(1, 5, HellTakerMap::eState::Move, NULL);
	
	
	SetMoveValue(3, 6, 5);
	SetMoveValue(4, 4, 6);
	SetMoveValue(1, 4, 7);

	Fire *pFire = (Fire*)OBJECTMANAGER->FindObject("Fire1");
	pFire->SetPosition(-360.0f, -110.0f);

	pFire = (Fire*)OBJECTMANAGER->FindObject("Fire2");
	pFire->SetPosition(360.0f, 340.0f);

	pFire = (Fire*)OBJECTMANAGER->FindObject("Fire3");
	pFire->SetPosition(255.0f, 390.0f);


	// Object
			//HellTaker
	HellTaker *pHelltaker = (HellTaker*)OBJECTMANAGER->FindObject("Helltaker");

	Vector2 position = MAPMANAGER->GetPosition(6, 5);
	MAPMANAGER->SetValue(6, 5, HellTakerMap::eState::Helltaker, pHelltaker);
	position = MAPMANAGER->GetPosition(6, 5);
	pHelltaker->SetPosition(position);


	
	pHelltaker->SetTry(322); // 32
	pHelltaker->Reset();
	


	// Helltake
	Pandemonica *pPandemonica = (Pandemonica*)OBJECTMANAGER->FindObject("Pandemonica1");
	MAPMANAGER->SetValue(4, 1, HellTakerMap::eState::Goal, pPandemonica);
	position = MAPMANAGER->GetPosition(4, 1);
	pPandemonica->SetPosition(position);
	pPandemonica->SetState(Pandemonica::DEMON1);
	

	// mob

	MAPMANAGER->SetValue(1, 4, HellTakerMap::eState::Mob, OBJECTMANAGER->FindObject("Mob1"));
	position = MAPMANAGER->GetPosition(1, 4);
	OBJECTMANAGER->FindObject("Mob1")->SetPosition(position);
	OBJECTMANAGER->FindObject("Mob1")->SetActive(true);

	MAPMANAGER->SetValue(3, 5, HellTakerMap::eState::Mob, OBJECTMANAGER->FindObject("Mob2"));
	position = MAPMANAGER->GetPosition(3, 5);
	OBJECTMANAGER->FindObject("Mob2")->SetPosition(position);
	OBJECTMANAGER->FindObject("Mob2")->SetActive(true);

	MAPMANAGER->SetValue(4, 4, HellTakerMap::eState::Mob, OBJECTMANAGER->FindObject("Mob3"));
	position = MAPMANAGER->GetPosition(4, 4);
	OBJECTMANAGER->FindObject("Mob3")->SetPosition(position);
	OBJECTMANAGER->FindObject("Mob3")->SetActive(true);

	// Box
	

	MAPMANAGER->SetValue(4, 3, HellTakerMap::eState::BOX, OBJECTMANAGER->FindObject("Box1"));
	position = MAPMANAGER->GetPosition(4, 3);
	OBJECTMANAGER->FindObject("Box1")->SetPosition(position);

	MAPMANAGER->SetValue(5, 3, HellTakerMap::eState::BOX, OBJECTMANAGER->FindObject("Box2"));
	position = MAPMANAGER->GetPosition(5, 3);
	OBJECTMANAGER->FindObject("Box2")->SetPosition(position);

	MAPMANAGER->SetValue(6, 3, HellTakerMap::eState::BOX, OBJECTMANAGER->FindObject("Box3"));
	position = MAPMANAGER->GetPosition(6, 3);
	OBJECTMANAGER->FindObject("Box3")->SetPosition(position);

	MAPMANAGER->SetValue(5, 4, HellTakerMap::eState::BOX, OBJECTMANAGER->FindObject("Box4"));
	position = MAPMANAGER->GetPosition(5, 4);
	OBJECTMANAGER->FindObject("Box4")->SetPosition(position);


	MAPMANAGER->SetValue(2, 4, HellTakerMap::eState::BOX, OBJECTMANAGER->FindObject("Box5"));
	position = MAPMANAGER->GetPosition(2, 4);
	OBJECTMANAGER->FindObject("Box5")->SetPosition(position);


	// Thap

	MAPMANAGER->SetValue(4, 6, HellTakerMap::eState::Trap, OBJECTMANAGER->FindObject("Trap1"));
	position = MAPMANAGER->GetPosition(4, 6);
	OBJECTMANAGER->FindObject("Trap1")->SetPosition(position);
	OBJECTMANAGER->FindObject("Trap1")->SetActive(true);
	dynamic_cast<Trap*>(OBJECTMANAGER->FindObject("Trap1"))->SetState(1);
	Trap::eState::DOWN;
	MAPMANAGER->SetValue(3, 7, HellTakerMap::eState::Trap, OBJECTMANAGER->FindObject("Trap2"));
	position = MAPMANAGER->GetPosition(3, 7);
	OBJECTMANAGER->FindObject("Trap2")->SetPosition(position);
	OBJECTMANAGER->FindObject("Trap2")->SetActive(true);
	dynamic_cast<Trap*>(OBJECTMANAGER->FindObject("Trap2"))->SetState(1);
	Trap::eState::DOWN;

	MAPMANAGER->SetValue(1, 7, HellTakerMap::eState::Trap, OBJECTMANAGER->FindObject("Trap3"));
	position = MAPMANAGER->GetPosition(1, 7);
	OBJECTMANAGER->FindObject("Trap3")->SetPosition(position);
	OBJECTMANAGER->FindObject("Trap3")->SetActive(true);
	dynamic_cast<Trap*>(OBJECTMANAGER->FindObject("Trap3"))->SetState(1);
	Trap::eState::DOWN;

	MAPMANAGER->SetValue(1, 6, HellTakerMap::eState::Trap, OBJECTMANAGER->FindObject("Trap4"));
	position = MAPMANAGER->GetPosition(1, 6);
	OBJECTMANAGER->FindObject("Trap4")->SetPosition(position);
	OBJECTMANAGER->FindObject("Trap4")->SetActive(true);
	dynamic_cast<Trap*>(OBJECTMANAGER->FindObject("Trap4"))->SetState(0);


	MAPMANAGER->SetValue(2, 7, HellTakerMap::eState::Trap, OBJECTMANAGER->FindObject("Trap5"));
	position = MAPMANAGER->GetPosition(2, 7);
	OBJECTMANAGER->FindObject("Trap5")->SetPosition(position);
	OBJECTMANAGER->FindObject("Trap5")->SetActive(true);
	dynamic_cast<Trap*>(OBJECTMANAGER->FindObject("Trap5"))->SetState(0);
	


	MAPMANAGER->SetValue(4, 7, HellTakerMap::eState::Trap, OBJECTMANAGER->FindObject("Trap6"));
	position = MAPMANAGER->GetPosition(4, 7);
	OBJECTMANAGER->FindObject("Trap6")->SetPosition(position);
	OBJECTMANAGER->FindObject("Trap6")->SetActive(true);
	dynamic_cast<Trap*>(OBJECTMANAGER->FindObject("Trap6"))->SetState(0);


	MAPMANAGER->SetValue(2, 3, HellTakerMap::eState::Key, OBJECTMANAGER->FindObject("Key1"));
	position = MAPMANAGER->GetPosition(2, 3);
	OBJECTMANAGER->FindObject("Key1")->SetPosition(position);

	MAPMANAGER->SetValue(5, 2, HellTakerMap::eState::LockBox, OBJECTMANAGER->FindObject("LockBox1"));
	position = MAPMANAGER->GetPosition(5, 2);
	OBJECTMANAGER->FindObject("LockBox1")->SetPosition(position);


}
void S10_Chapter7::SetMoveValue(int sx, int ex, int y)
{
	for (int i = sx; i <= ex; i++)
		MAPMANAGER->SetValue(i, y, HellTakerMap::eState::Move, NULL);

}

void S10_Chapter7::MakeObject(string name, string Class_name, int x, int y)
{
	
}

