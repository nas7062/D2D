#include "framework.h"
#include "ObjectManager.h"
/////////////////////////////////////////////////
//  생성자
/////////////////////////////////////////////////
ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
	Delete();
}
void ObjectManager::Delete()
{
	for (auto a : m_cmOjects)
		SAFE_DELETE(a.second);  // ObjectManager에 등록된것은 여기서 지움
	m_cmOjects.clear();
}
//////////////////////////////////////////////////
// Update
//////////////////////////////////////////////////
void ObjectManager::Update(string name, Matrix V, Matrix P)
{
	GameObject* pObject = FindObject(name);

	if (!pObject) return;
	pObject->Update(V, P);

}

void ObjectManager::Render(string name)
{
	GameObject* pObject = FindObject(name);

	if (!pObject) return;
	pObject->Render();

}
void ObjectManager::AddObject(string name, GameObject * obj)
{
	m_cmOjects.insert(make_pair(name, obj));
}

GameObject * ObjectManager::FindObject(string name)
{
	GameObject* pObject = nullptr;

	if (m_cmOjects.count(name))
		pObject = m_cmOjects[name];
	return pObject;
}




