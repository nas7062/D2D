#pragma once
class Fire : public GameObject
{
public: 
	void   Update(Matrix V, Matrix P)  override;
	void   Render() override;
	void   SetState(int state){ m_nFire = state; }

public:

private:

private: // ÇÔ¼ö
	void      CreateShaderResourceView(wstring strImageFile);

private:
	Animation  *m_pAnimation = nullptr;
	Texture    *m_pTexture = nullptr;
	int         m_nFire = 1;
	vector<ID3D11ShaderResourceView*>  m_cvSRVs;

public:
	Fire();
	~Fire();
};