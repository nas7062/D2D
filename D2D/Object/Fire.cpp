#include  "framework.h"
#include  "Fire.h"
#include  "Collider/Collider.h"
#include  "Object/HellTakerMap.h"
#include  "Object/AObject.h"
//#include  "Renders/Texture.h"

///////////////////////////////////////////////////////////
// »ý¼ºÀÚ
//////////////////////////////////////////////////////////
Fire::Fire()
{
	wstring  imgFile     = L"Marco.png";
	wstring  shaderFile  = L"00_Animation.fx";
	

	SetName("Fire");
	m_pAnimation = new Animation();
//	SetScale(0.3f, 0.3f);
	// IDLE
	{
		AnimationClip *pClip = new AnimationClip();
		imgFile = L"/helltaker/Fire/Fire (1).png";

		Texture *pTexture = pClip->CreateTexture(imgFile, shaderFile);

		for (int i = 1; i < 10; i++)
		{
			imgFile = L"/helltaker/Fire/Fire (" + to_wstring(i) + L").png";
			pClip->AddFrame(pTexture, imgFile, 0, 0, 0, 0, 0.1f);
		}	
		m_pAnimation->AddAnimationClip(pClip);
	}

	if( this->m_nFire)
		imgFile = L"/helltaker/fire/fireframe.png";
	else
		imgFile = L"/helltaker/fire/nofireframe.png";

	
	CreateShaderResourceView(L"/helltaker/fire/nofireframe.png");
	CreateShaderResourceView(L"/helltaker/fire/fireframe.png");
	m_pTexture = new Texture(imgFile, shaderFile);


}

Fire::~Fire()
{
	SAFE_DELETE(m_pAnimation);
	SAFE_DELETE(m_pTexture);
}
void Fire::Update(Matrix V, Matrix P)
{
	Vector2 position = GetPosition();
	

	Vector2 size = m_pTexture->GetRealTextureSize();
	position.y = position.y + size.y*0.5f;

	Color color = Color(230.0f/255.0f, 194.0f/255.0f, 106.0f/255.0f, 0);


	m_pAnimation->GetTexture()->GetShader()->AsVector("TextureColor")->SetFloatVector(color);
	m_pAnimation->SetPass(4);


	// Animation
	m_pAnimation->SetPlay(0);
	m_pAnimation->SetPosition(position);
	m_pAnimation->SetScale(Vector2(0.6f, 0.6f));
	m_pAnimation->SetRotation(m_Rotation);
	m_pAnimation->Update(V, P);

	m_pTexture->SetResource(this->m_cvSRVs[m_nFire]);
	m_pTexture->SetPosition(m_Position);
	m_pTexture->SetScale(m_Scale);
	m_pTexture->SetRotation(m_Rotation);
	m_pTexture->Update(V, P);


}

void Fire::Render()
{
	m_pTexture->Render();
	if( this->m_nFire)
		m_pAnimation->Render();

}

void Fire::CreateShaderResourceView(wstring strImageFile)
{
	ID3D11ShaderResourceView* pSRV;

	wstring strFile = L"./_Textures/" + strImageFile;

	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(
		Device, strFile.c_str(), NULL, NULL, &pSRV, NULL);
	assert(SUCCEEDED(hr));
	this->m_cvSRVs.push_back(pSRV);
}


