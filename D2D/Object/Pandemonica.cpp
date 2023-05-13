#include  "framework.h"
#include  "Pandemonica.h"
#include  "Collider/Collider.h"
#include  "Object/HellTakerMap.h"
#include  "Object/AObject.h"
#include  "Object/ClearEffect.h"

///////////////////////////////////////////////////////////
// »ý¼ºÀÚ
//////////////////////////////////////////////////////////
Pandemonica::Pandemonica()
{
	wstring  imgFile     = L"Marco.png";
	wstring  shaderFile  = L"00_Animation.fx";
	
	SetName("Pandemonica");
	m_pAnimation = new Animation();
	
	// Pandemonica
	{
		AnimationClip *pClip = new AnimationClip();
		imgFile = L"/helltaker/Pandemonica/Pandemonica (1).png";

		Texture *pTexture = pClip->CreateTexture(imgFile, shaderFile);

		for (int i = 1; i < 13; i++)
		{
			imgFile = L"/helltaker/Pandemonica/Pandemonica (" + to_wstring(i) + L").png";
			pClip->AddFrame(pTexture, imgFile, 0, 0, 100, 100, 0.05f);
		}	
		m_pAnimation->AddAnimationClip(pClip);
	}
	// Modeus
	{
		AnimationClip *pClip = new AnimationClip();
		imgFile = L"/helltaker/Modeus/Modeus (1).png";

		Texture *pTexture = pClip->CreateTexture(imgFile, shaderFile);

		for (int i = 1; i <= 12; i++)
		{
			imgFile = L"/helltaker/Modeus/Modeus (" + to_wstring(i) + L").png";
			pClip->AddFrame(pTexture, imgFile, 0, 0, 100, 100, 0.05f);
		}
		m_pAnimation->AddAnimationClip(pClip);
	}




	// Azazel
	{
		AnimationClip *pClip = new AnimationClip();
		imgFile = L"/helltaker/Azazel/azazel (1).png";

		Texture *pTexture = pClip->CreateTexture(imgFile, shaderFile);

		for (int i = 1; i < 13; i++)
		{
			imgFile = L"/helltaker/Azazel/azazel (" + to_wstring(i) + L").png";
			pClip->AddFrame(pTexture, imgFile, 0, 0, 100, 100, 0.05f);
		}
		m_pAnimation->AddAnimationClip(pClip);
	}

	// Zdrada
	{
		AnimationClip *pClip = new AnimationClip();
		imgFile = L"/helltaker/Zdrada/Zdrada (1).png";

		Texture *pTexture = pClip->CreateTexture(imgFile, shaderFile);

		for (int i = 1; i < 13; i++)
		{
			imgFile = L"/helltaker/Zdrada/Zdrada (" + to_wstring(i) + L").png";
			pClip->AddFrame(pTexture, imgFile, 0, 0, 100, 100, 0.05f);
		}
		m_pAnimation->AddAnimationClip(pClip);
	}

	// Malina
	{
		AnimationClip* pClip = new AnimationClip();
		imgFile = L"/helltaker/Malina/Malina (1).png";

		Texture* pTexture = pClip->CreateTexture(imgFile, shaderFile);

		for (int i = 1; i < 13; i++)
		{
			imgFile = L"/helltaker/Malina/Malina (" + to_wstring(i) + L").png";
			pClip->AddFrame(pTexture, imgFile, 0, 0, 100, 100, 0.05f);
		}
		m_pAnimation->AddAnimationClip(pClip);
	}
	// Demon1
	{
		AnimationClip *pClip = new AnimationClip();

		for (int i = 1; i <= 12; i++)
		{
			float FramSpeed = (1.0f) / 12;
			imgFile = L"/helltaker/Demon1/Demon1 (" + to_wstring(i) + L").png";
			Texture* pTexture = m_pAnimation->CreateTexture(imgFile, shaderFile);
			Vector2 size = pTexture->GetRealTextureSize();
			pClip->AddFrame(pTexture, 0, 0, size.x, size.y, FramSpeed);
		}
		m_pAnimation->AddAnimationClip(pClip);
	}

	// Demon7
	{
		AnimationClip *pClip = new AnimationClip();

		for (int i = 1; i <= 12; i++)
		{
			float FramSpeed = (1.0f) / 12;
			imgFile = L"/helltaker//Demon7/Demon7 (" + to_wstring(i) + L").png";
			Texture* pTexture = m_pAnimation->CreateTexture(imgFile, shaderFile);
			Vector2 size = pTexture->GetRealTextureSize();
			pClip->AddFrame(pTexture, 0, 0, size.x, size.y, FramSpeed);
		}
		m_pAnimation->AddAnimationClip(pClip);
	}

	
	// heart

	imgFile = L"/helltaker/Demons_Smallheart.png";
	m_pHeart = new Texture(imgFile, shaderFile);

	m_pEffect = new ClearEffect();

	
	m_pCollider = new Collider();
	m_pCollider->SetParent(this);


}

