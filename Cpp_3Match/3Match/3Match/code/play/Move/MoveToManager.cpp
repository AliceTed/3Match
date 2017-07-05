#include "MoveToManager.h"
#include <algorithm>
MoveToManager::MoveToManager()
	:m_moveQueue(),
	m_currentMoves()
{
}

MoveToManager::~MoveToManager()
{
}

void MoveToManager::update(float _deltaTime)
{
	registerMoves();
	movesUpdate(_deltaTime);
}

void MoveToManager::addMoveDatas(const DataList & _datas)
{
	m_moveQueue.push(_datas);
}

void MoveToManager::registerMoves()
{
	if (m_moveQueue.size() > 0)
	{
		auto queue = m_moveQueue.front();
		m_moveQueue.pop();
		for (auto data : queue)
		{			
			auto moveTo = MoveTo(data.target, data.target.lock()->getPosition(), data.targetPosition, data.duration);
			m_currentMoves.emplace_back(moveTo);
		}
	}
}

void MoveToManager::movesUpdate(float deltaTime)
{
	for (auto& i : m_currentMoves)
	{
		i.update(deltaTime);
	}
	auto itr = std::remove_if(m_currentMoves.begin(), m_currentMoves.end(), 
		[](const MoveTo& _m) {return _m.isEnd(); });
	m_currentMoves.erase(itr, m_currentMoves.end());
}
