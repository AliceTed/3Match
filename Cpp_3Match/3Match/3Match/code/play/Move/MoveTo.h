#pragma once
/**
* @file MoveTo.h
* @brief@ˆÚ“®
* @author ¼”ö—T–ç
* @date 2017/6/24
*/
#include <GSvector2.h>
#include<functional>
#include <memory>
#include "../Piece.h"
class MoveTo
{
public:
	MoveTo(std::weak_ptr<Piece> _target, const GSvector2& _from,const GSvector2& _to,
		float _duration, std::function<void()> _callBack = nullptr);
	~MoveTo();

	void update(float _deltaTime);
	bool isEnd()const;

private:
	GSvector2 m_from;
	GSvector2 m_to;
	float m_duration;
	float m_elapsedTime;
	std::function<void()> m_callBack;
	std::weak_ptr<Piece> m_target;
};
