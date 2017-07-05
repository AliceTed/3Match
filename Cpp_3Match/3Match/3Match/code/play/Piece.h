#pragma once
/**
* @file Piece.h
* @brief 
* @author 松尾裕也
* @date 2017/6/24
*/
#include <gslib.h>
#include "PIECE_KIND.h"
#include "../id/TEXTURE_ID.h"
class IRenderer;
class Piece
{
public:
	Piece(const GSvector2 & _position, PIECE_KIND _kind);
	~Piece();

	void update(float _deltaTime);
	void draw(const IRenderer& _renderer)const;

	void move(const GSvector2& _to);
	void dead(int _priority);
	bool isDead()const;
	void setKind(PIECE_KIND _kind);
	PIECE_KIND kind()const;
	int deadPriority()const;

	void select();
	void unSelect();

	const GSvector2& getPosition()const;
private:
	TEXTURE_ID kindToTexture(PIECE_KIND _kind)const;
private:
	GSvector2 m_position;
	PIECE_KIND m_kind;
	bool m_isDead;
	GScolor m_color;
	//段階的な削除演出に使う　値が小さいほど優先度が高い
	int m_deadPriority;
};