#include  "framework.h"
#include  "HellTaker.h"
#include  "Collider/Collider.h"
#include  "Object/HellTakerMap.h"
#include  "Object/AObject.h"
#include  "Object/Mob.h"
#include  "Object/Box.h"
#include  "Object/Dust.h"
#include  "Object/Pandemonica.h"
#include  "Object/Kick.h"
#include  "Object/Trap.h"
#include  "Object/Huge.h"
#include  "Object/Key.h"
#include  "Lesson/S00_DialogSucces.h"
#include  "Lesson/S03_LoadingScene.h"
#include  "Lesson/S11_Chapter8.h"

///////////////////////////////////////////////////////////
// 생성자
//////////////////////////////////////////////////////////
HellTaker::HellTaker()
{
	wstring  imgFile     = L"Marco.png";
	wstring  shaderFile  = L"00_Animation.fx";
	
	SetName("Macro");
	m_pAnimation = new Animation();
	m_pDust = new Dust();
	m_pKick = new Kick();
	m_pHuge = new Huge();
	m_pHuge->SetActive(false);

	//Texture *pTexture = m_pAnimation->CreateTexture(imgFile, shaderFile);

	// IDLE
	{
		AnimationClip *pClip = new AnimationClip();
		imgFile = L"/helltaker/player/player_Idle/Helltaker (1).png";

		Texture *pTexture = pClip->CreateTexture(imgFile, shaderFile);

		for (int i = 1; i < 13; i++)
		{
			imgFile = L"/helltaker/player/player_Idle/Helltaker (" + to_wstring(i) + L").png";
			pClip->AddFrame(pTexture, imgFile, 0, 40, 100, 140, 0.05f);
		}	
		m_pAnimation->AddAnimationClip(pClip);
	}

	// Move
	{
		AnimationClip *pClip = new AnimationClip();
		imgFile = L"/helltaker/player/player_Move/Move (1).png";

		Texture *pTexture = pClip->CreateTexture(imgFile, shaderFile);

		for (int i = 1; i < 6; i++)
		{
			imgFile = L"/helltaker/player/player_Move/Move (" + to_wstring(i) + L").png";
			pClip->AddFrame(pTexture, imgFile, 0, 40, 100, 140, 0.05f);
		}
		m_pAnimation->AddAnimationClip(pClip);
	}
	
	// Attack
	{
		AnimationClip *pClip = new AnimationClip(AnimationClip::eState::Once);
		imgFile = L"/helltaker/player/player_Attack/Attack (1).png";

		Texture *pTexture = pClip->CreateTexture(imgFile, shaderFile);

		for (int i = 1; i < 14; i++)
		{
			imgFile = L"/helltaker/player/player_Attack/Attack (" + to_wstring(i) + L").png";
			pClip->AddFrame(pTexture, imgFile, 0, 40, 100, 140, 0.05f);
		}
		m_pAnimation->AddAnimationClip(pClip);
	}


	// Goal
	{
		AnimationClip *pClip = new AnimationClip(AnimationClip::eState::Once);
		imgFile = L"/helltaker/player/Player_Goal/Get_Goal_Player (1).png";

		Texture *pTexture = pClip->CreateTexture(imgFile, shaderFile);

		for (int i = 1; i <= 24; i++)
		{
			imgFile = L"/helltaker/player/Player_Goal/Get_Goal_Player (" + to_wstring(i) + L").png";
			pClip->AddFrame(pTexture, imgFile, 0, 40, 100, 140, 0.05f);
		}
		m_pAnimation->AddAnimationClip(pClip);
	}


	m_pCollider = new Collider();
	m_pCollider->SetParent(this);

}

