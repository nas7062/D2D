#include  "framework.h"
#include  "Azazel.h"
#include  "Collider/Collider.h"
#include  "Object/HellTakerMap.h"
#include  "Object/AObject.h"

///////////////////////////////////////////////////////////
// »ý¼ºÀÚ
//////////////////////////////////////////////////////////
Azazel::Azazel()
{
	wstring  imgFile     = L"Marco.png";
	wstring  shaderFile  = L"00_Animation.fx";
	
	SetName("Azazel");
	m_pAnimation = new Animation();
	
	// IDLE
	{
		AnimationClip *pClip = new AnimationClip();
		imgFile = L"/helltaker/Azazel/azazel (1).png";

		Texture *pTexture = pClip->CreateTexture(imgFile, shaderFile);

		for (int i = 1; i < 13; i++)
		{
			imgFile = L"/helltaker/Azazel/azazel (" + to_wstring(i) + L").png";
			pClip->AddFrame(pTexture, imgFile, 0, 0, 100, 100, 0.1f);
		}	
		m_pAnimation->AddAnimationClip(pClip);
	}

	
	m_pCollider = new Collider();
	m_pCollider->SetParent(this);


}

Azazel::~Azazel()
{
	SAFE_DELETE(m_pAnimation);
	SAFE_DELETE(m_pCollider);
}
void Azazel::Update(Matrix V, Matrix P)
{
	Vector2 position = GetPosition();
	
	// Animation
	SetPosition(position);

	if (IsSuccess())
	{
		m_pAnimation->SetPass(3);
		m_Time = m_Time + TIMEMANAGER->Delta();
		if (m_Time >= 3.0f)
			m_Time = 3.0f;
		Color color = Color(0.8f, 0.8f, 0.6f, 0.0f);
		m_pAnimation->GetTexture()->GetShader()->AsVector("TextureColor")->SetFloatVector(color);
		m_pAnimation->SetFloatConstant("Time", m_Time/3.0f);
	}
		
	else
	{
		m_pAnimation->SetPass(0);
	}
		
	m_pAnimation->SetPlay((UINT)this->m_nState);
	m_pAnimation->SetPosition(position);
	m_pAnimation->SetScale(m_Scale);
	m_pAnimation->SetRotation(m_Rotation);
	m_pAnimation->Update(V, P);

	// Collider
	m_pCollider->SetPosition(position);
	m_pCollider->SetScale(m_Scale.x*m_pAnimation->GetTextureSize().x,
		                  m_Scale.y*m_pAnimation->GetTextureSize().y);
	m_pCollider->SetRotation(m_Rotation);
	m_pCollider->Update(V, P);

}

void Azazel::MoveObject(eDirection direction, Vector2 & position)
{
	
}


void Azazel::Render()
{
	m_pAnimation->Render();
	if (g_bVisibleCollisionCheck)
	{
		if (GetCollisionCheck())
			m_pCollider->SetColor(1.0f, 0.0f, 0.0f);
		else
			m_pCollider->SetColor(0.0f, 1.0f, 0.0f);
		m_pCollider->Render();
	}
}


