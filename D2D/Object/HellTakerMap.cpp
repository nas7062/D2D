#include  "framework.h"
#include  "HellTakerMap.h"
///////////////////////////////////////////////////////////
// 생성자
//////////////////////////////////////////////////////////
HellTakerMap::HellTakerMap()
{
}

HellTakerMap::~HellTakerMap()
{
	Clear();
}
//////////////////////////////////////////////////////
// m_cvMaps를 초기화
//////////////////////////////////////////////////////
void HellTakerMap::Clear()
{
	for (UINT i = 0; i < m_cvMaps.size(); i++)
		delete m_cvMaps[i];
	m_cvMaps.erase(m_cvMaps.begin(), m_cvMaps.end());
	SizeX = SizeY;
}
//////////////////////////////////////////////////////
//  Map의 Size를 초기생성한다
//////////////////////////////////////////////////////
void HellTakerMap::SetSize(int x, int y)
{
	Clear();

	for (int i = 0; i < (x*y); i++)
	{
		HTMAP *pMap = new HTMAP;
		pMap->m_State = eState::Wall;
		pMap->m_pGameObject = nullptr;
		pMap->m_pSecondObject = nullptr;
		m_cvMaps.push_back(pMap);
	}
	SizeX = x;
	SizeY = y;

}

void HellTakerMap::SetValue(int x, int y, eState state, GameObject * pObject)
{
	int    id = SizeX * y + x;   // 5x4 (x5,y4)  --> 1,1
	eState oldSate = m_cvMaps[id]->m_State;

	m_cvMaps[id]->m_State = (eState)((int)oldSate | (int)state);
	
	if (state == HellTakerMap::eState::Trap)
	{
		m_cvMaps[id]->m_pSecondObject = pObject;
		if (m_cvMaps[id]->m_pGameObject)
			return;
	}
	if (state == HellTakerMap::eState::Key)
	{
		m_cvMaps[id]->m_pSecondObject = pObject;
		if (m_cvMaps[id]->m_pGameObject)
			return;
	}


	m_cvMaps[id]->m_pGameObject = pObject;
}

void HellTakerMap::ResetValue(int x, int y, eState state)
{
	int    id = SizeX * y + x;   // 5x4 (x5,y4)  --> 1,1
	eState oldSate = m_cvMaps[id]->m_State;

	m_cvMaps[id]->m_State = (eState)((int)oldSate ^ (int)state);
	m_cvMaps[id]->m_pGameObject = NULL;
}

Vector2 HellTakerMap::GetPosition(int x, int y)
{
	Vector2 position;

	position.x = m_Offset.x + x * m_OffsetSize.x;
	position.y = m_Offset.y - y * m_OffsetSize.y;

	return position;
}

POINT HellTakerMap::GetMapXY(Vector2 position)
{
	position.x = fabs(position.x - m_Offset.x);
	position.y = fabs(position.y - m_Offset.y);

	POINT value = POINT{ 0,0 };

	value.x = (int)(position.x / m_OffsetSize.x);
	value.y = (int)(position.y / m_OffsetSize.y);
	return value;
}
////////////////////////////////////////////////////////////
//  Map에 있는 GameObject가져오기
////////////////////////////////////////////////////////////
GameObject * HellTakerMap::GetGameObject(int x, int y)
{
	int    id = SizeX * y + x;   
	return  m_cvMaps[id]->m_pGameObject;
}

GameObject * HellTakerMap::GetSecondObject(int x, int y)
{
	int    id = SizeX * y + x;
	return  m_cvMaps[id]->m_pSecondObject;
}

int HellTakerMap::GetValue(int x, int y)
{
	int    id = SizeX * y + x;   // 5x4 (x5,y4)  --> 1,1
	eState oldSate = m_cvMaps[id]->m_State;
	return  (int)oldSate;
}

bool HellTakerMap::IsWall(int x, int y)
{
	if (y < 0 || x < 0 || SizeX <= x || SizeY <= y)
		return true;

	int    id = SizeX * y + x;   // 5x4 (x5,y4)  --> 1,1
	eState oldSate = m_cvMaps[id]->m_State;

	if (oldSate == 0)
		return true;
	return false;
}

bool HellTakerMap::IsMob(int x, int y)
{
	int    id = SizeX * y + x;   // 5x4 (x5,y4)  --> 1,1
	eState oldSate = m_cvMaps[id]->m_State;

	if (oldSate & eState::Mob)
		return true;
	return false;
}

bool HellTakerMap::IsBox(int x, int y)
{
	int    id = SizeX * y + x;   // 5x4 (x5,y4)  --> 1,1
	eState oldSate = m_cvMaps[id]->m_State;

	// Box하고 Trap이 있는 경우
	oldSate = (eState)((int)oldSate ^ (int)eState::Trap);


	if (oldSate & eState::BOX)
		return true;
	return false;
}

bool HellTakerMap::IsGoal(int x, int y, POINT& pt)
{
	if (IsGoalEx2(x - 1, y,pt))
		return true;
	if (IsGoalEx2(x + 1, y,pt))
		return true;
	if (IsGoalEx2(x, y+1,pt))
		return true;
	if (IsGoalEx2(x, y - 1,pt))
		return true;
	return false;

}
bool HellTakerMap::IsGoalEx3(int x, int y, POINT& pt)
{
	if (IsGoalEx2(x , y, pt))
		return true;
	return false;

}



bool HellTakerMap::IsGoalEx2(int x, int y, POINT& pt)
{

	int    id = SizeX * y + x;   // 5x4 (x5,y4)  --> 1,1

	if (y < 0 || x < 0 || SizeX <= x || SizeY <= y)
		return false;

	eState oldSate = m_cvMaps[id]->m_State;

	if (oldSate & eState::Goal)
	{
		pt.x = x;
		pt.y = y;
		return true;
	}
		
	return false;
}




bool HellTakerMap::IsGoalEx(int x, int y)
{
	//bool a = IsGoal(x, y - 1);
	//bool b = IsGoal(x, y + 1);
	//
	//if (a == true || b == true)
	//	return true;
	//return false;

	return false;

}

bool HellTakerMap::IsTrap(int x, int y)
{

	int    id = SizeX * y + x;   // 5x4 (x5,y4)  --> 1,1

	if (y < 0 || x < 0 || SizeX <= x || SizeY <= y)
		return false;

	eState oldSate = m_cvMaps[id]->m_State;

	if (oldSate & eState::Trap)
		return true;
	return false;
}

bool HellTakerMap::IsKey(int x, int y)
{
	int    id = SizeX * y + x;   // 5x4 (x5,y4)  --> 1,1

	if (y < 0 || x < 0 || SizeX <= x || SizeY <= y)
		return false;

	eState oldSate = m_cvMaps[id]->m_State;

	if (oldSate & eState::Key)
		return true;
	return false;
}

bool HellTakerMap::IsLockBox(int x, int y)
{
	int    id = SizeX * y + x;   // 5x4 (x5,y4)  --> 1,1

	if (y < 0 || x < 0 || SizeX <= x || SizeY <= y)
		return false;

	eState oldSate = m_cvMaps[id]->m_State;

	if (oldSate & eState::LockBox)
		return true;
	return false;
}


