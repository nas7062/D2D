#pragma once
//////////////////////////////////////////////////////////////////
//  S02_IntroScene
//      웹툰형태의 설명을 보여주는 Scene
//////////////////////////////////////////////////////////////////
class S02_IntroScene : public Scene
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
	Animation       *m_pAnimation = nullptr;
	class  Rect     *m_pRect      = nullptr;
	vector<wstring> m_cvMessage;
	float    m_DelayTime = 0.0f;
// 함수
private:


// 생성자 & 소멸자
public:
	S02_IntroScene();
	~S02_IntroScene();
};