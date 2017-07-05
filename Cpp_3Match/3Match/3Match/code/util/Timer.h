#pragma once
/**
* @file Timer.h
* @brief　フレーム単位のタイマー
* @author 松尾裕也
* @date 2017/6/25
*/
#include <functional>
class Timer
{
public:
	Timer();
	~Timer()=default;
	void start(float _endTime,bool _isLoop=false, std::function<void()> _endCallback=nullptr);
	void update(float _deltaTime);
	bool isEnd()const;
	//!0~1
	float rate()const;
	bool isStart()const;
	void stop();
private:
	void timeEnd();
private:
	float m_currentTime;
	float m_endTime;

	bool m_isStart;
	bool m_isLoop;

	std::function<void()> m_endCallback;
};