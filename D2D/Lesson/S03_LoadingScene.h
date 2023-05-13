#pragma once
//////////////////////////////////////////////////////////////////
//  S03_LoadingScene
//      웹툰형태의 설명을 보여주는 Scene
//////////////////////////////////////////////////////////////////
class S03_LoadingScene : public Scene
{
 // defalut
public:
	void Update()  override;
	void Render()  override;
	void ChangeScene() override;
 // Getter
public:

//  Setter
public:
	void  SetState(int state) { m_nState = state; }

public:
	int					m_nState = 1;



// 변수
private:
	Animation  *m_pAnimation = nullptr;





// 함수
private:


// 생성자 & 소멸자
public:
	S03_LoadingScene();
	~S03_LoadingScene();
};