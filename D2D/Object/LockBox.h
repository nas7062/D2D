#pragma once

//////////////////////////////////////////////////
// LockBox Object로서 random을 이용하여 이미지를
// 설정한다
/////////////////////////////////////////////////
class LockBox : public GameObject
{
public: 
	void   Update(Matrix V, Matrix P)  override;
	void   Render() override;

public:

private:
	Texture    *m_pTexture   = nullptr;


public:
	LockBox();
	~LockBox();
};