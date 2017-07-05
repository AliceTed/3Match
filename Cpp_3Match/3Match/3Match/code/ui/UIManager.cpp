#include "UIManager.h"
#include "../renderer/desc/StringRenderDesc.h"
#include "../renderer/IRenderer.h"
UIManager::UIManager()
	:m_stateText("èÛë‘:"),
	m_combo(0),
	m_holdTime(1.0f)
{
}

void UIManager::changeGameState(GAME_STATE _state)
{
	m_stateText = "èÛë‘:";
	switch (_state)
	{
	case GAME_STATE::IDEL:
		m_stateText += "IDEL";
		break;
	case GAME_STATE::PIECE_MOVE:
		m_stateText += "PIECE_MOVE";
		break;
	case GAME_STATE::MATCH_CHECK:
		m_stateText += "MATCH_CHECK";
		break;
	case GAME_STATE::DELETE_PIECE:
		m_stateText += "DELETE_PIECE";
		break;
	case GAME_STATE::FILL_PIECE:
		m_stateText += "FILL_PIECE";
		break;
	case GAME_STATE::WAIT:
		m_stateText += "WAIT";
		break;
	case GAME_STATE::DESTROY_PIECE:
		m_stateText += "DESTROY_PIECE";
		break;
	default:
		m_stateText += "ïsñæ";
		break;
	}
}

void UIManager::resetCombo()
{
	m_combo = 0;
}

void UIManager::addCombo()
{
	m_combo++;
}

void UIManager::holdTime(float _rate)
{
	m_holdTime = 1-_rate;
}

void UIManager::draw(const IRenderer & _renderer) const
{
	StringRenderDesc desc;
	desc.position = GSvector2(50, 400);
	desc.string = "COMBO:" + std::to_string(m_combo);
	desc.font.size = 20;
	desc.color = GScolor(0,0,0,1);
	_renderer.draw(desc);

	desc.position = GSvector2(50, 450);
	desc.string = m_stateText;
	_renderer.draw(desc);

	desc.position = GSvector2(50, 500);
	desc.string = "écÇË:" + std::to_string(m_holdTime);
	_renderer.draw(desc);
}
