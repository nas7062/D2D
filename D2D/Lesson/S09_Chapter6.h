#pragma once
//////////////////////////////////////////////////////////////////
//  S09_Chapter6
//      Game 1st Stage
//////////////////////////////////////////////////////////////////
class S09_Chapter6 : public Scene
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
	S09_Chapter6();
	~S09_Chapter6();
};