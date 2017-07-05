#include "Piece.h"
#include <cassert>
#include "../renderer/IRenderer.h"
#include "../renderer/desc/SpriteRenderDesc.h"
#include "../id/CastID.h"
Piece::Piece(const GSvector2 & _position, PIECE_KIND _kind)
	:m_position(_position),
	m_kind(_kind),
	m_isDead(false),
	m_color(1.0f, 1.0f, 1.0f, 1.0f),
	m_deadPriority(0)
{
}

Piece::~Piece()
{
}

void Piece::update(float _deltaTime)
{
}

void Piece::draw(const IRenderer & _renderer) const
{
	SpriteRenderDesc desc;
	desc.matrix.translate(m_position);
	desc.textureID = CastID::id2uint(kindToTexture(m_kind));
	/*desc.color.a = m_alpha;*/
	desc.color = m_isDead ? GScolor(0.5f, 0.5f, 0.5f, 1.0f) : m_color;
	_renderer.draw(desc);
}

void Piece::move(const GSvector2 & _to)
{
	m_position = _to;
}

void Piece::dead(int _priority)
{
	m_isDead = true;
	m_deadPriority = _priority;
}

bool Piece::isDead() const
{
	return m_isDead;
}

void Piece::setKind(PIECE_KIND _kind)
{
	m_kind = _kind;
}

PIECE_KIND Piece::kind() const
{
	return m_kind;
}

int Piece::deadPriority() const
{
	return m_deadPriority;
}

void Piece::select()
{
	m_color = GScolor(0.5f, 0.5f, 0.5f, 1.0f);
}

void Piece::unSelect()
{
	m_color = GScolor(1.0f, 1.0f, 1.0f, 1.0f);
}

const GSvector2 & Piece::getPosition() const
{
	return m_position;
}

TEXTURE_ID Piece::kindToTexture(PIECE_KIND _kind) const
{
	switch (_kind)
	{
	case PIECE_KIND::RED:
		return TEXTURE_ID::RED;
	case PIECE_KIND::BLUE:
		return TEXTURE_ID::BLUE;
	case PIECE_KIND::GREEN:
		return TEXTURE_ID::GREEN;
	case PIECE_KIND::PURPLE:
		return TEXTURE_ID::PURPLE;
	case PIECE_KIND::YELLOW:
		return TEXTURE_ID::YELLOW;
	}
	return TEXTURE_ID::RED;
}
