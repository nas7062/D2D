#pragma once
class Rect
{
public:
	struct Vertex   // DX에서는 정점에 대한것을 정의하지 않기 때문에 사용자가 정의
	{
		D3DXVECTOR3  Position;
		D3DXCOLOR    Color;
	};
public: 
	void   Update(Matrix V, Matrix P);
	void   Render();

public:         // setter
	void		SetPosition(float x, float y) { m_Position = Vector2(x, y); }
	void		SetPosition(Vector2 position) { m_Position = position; }
	void		SetScale(float x, float y) { m_Scale = Vector2(x, y); }
	void		SetScale(Vector2 scale) { m_Scale = scale; }
	void		SetRotation(float x, float y, float z) { m_Rotation = Vector3(x, y, z); }
	void		SetRotation(Vector3 rotation) { m_Rotation = rotation; }
	void        SetColor(Color value) { m_Color = value; }



private:
	void   CreateVertexBuffer();   // user가 cpu(Device)에 생성한다
	void   UpdateWorld();

private:  // DIRECTX11 
	ID3D11Buffer   *m_pVertexBuffer = nullptr;  // 정점 Buffer
	ID3D11Buffer   *m_pIndexBuffer  = nullptr;  // 정점 index Buffer
	Shader         *m_pShader       = nullptr;
	Vertex          vertices[6];
	int             m_nVertexCount = 0;
private:
	Vector2        m_Position = Vector2(0.0f, 0.0f);
	Vector2        m_Scale    = Vector2(1.0f, 1.0f);
	Vector3        m_Rotation = Vector3(0.0f, 0.0f, 0.0f);
	Color          m_Color = Color(0.0f, 1.0f, 0.0f, 1.0f);

public:
	Rect();
	~Rect();
};