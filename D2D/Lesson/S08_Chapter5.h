#pragma once
//////////////////////////////////////////////////////////////////
//  
// 
// 
// 
//      Game 1st Stage
//////////////////////////////////////////////////////////////////
class S08_Chapter5 : public Scene
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
//	class    HellTaker    *m_pHelltaker   = nullptr;
//	class    Mob          *m_pMob[3];
//	class    Box          *m_Box[4]; 
//	class    Pandemonica  *m_pPandemonica = nullptr;
//	class    Fire         *m_pFire = nullptr;
// �Լ�
private:
	int   GetTry() { return m_nTry; }
	int        m_nTry = 23;

// ������ & �Ҹ���
public:
	S08_Chapter5();
	~S08_Chapter5();
};