#include  "framework.h"
#include  "LockBox.h"
#include  "Object/HellTakerMap.h"
///////////////////////////////////////////////////////////
// »ı¼ºÀÚ
//////////////////////////////////////////////////////////
LockBox::LockBox()
{

	wstring  imgFile     = L"/helltaker/LockBox/LockBox.png";
	wstring  shaderFile  = L"00_Animation.fx";
	
	SetName("LockBox");
	m_pTexture = new Texture(imgFile, shaderFile,0,0,100,100);
	

}

LockBox::~LockBox()
{
	SAFE_DELETE(m_pTexture);
}
void LockBox::Update(Matrix V, Matrix P)
{
	Vector2  position = m_Position;

	// Texture
	m_pTexture->SetPosition(position);
	m_pTexture->SetScale(m_Scale);
	m_pTexture->SetRotation(m_Rotation);
	m_pTexture->Update(V, P);

}

void LockBox::Render()
{
	if (!IsActive()) return;
	m_pTexture->Render();
}



