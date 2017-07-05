#pragma once
/**
* @file Bord.h
* @brief　ピース管理
* @author 松尾裕也
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
	//!移動データを追加
	void addMoveDatas(const DataList& _datas);

private:
	//!移動データを移動中に登録
	void registerMoves();
	//!移動中のMoveListをアップデート
	void movesUpdate(float deltaTime);
private:
	//移動開始のMoveData
	DataQueue m_moveQueue;
	//!移動中
	MoveList m_currentMoves;
};