#include  "framework.h"
#include  "ClearEffect.h"
#include  "Collider/Collider.h"
#include  "Object/HellTakerMap.h"
#include  "Object/AObject.h"
//#include  "Renders/Texture.h"

///////////////////////////////////////////////////////////
// »ý¼ºÀÚ
//////////////////////////////////////////////////////////
ClearEffect::ClearEffect()
{
	wstring  imgFile     = L"Marco.png";
	wstring  shaderFile  = L"00_Animation.fx";
	
	SetName("ClearEffect");
	m_pAnimation = new Animation();

	// DUST1
	{
		AnimationClip *pClip = new AnimationClip(AnimationClip::eState::Once);
		imgFile = L"/helltaker/Clear_Effect/Clear_Effect (1).png";

		Texture *pTexture = pClip->CreateTexture(imgFile, shaderFile);

		for (int i = 1; i <= 15; i++)
		{
			imgFile = L"/helltaker/Clear_Effect/Clear_Effect (" + to_wstring(i) + L").png";
			pClip->AddFrame(pTexture, imgFile, 0, 0, 0, 0, 0.08f);
		}	
		m_pAnimation->AddAnimationClip(pClip);
	}

}

ClearEffect::~ClearEffect()
{
	SAFE_DELETE(m_pAnimation);

}
void ClearEffect::Update(Matrix V, Matrix P)
{
	Vector2 position = GetPosition();
	
	Color color = Color(255.0f/255.0f, 255.0f/255.0f, 255.0f/255.0f, 0);

	m_pAnimation->GetTexture()->GetShader()->AsVector("TextureColor")->SetFloatVector(color);
	m_pAnimation->SetPass(4);

	// Animation
	m_pAnimation->SetPlay(m_nState);
	m_pAnimation->SetPosition(position);
	m_pAnimation->SetScale(m_Scale);
	m_pAnimation->SetRotation(m_Rotation);
	m_pAnimation->Update(V, P);

}

void ClearEffect::Render()
{
	m_pAnimation->Render();
}
