#pragma once
class Dust : public GameObject
{
public: 
	void   Update(Matrix V, Matrix P)  override;
	void   Render() override;

public:
	void   Random();
private:

private: // ÇÔ¼ö
	

private:
	Animation  *m_pAnimation = nullptr;
	Texture    *m_pTexture = nullptr;
	int         m_nFire = 1;
	int         m_nState = 0;

public:
	Dust(int nFire = 1);
	~Dust();
};