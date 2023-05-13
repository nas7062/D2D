#include  "framework.h"
#include  "Key.h"
#include  "Collider/Collider.h"
#include  "Object/HellTakerMap.h"
#include  "Object/AObject.h"
//#include  "Renders/Texture.h"

///////////////////////////////////////////////////////////
// »ý¼ºÀÚ
//////////////////////////////////////////////////////////
Key::Key()
{
	wstring  imgFile     = L"Marco.png";
	wstring  shaderFile  = L"00_Animation.fx";
	

	SetName("Key");
	m_pAnimation = new Animation();

	// Active
	{
		AnimationClip *pClip = new AnimationClip();
		imgFile = L"/helltaker/Key/Key (1).png";

		Texture *pTexture = pClip->CreateTexture(imgFile, shaderFile);

		for (int i = 1; i < 13; i++)
		{
			imgFile = L"/helltaker/Key/Key (" + to_wstring(i) + L").png";
			pClip->AddFrame(pTexture, imgFile, 0, 40, 90, 130, 0.1f);
		}	
		m_pAnimation->AddAnimationClip(pClip);
	}
	
	m_nState = 0;
	m_pAnimation->SetPlay(m_nState);
}

Key::~Key()
{
	SAFE_DELETE(m_pAnimation);

}
void Key::Update(Matrix V, Matrix P)
{
	Vector2 position = GetPosition();
	
	// Animation
	m_pAnimation->SetPlay(m_nState);
	m_pAnimation->SetPosition(position);
	m_pAnimation->SetScale(m_Scale);
	m_pAnimation->SetRotation(m_Rotation);
	m_pAnimation->Update(V, P);
}

void Key::Render()
{
	if( IsActive())
	  m_pAnimation->Render();
}