Pandemonica::~Pandemonica()
{
	SAFE_DELETE(m_pHeart);
	SAFE_DELETE(m_pAnimation);
	SAFE_DELETE(m_pCollider);
}
void Pandemonica::Update(Matrix V, Matrix P)
{
	Vector2 position = GetPosition();
	
	// Animation
	SetPosition(position);

	if (IsSuccess())
	{
		m_pAnimation->SetPass(5);
		m_Time = m_Time + TIMEMANAGER->Delta();
		if (m_Time >= 3.0f)
			m_Time = 3.0f;
		Color color = Color(0.9f, 0.9f, 0.9f, 0.0f);
		m_pAnimation->GetTexture()->GetShader()->AsVector("TextureColor")->SetFloatVector(color);
		m_pAnimation->SetFloatConstant("Time", m_Time/3.0f);

	}
		
	else
	{
		m_pAnimation->SetPass(0);
	}
		
	if (m_Heart_Move == 2 * 3.141592f)
		m_Heart_Move = 0.0f;
	m_Heart_Move += 2.0f * 3.141592f * TIMEMANAGER->Delta();


	m_pAnimation->SetPlay((UINT)this->m_nState);
	m_pAnimation->SetPosition(position);
	m_pAnimation->SetScale(m_Scale);
	m_pAnimation->SetRotation(m_Rotation);
	m_pAnimation->Update(V, P);

	//
	if (m_Heart_Move == 2 * 3.141592f)
		m_Heart_Move = 0.0f;
	m_Heart_Move += 2.0f * 3.141592f * TIMEMANAGER->Delta();

	m_pHeart->SetPosition(position.x - 30.0f, position.y + 50.0f + 5.0f*sinf(m_Heart_Move));
	m_pHeart->Update(V, P);


	// Collider
	m_pCollider->SetPosition(position);
	m_pCollider->SetScale(m_Scale.x*m_pAnimation->GetTextureSize().x,
		                  m_Scale.y*m_pAnimation->GetTextureSize().y);
	m_pCollider->SetRotation(m_Rotation);
	m_pCollider->Update(V, P);

	// effect


	m_pEffect->SetPosition(position);
	m_pEffect->SetScale(m_Scale);
	m_pEffect->Update(V, P);
}

void Pandemonica::MoveObject(eDirection direction, Vector2 & position)
{
	
}


void Pandemonica::Render()
{
	if( this->m_nState != eState::PANDEMONICA)
	    m_pHeart->Render();
	m_pAnimation->Render();
	if (g_bVisibleCollisionCheck)
	{
		if (GetCollisionCheck())
			m_pCollider->SetColor(1.0f, 0.0f, 0.0f);
		else
			m_pCollider->SetColor(0.0f, 1.0f, 0.0f);
		m_pCollider->Render();
	}

	if (IsSuccess())
	   m_pEffect->Render();
}


