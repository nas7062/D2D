#pragma once
//////////////////////////////////////////////////////////////////
//  S01_IntroScene
//      심연     :  무한배경
//      벨플라이 :   이미지
//      설명.....
//////////////////////////////////////////////////////////////////
class S01_IntroScene : public Scene
{
 // defalut
public:
	void Update()  override;
	void Render()  override;
 // Getter
private:

//  Setter
private:

// 변수
private:
	Texture* m_pBackground[2];       // 무한배경용 bACKGROUND
	Texture* m_pBeelFly = nullptr;   // 배경위에 올라오는 Image
	float    m_DelayTime = 0.0f;     // 다음신을 가기위한 시간 설정값
// 함수
private:
	void     OnButton1(int id);
	void     OnButton2(int id);
	void     OnButton3(int id);

// 생성자 & 소멸자
public:
	S01_IntroScene();
	~S01_IntroScene();
};