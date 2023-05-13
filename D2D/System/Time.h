#pragma once
////////////////////////////////////////////////////////
// �������α׷����� �������� ����̵ȴ�.  �÷��̾�/���� ����
//  Time, Ű����, ���콺 etc�� �̱���(���Ѱ��� �����ǰ� ����¹�)
//  ���� �����
//  ����� ���
//  1. ������/�Ҹ��ڸ�  public --> private�� 
//  2. public�Լ���  �����ϴ� �Լ��� �����
////////////////////////////////////////////////////////
class Time
{
public:
	// 2. public�Լ���  �����ϴ� �Լ��� �����
	static Time* GetInstance()
	{
		static  Time singletoneInstance;
		return  &singletoneInstance;
	}

public:
	void  Update();                    // �ð��� Update
	void  Update(float lockFPS);       // �ð��� Update    Frame Per Second
	float Delta() { return timeElased; }
	float GetRunning() { return m_RunningTime; }
	float timeElased = 0.0f;          // ���� ���������� ���� ����� �ð�
	float GetFPS() {return m_FramePerSecond;}
private:
	INT64 m_TickPerSecond = 0;         // �ʴ� Tick Count
	INT64 m_CurrentTime   = 0;         // ���� �ð�
	INT64 m_LastTime      = 0;         // ���� �ð�
	INT64 m_LastFPSUpdate = 0;         // ������ FPS ������Ʈ �ð�
	INT64 m_FPSUpdateInterval = 0;     // FPS ������Ʈ ����
	UINT  m_FrameCount = 0;            // Frame ��
	float m_RunningTime = 0.0f;        // ����ð� ( Start --> Current)
	float m_FramePerSecond = 0.0f;     // FPS

private:  // 1. ������/�Ҹ��ڸ�  public --> private�� 
	Time();
	~Time();
};

