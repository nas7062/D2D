#include  "framework.h"
#include  "BackGround.h"
#include  "Collider/Collider.h"
///////////////////////////////////////////////////////////
// ������
//////////////////////////////////////////////////////////
BackGround::BackGround()
{
	wstring  imgFile     = L"/helltaker/Chapter/back1.png";
	wstring  shaderFile  = L"00_Animation.fx";
	
	SetName("BackGround");
	m_pTextureBack1 = new Texture(imgFile, shaderFile);
	Vector2 size1 = m_pTextureBack1->GetRealTextureSize();
	m_pTextureBack1->SetPosition(-Main->GetWidth()*0.5f+size1.x*0.5f, 
		                          Main->GetHeight()*0.5f-size1.y*0.5f);



	imgFile = L"/helltaker/Chapter/back2.png";
	m_pTextureBack2 = new Texture(imgFile, shaderFile);

	Vector2 size2 = m_pTextureBack2->GetRealTextureSize();
	m_pTextureBack2->SetPosition(-Main->GetWidth()*0.5f+size2.x*0.5f,
		                         -Main->GetHeight()*0.5f + size2.y*0.5f);

}

BackGround::~BackGround()
{
	SAFE_DELETE(m_pTextureBack1);
	SAFE_DELETE(m_pTextureBack2);
}
void BackGround::Update(Matrix V, Matrix P)
{
	
	m_pTextureBack1->Update(V, P);
	m_pTextureBack2->Update(V, P);

}

void BackGround::Render()
{
	// ����
	Vector2 size1 = m_pTextureBack1->GetRealTextureSize();
	m_pTextureBack1->SetPosition(Main->GetWidth()*0.5f - size1.x*0.5f,
		Main->GetHeight()*0.5f - size1.y*0.5f);

	Vector2 size2 = m_pTextureBack2->GetRealTextureSize();
	m_pTextureBack2->SetPosition(Main->GetWidth()*0.5f - size2.x*0.5f,
		-Main->GetHeight()*0.5f + size2.y*0.5f);

	m_pTextureBack1->SetRotation(0.0f, 180.0f, 0.0f);
	m_pTextureBack2->SetRotation(0.0f, 180.0f, 0.0f);
	m_pTextureBack1->Render();
	m_pTextureBack2->Render();

	// ����


	m_pTextureBack1->SetPosition(-Main->GetWidth()*0.5f + size1.x*0.5f,
		Main->GetHeight()*0.5f - size1.y*0.5f);

	m_pTextureBack2->SetPosition(-Main->GetWidth()*0.5f + size2.x*0.5f,
		-Main->GetHeight()*0.5f + size2.y*0.5f);

	m_pTextureBack1->SetRotation(0.0f, 0.0f, 0.0f);
	m_pTextureBack2->SetRotation(0.0f, 0.0f, 0.0f);
	m_pTextureBack1->Render();
	m_pTextureBack2->Render();

}


