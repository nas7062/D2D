#pragma once
#include "Base/Scene.h"
//////////////////////////////////////////////////////////////////
// S04
// ù���� ���� ��������
//////////////////////////////////////////////////////////////////
class S10_Chapter7 : public Scene
{
 // defalut
public:
	void Update()  override;
	void Render()  override;

	void ChangeScene() override;
 // Getter
private:

//  Setter
private:

// ����
private:
	Texture *m_pTexture = nullptr;				// Game backGround
	class BackGround *m_pBackground = nullptr;	//�¿� �ϳ��� ������ ��Ʈ�� �������� ��������.

	bool show = true;		// ��ǥ ����
// �Լ�
private:
	void SetMoveValue(int sx,int ex, int y);
	void MakeObject(string name,string Class_name, int x, int y);

// ������ & �Ҹ���
public:
	S10_Chapter7();
	~S10_Chapter7();
};