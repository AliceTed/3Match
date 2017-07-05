#pragma once
/**
* @file Bord.h
* @brief　ピース管理
* @author 松尾裕也
* @date 2017/6/24
*/

#include <memory>
#include <vector>
#include "../util/Array2D.h"
#include "../util/IntVector2.h"
#include "Move\MoveToManager.h"
#include "PIECE_KIND.h"
#include "Piece.h"
#include "../util/Timer.h"
class IRenderer;
class UIManager;
class Bord
{
	using PiecePtr = std::shared_ptr<Piece>;
	using Conatiner = std::vector<PiecePtr>;
public:
	Bord();
	~Bord();

	void update(float _deltaTime);
	void draw(const IRenderer& _renderer)const;
	std::weak_ptr<Piece> getNearestPiece(const GSvector2& input)const;
	//!指定ピースの位置をボード上の位置に修正
	void resetPosition(PiecePtr _piece);
	void switchPiece(PiecePtr _p1, PiecePtr _p2);

	bool hasMatch()const;
	void deleteMatchPiece(std::function<void()> _callback = nullptr);
	//!ピースが消えている場所を詰めて、新しいピースを生成する
	void  fillPiece(std::function<void()> _callback = nullptr);

	//優先度順で死亡状態のpieceを削除
	void destroyPiece(float _deltaTime, UIManager* _ui, std::function<void()> _callback = nullptr);
private:
	void instantiatePiece(const IntVector2& _location);
	void setPiece(const IntVector2& _location, PiecePtr _piece);
	//!ピースからボード上の位置取得
	IntVector2 getPieceBoardPos(PiecePtr _piece)const;
	//!ボード上の位置からワールド座標取得
	GSvector2 getPieceWorldPos(const IntVector2& _location)const;
	const PiecePtr getPiece(const IntVector2& _location)const;
	bool isInBord(const IntVector2& _index)const;

	//!
	bool isMatchPiece(PiecePtr _piece)const;

	//! 対象の方向に引数で指定したの種類のピースがいくつあるかを返す
	int getSameKindPieceNum(PIECE_KIND _kind, const IntVector2& _pos, const IntVector2& _searchDir)const;

	bool isKindPiece(const IntVector2& _index, PIECE_KIND _kind)const;

	//!特定のピースのが削除されているかを判断し、削除されているなら詰めるか、それができなければ新しく生成する
	void fillPiece(const IntVector2& _location);

	void createPiece(const IntVector2& _location);

	PIECE_KIND getRandomKind()const;

	//!指定のpieceがマッチしている場合、ほかのマッチしたピースとともに死亡状態にする
	void deadMatchPiece(const IntVector2& _location, PIECE_KIND _kind,int _deadPriority);
	
	//優先度の高いものを配列で取得
	std::vector<PiecePtr> highPriorityPieces()const;
	//重複しているピースを削除
	void samePieceDestroy(const std::vector<PiecePtr>& _pieces);
	//!一定spanで呼ばれる削除処理 削除するピースがなくなった時 falseが返ってくる
	bool destroyPiece();
private:
	Conatiner m_bord;
	MoveToManager m_moveToManager;
	//!穴埋めするピースの移動を格納
	std::vector<MoveData> m_fillMoveDatas;
	//!新しく生成するピースの位置を格納
	std::vector<IntVector2> m_createLocation;

	Timer m_destroySpan;

	static const IntVector2 MAP_SIZE;
	static const float SWITCH_PIECE_DURATION;
	static const float Fill_PIECE_DURATION;
	static const float DESTROY_SPAN;

public:
	//Playで使うため
	static const float PIECE_SIZE;
};
