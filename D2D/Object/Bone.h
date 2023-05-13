#pragma once

//////////////////////////////////////////////////
// Bone Object�μ� random�� �̿��Ͽ� �̹�����
// �����Ѵ�
/////////////////////////////////////////////////
class Bone : public GameObject
{
public: 
	void   Update(Matrix V, Matrix P)  override;
	void   Render() override;

public:
	class Collider*  GetCollider() { return m_pCollider; }
	void   MoveObject(eDirection direction, Vector2& position);
	void   Reset() { m_Gravirty = 0.0f; };

private:
	void      CreateShaderResourceView(wstring strImageFile);
private:
	int        m_nID_SRV = 0;  // Texture 1�� �̹����� ������ ������ �ֵ���
	Texture    *m_pTexture   = nullptr;
	class      Collider      *m_pCollider = nullptr;
	float      m_MoveSpeed = 0.0f;
	float      m_Gravirty = 0.0f;
	int        m_nID=0;
	vector<ID3D11ShaderResourceView*>  m_cvSRVs;

public:
	Bone(int id);
	~Bone();
};