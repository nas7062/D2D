#pragma once
class Mob : public GameObject
{
public:
	enum eState
	{
		IDLE = 0,
		WALK,
		DEAD
	};
public: 
	void   Update(Matrix V, Matrix P)  override;
	void   Render() override;
	void   Reset();
	void   SetState(eState state) { m_nState = state; }
public:
	void   MoveObject(eDirection direction, Vector2& position);
	void   SetMoveSpeed(float moveSpeed) { m_MoveSpeed = moveSpeed; }
	class  Collider*  GetCollider() { return m_pCollider; }
	vector<class Bone*>    m_cvBones;


private:
	eState     m_nState = eState::IDLE;

private: // ÇÔ¼ö
	

private:
	Animation  *m_pAnimation = nullptr;
	float      m_MoveSpeed = 200.0f;
	class      Collider      *m_pCollider = nullptr;

public:
	Mob();
	~Mob();
};