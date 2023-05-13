#pragma once
//////////////////////////////////////////////////
// Aniamtion  --> Image �������� ������ �ִ� Class
// rendering�ϴ� class
// Animation Class
//   ---> Aniamtion Clip Class
//         --> Texture Class
//////////////////////////////////////////////////
class Animation
{
public:
	void      Update(Matrix V, Matrix P);
	void      Render();
public:      // other
	void      AddAnimationClip(class AnimationClip *pClip){m_cvAnimationClips.push_back(pClip);}
	class     Texture*  CreateTexture(wstring strImageFile, wstring strShaderFile);
	bool      IsPlay();  // ���� Animation�� ���۵ǰ� �ִ°�?

public:		// setter
	void		SetPosition(float x, float y) { m_Position = Vector2(x, y); }
	void		SetPosition(Vector2 position) { m_Position = position; }
	void		SetScale(float x, float y) { m_Scale = Vector2(x, y); }
	void		SetScale(Vector2 scale) { m_Scale = scale; }
	void		SetRotation(float x, float y, float z) { m_Rotation = Vector3(x, y, z); }
	void		SetRotation(Vector3 rotation) { m_Rotation = rotation; }
	void		SetTech(int tech);
	void		SetPass(int pass);
	void		SetFloatConstant(string strName, float delta);
	void        SetPlay(UINT PlayNo);    // AnimationClip ��  Index�� ����
	void        SetStop();               // ������ Stop�ϰ� ������
public:   // getter
	Vector2		GetPosition() { return m_Position; }
	Vector2		GetScale()    { return m_Scale; }
	Vector3		GetRotation() { return m_Rotation; }
	Vector2     GetTextureSize();
	Vector2     GetRealTextureSize();
	Texture*    GetTexture();
	int         GetCurrentFrameNo();

	
private:
	Vector2      m_Scale    = Vector2(1.0f, 1.0f);        // Scale
	Vector2      m_Position = Vector2(0.0f, 0.0f);        // ��ǥ
	Vector3      m_Rotation = Vector3(0.0f, 0.0f, 0.0f);  // ȸ��
	vector<class AnimationClip*>   m_cvAnimationClips;    // IDLE,WALK,ATTACK
	UINT         m_nCurrentClip = 0;
	class        Texture    *m_pTexture = nullptr;        // �� Image run,walk

public:
	Animation();
	~Animation();
};
