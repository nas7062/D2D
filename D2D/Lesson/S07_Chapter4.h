#pragma once
//////////////////////////////////////////////////////////////////
//  S07_Chapter4
//      Game 1st Stage
//////////////////////////////////////////////////////////////////
class S07_Chapter4 : public Scene
{
 // defalut
public:
	void Update()  override;
	void Render()  override;
	void ChangeScene() override;     // ���� ����ɶ� �ʱ�ȭ�Ͽ��� �ϴ� ����
 // Getter
private:

//  Setter
private:

// ����
private:
	Texture    *m_pTexture   = nullptr;                 // Game background
	class    BackGround   *m_pBackGround  = nullptr;    // �¿� Hit��, Stageǥ��

// �Լ�
private:
	int   GetTry() { return m_nTry; }
	int        m_nTry = 23;

// ������ & �Ҹ���
public:
	S07_Chapter4();
	~S07_Chapter4();
};