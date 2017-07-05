#pragma once
/**
* @file MoveData.h
* @brief�@MoveTo�f�[�^�ێ��p�\����
* @author �����T��
* @date 2017/6/24
*/
#include <gslib.h>
#include <memory>
#include "../Piece.h"
struct MoveData
{
	MoveData(std::weak_ptr<Piece> _target,const GSvector2& _targetPosition,float _duration)
		:target(_target), targetPosition(_targetPosition),duration(_duration)
	{
	}

	std::weak_ptr<Piece> target;
	GSvector2 targetPosition;
	float duration;
};