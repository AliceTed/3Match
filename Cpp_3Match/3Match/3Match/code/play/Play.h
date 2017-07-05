#pragma once
/**
* @file Play.h
* @brief@ƒvƒŒƒC‚ÌŠÇ—
* @author ¼”ö—T–ç
* @date 2017/6/24
*/
#include "Bord.h"
#include "../util/Timer.h"
#include "GAME_STATE.h"
#include "../ui/UIManager.h"
class Play
{
	using PiecePtr=std::weak_ptr<Piece>;
public:
	Play();
	~Play()=default;

	void update(float deltaTime);
	void draw(const IRenderer& _renderer)const;

private:
	void piece_move(float _deltaTime);
	void select_piece();
	void matchCheck();
	void deletePiece();
	void fillPiece();

	void waiting(float _deltaTime);

	void destoryPiece(float _deltaTime);

	void changeWait(GAME_STATE _next,float _time);

	void holdPiece();
	void releasePiece();

private:
	Bord m_bord;
	UIManager m_uiManager;
	PiecePtr m_selectPiece;
	Timer m_waitTimer;
	//“®‚©‚µ‚Ä‚¢‚ç‚ê‚éŠÔ
	Timer m_holdTimer;

	GAME_STATE m_currentState;

	static const float WAIT_TIME;
	static const float HOLD_TIME;
};
