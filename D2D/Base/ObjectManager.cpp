#include "framework.h"
#include "ObjectManager.h"
/////////////////////////////////////////////////
//  ������
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
		SAFE_DELETE(a.second);  // ObjectManager�� ��ϵȰ��� ���⼭ ����
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




