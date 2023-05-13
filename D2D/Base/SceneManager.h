#pragma once
////////////////////////////////////////////////////////
// Scene�� �����ϴ� Class
////////////////////////////////////////////////////////
class SceneManager
{
public:
	static SceneManager* GetInstance()
	{
		static SceneManager instance;
		return &instance;
	}

public:
	// Scene�� ���� ���ۼ���
	enum eState
	{
		PLAY = 0,		// �����Ҽ� �ִ� ����
		UNCONTROLABLE,	// �÷��̾� ĳ������ ������ �Ұ����� ����
		PAUSE			// ȭ���� ������ ����
	};
	eState     m_nState = eState::PLAY;

public:
	void    SetSceneState() { m_nState = eState::PLAY; }
	void    SetDialogSceneState() { m_nState = eState::UNCONTROLABLE; }
	void	Update();      
	void	Render();
	void	Delete();
	void	ChangeScene(string name);
	void	ChangeDialogScene(string name);
	Scene*	GetScene(string name);
	Scene*	GetDialogScene(string name);
	Scene*  GetCurrentScene();
	void    LoadingObject();
	void    SetStartSceneName(string value) { m_strStartSceneName = value; }
	string  GetStartSceneName() { return m_strStartSceneName; }
	bool    IsLoadingEnd() { return m_bLoadingEnd; }
private:
	void    ThreadStart();
	void    ThreadStart2();
	bool    m_bLoadingEnd = false;

private: 
	vector<class Scene*>  m_cvScenes;        // Scene�� ��� �ִ� vector
	vector<class Scene*>  m_cvDialogScenes;
	string   m_strStartSceneName;

private:
	SceneManager();
private:
	~SceneManager();
};

