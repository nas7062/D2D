#include "framework.h"
#include "Camera.h"
#include  "Renders/Texture.h"

////////////////////////////////////////////////////////////////
//  ������
////////////////////////////////////////////////////////////////
Camera::Camera()
{
	// �⺻
	Vector3 eye = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
	Vector3 at = Vector3(0.0f, 0.0f, 1.0f);
	m_View = LookAt(eye, (eye + at), up); // D3DXMatrixLookAtLH(&V, &eye, &(eye + at), &up);

	// Texture

	wstring  shaderFile = L"14_Sprite.fx";
	wstring  imageFile = L"/Camera.png";
	m_pTexture = new Texture(imageFile, shaderFile);

}
////////////////////////////////////////////////////////////////
//  �Ҹ���
////////////////////////////////////////////////////////////////
Camera::~Camera()
{
	SAFE_DELETE(m_pTexture);
	
}
////////////////////////////////////////////////////////////////
//  Scene���� View,Projection�� ����� ���� ���
///////////////////////////////////////////////////////////////
void Camera::Update()
{
	Vector2 location = GetPosition();

	//ī�޶� ��鸲 ȿ��
	if (m_bEffect)
	{
		Effect();
		location = GetPosition();
	}
	else
	{
		if (this->m_pGameObj) // Camera�� ����� GameObject�� ��ġ�� �����ͼ� ����
		{
			location = m_pGameObj->GetPosition();
			location = location + m_Offset;
		}
		else
		{
			PreUpdate();    // Ű���� �Է¿� ���� ��ġ ��ǥ
			location = GetPosition();
		}
	}

	if (m_bLimit)
	{
		if (location.x > m_Right.x)
			location.x = m_Right.x;
		if (location.y > m_Right.y)
			location.y = m_Right.y;
		if (location.x < m_Left.x)
			location.x = m_Left.x;
		if (location.y < m_Left.y)
			location.y = m_Left.y;

	}



	SetPosition(location);

	Vector3 eye = Vector3(m_Position.x, m_Position.y, 0.0f);
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
	Vector3 at = Vector3(0.0f, 0.0f, 1.0f);
	m_View = LookAt(eye, (eye + at), up); // D3DXMatrixLookAtLH(&V, &eye, &(eye + at), &up);
}

////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////
void Camera::Update(Matrix V, Matrix P)
{

	m_pTexture->SetPosition(m_Position);
	m_pTexture->SetScale(0.5f, 0.5f);
	m_pTexture->Update(V, P);
}

void Camera::Render()
{
	m_pTexture->Render();
}

Matrix Camera::GetViewMatrix()
{
	return m_View;
}

Matrix Camera::GetProjectionMatrix()
{
	Matrix  P;
	//D3DXMatrixOrthoOffCenterLH(&P, 0.0f, (float)Main->GetWidth(),
	//	0.0f, (float)Main->GetHeight(), -1.0f, 1.0f);

	//ȭ���߽��� 0.0,0.0
	D3DXMatrixOrthoOffCenterLH(&P, -(float)Main->GetWidth()*0.5f, 
		                            (float)Main->GetWidth()*0.5f,
		                           -(float)Main->GetHeight()*0.5f, 
		                            (float)Main->GetHeight()*0.5f,
									-1.0f, 1.0f);
	return  P;
}
////////////////////////////////////////////////////////////////
// Window��ǥ�� ���� ��ǥ�� ��ȯ
///////////////////////////////////////////////////////////////
void Camera::WCtoVC(Vector2 & position)
{
	Matrix vp = GetViewMatrix()*GetProjectionMatrix();  // ����ȭ�鿡 ����Ǵ� matrix
	// inverse 
	D3DXMatrixInverse(&vp, NULL, &vp);

	position.x =   (position.x / Main->GetWidth())*2.0f - 1.0f;
	position.y = -((position.y / Main->GetHeight())*2.0f - 1.0f);

	D3DXVec2TransformCoord(&position, &position, &vp);

}
void Camera::VCtoWC(Vector2 & position)
{

	Matrix vp = GetViewMatrix()*GetProjectionMatrix();
	Matrix S;
	Matrix T;
	Matrix W;

	D3DXMatrixScaling(&S, Main->GetWidth()*0.5f, -Main->GetHeight()*0.5f, 0.0f);
	D3DXMatrixTranslation(&T, Main->GetWidth()*0.5f, Main->GetHeight()*0.5f, 0.0f);

	W = vp * S*T;
	D3DXVec2TransformCoord(&position, &position, &W);
}


