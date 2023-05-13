#pragma once
class BackGround : public GameObject
{
public: 
	void   Update(Matrix V, Matrix P)  override;
	void   Render() override;

public:

private:

private:
	Texture  *m_pTextureBack1 = nullptr;
	Texture  *m_pTextureBack2 = nullptr;
public:
	BackGround();
	~BackGround();
};