#pragma once
//////////////////////////////////////////////////////////////////
//  S06_Chapter3
//      Game 1st Stage
//////////////////////////////////////////////////////////////////
class S06_Chapter3 : public Scene
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
	void   MakeTrap(int id, int x, int y, int state);

// ����
private:
	Texture    *m_pTexture   = nullptr;                 // Game background
	class    BackGround   *m_pBackGround  = nullptr;    // �¿� Hit��, Stageǥ��
//	class    HellTaker    *m_pHelltaker   = nullptr;
//	class    Mob          *m_pMob[3];
//	class    Box          *m_Box[4]; 
//	class    Pandemonica  *m_pPandemonica = nullptr;
//	class    Fire         *m_pFire = nullptr;
// �Լ�
private:
	int   GetTry() { return m_nTry; }
	int        m_nTry = 32;

// ������ & �Ҹ���
public:
	S06_Chapter3();
	~S06_Chapter3();
};