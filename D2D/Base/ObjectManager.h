#pragma once
////////////////////////////////////////////////////////
// Object를 관리하는 Class
////////////////////////////////////////////////////////

#define  OBJECTMANAGER  ObjectManager::GetInstance()

class ObjectManager
{
public:
	static ObjectManager* GetInstance()
	{
		static ObjectManager instance;
		return &instance;
	}

public:
	void			Update(string name,Matrix V, Matrix P);      
	void			Render(string name);
	void			AddObject(string name, GameObject* obj);
	GameObject*     FindObject(string name);

private:
	map<string, GameObject*>   m_cmOjects;
private: 
	void	Delete();
private: //생성자
	ObjectManager();
public:  //소멸자
	~ObjectManager();
};

