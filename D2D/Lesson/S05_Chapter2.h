#pragma once

//////////////////////////////////////////////////////////////////
// S05_Chapter2
//		Game 1st Stage
//////////////////////////////////////////////////////////////////
class S05_Chapter2 : public Scene
{
 // defalut
public:
	void Update()  override;
	void Render()  override;
	void ChangeScene() override;	// ���� ����� �� �ʱ�ȭ�Ͽ��� �ϴ� ����
 // Getter
private:

//  Setter
private:

// ����
private:
	Texture		*m_pTexture   = nullptr;			// Game background
	class	BackGround	*m_pBackground = nullptr;	// �¿� Try��, Stageǥ��
//	class	HellTaker	*m_pHelltaker  = nullptr;
//	class	Mob			*m_pMob[3];
//	class	Box			*m_Box[4];
//	class	Pandemonica	*m_pPandemonica = nullptr;
//	class	Fire		*m_pFire = nullptr;
// �Լ�
private:
	int   GetTry() { return m_nTry; }
	int        m_nTry = 24;

// ������ & �Ҹ���
public:
	S05_Chapter2();
	~S05_Chapter2();
};