#pragma once
class Trap : public GameObject
{
public:
	enum eState
	{
		UP = 0,
		DOWN,
		DOWN_UP,
		UP_DOWN
	};
	


public: 
	void   Update(Matrix V, Matrix P)  override;
	void   Render() override;

public:
	void   SetToggle();  
	int    GetState() { if (m_nState2 == eState::UP) return 0; else return 1; }
	void   Reset() { m_nState2 = eState::UP; }
	void   SetState(int state); 
	int    GetNextState();
private:

private: // ÇÔ¼ö
	

private:
	Animation  *m_pAnimation = nullptr;
	int         m_nState = 0;
	eState      m_nState2 = eState::UP;

public:
	Trap();
	~Trap();
};