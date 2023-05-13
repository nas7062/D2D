#pragma once
class HellTaker : public GameObject
{
public:
	enum eState
	{
		IDLE = 0,
		WALK,
		ATTACK,
		GOAL
	};
public: 
	void   Update(Matrix V, Matrix P)  override;
	void   Render() override;
public:
	void  SetMoveSpeed(float moveSpeed) { m_MoveSpeed = moveSpeed; }
	class Collider* GetCollider() { return m_pCollider; }
	void  SetTry(int value) {m_nTry = value;}
	int   GetTry() { return m_nTry; }
	void  DecrementTry();  
	void  Reset();
	void  SetState(eState state){ m_nState = state; }
	int        m_nTry = 25;
	
private: // 함수
	void       MoveObject(eDirection direction, Vector2& position);
	
private:
	eState     m_nState = eState::IDLE;
	Animation  *m_pAnimation  = nullptr;
	Vector2    m_MovePosition = Vector2(0.0f, 0.0f); // MoveObject에서 저장된다
	class      Dust  *m_pDust  = nullptr;
	class      Kick  *m_pKick  = nullptr;
	class      Huge  *m_pHuge  = nullptr;
	float      m_Time = 0.0f;
	float      m_MoveSpeed = 200.0f;
	int        m_nMoveCount = 0;
	class      Collider      *m_pCollider = nullptr;
	
	bool       m_bAttacked = false;
	bool       m_bAuqireKey = false;
	vector<wstring>     m_strMessage;
public:
	HellTaker();
	~HellTaker();
};