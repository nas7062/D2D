#pragma once
class Azazel : public GameObject
{
public: 
	void   Update(Matrix V, Matrix P)  override;
	void   Render() override;


public:
	void   MoveObject(eDirection direction, Vector2& position);
	void   SetMoveSpeed(float moveSpeed) { m_MoveSpeed = moveSpeed; }
	class  Collider*  GetCollider() { return m_pCollider; }
	bool   IsSuccess() { return m_bSuccess; }
	void   SetSuccess(bool value) { m_bSuccess = value; m_Time = 0.0f;}

private:
	enum eState 
	{
        IDLE = 0,
		WALK
	};
	eState     m_nState = eState::IDLE;

private: // ÇÔ¼ö
	

private:
	Animation  *m_pAnimation = nullptr;
	float      m_MoveSpeed = 200.0f;
	class      Collider      *m_pCollider = nullptr;
	bool       m_bSuccess = false;
	float      m_Time = 0.0f;

public:
	Azazel();
	~Azazel();
};