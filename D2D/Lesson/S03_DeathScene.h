#pragma once
//////////////////////////////////////////////////////////////////
//  S03_DeathScene
//      웹툰형태의 설명을 보여주는 Scene
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
	
// 변수
private:
	Animation  *m_pAnimation = nullptr;
	Vector2    m_Position = Vector2(0.0f, 0.0f);
// 함수
private:


// 생성자 & 소멸자
public:
	S03_DeathScene();
	~S03_DeathScene();
};