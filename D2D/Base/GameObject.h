#pragma once
////////////////////////////////////////////////////////
//  Gameobject �߻�ȭ Class
//       --> Intro,Boss : Class�� ���� ������ ���� 
//           ��ӹ޾Ƽ� ����� �ϰ���
//  1. Virtual�� ���ǵ� �Լ��� ������ �߻�ȭ Class��� �Ѵ�
//  2. Delete�Ǵ� ���� �˾ƺ��� :  Child -> Parent
//  3. private, protected �˾ƺ��� :
////////////////////////////////////////////////////////
class GameObject
{
public:
	enum eDirection
	{
		Left = 0,
		Right,
		Up,
		Down
	};

public:
	virtual void  Update(Matrix V, Matrix P) = 0;        // ���� �����Լ�, ��ӹ��� ������ ����
	virtual void  Render() = 0;                          // ���� �����Լ�, ��ӹ��� ������ ����
	                                  
	// Setter
	void		SetPosition(float x, float y) { m_Position = Vector2(x, y); }
	void		SetPosition(Vector2 position) { m_Position = position; }
	void		SetScale(float x, float y) { m_Scale = Vector2(x, y); }
	void		SetScale(Vector2 scale) { m_Scale = scale; }
	void		SetRotation(float x, float y, float z) { m_Rotation = Vector3(x, y, z); }
	void		SetRotation(Vector3 rotation) { m_Rotation = rotation; }
	void        SetName(string name) { m_strName = name; }
	void        SetCollisionCheck(bool collision) { m_bCollisionCheck = collision; }
	void        SetActive(bool active) { m_bActive = active; }
	// Getter
	Vector2     GetPosition() { return m_Position; }
	Vector2     GetScale()    { return m_Scale; }
	Vector3     GetRotation() { return m_Rotation; }
	string      GetName()     { return m_strName; }
	bool        IsActive()    { return m_bActive; }
	bool        GetCollisionCheck() { return m_bCollisionCheck; }

protected: // �ٸ� Class���� ���� �ȵǴ� �� --> ��ӹ��� Class������ ���ٵ�
	Vector2   m_Scale = Vector2(1.0f, 1.0f);       // Scale
	Vector2   m_Position = Vector2(0.0f, 0.0f);       // ��ǥ
	Vector3   m_Rotation = Vector3(0.0f, 0.0f, 0.0f);  // ȸ��
	string    m_strName;    // Object Name
	bool      m_bActive = true;
	bool      m_bCollisionCheck = false;   // �浹�˻�� Check

private:   // �ٸ� Class���� ���� �ȵǴ� �� --> ��ӹ��� Class������ ���� �ȵ�


public:
	GameObject() {};
	~GameObject(){};
};

