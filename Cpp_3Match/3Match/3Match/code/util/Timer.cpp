#include "Timer.h"
#include "Math.h"


Timer::Timer()
	: m_currentTime(0.0f),
	m_endTime(0.0f),
	m_isStart(false),
	m_endCallback(nullptr)
{
}

void Timer::start(float _endTime, bool _isLoop, std::function<void()> _endCallback)
{
	m_currentTime = 0.0f;
	m_endTime = _endTime;
	m_isStart = true;
	m_endCallback = _endCallback;
	m_isLoop = _isLoop;
}

void Timer::update(float _deltaTime)
{
	if (!m_isStart)return;

	if (isEnd())
	{
		timeEnd();
		return;
	}
	m_currentTime = Math::clamp(m_currentTime + _deltaTime, 0.0f, m_endTime);
}

bool Timer::isEnd() const
{
	return m_currentTime >= m_endTime;
}

float Timer::rate() const
{
	return m_currentTime / m_endTime;
}

bool Timer::isStart() const
{
	return m_isStart;
}

void Timer::stop()
{
	m_isStart = false;
}

void Timer::timeEnd()
{
	if (m_endCallback != nullptr)
	{
		m_endCallback();
	}
	if (!m_isLoop)return;
	m_currentTime = 0.0f;
}
