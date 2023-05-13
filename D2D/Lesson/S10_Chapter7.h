#pragma once
#include "Base/Scene.h"
//////////////////////////////////////////////////////////////////
// S04
// 첫번쨰 게임 스태이지
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

// 변수
private:
	Texture *m_pTexture = nullptr;				// Game backGround
	class BackGround *m_pBackground = nullptr;	//좌우 하나씩 왼쪽은 히트수 오른쪽은 스태이지.

	bool show = true;		// 좌표 숫자
// 함수
private:
	void SetMoveValue(int sx,int ex, int y);
	void MakeObject(string name,string Class_name, int x, int y);

// 생성자 & 소멸자
public:
	S10_Chapter7();
	~S10_Chapter7();
};