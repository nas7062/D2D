#include  "framework.h"
#include  "Bone.h"
#include  "Object/HellTakerMap.h"
#include  "Collider/Collider.h"
///////////////////////////////////////////////////////////
// 생성자
//////////////////////////////////////////////////////////
Bone::Bone(int id)
{
	m_nID_SRV = rand() % 2;
	m_nID = id;

	wstring  imgFile     = L"/helltaker/Bone/Bone (1).png";
	wstring  shaderFile  = L"00_Animation.fx";
	
	SetName("Bone");
	m_pTexture = new Texture(imgFile, shaderFile,0,0,0,0);
	
	// image가 여러게 있는 것을 처리

	for (int i = 1; i < 4; i++)
	{
		imgFile = L"/helltaker/Bone/Bone (" + to_wstring(i) +L").png";
		this->CreateShaderResourceView(imgFile);
	}

	m_pCollider = new Collider();
	m_pCollider->SetParent(this);

	if(rand() % 2)
		m_MoveSpeed = 300.0f + (float)(rand() % 10)*50;
	else
		m_MoveSpeed = -(300.0f + (float)(rand() % 10) * 50);
}

Bone::~Bone()
{
	SAFE_DELETE(m_pTexture);
	SAFE_DELETE(m_pCollider);
}
void Bone::Update(Matrix V, Matrix P)
{
	Vector2 position = GetPosition();
	float   roll = TIMEMANAGER->GetRunning()*900.0f;
	float   Angle[] = { 0.15f, -0.17f, 0.67f, -0.8f, 0.93f,
					  -0.35f,  0.17f,-0.67f,  0.8f,-0.53f };


	// 오늘 Test Sin, Cos 방향성을 여러개 줄수 있게끔....

	if(Angle[m_nID] < 0)
		position.x = position.x -cosf(Angle[m_nID])*7.0f;
	else
		position.x = position.x + cosf(Angle[m_nID])*7.0f;
	position.y = position.y + sinf(Angle[m_nID])*12.0f - m_Gravirty;
	m_Gravirty = m_Gravirty + 0.15f;   // 위로 올라갔다가 떨어지게

	printf("==> %f %f\n", m_MoveSpeed,position.x);
	

	SetRotation(0.0f, 0.0f, roll);
	SetPosition(position);

	// Texture
	m_pTexture->SetResource(this->m_cvSRVs[m_nID_SRV]);
	m_pTexture->SetPosition(position);
	m_pTexture->SetScale(m_Scale);
	m_pTexture->SetRotation(m_Rotation);
	m_pTexture->Update(V, P);

	// Collider
	m_pCollider->SetPosition(m_Position);
	m_pCollider->SetScale(m_Scale.x*m_pTexture->GetTextureSize().x,
		                  m_Scale.y*m_pTexture->GetTextureSize().y);
	m_pCollider->SetRotation(m_Rotation);
	m_pCollider->Update(V, P);


}

void Bone::Render()
{
	if (!IsActive()) return;

	m_pTexture->Render();
	return;
	if (g_bVisibleCollisionCheck)
	{
		if (GetCollisionCheck())
			m_pCollider->SetColor(1.0f, 0.0f, 0.0f);
		else
			m_pCollider->SetColor(0.0f, 1.0f, 0.0f);
		m_pCollider->Render();
	}
}

void Bone::MoveObject(eDirection direction, Vector2 & position)
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
	{
	//	SetActive(false);
	//	MAPMANAGER->SetValue(Oldpt.x, Oldpt.y, HellTakerMap::eState::Move, NULL);
		return;
	}

	if (MAPMANAGER->IsBox(pt.x, pt.y))
	{
	//	SetActive(false);
	//	MAPMANAGER->SetValue(Oldpt.x, Oldpt.y, HellTakerMap::eState::Move, NULL);
		return;
	}
	if (MAPMANAGER->IsMob(pt.x, pt.y))
	{
	//	SetActive(false);
	//	MAPMANAGER->SetValue(Oldpt.x, Oldpt.y, HellTakerMap::eState::Move, NULL);
		return;
	}
	if (MAPMANAGER->IsGoal(pt.x, pt.y,pt))
		return;


	MAPMANAGER->SetValue(Oldpt.x, Oldpt.y, HellTakerMap::eState::Move, NULL);
	MAPMANAGER->SetValue(pt.x, pt.y, HellTakerMap::eState::BOX, this);


	Vector2 position2 = MAPMANAGER->GetPosition(pt.x, pt.y);
	SetPosition(position2);




}

void Bone::CreateShaderResourceView(wstring strImageFile)
{
	ID3D11ShaderResourceView* pSRV;

	wstring strFile = L"./_Textures/" +  strImageFile;

	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(
		Device, strFile.c_str(), NULL, NULL, &pSRV, NULL);
	assert(SUCCEEDED(hr));
	this->m_cvSRVs.push_back(pSRV);
}


