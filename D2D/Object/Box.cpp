#include  "framework.h"
#include  "Box.h"
#include  "Object/HellTakerMap.h"
#include  "Collider/Collider.h"
///////////////////////////////////////////////////////////
// 생성자
//////////////////////////////////////////////////////////
Box::Box()
{
	m_nID_SRV = rand() % 10;


	wstring  imgFile     = L"/helltaker/Box/Box (1).png";
	wstring  shaderFile  = L"00_Animation.fx";
	
	SetName("Box");
	m_pTexture = new Texture(imgFile, shaderFile,0,10,100,95);
	
	// image가 여러게 있는 것을 처리

	for (int i = 1; i < 12; i++)
	{
		imgFile = L"/helltaker/Box/Box (" + to_wstring(i) +L").png";
		this->CreateShaderResourceView(imgFile);
	}
//	SetScale(0.8, 0.8);
	m_pCollider = new Collider();
	m_pCollider->SetParent(this);

}

Box::~Box()
{
	SAFE_DELETE(m_pTexture);
	SAFE_DELETE(m_pCollider);
}
void Box::Update(Matrix V, Matrix P)
{
	Vector2  position = m_Position;

	position.y = position.y + 10;

	// Texture
	m_pTexture->SetResource(this->m_cvSRVs[m_nID_SRV]);
	m_pTexture->SetPosition(position);
	m_pTexture->SetScale(m_Scale);
	m_pTexture->SetRotation(m_Rotation);
	m_pTexture->Update(V, P);

	// Collider
	m_pCollider->SetPosition(position);
	m_pCollider->SetScale(m_Scale.x*m_pTexture->GetTextureSize().x,
		                  m_Scale.y*m_pTexture->GetTextureSize().y);
	m_pCollider->SetRotation(m_Rotation);
	m_pCollider->Update(V, P);


}

void Box::Render()
{
	if (!IsActive()) return;

	m_pTexture->Render();
	if (g_bVisibleCollisionCheck)
	{
		if (GetCollisionCheck())
			m_pCollider->SetColor(1.0f, 0.0f, 0.0f);
		else
			m_pCollider->SetColor(0.0f, 1.0f, 0.0f);
		m_pCollider->Render();
	}
}

void Box::MoveObject(eDirection direction, Vector2 & position)
{
	POINT pt = MAPMANAGER->GetMapXY(position);
	POINT Oldpt = pt;

	if (!IsActive())
		return;

	switch (direction)
	{
	case eDirection::Right:
		pt.x = pt.x + 1;
		SetRotation(0.0f, 0.0f, 0.0f);
		break;
	case eDirection::Left:
		pt.x = pt.x - 1;
		SetRotation(0.0f, 180.0f, 0.0f);
		break;
	case eDirection::Up:
		pt.y = pt.y - 1;
		break;
	case eDirection::Down:
		pt.y = pt.y + 1;
		break;

	}
	if (MAPMANAGER->IsWall(pt.x, pt.y))
		return;

	if (MAPMANAGER->IsBox(pt.x, pt.y))
		return;

	if (MAPMANAGER->IsMob(pt.x, pt.y))
		return;

	if (MAPMANAGER->IsGoalEx3(pt.x, pt.y,pt))
		return;
	if (MAPMANAGER->IsLockBox(pt.x, pt.y))
		return;




	// BOX + TRAP  --> Move

	MAPMANAGER->ResetValue(Oldpt.x, Oldpt.y, HellTakerMap::eState::BOX);
	MAPMANAGER->SetValue(pt.x, pt.y, HellTakerMap::eState::BOX, this);


	Vector2 position2 = MAPMANAGER->GetPosition(pt.x, pt.y);
	SetPosition(position2);




}

void Box::CreateShaderResourceView(wstring strImageFile)
{
	ID3D11ShaderResourceView* pSRV;

	wstring strFile = L"./_Textures/" +  strImageFile;

	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(
		Device, strFile.c_str(), NULL, NULL, &pSRV, NULL);
	assert(SUCCEEDED(hr));
	this->m_cvSRVs.push_back(pSRV);
}


