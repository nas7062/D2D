#include  "framework.h"
#include  "Huge.h"
#include  "Collider/Collider.h"
#include  "Object/HellTakerMap.h"
#include  "Object/AObject.h"
//#include  "Renders/Texture.h"

///////////////////////////////////////////////////////////
// »ý¼ºÀÚ
//////////////////////////////////////////////////////////
Huge::Huge()
{
	wstring  imgFile     = L"Marco.png";
	wstring  shaderFile  = L"00_Animation.fx";
	
	// Audio
	//Audio->AddSound("KICK", "./_Sounds/character_move_01-sharedassets0.assets-328.wav");


	SetName("Huge");
	m_pAnimation = new Animation();
//	SetScale(0.3f, 0.3f);
	// Kick1
	{
		AnimationClip *pClip = new AnimationClip(AnimationClip::eState::Once);
		imgFile = L"/helltaker/Huge/Huge_red (1).png";

		Texture *pTexture = pClip->CreateTexture(imgFile, shaderFile);

		for (int i = 1; i < 20; i++)
		{
			imgFile = L"/helltaker/Huge/Huge_red (" + to_wstring(i) + L").png";
			pClip->AddFrame(pTexture, imgFile, 0, 0, 0, 0, 0.08f);
		}	
		m_pAnimation->AddAnimationClip(pClip);
	}
	// Kick2
	{
		AnimationClip *pClip = new AnimationClip(AnimationClip::eState::Once);
		imgFile = L"/helltaker/Huge/Huge_yellow (1).png";

		Texture *pTexture = pClip->CreateTexture(imgFile, shaderFile);

		for (int i = 1; i < 10; i++)
		{
			imgFile = L"/helltaker/Huge/Huge_yellow (" + to_wstring(i) + L").png";
			pClip->AddFrame(pTexture, imgFile, 0, 0, 0, 0, 0.08f);
		}
		m_pAnimation->AddAnimationClip(pClip);
	}

	m_pAnimation->SetPlay(m_nState);
}

Huge::~Huge()
{
	SAFE_DELETE(m_pAnimation);

}
void Huge::Update(Matrix V, Matrix P)
{
	Vector2 position = GetPosition();
	
	if (!m_pAnimation->IsPlay())
		SetActive(false);

	// Animation
	m_pAnimation->SetPlay(m_nState);
	m_pAnimation->SetPosition(position);
	m_pAnimation->SetScale(m_Scale);
	m_pAnimation->SetRotation(m_Rotation);
	m_pAnimation->Update(V, P);

}

void Huge::Render()
{
	if (!IsActive()) return;
	m_pAnimation->Render();
}

void Huge::SetState(int id)
{
	m_pAnimation->SetPlay(id);
	m_nState = id;
}

