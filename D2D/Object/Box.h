#pragma once

//////////////////////////////////////////////////
// Box Object�μ� random�� �̿��Ͽ� �̹�����
// �����Ѵ�
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
	int        m_nID_SRV = 0;  // Texture 1�� �̹����� ������ ������ �ֵ���
	Texture    *m_pTexture   = nullptr;
	class      Collider      *m_pCollider = nullptr;
	vector<ID3D11ShaderResourceView*>  m_cvSRVs;

public:
	Box();
	~Box();
};