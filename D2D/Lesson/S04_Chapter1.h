#pragma once
//////////////////////////////////////////////////////////////////
//  S04_Chapter1
//      Game 1st Stage
//////////////////////////////////////////////////////////////////
class S04_Chapter1 : public Scene
{
 // defalut
public:
	void Update()  override;
	void Render()  override;
	void ChangeScene() override;     // 신이 변경될때 초기화하여야 하는 변수
 // Getter
private:

//  Setter
private:

// 변수
private:
	Texture    *m_pTexture   = nullptr;                 // Game background
	class    BackGround   *m_pBackGround  = nullptr;    // 좌우 Hit수, Stage표기
//	class    HellTaker    *m_pHelltaker   = nullptr;
//	class    Mob          *m_pMob[3];
//	class    Box          *m_Box[4]; 
//	class    Pandemonica  *m_pPandemonica = nullptr;
//	class    Fire         *m_pFire = nullptr;
// 함수
private:


// 생성자 & 소멸자
public:
	S04_Chapter1();
	~S04_Chapter1();
};