HellTaker::~HellTaker()
{
	SAFE_DELETE(m_pAnimation);
	SAFE_DELETE(m_pCollider);
}
void HellTaker::Update(Matrix V, Matrix P)
{
	Vector2 position = GetPosition();

	

	// Key or Mouse 이동

	if (m_nState != eState::WALK)
	{
		if (KEYMANAGER->Down('W') || KEYMANAGER->Down(VK_UP))
			MoveObject(eDirection::Up, position);
		else if (KEYMANAGER->Down('S') || KEYMANAGER->Down(VK_DOWN))
			MoveObject(eDirection::Down, position);
		else if (KEYMANAGER->Down('D') || KEYMANAGER->Down(VK_RIGHT))
			MoveObject(eDirection::Right, position);
		else if (KEYMANAGER->Down('A') || KEYMANAGER->Down(VK_LEFT))
			MoveObject(eDirection::Left, position);
		else
			; 
	}
	else if (m_nState == eState::WALK)
	{
		m_Time = m_Time + TIMEMANAGER->Delta();
		if (m_Time > 0.02f)
		{
			m_nMoveCount++;
			m_Time = 0.0f;
			if (m_nMoveCount < 11)
			{
				position.x = position.x + m_MovePosition.x;
				position.y = position.y + m_MovePosition.y;	
				if(!Audio->Playing("DUST"))
				  Audio->Play("DUST");
			}
			else
			{
				m_nMoveCount = 0;
				m_nState = eState::IDLE;
				Audio->Stop("DUST");
			}
		}
	}


	if (m_nState == eState::ATTACK)
	{
		if (!m_pAnimation->IsPlay())
			m_nState = eState::IDLE;
	}

	if (m_nState == eState::GOAL)
	{
		if (!m_pAnimation->IsPlay())
		{
			Scene *pScene = SCENEMANAGER->GetScene("S03_LoadingScene");
			pScene->SetNextSceneName(SCENEMANAGER->GetCurrentScene()->GetNextSceneName());
			SCENEMANAGER->ChangeScene("S03_LoadingScene");
			Reset();
			return;
		}
			
	}


	if (m_bAttacked)
	{
		if (!m_pHuge->IsActive())
		{
			m_bAttacked = false;
		//	this->DecrementTry();
		}
	}

	// Dust
	m_pDust->Update(V, P);
	m_pKick->Update(V, P);
	m_pHuge->Update(V, P);


	// Animation
	SetPosition(position);
	m_pAnimation->SetPlay((UINT)this->m_nState);
	m_pAnimation->SetPosition(position);
	m_pAnimation->SetScale(m_Scale);
	m_pAnimation->SetRotation(m_Rotation);
	m_pAnimation->Update(V, P);

	// Collider
	m_pCollider->SetPosition(position);
	m_pCollider->SetScale(m_Scale.x*m_pAnimation->GetTextureSize().x,
		                  m_Scale.y*m_pAnimation->GetTextureSize().y);
	m_pCollider->SetRotation(m_Rotation);
	m_pCollider->Update(V, P);

}

