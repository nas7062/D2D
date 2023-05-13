#pragma once
class Kick : public GameObject
{
public: 
	void   Update(Matrix V, Matrix P)  override;
	void   Render() override;

public:
	void   Random();
private:

private: // �Լ�
	

private:
	Animation  *m_pAnimation = nullptr;
	Texture    *m_pTexture = nullptr;
	int         m_nState = 0;

public:
	Kick();
	~Kick();
};