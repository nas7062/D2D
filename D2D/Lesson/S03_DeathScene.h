#pragma once
//////////////////////////////////////////////////////////////////
//  S03_DeathScene
//      ���������� ������ �����ִ� Scene
//////////////////////////////////////////////////////////////////
class S03_DeathScene : public Scene
{
 // defalut
public:
	void Update()  override;
	void Render()  override;
	void ChangeScene() override;
	void       SetPoisition(Vector2 pos) { m_Position = pos; }
 // Getter
private:

//  Setter
private:
	
// ����
private:
	Animation  *m_pAnimation = nullptr;
	Vector2    m_Position = Vector2(0.0f, 0.0f);
// �Լ�
private:


// ������ & �Ҹ���
public:
	S03_DeathScene();
	~S03_DeathScene();
};