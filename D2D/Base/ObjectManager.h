#pragma once
////////////////////////////////////////////////////////
// Object�� �����ϴ� Class
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
private: //������
	ObjectManager();
public:  //�Ҹ���
	~ObjectManager();
};

