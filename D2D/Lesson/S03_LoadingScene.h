#pragma once
//////////////////////////////////////////////////////////////////
//  S03_LoadingScene
//      ���������� ������ �����ִ� Scene
//////////////////////////////////////////////////////////////////
class S03_LoadingScene : public Scene
{
 // defalut
public:
	void Update()  override;
	void Render()  override;
	void ChangeScene() override;
 // Getter
public:

//  Setter
public:
	void  SetState(int state) { m_nState = state; }

public:
	int					m_nState = 1;



// ����
private:
	Animation  *m_pAnimation = nullptr;





// �Լ�
private:


// ������ & �Ҹ���
public:
	S03_LoadingScene();
	~S03_LoadingScene();
};