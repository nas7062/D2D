#include  "framework.h"
#include  "Trap.h"
#include  "Collider/Collider.h"
#include  "Object/HellTakerMap.h"
#include  "Object/AObject.h"
//#include  "Renders/Texture.h"

///////////////////////////////////////////////////////////
// »ý¼ºÀÚ
//////////////////////////////////////////////////////////
Trap::Trap()
{
	wstring  imgFile     = L"Marco.png";
	wstring  shaderFile  = L"00_Animation.fx";
	

	SetName("Trap");
	m_pAnimation = new Animation();

	// Active
	{
		AnimationClip *pClip = new AnimationClip();
		imgFile = L"/helltaker/Trap/Thorn (5).png";

		Texture *pTexture = pClip->CreateTexture(imgFile, shaderFile);
		pClip->AddFrame(pTexture, imgFile, 0, 60, 100, 160, 0.15f);

		m_pAnimation->AddAnimationClip(pClip);
	}
	// Trap
	{
		AnimationClip *pClip = new AnimationClip();
		imgFile = L"/helltaker/Trap/Thorn (9).png";

		Texture *pTexture = pClip->CreateTexture(imgFile, shaderFile);
		pClip->AddFrame(pTexture, imgFile, 0, 60, 100, 160, 0.15f);
		m_pAnimation->AddAnimationClip(pClip);
	}

	// Down --> Up 
	{
		AnimationClip *pClip = new AnimationClip(AnimationClip::eState::Once);
		imgFile = L"/helltaker/Trap/Thorn (1).png";

		Texture *pTexture = pClip->CreateTexture(imgFile, shaderFile);
		for (int i = 9; i >= 5; i--)
		{
			imgFile = L"/helltaker/Trap/Thorn (" + to_wstring(i) + L").png";
			pClip->AddFrame(pTexture, imgFile, 0, 60, 100, 160, 0.3 / 5.0f);
		}
		m_pAnimation->AddAnimationClip(pClip);
	}

	// Up --> Down 

	{
		AnimationClip *pClip = new AnimationClip(AnimationClip::eState::Once);
		imgFile = L"/helltaker/Trap/Thorn (1).png";

		Texture *pTexture = pClip->CreateTexture(imgFile, shaderFile);
		for (int i = 5; i <= 9; i++)
		{
			imgFile = L"/helltaker/Trap/Thorn (" + to_wstring(i) + L").png";
			pClip->AddFrame(pTexture, imgFile, 0, 60, 100, 160, 0.3/5.0f);
		}
		m_pAnimation->AddAnimationClip(pClip);
	}

	m_nState = 0;
	m_pAnimation->SetPlay(m_nState);
}

Trap::~Trap()
{
	SAFE_DELETE(m_pAnimation);

}
void Trap::Update(Matrix V, Matrix P)
{
	Vector2 position = GetPosition();
	
	if (!m_pAnimation->IsPlay())
	{
		if (m_nState2 == eState::DOWN_UP)
			m_nState2 = eState::UP;
		if (m_nState2 == eState::UP_DOWN)
			m_nState2 = eState::DOWN;

	}

	// Animation
	m_pAnimation->SetPlay((UINT)m_nState2);
	m_pAnimation->SetPosition(position);
	m_pAnimation->SetScale(m_Scale);
	m_pAnimation->SetRotation(m_Rotation);
	m_pAnimation->Update(V, P);






}

void Trap::Render()
{
	m_pAnimation->Render();
}

void Trap::SetToggle()
{
	if (m_nState == 0)
		m_nState2 = eState::UP_DOWN;
	if (m_nState == 1)
		m_nState2 = eState::DOWN_UP;
	if (m_nState)  
		m_nState = 0; 
	else m_nState = 1;

}

void Trap::SetState(int state)
{
	if (state == 0)
		m_nState2 = eState::UP;
	if (m_nState == 1)
		m_nState2 = eState::DOWN;

	m_nState = state;
}

int Trap::GetNextState()
{

	string name = SCENEMANAGER->GetCurrentScene()->GetSceneName();

	if (name != "S05_Chapter2")
		return(GetState());
	
	if (GetState())
		return 0;
	else
		return 1;
}
