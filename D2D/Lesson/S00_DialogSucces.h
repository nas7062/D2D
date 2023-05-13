#pragma once
#include  "Base/Scene.h"
//////////////////////////////////////////////////////////////////
// S00_DialogSucces
//		���������� ������ �����ִ� Scene 
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

	// ����
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

	Animation	*m_pPandAnimation1 = nullptr;	// Pandemonica�� Ŭ���� ��� Animation
	Animation	*m_pPandAnimation2 = nullptr;	// Pandemonica�� Ŭ���� ��� Animation
	Animation	*m_pPandAnimation3 = nullptr;	// Pandemonica�� Ŭ���� ��� Animation
	Animation	*m_pPandAnimation4 = nullptr;	// Pandemonica�� Ŭ���� ��� Animation
	Animation	*m_pPandAnimation5 = nullptr;	// Pandemonica�� Ŭ���� ��� Animation
	Animation* m_pPandAnimation6 = nullptr;	// Pandemonica�� Ŭ���� ��� Animation
	Animation* m_pPandAnimation7 = nullptr;	// Pandemonica�� Ŭ���� ��� Animation



	Animation   *m_pPandAnimation = nullptr;  // pointer�� ���
	vector<wstring> m_cvMessage;
	int	str_num = 0;	// m_cvMessage(���)�� Index�� ��Ÿ���� ����
	int page = 0;		// �ش� ���̾�αװ� �����ִ� �̺�Ʈ�� ���൵�� ��Ÿ���� ����
	float	m_Time = 0.0f;

	// �Լ�
private:
	float	F(float time) { return 1.0f - pow(1.0f - time, 3); }	// ����ð��� ���� ������Ʈ�� �������� ���� (Cubic EaseOut �Լ��� ���)
	void    OnButtonSuccess(int id);
	void    OnButtonFail(int id);
	// ������ & �Ҹ���
public:
	S00_DialogSucces();
	~S00_DialogSucces();
};