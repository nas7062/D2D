#pragma once
class Pandemonica : public GameObject
{
public: 
	void   Update(Matrix V, Matrix P)  override;
	void   Render() override;

public:
	enum eState
	{
		PANDEMONICA = 0,
		MODEUS,
		AZAZEL,
		ZDRADA,
		MALINA,
		DEMON1,
		DEMON7
	};

public:
	void   MoveObject(eDirection direction, Vector2& position);
	void   SetMoveSpeed(float moveSpeed) { m_MoveSpeed = moveSpeed; }
	class  Collider*  GetCollider() { return m_pCollider; }
	bool   IsSuccess() { return m_bSuccess; }
	void   SetSuccess(bool value) { m_bSuccess = value; m_Time = 0.0f;}
	void   SetState(eState state) { m_nState = state; }

private:
	eState     m_nState = eState::PANDEMONICA;
	class      ClearEffect  *m_pEffect = nullptr;
private: // ÇÔ¼ö
	

private:
	Texture    *m_pHeart = nullptr;
	Animation  *m_pAnimation = nullptr;
	float      m_MoveSpeed = 200.0f;
	class      Collider      *m_pCollider = nullptr;
	bool       m_bSuccess = false;
	float      m_Time = 0.0f;
	float      m_Heart_Move = 0.0f;
public:
	Pandemonica();
	~Pandemonica();
};