#pragma once
#include  "Base/Scene.h"
//////////////////////////////////////////////////////////////////
// S00_DialogSucces
//		웹툰형태의 설명을 보여주는 Scene 
//////////////////////////////////////////////////////////////////
class S00_DialogSucces : public Scene
{
	// defalut
public:
	void Update()  override;
	void Render()  override;
	void ChangeScene() override;

public:
	wstring				m_strButtonName1;
	wstring				m_strButtonName2;
	wstring				m_strBanner;
	string              m_strSuccessScene;
	string              m_strNoSuccessScene;
	vector<wstring>     m_strMessage;


	// Getter
private:

	//  Setter
private:

	// 변수
private:
	enum eState
	{
		DIALOG = 0,
		FADE_IN ,
		FADE_OUT
	};
	eState m_nState = eState::DIALOG;
private:
	const float MAX_TIME = 3.0f;

	Animation	*m_pPandAnimation1 = nullptr;	// Pandemonica용 클립을 담는 Animation
	Animation	*m_pPandAnimation2 = nullptr;	// Pandemonica용 클립을 담는 Animation
	Animation	*m_pPandAnimation3 = nullptr;	// Pandemonica용 클립을 담는 Animation
	Animation	*m_pPandAnimation4 = nullptr;	// Pandemonica용 클립을 담는 Animation
	Animation	*m_pPandAnimation5 = nullptr;	// Pandemonica용 클립을 담는 Animation
	Animation* m_pPandAnimation6 = nullptr;	// Pandemonica용 클립을 담는 Animation
	Animation* m_pPandAnimation7 = nullptr;	// Pandemonica용 클립을 담는 Animation



	Animation   *m_pPandAnimation = nullptr;  // pointer로 사용
	vector<wstring> m_cvMessage;
	int	str_num = 0;	// m_cvMessage(대사)의 Index를 나타내는 변수
	int page = 0;		// 해당 다이얼로그가 보여주는 이벤트의 진행도를 나타내는 변수
	float	m_Time = 0.0f;

	// 함수
private:
	float	F(float time) { return 1.0f - pow(1.0f - time, 3); }	// 경과시간에 따른 오브젝트의 움직임을 조절 (Cubic EaseOut 함수를 사용)
	void    OnButtonSuccess(int id);
	void    OnButtonFail(int id);
	// 생성자 & 소멸자
public:
	S00_DialogSucces();
	~S00_DialogSucces();
};