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
	void ChangeScene() override;     // 신이 변경될때 초기화하여야 하는 변수

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

	// 변수
private:
	Texture* m_pTexture = nullptr;                 // Game background
	class    BackGround* m_pBackGround = nullptr;    // 좌우 Hit수, Stage표기
//	class    HellTaker    *m_pHelltaker   = nullptr;
//	class    Mob          *m_pMob[3];
//	class    Box          *m_Box[4]; 
//	class    Pandemonica  *m_pPandemonica = nullptr;
//	class    Fire         *m_pFire = nullptr;
// 함수
private:


	// 생성자 & 소멸자
public:
	S11_Chapter8();
	~S11_Chapter8();
};