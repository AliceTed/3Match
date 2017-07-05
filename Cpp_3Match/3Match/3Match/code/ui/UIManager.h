#pragma once
/**
* @file UIManager.h
* @brief@UI‚ÌŠÇ—
* @author ¼”ö—T–ç
* @date 2017/6/25
*/
#include <string>
#include "../play/GAME_STATE.h"
class IRenderer;
class UIManager
{
public:
	UIManager();
	~UIManager()=default;

	void changeGameState(GAME_STATE _state);

	void resetCombo();
	void addCombo();

	void holdTime(float _rate);

	void draw(const IRenderer& _renderer)const;

private:
	std::string m_stateText;
	float m_holdTime;
	int m_combo;

};