#include   "framework.h"
#include   "Animation.h"
#include   "Texture.h"
#include   "Renders/Shader.h"
#include   "AnimationClip.h"
///////////////////////////////////////////////////////////////
// ������
//////////////////////////////////////////////////////////////
Animation::Animation()
{
}
///////////////////////////////////////////////////////////////
// �Ҹ���
//////////////////////////////////////////////////////////////
Animation::~Animation()
{
	SAFE_DELETE(m_pTexture);

	if (m_cvAnimationClips.size())
	{
		for(UINT i=0; i< m_cvAnimationClips.size(); i++)
			delete m_cvAnimationClips[i];
		m_cvAnimationClips.erase(m_cvAnimationClips.begin(),
			m_cvAnimationClips.end());
	}

}
///////////////////////////////////////////////////////////////
//  AnimaionClip�� �ִ� �����͸� Update
//////////////////////////////////////////////////////////////
void Animation::Update(Matrix V, Matrix P)
{
	AnimationClip *pClip = nullptr;
	if (m_cvAnimationClips.size() == 0) return;
	if (m_nCurrentClip >= m_cvAnimationClips.size()) return;

	pClip = m_cvAnimationClips[m_nCurrentClip];

	pClip->SetPosition(m_Position);
	pClip->SetScale(m_Scale);
	pClip->SetRotation(m_Rotation);

	pClip->Update(V, P);               // Last�� Object View, Projection Update

}
///////////////////////////////////////////////////////////////
//  Render
//////////////////////////////////////////////////////////////
void Animation::Render()
{
	AnimationClip *pClip = nullptr;
	if (m_cvAnimationClips.size() == 0) return;
	if (m_nCurrentClip >= m_cvAnimationClips.size()) return;

	pClip = m_cvAnimationClips[m_nCurrentClip];
	pClip->Render();

}
///////////////////////////////////////////////////////////////
//  1. marco.pngó�� run,walk,attack etc�� �����Ϸ� �̷����
//    ���� Texture�� Aniamtion�� �����Ѵ�
//  2. �׷��� �ʴ� ����  AnimationClip class�� �ִ� 
//     CreateTexture()�� �̿��Ѵ�
//     walk.png, attack.png,
//  3. sprite ���ƾ� �ִ� ��� : Dead1.png ....... Dead15.png
//////////////////////////////////////////////////////////////
Texture * Animation::CreateTexture(wstring strImageFile, wstring strShaderFile)
{
	this->m_pTexture = new Texture(strImageFile, strShaderFile);
	return this->m_pTexture;
}
///////////////////////////////////////////////////////////////
// AnmationClip�� �Ӽ��� Once�� �Ǿ� �ִ� ���
// ���� ���� ���ΰ� Check
///////////////////////////////////////////////////////////////
bool Animation::IsPlay()
{
	AnimationClip *pClip = m_cvAnimationClips[m_nCurrentClip];
	return pClip->IsPlay();
}
///////////////////////////////////////////////////////////////
// VS,PS�� ����Ҷ� technique11�� ���� tech ��ȣ
//technique11 T0
//{
//	pass P0
//	{
//	}
//	pass P1
//	{
//	}
///////////////////////////////////////////////////////////////
void Animation::SetTech(int tech)
{
	AnimationClip *pClip = nullptr;
	if (m_cvAnimationClips.size() == 0) return;
	if (m_nCurrentClip >= m_cvAnimationClips.size()) return;

	pClip = m_cvAnimationClips[m_nCurrentClip];
	pClip->SetTech(tech);
}
///////////////////////////////////////////////////////////////
// VS,PS�� ����Ҷ� pass�� ���� tech ��ȣ
//technique11 T0
//{
//	pass P0
//	{
//	}
//	pass P1
//	{
//	}
///////////////////////////////////////////////////////////////
void Animation::SetPass(int pass)
{
	AnimationClip *pClip = nullptr;
	if (m_cvAnimationClips.size() == 0) return;
	if (m_nCurrentClip >= m_cvAnimationClips.size()) return;

	pClip = m_cvAnimationClips[m_nCurrentClip];
	pClip->SetPass(pass);
}
///////////////////////////////////////////////////////////////
// Shader���Ͽ� float������ ����Ҷ� �����Ͱ� �������� �Ҷ�
///////////////////////////////////////////////////////////////
void Animation::SetFloatConstant(string strName, float delta)
{
	AnimationClip *pClip = nullptr;
	if (m_cvAnimationClips.size() == 0) return;
	if (m_nCurrentClip >= m_cvAnimationClips.size()) return;

	pClip = m_cvAnimationClips[m_nCurrentClip];
	pClip->SetFloatConstant(strName, delta);
}
///////////////////////////////////////////////////////////////
// Player�� Update(),Render()���� Call
///////////////////////////////////////////////////////////////
void Animation::SetPlay(UINT PlayNo)
{

//  ������ Play�� Number�� ������ �ٲ��� �ʰԲ�
//	if (PlayNo == m_nCurrentClip)  
//		return;

	AnimationClip *pClip = nullptr;
	if (m_cvAnimationClips.size() == 0) return;
	if (m_nCurrentClip >= m_cvAnimationClips.size()) return;

	pClip = m_cvAnimationClips[m_nCurrentClip];

	if (pClip->IsPlay() && (PlayNo == m_nCurrentClip))
		return;


	pClip->SetPlay();
	m_nCurrentClip = PlayNo;

}

void Animation::SetStop()
{
	AnimationClip *pClip = nullptr;
	if (m_cvAnimationClips.size() == 0) return;
	if (m_nCurrentClip >= m_cvAnimationClips.size()) return;

	pClip = m_cvAnimationClips[m_nCurrentClip];
	pClip->SetStop();
}

Vector2 Animation::GetTextureSize()
{
	AnimationClip *pClip = m_cvAnimationClips[m_nCurrentClip];
	return pClip->GetTextureSize();
}

Vector2 Animation::GetRealTextureSize()
{
	AnimationClip *pClip = m_cvAnimationClips[m_nCurrentClip];
	return pClip->GetRealTextureSize();
}

Texture * Animation::GetTexture()
{
	AnimationClip *pClip = m_cvAnimationClips[m_nCurrentClip];
	return pClip->GetTexture();
}

int Animation::GetCurrentFrameNo()
{
	AnimationClip *pClip = m_cvAnimationClips[m_nCurrentClip];
	return pClip->GetCurrentFrameNo();
}
