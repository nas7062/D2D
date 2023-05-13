#include "framework.h"
#include "Time.h"
// https://blog.naver.com/wjdeh313/222071831028
///////////////////////////////////////////////////////////
// ������ & �Ҹ���
//////////////////////////////////////////////////////////
Time::Time()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&m_CurrentTime);
	QueryPerformanceCounter((LARGE_INTEGER*)&m_LastTime);
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_TickPerSecond);  // CPU�� Frequency

	m_FPSUpdateInterval = m_TickPerSecond >> 1;
	//printf("Time = %d\n", m_CurrentTime);
}

Time::~Time()
{
}
void Time::Update()  // Game->Update() -> Game->Render()
{
	// 1. ����ð��� ������ �ð� ���ݹ� ����ð��� ����Ѵ�
	QueryPerformanceCounter((LARGE_INTEGER*)&m_CurrentTime);
	timeElased = (float)(m_CurrentTime - m_LastTime) / (float)m_TickPerSecond;
	m_RunningTime = m_RunningTime + timeElased;

	// 2. FPS Update
	m_FrameCount++;

	if (m_CurrentTime - m_LastFPSUpdate >= m_FPSUpdateInterval)
	{
		float tmpCurrentTime = (float)m_CurrentTime / (float)m_TickPerSecond;
		float tmpLastTime =    (float)m_LastFPSUpdate/ (float)m_TickPerSecond;

		m_FramePerSecond = (float)m_FrameCount / (tmpCurrentTime - tmpLastTime);
		m_LastFPSUpdate = m_CurrentTime;
		m_FrameCount = 0;

	}
	m_LastTime = m_CurrentTime;

}

void Time::Update(float lockFPS)
{
	// 1. ����ð��� ������ �ð� ���ݹ� ����ð��� ����Ѵ�
	QueryPerformanceCounter((LARGE_INTEGER*)&m_CurrentTime);
	timeElased = (float)(m_CurrentTime - m_LastTime) / (float)m_TickPerSecond;
	

	while(timeElased < 1.0f/ lockFPS)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&m_CurrentTime);
		timeElased = (float)(m_CurrentTime - m_LastTime) / (float)m_TickPerSecond;

	}
	m_RunningTime = m_RunningTime + timeElased;

	// 2. FPS Update
	m_FrameCount++;

	if (m_CurrentTime - m_LastFPSUpdate >= m_FPSUpdateInterval)
	{
		float tmpCurrentTime = (float)m_CurrentTime / (float)m_TickPerSecond;
		float tmpLastTime = (float)m_LastFPSUpdate / (float)m_TickPerSecond;

		m_FramePerSecond = (float)m_FrameCount / (tmpCurrentTime - tmpLastTime);
		m_LastFPSUpdate = m_CurrentTime;
		m_FrameCount = 0;

	}
	m_LastTime = m_CurrentTime;



}


