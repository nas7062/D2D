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
	void ChangeScene() override;     // 신이 변경될때 초기화하여야 하는 변수
 // Getter
private:

//  Setter
private:

// 변수
private:
	Texture    *m_pTexture   = nullptr;                 // Game background
	class    BackGround   *m_pBackGround  = nullptr;    // 좌우 Hit수, Stage표기

// 함수
private:
	int   GetTry() { return m_nTry; }
	int        m_nTry = 23;

// 생성자 & 소멸자
public:
	S07_Chapter4();
	~S07_Chapter4();
};