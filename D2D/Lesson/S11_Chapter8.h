#pragma once
//////////////////////////////////////////////////////////////////
//  S11_Chapter8
//      Game 1st Stage
//////////////////////////////////////////////////////////////////
class S11_Chapter8 : public Scene
{
	// defalut
public:
	void Update()  override;
	void Render()  override;
	void ChangeScene() override;     // ���� ����ɶ� �ʱ�ȭ�Ͽ��� �ϴ� ����

public:
	void ChanageMapOffset(float y);


	// Getter
private:

	//  Setter



private:
	void   MakeTrap(int id, int x, int y, int state);
	void   SetPandemonica(bool bInit);
	void   SetHelltaker(bool bInit);
	void   SetMob(bool bInit);

	// ����
private:
	Texture* m_pTexture = nullptr;                 // Game background
	class    BackGround* m_pBackGround = nullptr;    // �¿� Hit��, Stageǥ��
//	class    HellTaker    *m_pHelltaker   = nullptr;
//	class    Mob          *m_pMob[3];
//	class    Box          *m_Box[4]; 
//	class    Pandemonica  *m_pPandemonica = nullptr;
//	class    Fire         *m_pFire = nullptr;
// �Լ�
private:


	// ������ & �Ҹ���
public:
	S11_Chapter8();
	~S11_Chapter8();
};