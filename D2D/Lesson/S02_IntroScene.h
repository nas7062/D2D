#pragma once
//////////////////////////////////////////////////////////////////
//  S02_IntroScene
//      ���������� ������ �����ִ� Scene
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

// ����
private:
	Animation       *m_pAnimation = nullptr;
	class  Rect     *m_pRect      = nullptr;
	vector<wstring> m_cvMessage;
	float    m_DelayTime = 0.0f;
// �Լ�
private:


// ������ & �Ҹ���
public:
	S02_IntroScene();
	~S02_IntroScene();
};