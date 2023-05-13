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

// 변수
private:
	Texture* m_pBackground      = nullptr;
	class    AObject* m_pPlayer = nullptr;
// 함수
private:


// 생성자 & 소멸자
public:
	AScene();
	~AScene();
};