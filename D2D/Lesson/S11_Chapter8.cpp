#include  "framework.h"
#include  "S11_Chapter8.h"
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
S11_Chapter8::S11_Chapter8()
{
	// Scene의 Active 및 Name 설정
	SetActive(false);                               //  스레드에서 생성할 신은  false로 둔다
	SetSceneName("S11_Chapter8");                //  현재 신 Name
	SetNextSceneName("S07_Chapter4");           //  다음 신 Name

	// Object 생성
	wstring  strImageFile = L"/helltaker/Chapter/Chapter (9).png";
	wstring  strShaderFile = L"00_Animation.fx";

	m_pTexture = new Texture(strImageFile, strShaderFile);
	//	m_pTexture->SetPosition(Vector2(0.0f, -400.0f));

	m_pTexture->SetPosition(Vector2(0.0f, 500.0f));

	m_pBackGround = new BackGround();


	// CAMERA 속성부여

	//CAMERA->SetObject(m_pPlayer);    // Player를 기준으로 카메라 위치기 변한다

	//ChangeScene();
}

S11_Chapter8::~S11_Chapter8()
{
	SAFE_DELETE(m_pTexture);
}
////////////////////////////////////////////////////////////////////////
// Scene Update
// 1. 카메라 Update 및 View, Projection Matrix 생성
// 2. 
///////////////////////////////////////////////////////////////////////
void S11_Chapter8::Update()
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


	CAMERA->Update(V, P);
	m_pTexture->Update(V, P);
	m_pBackGround->Update(V, P);

	OBJECTMANAGER->Update("Pandemonica1", V, P);
	OBJECTMANAGER->Update("Helltaker", V, P);

	for (int i = 1; i <= 8; i++)
	{
		string  name = "Mob" + to_string(i);
		OBJECTMANAGER->Update(name, V, P);
	}




	HellTaker* pHelltaker = (HellTaker*)OBJECTMANAGER->FindObject("Helltaker");


	if (pHelltaker->GetTry() < 0)
	{
		Scene* pScene = SCENEMANAGER->GetScene("S03_LoadingScene");
		pScene->SetNextSceneName("S11_Chapter8");

		pScene = SCENEMANAGER->GetScene("S03_DeathScene");
		pScene->SetNextSceneName("S03_LoadingScene");

		S03_DeathScene* pDepthScene = (S03_DeathScene*)pScene;
		pDepthScene->SetPoisition(pHelltaker->GetPosition());

		SCENEMANAGER->ChangeScene("S03_DeathScene");
		return;
	}


}

void S11_Chapter8::Render()
{
	HellTaker* pHelltaker = (HellTaker*)OBJECTMANAGER->FindObject("Helltaker");

	m_pTexture->Render();
	m_pBackGround->Render();

	for (int i = 1; i <= 8; i++)
	{
		string  name = "Mob" + to_string(i);
		OBJECTMANAGER->Render(name);
	}


	OBJECTMANAGER->Render("Pandemonica1");
	OBJECTMANAGER->Render("Helltaker");



	//	pHelltaker->Render();

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

		//  Hit수 Stage
		wstring  str2 = to_wstring(pHelltaker->GetTry());  // Animation->AnimationClip.m_nCurrent

		if (str2 == L"0")
			str2 = L"X";

		Vector2   pos2 = Vector2(100, 700);
		DirectWrite::RenderText(str2, pos2, 255, 255, 255, 180.0f);

		wstring   str3 = L"Ⅷ";
		Vector2   pos3 = Vector2(1650, 700);
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

void S11_Chapter8::ChangeScene()
{
	// 픞레이어, Box, Mob, Goal 위치를 초기화


	// Chapter8
	m_pTexture->SetPosition(Vector2(0.0f, 500.0f));

	MAPMANAGER->Clear();
	MAPMANAGER->SetSize(5, 15);
	MAPMANAGER->SetOffSet(-200.0f, 950.0f);

	for (int y = 3; y <= 13; y++)
	{
		MAPMANAGER->SetValue(1, y, HellTakerMap::eState::Move, NULL);
		MAPMANAGER->SetValue(2, y, HellTakerMap::eState::Move, NULL);
		MAPMANAGER->SetValue(3, y, HellTakerMap::eState::Move, NULL);
	}


	SetPandemonica(true);
	SetHelltaker(true);
	SetMob(true);

}

void S11_Chapter8::ChanageMapOffset(float y)
{

	//	MAPMANAGER->SetOffSet(-200.0f, 1650.0f);
	//	SetPandemonica(false);
	//	SetHelltaker(false);

		// Chapter8 위치 변경
	m_pTexture->SetPosition(Vector2(0.0f, m_pTexture->GetPosition().y + y));


	Vector2 offset = MAPMANAGER->GetMapOffSet();

	MAPMANAGER->SetOffSet(offset.x, offset.y + y);
	SetPandemonica(false);
	SetHelltaker(false);
	SetMob(false);




}

void S11_Chapter8::MakeTrap(int id, int x, int y, int state)
{
	string name = "Trap" + to_string(id);
	MAPMANAGER->SetValue(x, y, HellTakerMap::eState::Trap, OBJECTMANAGER->FindObject(name));
	Vector2 position = MAPMANAGER->GetPosition(x, y);
	OBJECTMANAGER->FindObject(name)->SetPosition(position);
	OBJECTMANAGER->FindObject(name)->SetActive(true);
	dynamic_cast<Trap*>(OBJECTMANAGER->FindObject(name))->SetState(state);
}

void S11_Chapter8::SetPandemonica(bool bInit)
{
	Pandemonica* pPandemonica = (Pandemonica*)OBJECTMANAGER->FindObject("Pandemonica1");
	MAPMANAGER->SetValue(2, 0, HellTakerMap::eState::Goal, OBJECTMANAGER->FindObject("Pandemonica1"));
	Vector2 position = MAPMANAGER->GetPosition(2, 0);
	OBJECTMANAGER->FindObject("Pandemonica1")->SetPosition(position);
	if (bInit)
		pPandemonica->SetSuccess(false);
	pPandemonica->SetState(Pandemonica::eState::MODEUS);


}

void S11_Chapter8::SetHelltaker(bool bInit)
{
	HellTaker* pHelltaker = (HellTaker*)OBJECTMANAGER->FindObject("Helltaker");

	pHelltaker->Reset();
	MAPMANAGER->SetValue(2, 12, HellTakerMap::eState::Helltaker, pHelltaker);
	Vector2  position = MAPMANAGER->GetPosition(2, 12);
	pHelltaker->SetPosition(position);
	if (bInit)
		pHelltaker->SetTry(12);



}

void S11_Chapter8::SetMob(bool bInit)
{
	// mob
	int  id = 1;
	for (int y = 3; y <= 10; y++)
	{
		string  name = "Mob" + to_string(id);

		MAPMANAGER->SetValue(2, y, HellTakerMap::eState::Mob, OBJECTMANAGER->FindObject(name));
		Vector2 position = MAPMANAGER->GetPosition(2, y);
		OBJECTMANAGER->FindObject(name)->SetPosition(position);
		if (bInit)
			OBJECTMANAGER->FindObject(name)->SetActive(true);
		id++;
	}




}