void HellTaker::MoveObject(eDirection direction, Vector2 & position)
{
	POINT pt = MAPMANAGER->GetMapXY(position);
	POINT Oldpt = pt;
	POINT Goalpt = pt;
	POINT GoalPt2 = pt;

	

	switch (direction)
	{
	case eDirection::Right:
		pt.x     = pt.x + 1;
		Goalpt.x = pt.x + 1;
		m_MovePosition = Vector2(10.0f, 0.0f);
		SetRotation(0.0f, 0.0f, 0.0f);
		break;
	case eDirection::Left:
		pt.x = pt.x - 1;
		Goalpt.x = pt.x - 1;
		SetRotation(0.0f, 180.0f, 0.0f);
		m_MovePosition = Vector2(-10.0f, 0.0f);
		break;
	case eDirection::Up:
		pt.y = pt.y - 1;
		Goalpt.y = pt.y - 1;
		m_MovePosition = Vector2(0.0f, 10.0f);
		break;
	case eDirection::Down:
		pt.y = pt.y + 1;
		Goalpt.y = pt.y + 1;
		m_MovePosition = Vector2(0.0f, -10.0f);
		break;

	}


	if (MAPMANAGER->IsWall(pt.x, pt.y))
		return;

	if (MAPMANAGER->IsMob(pt.x, pt.y))
	{
		Mob *pObject = (Mob*) MAPMANAGER->GetGameObject(pt.x, pt.y);
		Vector2 position2 = pObject->GetPosition();
		pObject->MoveObject(direction, position2);
		this->DecrementTry();
		m_nState = eState::ATTACK;
		m_pKick->Random();
		m_pKick->SetPosition(position2);

		if (MAPMANAGER->IsTrap(Oldpt.x, Oldpt.y))
		{
			Trap *pObject2 = dynamic_cast<Trap*>(MAPMANAGER->GetSecondObject(Oldpt.x, Oldpt.y));
			if(pObject2->GetState() == 0)
				this->DecrementTry();
		}
		return;
	}
	if (MAPMANAGER->IsBox(pt.x, pt.y))
	{

		Box *pObject = (Box*)MAPMANAGER->GetGameObject(pt.x, pt.y);
		Vector2 position2 = pObject->GetPosition();
		pObject->MoveObject(direction, position2);
		this->DecrementTry();
		m_nState = eState::ATTACK;
		m_pKick->Random();
		m_pKick->SetPosition(position2);

		if (MAPMANAGER->IsTrap(Oldpt.x, Oldpt.y))
		{
			Trap *pObject2 = dynamic_cast<Trap*>(MAPMANAGER->GetSecondObject(Oldpt.x, Oldpt.y));
			if (pObject2->GetState() == 0)
				this->DecrementTry();
		}
		return;
	}
//	if (MAPMANAGER->IsGoal(Goalpt.x, Goalpt.y) || MAPMANAGER->IsGoalEx(Goalpt.x, Goalpt.y))
	if (MAPMANAGER->IsGoal(GoalPt2.x, GoalPt2.y, GoalPt2) )
	{
		GameObject* pObject = MAPMANAGER->GetGameObject(GoalPt2.x, GoalPt2.y);
		if (pObject->GetName() == "Pandemonica")
		{
			Pandemonica *pObject2 = (Pandemonica*)MAPMANAGER->GetGameObject(GoalPt2.x, GoalPt2.y);
			pObject2->SetSuccess(true);
		}

		// 처리
		S00_DialogSucces  *pS00_DialogSucces = (S00_DialogSucces*)SCENEMANAGER->GetDialogScene("S00_DialogSucces");

		Scene *pCurrentScene = SCENEMANAGER->GetCurrentScene();

		pS00_DialogSucces->m_strNoSuccessScene = pCurrentScene->GetSceneName();
		pS00_DialogSucces->m_strSuccessScene = pCurrentScene->GetNextSceneName();

		wstring str2;
		if (pCurrentScene->GetSceneName() == "S04_Chapter1")
		{
			pS00_DialogSucces->m_strBanner = L"S06 주인공 이름";
			pS00_DialogSucces->m_strButtonName1 = L" 오히려 '그쪽'을 도와줘야 할판인데?";
			pS00_DialogSucces->m_strButtonName2 = L"우리 집에 한번 오면 알게 될거야";
		}
		
		if (pCurrentScene->GetSceneName() == "S05_Chapter2")
		{
			
			pS00_DialogSucces->m_strButtonName1 = L"그럴시간 없어.여자들 모으느라 바빠.";
			pS00_DialogSucces->m_strButtonName2 = L"좋아. 물어볼 필요도 없지";
		}

		if (pCurrentScene->GetSceneName() == "S06_Chapter3")
		{
			pS00_DialogSucces->m_strBanner = L"S06 주인공 이름";
			pS00_DialogSucces->m_strButtonName1 = L"좋아,물어볼 필요도없지.";
			pS00_DialogSucces->m_strButtonName2 = L"잠깐,일이 너무 쉽게 흘러가는데.좀 물어봐야겠어.";
		}

		if (pCurrentScene->GetSceneName() == "S07_Chapter4")
		{
			pS00_DialogSucces->m_strBanner = L"S07 주인공 이름";
			pS00_DialogSucces->m_strButtonName1 = L"그쪽이랑 노는게 가장 재밌어 보이는데.";
			pS00_DialogSucces->m_strButtonName2 = L"정말 달콤하네.제발 날 더 모욕해줘.";
		}

		if (pCurrentScene->GetSceneName() == "S08_Chapter5")
		{
			pS00_DialogSucces->m_strBanner = L"S08 주인공 이름";
			pS00_DialogSucces->m_strButtonName1 = L"잠깐 왠지후회할거 같은데.";
			pS00_DialogSucces->m_strButtonName2 = L"여기엔 하렘 따윈 없어. 그냥 리듬돌죽 게임 뿐이지.";
		}

		if (pCurrentScene->GetSceneName() == "S09_Chapter6")
		{
			pS00_DialogSucces->m_strBanner = L"S09 주인공 이름";
			pS00_DialogSucces->m_strButtonName1 = L"악마를 찾고있어";
			pS00_DialogSucces->m_strButtonName2 = L"천사를 찾고있어";
		}

		if (pCurrentScene->GetSceneName() == "S10_Chapter7")
		{
			pS00_DialogSucces->m_strBanner = L"S10 주인공 이름";
			pS00_DialogSucces->m_strButtonName1 = L"푸는데 힘 좀 썻지.같이 하렘에 낄 생각 있나?";
			pS00_DialogSucces->m_strButtonName2 = L"그냥 메뉴에서 스킵하면서 왔지.같이 하렘에 낄 생각있나?";
		}



		SCENEMANAGER->ChangeDialogScene("S00_DialogSucces");
		return;
	}
	
	if (MAPMANAGER->IsTrap(pt.x, pt.y))
	{
		Trap *pObject = dynamic_cast<Trap*>(MAPMANAGER->GetSecondObject(pt.x, pt.y));
	
		if (pObject->GetNextState())   // 현재 off -> 행동 on 조절
		{
			Vector2 position2 = MAPMANAGER->GetPosition(pt.x, pt.y);
			m_pHuge->SetPosition(position2);
			m_pHuge->SetActive(true);
			m_pHuge->SetState(0);
			m_bAttacked = true;
			this->DecrementTry();
		}	  
	}

	if (MAPMANAGER->IsKey(pt.x, pt.y))
	{

		Key *pObject = dynamic_cast<Key*>(MAPMANAGER->GetSecondObject(pt.x, pt.y));
		
		pObject->SetActive(false);

		Vector2 position2 = MAPMANAGER->GetPosition(pt.x, pt.y);
		m_pHuge->SetPosition(position2);
		m_pHuge->SetActive(true);
		m_pHuge->SetState(1);
		m_bAttacked  = true;
		m_bAuqireKey = true;
		MAPMANAGER->ResetValue(pt.x, pt.y, HellTakerMap::eState::Key);

	}


	if (MAPMANAGER->IsLockBox(pt.x, pt.y))
	{
		if (MAPMANAGER->IsTrap(Oldpt.x, Oldpt.y))
		{
			Trap *pObject2 = dynamic_cast<Trap*>(MAPMANAGER->GetSecondObject(Oldpt.x, Oldpt.y));
			if (pObject2->GetState() == 0)
				this->DecrementTry();
		}


		if (this->m_bAuqireKey)
		{
			MAPMANAGER->GetGameObject(pt.x, pt.y)->SetActive(false);
			Vector2 position2 = MAPMANAGER->GetPosition(pt.x, pt.y);
			m_pHuge->SetPosition(position2);
			m_pHuge->SetActive(true);
			m_pHuge->SetState(1);
			m_bAttacked = true;
			MAPMANAGER->ResetValue(pt.x, pt.y, HellTakerMap::eState::LockBox);
		}
		else
		{
			this->DecrementTry();
			return;
		}
			
	}


	m_pDust->Random();
	m_pDust->SetPosition(position);

	this->DecrementTry();
	MAPMANAGER->ResetValue(Oldpt.x, Oldpt.y, HellTakerMap::eState::Helltaker);
	MAPMANAGER->SetValue(pt.x, pt.y, HellTakerMap::eState::Helltaker,this);

	m_nMoveCount = 0;
	m_Time = 0.0f;
	this->m_nState = eState::WALK;

	// Chapter8에서는 Texture와 MapOffset을 변경하여야 한다

	Scene *pCurrentScene = SCENEMANAGER->GetCurrentScene();
	if (pCurrentScene->GetSceneName() == "S11_Chapter8")
	{
		S11_Chapter8  *pScene = (S11_Chapter8*)pCurrentScene;
		switch (direction)
		{
		case eDirection::Up:
			pScene->ChanageMapOffset(-100.0f);
			break;
		case eDirection::Down:
			pScene->ChanageMapOffset(100.0f);
			break;

		}
	}




}


