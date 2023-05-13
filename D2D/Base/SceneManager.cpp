#include "framework.h"
#include "SceneManager.h"
#include "Lesson/AScene.h"
#include "Lesson/S01_IntroScene.h"
#include "Lesson/S02_IntroScene.h"
#include "Lesson/S03_LoadingScene.h"
#include  "Lesson/S03_DeathScene.h"
#include "Lesson/S04_Chapter1.h"
#include  "Lesson/S05_Chapter2.h"
#include  "Lesson/S06_Chapter3.h"
#include "Lesson/S07_Chapter4.h"
#include "Lesson/S08_Chapter5.h"
#include "Lesson/S09_Chapter6.h"
#include  "Lesson/S10_Chapter7.h"
#include "Lesson/S11_Chapter8.h"
#include "Object/Bone.h"
#include "Object/Box.h"
#include "Object/HellTaker.h"
#include "Object/Dust.h"
#include "Object/Mob.h"
#include "Base/ObjectManager.h"
#include "Object/Fire.h"
#include "Object/Trap.h"
#include "Object/Key.h"
#include "Object/LockBox.h"
#include "Object/Pandemonica.h"
#include "Lesson/S00_DialogSucces.h"

#include  "Object/Button.h"

/////////////////////////////////////////////////
//  생성자
/////////////////////////////////////////////////
SceneManager::SceneManager()
{
	CAMERA->SetKeyInput(false);


	m_cvScenes.push_back(new S01_IntroScene());       // itro scene

	SetStartSceneName("S04_Chapter1");
	
	
	// 쓰레드를 통해서 background로 여러개의 신을 Loading

//	m_cvScenes.push_back(new S02_IntroScene());
//	m_cvScenes.push_back(new S03_LoadingScene());
//	m_cvScenes.push_back(new S03_DeathScene());
//	m_cvScenes.push_back(new S04_Chapter1());

//	return;
	thread t1(bind(&SceneManager::ThreadStart, this));
	t1.detach();  // wait 없이 쓰레드가 동작 

	thread t2(bind(&SceneManager::ThreadStart2, this));
	t2.detach();  // wait 없이 쓰레드가 동작 

}

SceneManager::~SceneManager()
{
	Delete();
}
void SceneManager::Delete()
{
	for (UINT i = 0; i < m_cvScenes.size(); i++)
		delete m_cvScenes[i];
	m_cvScenes.erase(m_cvScenes.begin(), m_cvScenes.end());
}

void SceneManager::ChangeScene(string name)
{
	for (UINT i = 0; i < m_cvScenes.size(); i++)
	{
		m_cvScenes[i]->SetActive(false);
		if (m_cvScenes[i]->GetSceneName() == name)
		{
			m_cvScenes[i]->SetActive(true);
			m_cvScenes[i]->ChangeScene();
		}
			
	}

}

void SceneManager::ChangeDialogScene(string name)
{
	for (UINT i = 0; i < m_cvDialogScenes.size(); i++)
	{
		m_cvDialogScenes[i]->SetActive(false);
		if (m_cvDialogScenes[i]->GetSceneName() == name)
		{
			m_cvDialogScenes[i]->SetActive(true);
			m_cvDialogScenes[i]->ChangeScene();
			m_nState = eState::UNCONTROLABLE;
		}

	}
}

Scene * SceneManager::GetScene(string name)
{
	Scene *pScene = nullptr;

	for (UINT i = 0; i < m_cvScenes.size(); i++)
	{
		if (m_cvScenes[i]->GetSceneName() == name)
			pScene = m_cvScenes[i];
	}
	return pScene;
}

Scene * SceneManager::GetDialogScene(string name)
{
	Scene *pScene = nullptr;

	for (UINT i = 0; i < m_cvDialogScenes.size(); i++)
	{
		if (m_cvDialogScenes[i]->GetSceneName() == name)
			pScene = m_cvDialogScenes[i];
	}
	return pScene;
}

Scene * SceneManager::GetCurrentScene()
{
	Scene *pScene = nullptr;

	for (UINT i = 0; i < m_cvScenes.size(); i++)
	{
		if (!m_cvScenes[i]->IsActive())
			continue;
		pScene = m_cvScenes[i];
		break;
	}
	return pScene;
}

