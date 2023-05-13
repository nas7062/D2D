#pragma once
////////////////////////////////////////////////////////
//  Scene �߻�ȭ Class
//       --> Intro,Boss : Class�� ���� ������ ���� 
//           ��ӹ޾Ƽ� ����� �ϰ���
//  1. Virtual�� ���ǵ� �Լ��� ������ �߻�ȭ Class��� �Ѵ�
//  2. Delete�Ǵ� ���� �˾ƺ��� :  Child -> Parent
//  3. private, protected �˾ƺ��� :
////////////////////////////////////////////////////////
class Scene
{
public:
	virtual void  Update() = 0;        // ���� �����Լ�, ��ӹ��� ������ ����
	virtual void  Render() = 0;        // ���� �����Լ�, ��ӹ��� ������ ����
	                                   // virtual void  Update(); --> �����Լ�
	virtual void   ChangeScene() { }
	// Setter
	void   SetActive(bool active) { m_Active = active; }
	void   SetSceneName(string scnename) { m_strSceneName = scnename; }
	void   SetNextSceneName(string scnename) { m_strNextSceneName = scnename; }
	// Getter
	bool   IsActive() { return m_Active; }
	string GetSceneName() { return m_strSceneName; }
	string GetNextSceneName() { return m_strNextSceneName; }

protected: // �ٸ� Class���� ���� �ȵǴ� �� --> ��ӹ��� Class������ ���ٵ�
	bool   m_Active = true;
	string m_strSceneName;
	string m_strNextSceneName;

private:   // �ٸ� Class���� ���� �ȵǴ� �� --> ��ӹ��� Class������ ���� �ȵ�


public:
	Scene() {};
	~Scene(){};
};

