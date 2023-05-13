#include  "framework.h"
#include  "Texture.h"
#include  "Renders/Shader.h"
#include "AnimationClip.h"

///////////////////////////////////////////////////////////////
// 생성자
//////////////////////////////////////////////////////////////
AnimationClip::AnimationClip(eState state)
{
	if (state == eState::Once)
		SetOnce();
}

AnimationClip::~AnimationClip()
{
	if (m_cvFrames.size())
	{
		for (UINT i = 0; i < m_cvFrames.size(); i++)
			delete m_cvFrames[i];

		m_cvFrames.erase(m_cvFrames.begin(), m_cvFrames.begin()+ m_cvFrames.size());
	}

	SAFE_DELETE(m_pTexture);

	if (m_cvSRVs.size())
	{
		for (UINT i = 0; i < m_cvSRVs.size(); i++)
			SAFE_RELEASE(m_cvSRVs[i]);

		m_cvSRVs.erase(m_cvSRVs.begin(), m_cvSRVs.end());
	}

}

//////////////////////////////////////////////////////
// 1. 시간에 따라 Frame의 인덱스를 변경 
// 2. 해당되는 Frame의 좌표,스케일,회전 정보를 넘겨준다
/////////////////////////////////////////////////////
void AnimationClip::Update(Matrix V, Matrix P)
{
	// 이상처리
	if (m_cvFrames.size() == 0) return;
	if (m_cvFrames.size() <= m_nCurrentFrame) return;

	Frame *pFrame = m_cvFrames[m_nCurrentFrame];

	// 시간 check
	if (IsPlay())
	{
		this->m_PlayTime = m_PlayTime + TIMEMANAGER->Delta();
		if (m_PlayTime >= pFrame->m_Time)
		{
			m_nCurrentFrame++;     // 다음 image index
			if (m_nCurrentFrame == m_cvFrames.size())
			{
				if (m_nPlayMode == 0) // Once --> Attack
				{
					m_nCurrentFrame = m_cvFrames.size() - 1;
					SetStop();
				}
				else	
				m_nCurrentFrame = 0; // 최초 Image
			}
			m_PlayTime = 0.0f;
		}
		
	}

	pFrame = m_cvFrames[m_nCurrentFrame];

	if (m_cvSRVs.size() > 0)
	{
		pFrame->m_Image->SetResource(m_cvSRVs[m_nCurrentFrame]);
	}


		

	// ImageFile이 변경 되는 경우  후에....

	//if(m_pSRV)
	//	pFrame->m_Image->SetR

	// 좌표,SCALE등을 넘겨준다

	/*
	for (UINT i = 0; i < m_cvFrames.size(); i++)
	{
		m_cvFrames[i]->m_Image->SetPosition(m_Position);
		m_cvFrames[i]->m_Image->SetScale(m_Scale);
		m_cvFrames[i]->m_Image->SetRotation(m_Rotation);
		m_cvFrames[i]->m_Image->SetOffset(m_cvFrames[i]->m_Offset);
		m_cvFrames[i]->m_Image->SetOffsetSize(m_cvFrames[i]->m_OffsetSize);
		m_cvFrames[i]->m_Image->Update(V, P);
	}
	*/
	pFrame->m_Image->SetPosition(m_Position);
	pFrame->m_Image->SetScale(m_Scale);
	pFrame->m_Image->SetRotation(m_Rotation);
	pFrame->m_Image->SetOffset(pFrame->m_Offset);
	pFrame->m_Image->SetOffsetSize(pFrame->m_OffsetSize);
	pFrame->m_Image->Update(V, P);
}

void AnimationClip::Render()
{
	// 이상처리
	if (m_cvFrames.size() == 0) return;
	if (m_cvFrames.size() <= m_nCurrentFrame) return;

	Frame *pFrame = m_cvFrames[m_nCurrentFrame];
	pFrame->m_Image->Render();
}

void AnimationClip::AddFrame(Texture * image, float startX, float startY, float endX, float endY, float delta)
{
	Frame *pFrame        = new Frame();
	pFrame->m_Image      = image;
	pFrame->m_Offset     = Vector2(startX, startY);
	pFrame->m_OffsetSize = Vector2(endX-startX, endY - startY);
	pFrame->m_Time = delta;

//	printf("%f %f %f %f\n", startX, startY, endX - startX, endY - startY);
	m_cvFrames.push_back(pFrame);
}

void AnimationClip::AddFrame(Texture * image, wstring ImageFileName, float startX, float startY, float endX, float endY, float delta)
{

	Frame *pFrame = new Frame();
	pFrame->m_Image = image;
	pFrame->m_Offset = Vector2(startX, startY);
	pFrame->m_OffsetSize = Vector2(endX - startX, endY - startY);
	pFrame->m_Time = delta;
	pFrame->m_strImageFile = ImageFileName;
	m_cvFrames.push_back(pFrame);


	wstring strFile = L"./_Textures/" + ImageFileName;
	CreateShaderResourceView(strFile);



	// ImageFile 

	D3DX11_IMAGE_INFO  ImageInfo;

	HRESULT hr = D3DX11GetImageInfoFromFile(strFile.c_str(), NULL, &ImageInfo, NULL);

	float TextureWidth = (float)ImageInfo.Width;
	float TextureHeight = (float)ImageInfo.Height;

	if (pFrame->m_OffsetSize.x == 0.0)
		pFrame->m_OffsetSize.x = TextureWidth;
	if (pFrame->m_OffsetSize.y == 0.0)
		pFrame->m_OffsetSize.y = TextureHeight;

}

Texture* AnimationClip::CreateTexture(wstring strImageFile, wstring strShaderFile)
{
	this->m_pTexture = new Texture(strImageFile, strShaderFile);
	return this->m_pTexture;
}

void AnimationClip::CreateShaderResourceView(wstring strImageFile)
{
	ID3D11ShaderResourceView* pSRV;

	long  start = GetTickCount();
	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(
		Device, strImageFile.c_str(), NULL, NULL, &pSRV, NULL);
	assert(SUCCEEDED(hr));
	this->m_cvSRVs.push_back(pSRV);
	long end =  GetTickCount();

	//printf("%ws %d\n", strImageFile.c_str(),end - start);
}

Vector2 AnimationClip::GetTextureSize()
{
	Vector2 size(0.0f, 0.0f);

	if (m_cvFrames.size() == 0)
		return size;
	Frame *pFrame = m_cvFrames[m_nCurrentFrame];
	
	return pFrame->m_OffsetSize;
}

Vector2 AnimationClip::GetRealTextureSize()
{
	Vector2 size(0.0f, 0.0f);
	if (m_cvFrames.size() == 0)
		return size;
	Frame *pFrame = m_cvFrames[m_nCurrentFrame];
	size = Vector2(pFrame->m_Image->GetRealTextureSize());
	return size;
}

Texture * AnimationClip::GetTexture()
{
	if (this->m_pTexture)
		return m_pTexture;

	if (m_cvFrames.size() == 0)
	   return nullptr;
	Frame *pFrame = m_cvFrames[m_nCurrentFrame];
	return pFrame->m_Image;
}


