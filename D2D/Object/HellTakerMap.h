#pragma once

#define  MAPMANAGER          HellTakerMap::GetInstance() 
//////////////////////////////////////////////////////////
// Map은 신마다 별도로 가지고 있을 필요가 없기 때문에
// 싱글톤으로 생성
/////////////////////////////////////////////////////////
class HellTakerMap
{
public:
	static HellTakerMap* GetInstance()
	{
		static HellTakerMap singleToneInstance;
		return &singleToneInstance;
	}
	void   Clear();  // 메모리가 생성된것은 지워야한다
public:
	enum eState
	{
		Wall = 0,        // Move 할 수 없는 곳
		Move = 1,        // Move가능
		Helltaker = 2,   // Helltaker          0011 1011
		BOX  = 4,
		Mob  = 8,
		Trap = 16,
		Goal = 32,
		Key  = 64,
		LockBox = 128
	};

public: // setter
	void   SetSize(int x, int y);
	void   SetValue(int x, int y, eState state, GameObject *pObject);
	void   ResetValue(int x, int y, eState state);
	void   SetOffSet(float x, float y) { m_Offset = Vector2(x, y); }
public: // getter
	Vector2     GetMapOffSet() { return m_Offset; }
	Vector2		GetPosition(int x, int y);
	POINT		GetMapXY(Vector2 position);
	GameObject* GetGameObject(int x, int y);
	GameObject* GetSecondObject(int x, int y);
	int			GetRowSize() { return SizeY; }
	int			GetColSize() { return SizeX; }
	int			GetValue(int x, int y);
	bool		IsWall(int x, int y);
	bool		IsMob(int x, int y);
	bool        IsBox(int x, int y);
	bool        IsGoal(int x, int y,POINT& pt);
	bool        IsGoalEx(int x, int y);
	bool        IsGoalEx2(int x, int y, POINT& pt);
	bool        IsGoalEx3(int x, int y, POINT& pt);
	bool        IsTrap(int x, int y);
	bool        IsKey(int x, int y);
	bool        IsLockBox(int x, int y);

private:
	struct HTMAP
	{
		eState m_State;
		class  GameObject* m_pGameObject;
		class  GameObject* m_pSecondObject;
	};
	vector<HTMAP*> m_cvMaps;
	int    SizeX = 0;
	int    SizeY = 0;
	Vector2  m_Offset      = Vector2(-400.0f, 350.f);
	Vector2  m_OffsetSize  = Vector2(100.0f, 100.f);
private:
	

private:
	HellTakerMap();
public:
	~HellTakerMap();
};