#include "MoveTo.h"

MoveTo::MoveTo(std::weak_ptr<Piece> _target, const GSvector2 & _from,
	const GSvector2 & _to, float _duration, std::function<void()> _callBack)
	:m_target(_target),
	m_from(_from),
	m_to(_to),
	m_duration(_duration),
	m_elapsedTime(0.0f),
	m_callBack(_callBack)
{
}

MoveTo::~MoveTo()
{
}
void MoveTo::update(float _deltaTime)
{
	m_elapsedTime += _deltaTime;
	if (m_target.expired())
	{
		m_elapsedTime = m_duration;
		return;
	}
	if (isEnd())
	{
		// アニメーションの終了処理
		m_target.lock()->move(m_to);
		if (m_callBack != nullptr)
		{
			m_callBack();
		}
		return;
	}
	auto rate = m_elapsedTime / m_duration;
	m_target.lock()->move(m_from.lerp(m_to, rate));
}

bool MoveTo::isEnd() const
{
	return m_elapsedTime >= m_duration;
}
