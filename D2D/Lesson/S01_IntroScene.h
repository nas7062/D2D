#pragma once
//////////////////////////////////////////////////////////////////
//  S01_IntroScene
//      �ɿ�     :  ���ѹ��
//      ���ö��� :   �̹���
//      ����.....
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

// ����
private:
	Texture* m_pBackground[2];       // ���ѹ��� bACKGROUND
	Texture* m_pBeelFly = nullptr;   // ������� �ö���� Image
	float    m_DelayTime = 0.0f;     // �������� �������� �ð� ������
// �Լ�
private:
	void     OnButton1(int id);
	void     OnButton2(int id);
	void     OnButton3(int id);

// ������ & �Ҹ���
public:
	S01_IntroScene();
	~S01_IntroScene();
};