#pragma once
////////////////////////////////////////////////////////
//  Camera Class
////////////////////////////////////////////////////////
class Camera
{
public:
	static Camera* GetInstance()
	{
		static Camera singleToneInstance;
		return &singleToneInstance;
	}
	void		Update();                    // View, Projection Matrix Update
	void		Update(Matrix V, Matrix P);  // ī�޶� ���� m_pTexture Update
	void		Render();                    //  render
public:			// Setter
	void		SetPosition(float x, float y)  { m_Position = Vector2(x, y); }
	void		SetPosition(Vector2  position) { m_Position = position; }
	void		SetOffset(float x, float y)    { m_Offset = Vector2(x, y); }
	void		SetOffset(Vector2  offset)     { m_Offset = offset; }
	void		SetObject(class GameObject *pObject) { m_pGameObj = pObject; }
	void        SetEffect() { m_bEffect = true; m_PlayTime = 0.0f;}
	void		SetMoveSpeed(float x, float y) { m_MoveSpeed = Vector2(x, y); }
	void		SetMoveSpeed(Vector2  speed)   { m_MoveSpeed = speed; }
	void        SetLeftCorner(Vector2 left)    { m_Left = left; }
	void        SetRightCorner(Vector2 right) { m_Right = right; }
	void        SetLimit(bool limit) { m_bLimit = limit; }
	void        SetKeyInput(bool keyinput)    { m_bkeyInput = keyinput; }
public:    // Getter
	Vector2		GetPosition() { return m_Position; }
	Matrix		GetViewMatrix();
	Matrix		GetProjectionMatrix();
	void		WCtoVC(Vector2& position);   // Window Coord -> View Coord
	void        VCtoWC(Vector2 & position);  // View Coord -> Window Coord

private:
	void		PreUpdate();                 // Ű���� �Է½� ī�޶� �̵� ��ġ ��ȯ
    Matrix		LookAt(Vector3 eye, Vector3 at, Vector3 upVector);
	void        Effect();
private:
	class			Texture *m_pTexture = nullptr;
	Vector2			m_Position  = Vector2(0.0f, 0.0f);
	Vector2			m_MoveSpeed = Vector2(200.0f, 200.0f); // ī�޶� ��ġ ����� �ð��� ���� Speed
	Matrix			m_View;
	Matrix			m_Projection;
	class           GameObject		*m_pGameObj = nullptr;  // GameObject�� �����ϸ� ī�޶� GameOject�� �پ� �ִ� �� ó�� �ൿ
	Vector2         m_Offset = Vector2(0.0f, 0.0f);
	Vector2         m_Left = Vector2(0.0f, 0.0f);
	Vector2         m_Right = Vector2(0.0f, 0.0f);
private:
	bool            m_bEffect  = false;
	bool            m_bLimit = false;
	float           m_PlayTime  = 0.0f;   // effect �Ǵ� �ð��� ����
	float           m_DelayTime = 0.5f;   // effect �߻��� delay �Ǵ� �ð�
	bool            m_bkeyInput = true;
public:
	~Camera();
private:
	Camera();
	
};

