#include  "framework.h"
#include  "Button.h"
#include  "Collider/Collider.h"
#include   "System/Keyboard.h"
///////////////////////////////////////////////////////////
// 持失切
//////////////////////////////////////////////////////////
Button::Button()
{
	wstring  imgFile     = L"/helltaker/Button/button1000x100.png";
	wstring  shaderFile  = L"00_Animation.fx";
	
	SetName("Button");
	m_pButton = new Texture(imgFile, shaderFile);
}

Button::~Button()
{
	SAFE_DELETE(m_pButton);
}
void Button::Update(Matrix V, Matrix P)
{
	Color color = Color(255.0f / 255.0f, 150.0f / 255.0f, 165.0f / 255.0f, 0);

	if (m_bSelect)
	{
		if (KEYMANAGER->Down('W') || KEYMANAGER->Down(VK_UP))
		{
			m_bSelect = false;
			if (this->m_fpButtonCallBack)
				m_fpButtonCallBack(0);
		}
			
		if (KEYMANAGER->Down('S') || KEYMANAGER->Down(VK_DOWN))
		{
			m_bSelect = false;
			if (this->m_fpButtonCallBack)
				m_fpButtonCallBack(0);
		}
			
		if (KEYMANAGER->Down(VK_RETURN) || KEYMANAGER->Down(VK_SPACE))
		{
			if (this->m_fpButtonCallBack)
				m_fpButtonCallBack(1);
		}
	

	}






	if( this->m_bSelect)
		color = Color(230.0f / 255.0f, 77.0f / 255.0f, 81.0f / 255.0f, 0);
	else
		color = Color(101.0f / 255.0f, 61.0f / 255.0f, 81.0f / 255.0f, 0);

	m_pButton->GetShader()->AsVector("TextureColor")->SetFloatVector(color);
	m_pButton->SetPass(4);
	m_pButton->SetPosition(m_Position);
	m_pButton->SetScale(m_Scale);
	m_pButton->Update(V, P);

}

void Button::Render()
{
	m_pButton->Render();

	// 2D Render越切 
	//2D Render
	DirectWrite::GetDC()->BeginDraw();
	{
		float x = -(m_strButton.length()*30.0f*0.5f);
		Vector2   pos2 = Vector2(x, m_Position.y+m_pButton->GetRealTextureSize().y*0.3f);
		CAMERA->VCtoWC(pos2);
		DirectWrite::RenderText(m_strButton, pos2, 255, 0, 255, 30.0f);
	}
	DirectWrite::GetDC()->EndDraw();

}


