#include "Play.h"
#include <cassert>
#include "../device/Input.h"
#include "Piece.h"

const float Play::WAIT_TIME = 30.0f; 
const float Play::HOLD_TIME = 240.0f;
Play::Play()
	:m_bord(),
	m_uiManager(),
	m_selectPiece(),
	m_currentState(GAME_STATE::IDEL),
	m_waitTimer(),
	m_holdTimer()
{
}

void Play::update(float deltaTime)
{
	switch (m_currentState)
	{
	case GAME_STATE::IDEL:
		select_piece();
		break;
	case GAME_STATE::PIECE_MOVE:
		piece_move(deltaTime);
		break;
	case GAME_STATE::MATCH_CHECK:
		matchCheck();
		break;
	case GAME_STATE::DELETE_PIECE:
		deletePiece();
		break;
	case GAME_STATE::FILL_PIECE:
		fillPiece();
		break;
	case GAME_STATE::WAIT:
		waiting(deltaTime);
		break;
	case GAME_STATE::DESTROY_PIECE:
		destoryPiece(deltaTime);
		break;
	default:
		break;
	}
	m_uiManager.changeGameState(m_currentState);
	
	m_bord.update(deltaTime);
}

void Play::draw(const IRenderer & _renderer) const
{
	m_bord.draw(_renderer);
	m_uiManager.draw(_renderer);
}

void Play::piece_move(float _deltaTime)
{
	const Input& input = Input::getInstance();
	
	m_uiManager.holdTime(m_holdTimer.rate());
	m_holdTimer.update(_deltaTime);
	if (input.mouseState(MOUSE::LEFT))
	{
		holdPiece();				
	}
	if(input.mouseUp(MOUSE::LEFT))
	{
		releasePiece();
	}
	
}

void Play::select_piece()
{
	const Input& input = Input::getInstance();
	if (!input.mouseDown(MOUSE::LEFT))return;
	/*if (!m_selectPiece.expired())return;*/

	m_selectPiece = m_bord.getNearestPiece(input.mousePosition());
	m_currentState = GAME_STATE::PIECE_MOVE;
	m_uiManager.resetCombo();
	m_holdTimer.start(HOLD_TIME, false, [&]()
	{
		releasePiece();
	});
}

void Play::matchCheck()
{
	m_currentState = m_bord.hasMatch() ? GAME_STATE::DELETE_PIECE : GAME_STATE::IDEL;
}

void Play::deletePiece()
{
	m_currentState = GAME_STATE::DESTROY_PIECE;
	m_bord.deleteMatchPiece();
}

void Play::fillPiece()
{
	changeWait(GAME_STATE::MATCH_CHECK, WAIT_TIME);
	m_bord.fillPiece();
}


void Play::waiting(float _deltaTime)
{
	m_waitTimer.update(_deltaTime);
}

void Play::destoryPiece(float _deltaTime)
{
	m_bord.destroyPiece(_deltaTime,&m_uiManager,[&]() { m_currentState = GAME_STATE::FILL_PIECE; });
}

void Play::changeWait(GAME_STATE _next, float _time)
{
	m_currentState = GAME_STATE::WAIT;
	m_waitTimer.start(_time, false, [&,_next]() { m_currentState = _next; });
}

void Play::holdPiece()
{
	if (m_holdTimer.isEnd())return;
	const Input& input = Input::getInstance();
	auto in_pos = input.mousePosition();
	auto piece = m_bord.getNearestPiece(in_pos);

	if (piece.expired())return;
	if (m_selectPiece.expired())return;

	auto piece_ptr = piece.lock();
	auto select_ptr = m_selectPiece.lock();
	if (piece_ptr != select_ptr)
	{
		m_bord.switchPiece(select_ptr, piece_ptr);
	}
	const float pieceHalf = Bord::PIECE_SIZE*0.5f;
	auto offset = GSvector2(-pieceHalf, -pieceHalf);
	select_ptr->select();
	select_ptr->move(in_pos + offset);
}

void Play::releasePiece()
{
	m_currentState = GAME_STATE::MATCH_CHECK;
	if (m_selectPiece.expired())return;
	auto select_ptr = m_selectPiece.lock();
	select_ptr->unSelect();
	m_bord.resetPosition(select_ptr);
	m_uiManager.holdTime(0.0f);
}
