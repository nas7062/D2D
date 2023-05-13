#pragma once
////////////////////////////////////////////////////////
// Scene을 관리하는 Class
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
	// Scene에 대한 조작설정
	enum eState
	{
		PLAY = 0,		// 조작할수 있는 상태
		UNCONTROLABLE,	// 플레이어 캐릭터의 조작이 불가능한 상태
		PAUSE			// 화면이 정지된 상태
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
	vector<class Scene*>  m_cvScenes;        // Scene을 담아 넣는 vector
	vector<class Scene*>  m_cvDialogScenes;
	string   m_strStartSceneName;

private:
	SceneManager();
private:
	~SceneManager();
};

