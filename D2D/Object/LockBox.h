#pragma once

//////////////////////////////////////////////////
// LockBox Object�μ� random�� �̿��Ͽ� �̹�����
// �����Ѵ�
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