void SceneManager::LoadingObject()
{
	HellTaker *pHelltaker = new HellTaker();
	OBJECTMANAGER->AddObject("Helltaker", pHelltaker);

	long nStart = GetTickCount();




	for (int i = 0; i < 10; i++)
	{
		Mob *pMob = new Mob();
		string name = "Mob" + to_string(i + 1);
		OBJECTMANAGER->AddObject(name, pMob);
	}

	for (int i = 0; i <14; i++)
	{
		Box *pBox = new Box();
		string name = "Box" + to_string(i + 1);
		OBJECTMANAGER->AddObject(name, pBox);
	}

	for (int i = 0; i < 4; i++)
	{
		Pandemonica *pPandemonica = new Pandemonica();
		string name = "Pandemonica" + to_string(i + 1);
		OBJECTMANAGER->AddObject(name, pPandemonica);
	}

	for (int i = 0; i < 4; i++)
	{
		Fire *pFire = new Fire();
		string name = "Fire" + to_string(i + 1);
		OBJECTMANAGER->AddObject(name, pFire);
	}


	// Bone을 생성
	for (int i = 0; i < 20; i++)
	{
		Bone* pBone = new Bone(i / 2);
		string  name = "Bone" + to_string(i);
		OBJECTMANAGER->AddObject(name, pBone);
	}

	// Trap을 생성
	for (int i = 0; i <= 11; i++)
	{
		Trap* pTrap = new Trap();
		string  name = "Trap" + to_string(i);
		OBJECTMANAGER->AddObject(name, pTrap);
	}

	// Key을 생성
	for (int i = 0; i < 2; i++)
	{
		Key* pKey = new Key();
		string  name = "Key" + to_string(i);
		OBJECTMANAGER->AddObject(name, pKey);
	}
	// LockBox을 생성
	for (int i = 0; i < 2; i++)
	{
		LockBox* pLockBox = new LockBox();
		string  name = "LockBox" + to_string(i);
		OBJECTMANAGER->AddObject(name, pLockBox);
	}



	long nEnd = GetTickCount();

	printf("Object %d\n", nEnd - nStart);
}

////////////////////////////////////////////////////////////////
// 스레드   : 데이터 (int a),코드(소스코드),heap(memory Allocation)을 공유할수 있음       
//           stack은 공유 할 수 없다
// 프로세스 : 전부공유가 가능,  IPC( Inter process Control)규약을 이영하여
//            Share할 수 있도록 정부 만들어야 함 --> 비용,시간
//            * 데이터 : 전역변수 , Static
//            * 코드   : if (m_cvScenes[i]->IsActive())
//            * HEAP   : malloc, new
//            * STACK  : 재귀함수 ( 함수포인터, 지역변수, 매개변수)
// 
////////////////////////////////////////////////////////////////
void SceneManager::ThreadStart()
{
	//thread t1(bind(&SceneManager::ThreadStart2, this));
	//t1.detach();  // wait 없이 쓰레드가 동작 

	long nStart = GetTickCount();
	m_cvScenes.push_back(new S02_IntroScene());
	m_cvScenes.push_back(new S03_LoadingScene());
	m_cvScenes.push_back(new S03_DeathScene());

	long nEnd = GetTickCount();

	
}

void SceneManager::ThreadStart2()
{
	long nStart = GetTickCount();
	long nEnd = GetTickCount();

	LoadingObject();
	nEnd = GetTickCount();
	

	m_cvScenes.push_back(new S04_Chapter1());
	m_cvScenes.push_back(new S05_Chapter2());
	m_cvScenes.push_back(new S06_Chapter3());
	m_cvScenes.push_back(new S07_Chapter4());
	m_cvScenes.push_back(new S08_Chapter5());
	m_cvScenes.push_back(new S09_Chapter6());
	m_cvScenes.push_back(new S10_Chapter7());
	m_cvScenes.push_back(new S11_Chapter8());


	m_cvDialogScenes.push_back(new S00_DialogSucces());
	
	m_bLoadingEnd = true;

	//printf("Thread2 End %d\n", nEnd - nStart);
}

//////////////////////////////////////////////////
// 각각의 Scene을 Update
/////////////////////////////////////////////////
void SceneManager::Update()
{
	if (m_nState == eState::PLAY)
	{
		for (UINT i = 0; i < m_cvScenes.size(); i++)
		{
			if (m_cvScenes[i]->IsActive())
				m_cvScenes[i]->Update();
		}
	}
	if (m_nState == eState::UNCONTROLABLE)
	{
		for (UINT i = 0; i < m_cvDialogScenes.size(); i++)
		{
			if (m_cvDialogScenes[i]->IsActive())
				m_cvDialogScenes[i]->Update();
		}

	}

}
//////////////////////////////////////////////////
// 각각의 Scene을 Rendering
/////////////////////////////////////////////////
void SceneManager::Render()
{
	if (m_nState == eState::PLAY)
	{
		for (UINT i = 0; i < m_cvScenes.size(); i++)
		{
			if (m_cvScenes[i]->IsActive())
				m_cvScenes[i]->Render();
		}
	}
	if (m_nState == eState::UNCONTROLABLE)
	{
		for (UINT i = 0; i < m_cvDialogScenes.size(); i++)
		{
			if (m_cvDialogScenes[i]->IsActive())
				m_cvDialogScenes[i]->Render();
		}

	}


	ImGui::Render();
}



