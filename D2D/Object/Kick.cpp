#include  "framework.h"
#include  "Kick.h"
#include  "Collider/Collider.h"
#include  "Object/HellTakerMap.h"
#include  "Object/AObject.h"
//#include  "Renders/Texture.h"

///////////////////////////////////////////////////////////
// »ý¼ºÀÚ
//////////////////////////////////////////////////////////
Kick::Kick()
{
	wstring  imgFile     = L"Marco.png";
	wstring  shaderFile  = L"00_Animation.fx";
	

	// Audio
	Audio->AddSound("KICK", "./_Sounds/character_move_01-sharedassets0.assets-328.wav");


	SetName("Kick");
	m_pAnimation = new Animation();
//	SetScale(0.3f, 0.3f);
	// Kick1
	{
		AnimationClip *pClip = new AnimationClip();
		imgFile = L"/helltaker/Kick/Kick (1).png";

		Texture *pTexture = pClip->CreateTexture(imgFile, shaderFile);

		for (int i = 1; i < 5; i++)
		{
			imgFile = L"/helltaker/Kick/Kick (" + to_wstring(i) + L").png";
			pClip->AddFrame(pTexture, imgFile, 0, 0, 0, 0, 0.08f);
		}	
		m_pAnimation->AddAnimationClip(pClip);
	}
	// Kick2
	{
		AnimationClip *pClip = new AnimationClip();
		imgFile = L"/helltaker/Kick/Kick (5).png";

		Texture *pTexture = pClip->CreateTexture(imgFile, shaderFile);

		for (int i = 5; i < 9; i++)
		{
			imgFile = L"/helltaker/Kick/Kick (" + to_wstring(i) + L").png";
			pClip->AddFrame(pTexture, imgFile, 0, 0, 0, 0, 0.08f);
		}
		m_pAnimation->AddAnimationClip(pClip);
	}

	m_pAnimation->SetPlay(m_nState);
}

Kick::~Kick()
{
	SAFE_DELETE(m_pAnimation);

}
void Kick::Update(Matrix V, Matrix P)
{
	Vector2 position = GetPosition();
	
//	Color color = Color(255.0f/255.0f, 150.0f/255.0f, 165.0f/255.0f, 0);
//
//	m_pAnimation->GetTexture()->GetShader()->AsVector("TextureColor")->SetFloatVector(color);
//	m_pAnimation->SetPass(4);


	// Animation
	m_pAnimation->SetPlay(m_nState);
	m_pAnimation->SetPosition(position);
	m_pAnimation->SetScale(m_Scale);
	m_pAnimation->SetRotation(m_Rotation);
	m_pAnimation->Update(V, P);



}

void Kick::Render()
{
	m_pAnimation->Render();
}

void Kick::Random()
{
	while (1)
	{
		int id = rand() % 2;
		if (id == m_nState) continue;
		m_nState = id;
		break;
	}
}
