#pragma once
class Key : public GameObject
{
public: 
	void   Update(Matrix V, Matrix P)  override;
	void   Render() override;

public:
	void   SetToggle() { if(m_nState)  m_nState = 0; else m_nState = 1;};
	int    GetState() { return m_nState; }
	void   Reset(){ m_nState = 0; }
private:

private: // ÇÔ¼ö
	

private:
	Animation  *m_pAnimation = nullptr;
	int         m_nState = 0;

public:
	Key();
	~Key();
};