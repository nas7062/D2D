#pragma once
#define KEYMAX 256
////////////////////////////////////////////////////////////
// Ű����,Time,���콺 �����  �̱��溣�̽��� �����
////////////////////////////////////////////////////////////
class Keyboard
{
public:
	static Keyboard* GetInstance()
	{
		static Keyboard singleToneInstance;   // class �� ����
		return &singleToneInstance;           // class�� �ּҸ� return
	}
public:
	bool Down(int key);                       // Key�� �ѹ� ������ ���
	bool Up(int key);                         // Key�� �ѹ� Up�� ���
	bool Press(int key);                      // Key�� ��������� ������ ���
	bool Toggle(int key);                     // Key�� On/Off
private:
	bitset<KEYMAX>  m_KeyUP;                  // UP�� ����
	bitset<KEYMAX>  m_KeyDown;                // Down�� ����
	bitset<KEYMAX>  GetKeyUp()   { return m_KeyUP; }
	bitset<KEYMAX>  GetKeyDown() { return m_KeyDown; }
	void  SetKeyDown(int key, bool state) { m_KeyDown.set(key, state); }
	void  SetKeyUp(int key, bool state)   { m_KeyUP.set(key, state); }
private: // ������/�Ҹ��� private�� �Ѵ�
	Keyboard();
	~Keyboard();

};

