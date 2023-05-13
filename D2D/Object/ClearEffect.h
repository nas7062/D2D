#pragma once
class ClearEffect : public GameObject
{
public: 
	void   Update(Matrix V, Matrix P)  override;
	void   Render() override;

private:

private: // ÇÔ¼ö
	

private:
	Animation  *m_pAnimation = nullptr;
	int         m_nState = 0;

public:
	ClearEffect();
	~ClearEffect();
};