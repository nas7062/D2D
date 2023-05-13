#include  "framework.h"
#include  "Dust.h"
#include  "Collider/Collider.h"
#include  "Object/HellTakerMap.h"
#include  "Object/AObject.h"
//#include  "Renders/Texture.h"

///////////////////////////////////////////////////////////
// »ý¼ºÀÚ
//////////////////////////////////////////////////////////
Dust::Dust(int nFire)
{
	wstring  imgFile     = L"Marco.png";
	wstring  shaderFile  = L"00_Animation.fx";
	
	this->m_nFire = nFire;

	// 

	Audio->AddSound("DUST", "./_Sounds/character_move_01-sharedassets0.assets-328.wav");


	SetName("Dust");
	m_pAnimation = new Animation();
//	SetScale(0.3f, 0.3f);
	// DUST1
	{
		AnimationClip *pClip = new AnimationClip();
		imgFile = L"/helltaker/Dust/Dust1 (1).png";

		Texture *pTexture = pClip->CreateTexture(imgFile, shaderFile);

		for (int i = 1; i < 4; i++)
		{
			imgFile = L"/helltaker/Dust/Dust1 (" + to_wstring(i) + L").png";
			pClip->AddFrame(pTexture, imgFile, 0, 0, 0, 0, 0.08f);
		}	
		m_pAnimation->AddAnimationClip(pClip);
	}

	{
		AnimationClip *pClip = new AnimationClip();
		imgFile = L"/helltaker/Dust/Dust2 (1).png";

		Texture *pTexture = pClip->CreateTexture(imgFile, shaderFile);

		for (int i = 1; i < 4; i++)
		{
			imgFile = L"/helltaker/Dust/Dust2 (" + to_wstring(i) + L").png";
			pClip->AddFrame(pTexture, imgFile, 0, 0, 0, 0, 0.08f);
		}
		m_pAnimation->AddAnimationClip(pClip);
	}

	{
		AnimationClip *pClip = new AnimationClip();
		imgFile = L"/helltaker/Dust/Dust3 (1).png";

		Texture *pTexture = pClip->CreateTexture(imgFile, shaderFile);

		for (int i = 1; i < 4; i++)
		{
			imgFile = L"/helltaker/Dust/Dust3 (" + to_wstring(i) + L").png";
			pClip->AddFrame(pTexture, imgFile, 0, 0, 0, 0, 0.08f);
		}
		m_pAnimation->AddAnimationClip(pClip);
	}
	m_pAnimation->SetPlay(m_nState);
}

Dust::~Dust()
{
	SAFE_DELETE(m_pAnimation);

}
void Dust::Update(Matrix V, Matrix P)
{
	Vector2 position = GetPosition();
	
	Color color = Color(255.0f/255.0f, 150.0f/255.0f, 165.0f/255.0f, 0);

	m_pAnimation->GetTexture()->GetShader()->AsVector("TextureColor")->SetFloatVector(color);
	m_pAnimation->SetPass(4);


	// Animation
	m_pAnimation->SetPlay(m_nState);
	m_pAnimation->SetPosition(position);
	m_pAnimation->SetScale(m_Scale);
	m_pAnimation->SetRotation(m_Rotation);
	m_pAnimation->Update(V, P);



}

void Dust::Render()
{
	m_pAnimation->Render();
}

void Dust::Random()
{
	while (1)
	{
		int id = rand() % 3;
		if (id == m_nState) continue;
		m_nState = id;
		break;
	}
}