void HellTaker::Render()
{
	if (this->m_nState == eState::WALK)
		m_pDust->Render();
	if (this->m_nState == eState::ATTACK)
	   m_pKick->Render();

	m_pHuge->Render();

	m_pAnimation->Render();
	if (g_bVisibleCollisionCheck)
	{
		if (GetCollisionCheck())
			m_pCollider->SetColor(1.0f, 0.0f, 0.0f);
		else
			m_pCollider->SetColor(0.0f, 1.0f, 0.0f);
		m_pCollider->Render();
	}

	

	
	
}
void HellTaker::DecrementTry()
{
	int nToggle = 0;
	m_nTry = m_nTry - 1; 

	// Trap을 아는 방법

	string name = SCENEMANAGER->GetCurrentScene()->GetSceneName();

	if (name != "S05_Chapter2")
		nToggle = 1;


	// static_cast   --> 컴파일에서 이상유무
	// dynamic_cast  --> Runtime시 제대로 casting이 안되면 null

	for (int y = 0; y < MAPMANAGER->GetRowSize(); y++)
	{
		for (int x = 0; x < MAPMANAGER->GetColSize(); x++) 
		{
			if (!MAPMANAGER->IsTrap(x, y)) continue;
			if (nToggle)
			{
				Trap *pTrap = dynamic_cast<Trap*>(MAPMANAGER->GetSecondObject(x, y));
				if (pTrap)
					pTrap->SetToggle();
			}
		}
	}
}

void HellTaker::Reset()
{
	m_MovePosition = Vector2(0.0f, 0.0f); 
	this->m_nState = eState::IDLE;
	SetRotation(0.0f, 0.0f, 0.0f);
	Audio->Stop("DUST");
	m_bAttacked = false;
	m_bAuqireKey = false;
}