void Camera::PreUpdate()
{
	Vector2 move = Vector2(0.0f, 0.0f);

	if (this->m_bkeyInput == false)
		return;

	if (KEYMANAGER->Press(VK_RIGHT))
		move = Vector2(m_MoveSpeed.x, 0.0f);
	if (KEYMANAGER->Press(VK_LEFT))
		move = Vector2(-m_MoveSpeed.x, 0.0f);
	if (KEYMANAGER->Press(VK_UP))
		move = Vector2(0.0f, m_MoveSpeed.y);
	if (KEYMANAGER->Press(VK_DOWN))
		move = Vector2(0.0f, -m_MoveSpeed.y);

	Vector2 location = m_Position;
	location = location + move * TIMEMANAGER->Delta();
	SetPosition(location);
}

Matrix Camera::LookAt(Vector3 eye, Vector3 at, Vector3 upVector)
{
	Vector3 forward = at - eye;
	D3DXVec3Normalize(&forward, &forward);

	Vector3 side;
	D3DXVec3Cross(&side, &upVector, &forward);
	D3DXVec3Normalize(&side, &side);

	Vector3 up;
	D3DXVec3Cross(&up, &forward, &side);
	Vector3 pos(-D3DXVec3Dot(&eye, &side), -D3DXVec3Dot(&eye, &up), -D3DXVec3Dot(&eye, &forward));

	Matrix View;

	// ����� �ʱ�ȭ
	D3DXMatrixIdentity(&View);

	View._11 = side.x;
	View._12 = up.x;
	View._13 = forward.x;
	View._14 = 0.0f;

	View._21 = side.y;
	View._22 = up.y;
	View._23 = forward.y;
	View._24 = 0.0f;

	View._31 = side.z;
	View._32 = up.z;
	View._33 = forward.z;
	View._34 = 0.0f;

	View._41 = pos.x;
	View._42 = pos.y;
	View._43 = pos.z;
	View._44 = 1.0f;
	return View;

}
////////////////////////////////////////////////////////////////
// ī�޶� ��鸲 ȿ��
// W = sin(2*3.141592*(t*frequence)+phase)* amp(delay�ð�-time)/delay�ð�
//  T: ����ð�, amp : ������ (���), 
////////////////////////////////////////////////////////////////
void Camera::Effect()
{
	Vector2 location = GetPosition();  //���� ī�޶��� �������� �����´�

	m_PlayTime = m_PlayTime + TIMEMANAGER->Delta();
	if (m_PlayTime < this->m_DelayTime)
	{
		location.x += (cos(2.0f*3.141592f*m_PlayTime * 3)* 10.f +
			cos(2.0f*3.141592f*m_PlayTime * 7 + 0.2f)   * 10.f +
			cos(2.0f*3.141592f*m_PlayTime * 15 + 0.5f) * 1.1f)*
			(m_DelayTime - m_PlayTime) / m_DelayTime;
		location.y += (sin(2.0f*3.141592f*m_PlayTime * 3)* 10.f +
			cos(2.0f*3.141592f*m_PlayTime * 7 + 0.2f)   * 10.f +
			cos(2.0f*3.141592f*m_PlayTime * 15 + 0.5f) * 1.1f)*
			(m_DelayTime - m_PlayTime) / m_DelayTime;
	}
	else
	{
		m_PlayTime = 0.0f;
		m_bEffect = false;
	}
	SetPosition(location);
}


