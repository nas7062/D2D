#pragma once

//////////////////////////////////////////////////////////////////
// 
//
//
//////////////////////////////////////////////////////////////////
class AScene : public Scene
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
	Texture* m_pBackground      = nullptr;
	class    AObject* m_pPlayer = nullptr;
// �Լ�
private:


// ������ & �Ҹ���
public:
	AScene();
	~AScene();
};