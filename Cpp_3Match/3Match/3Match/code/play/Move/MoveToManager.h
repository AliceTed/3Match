#pragma once
/**
* @file Bord.h
* @brief�@�s�[�X�Ǘ�
* @author �����T��
* @date 2017/6/24
*/
#include <vector>
#include <queue>
#include "MoveData.h"
#include "MoveTo.h"
#include "../Piece.h"
using DataList = std::vector<MoveData>;
class MoveToManager
{
	using DataQueue = std::queue<DataList>;
	using MoveList = std::vector<MoveTo>;
public:
	MoveToManager();
	~MoveToManager();

	void update(float _deltaTime);
	//!�ړ��f�[�^��ǉ�
	void addMoveDatas(const DataList& _datas);

private:
	//!�ړ��f�[�^���ړ����ɓo�^
	void registerMoves();
	//!�ړ�����MoveList���A�b�v�f�[�g
	void movesUpdate(float deltaTime);
private:
	//�ړ��J�n��MoveData
	DataQueue m_moveQueue;
	//!�ړ���
	MoveList m_currentMoves;
};