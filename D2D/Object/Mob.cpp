#include  "framework.h"
#include  "Mob.h"
#include  "Collider/Collider.h"
#include  "Object/HellTakerMap.h"
#include  "Object/AObject.h"
#include  "Object/Bone.h"
#include  "Base/ObjectManager.h"
#include  "Object/Trap.h"

///////////////////////////////////////////////////////////
// »ý¼ºÀÚ
//////////////////////////////////////////////////////////
Mob::Mob()
{
	wstring  imgFile     = L"Marco.png";
	wstring  shaderFile  = L"00_Animation.fx";
	
	SetName("Macro");
	m_pAnimation = new Animation();
	
	// IDLE
	{
		AnimationClip *pClip = new AnimationClip();
		imgFile = L"/helltaker/mob/mob (1).png";

		Texture *pTexture = pClip->CreateTexture(imgFile, shaderFile);

		for (int i = 8; i < 19; i++)
		{
			imgFile = L"/helltaker/mob/mob (" + to_wstring(i) + L").png";
			pClip->AddFrame(pTexture, imgFile, 0, 40, 100, 140, 0.05f);
		}	
		m_pAnimation->AddAnimationClip(pClip);
	}
	// KICK
	{
		AnimationClip *pClip = new AnimationClip(AnimationClip::Once);
		imgFile = L"/helltaker/mob/mob (1).png";

		Texture *pTexture = pClip->CreateTexture(imgFile, shaderFile);

		for (int i = 1; i < 8; i++)
		{
			imgFile = L"/helltaker/mob/mob (" + to_wstring(i) + L").png";
			pClip->AddFrame(pTexture, imgFile, 0, 40, 100, 140, 0.05f);
		}
		m_pAnimation->AddAnimationClip(pClip);
	}
	
	// KICK
	{
		AnimationClip *pClip = new AnimationClip(AnimationClip::Once);
		imgFile = L"/helltaker/mob/mob (1).png";

		Texture *pTexture = pClip->CreateTexture(imgFile, shaderFile);

		for (int i = 1; i < 8; i++)
		{
			imgFile = L"/helltaker/mob/mob (" + to_wstring(i) + L").png";
			pClip->AddFrame(pTexture, imgFile, 0, 40, 100, 140, 0.05f);
		}
		m_pAnimation->AddAnimationClip(pClip);
	}


	m_pCollider = new Collider();
	m_pCollider->SetParent(this);


}

Mob::~Mob()
{
	SAFE_DELETE(m_pAnimation);
	SAFE_DELETE(m_pCollider);
}
void Mob::Update(Matrix V, Matrix P)
{
	Vector2 position = GetPosition();
	POINT   pt = MAPMANAGER->GetMapXY(position);


	for (auto a : m_cvBones)
		a->Update(V, P);

	if (!IsActive())
		return;

	if (this->m_nState == eState::DEAD)
	{
		float   roll = TIMEMANAGER->GetRunning()*900.0f;
		SetRotation(0.0f, 0.0f, roll);
		position.x = position.x + cosf(0.835)*7.0f;
		position.y = position.y + sinf(0.835)*12.0f;
	}
	else
	{
		pt = MAPMANAGER->GetMapXY(position);
		if (MAPMANAGER->IsTrap(pt.x, pt.y))
		{
			Trap *pObject = dynamic_cast<Trap*>(MAPMANAGER->GetSecondObject(pt.x, pt.y));

			if (pObject->GetState() == 0)
			{
				this->m_nState = eState::DEAD;
				MAPMANAGER->ResetValue(pt.x, pt.y, HellTakerMap::eState::Mob);
			}
			return;
		}



	}

	// Animation
	SetPosition(position);


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



	if (m_nState == eState::WALK)
	{
		if (!m_pAnimation->IsPlay())
			m_nState = eState::IDLE;
	}


	if (m_nState == eState::DEAD)
	{
		if (!m_pAnimation->IsPlay())
		{
			SetActive(false);
			Reset();
		}
	}

}

void Mob::MoveObject(eDirection direction, Vector2 & position)
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
		SetState(eState::DEAD);
		MAPMANAGER->ResetValue(Oldpt.x, Oldpt.y, HellTakerMap::eState::Mob);
		
		if (m_cvBones.size())
			m_cvBones.clear();
		for (int i = 0; i < 20; i++)
		{
			string name = "Bone" + to_string(i);
			Bone* pBone = (Bone*)OBJECTMANAGER->FindObject(name);
			pBone->Reset();
			Vector2 position2 = position;
			position2.x = position2.x - i * 10;
			position2.y = position2.y + i * 10;
			pBone->SetPosition(position2);
			m_cvBones.push_back(pBone);
		}
		return;
	}
		
	if (MAPMANAGER->IsBox(pt.x, pt.y))
	{
		SetActive(false);
		MAPMANAGER->ResetValue(Oldpt.x, Oldpt.y, HellTakerMap::eState::Mob);
		return;
	}
	if (MAPMANAGER->IsMob(pt.x, pt.y))
	{
		SetActive(false);
		MAPMANAGER->ResetValue(Oldpt.x, Oldpt.y, HellTakerMap::eState::Mob);
		return;
	}

	SetState(eState::WALK);
	MAPMANAGER->ResetValue(Oldpt.x, Oldpt.y, HellTakerMap::eState::Mob);
	MAPMANAGER->SetValue(pt.x, pt.y, HellTakerMap::eState::Mob, this);


	Vector2 position2 = MAPMANAGER->GetPosition(pt.x, pt.y);
	SetPosition(position2);
}


void Mob::Render()
{
	for (auto a : m_cvBones)
		a->Render();

	if (!IsActive())
		return;

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
void Mob::Reset()
{
	this->m_nState = eState::IDLE;
	SetRotation(0.0f, 0.0f, 0.0f);
}


