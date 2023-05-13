#pragma once

//////////////////////////////////////////////////
// Box Object로서 random을 이용하여 이미지를
// 설정한다
/////////////////////////////////////////////////
class Box : public GameObject
{
public: 
	void   Update(Matrix V, Matrix P)  override;
	void   Render() override;

public:
	class Collider*  GetCollider() { return m_pCollider; }
	void   MoveObject(eDirection direction, Vector2& position);

private:
	void      CreateShaderResourceView(wstring strImageFile);
private:
	int        m_nID_SRV = 0;  // Texture 1에 이미지를 여려개 넣을수 있도록
	Texture    *m_pTexture   = nullptr;
	class      Collider      *m_pCollider = nullptr;
	vector<ID3D11ShaderResourceView*>  m_cvSRVs;

public:
	Box();
	~Box();
};