#include "Bord.h"
#include <cmath>
#include <iterator> 
#include "Piece.h"
#include "../renderer/desc/StringRenderDesc.h"
#include "../renderer/IRenderer.h"
#include "../ui/UIManager.h"
const IntVector2 Bord::MAP_SIZE = IntVector2(6, 5);
const float Bord::PIECE_SIZE = 64.0f;
const float Bord::SWITCH_PIECE_DURATION = 5.0f;
const float Bord::Fill_PIECE_DURATION = 30.0f;
const float Bord::DESTROY_SPAN =20.0f;

Bord::Bord()
	:m_bord(MAP_SIZE.x * MAP_SIZE.y),
	m_moveToManager(),
	m_fillMoveDatas()
{
	for (auto x = 0; x < MAP_SIZE.x; x++)
	{
		for (auto y = 0; y < MAP_SIZE.y; y++)
		{
			instantiatePiece(IntVector2(x, y));
		}
	}
}

Bord::~Bord()
{
	m_bord.clear();
}

void Bord::update(float _deltaTime)
{
	m_moveToManager.update(_deltaTime);
	for (const auto& p : m_bord)
	{
		if (p)
		{
			p->update(_deltaTime);
		}
	}
}
void Bord::draw(const IRenderer & _renderer) const
{
	for (const auto& p : m_bord)
	{
		if (p)
		{
			p->draw(_renderer);
		}
	}
}

std::weak_ptr<Piece> Bord::getNearestPiece(const GSvector2 & input)const
{
	auto x = static_cast<int>(std::fminf(input.x / PIECE_SIZE, MAP_SIZE.x - 1));
	auto y = static_cast<int>(std::fminf(input.y / PIECE_SIZE, MAP_SIZE.y - 1));
	return getPiece(IntVector2(x, y));
}

void Bord::resetPosition(PiecePtr _piece)
{
	auto pos = getPieceBoardPos(_piece);
	auto loc = GSvector2(pos.x, pos.y)*PIECE_SIZE;
	_piece->move(loc);
}

void Bord::switchPiece(PiecePtr _p1, PiecePtr _p2)
{
	// 位置を移動する
	std::vector<MoveData> dataList;

	auto p1BoardLoc = getPieceBoardPos(_p1);
	auto p2BoardLoc = getPieceBoardPos(_p2);
	//選択中のpieceはマウスに沿って動くようにしたのでコメントアウト
	//dataList.emplace_back(MoveData(_p1, getPieceWorldPos(p2BoardLoc), SWITCH_PIECE_DURATION));
	dataList.emplace_back(MoveData(_p2, getPieceWorldPos(p1BoardLoc), SWITCH_PIECE_DURATION));
	m_moveToManager.addMoveDatas(dataList);
	// 盤面データを更新する
	setPiece(p1BoardLoc, _p2);
	setPiece(p2BoardLoc, _p1);
}

bool Bord::hasMatch() const
{
	for (auto& piece : m_bord)
	{
		if (isMatchPiece(piece))
		{
			return true;
		}
	}
	return false;
}

void Bord::deleteMatchPiece(std::function<void()> _callback)
{
	int deadPriority = 0;
	for (auto& piece : m_bord)
	{
		if (piece != nullptr)
		{
			if (isMatchPiece(piece))
			{
				auto loc = getPieceBoardPos(piece);
				deadMatchPiece(loc, piece->kind(), deadPriority);
				deadPriority++;
			}
		}
	}

	if (_callback == nullptr)return;
	_callback();
}

void Bord::fillPiece(std::function<void()> _callback)
{
	m_fillMoveDatas.clear();
	m_createLocation.clear();
	for (auto x = MAP_SIZE.x - 1; x >= 0; x--)
	{
		for (auto y = MAP_SIZE.y - 1; y >= 0; y--)
		{
			fillPiece(IntVector2(x, y));
		}
	}

	m_moveToManager.addMoveDatas(m_fillMoveDatas);
	if (_callback == nullptr)return;
	_callback();
}

void Bord::instantiatePiece(const IntVector2 & _location)
{
	GSvector2 pos = GSvector2(_location.x, _location.y)*PIECE_SIZE;
	auto piece = std::make_shared<Piece>(pos, getRandomKind());
	setPiece(_location, piece);
}

void Bord::setPiece(const IntVector2 & _location, PiecePtr _piece)
{
	PiecePtr& piece = m_bord[_location.y*MAP_SIZE.x + _location.x];
	piece.reset();
	piece = _piece;
}

IntVector2 Bord::getPieceBoardPos(PiecePtr _piece) const
{
	for (auto x = 0; x < MAP_SIZE.x; x++)
	{
		for (auto y = 0; y < MAP_SIZE.y; y++)
		{
			auto loc = IntVector2(x, y);
			if (getPiece(loc) == _piece)
			{
				return loc;
			}
		}
	}
	return IntVector2::ZERO;
}

GSvector2 Bord::getPieceWorldPos(const IntVector2 & _location) const
{
	return GSvector2(_location.x* PIECE_SIZE + (MAP_SIZE.x / 2), _location.y* PIECE_SIZE + (MAP_SIZE.y / 2));
}

const Bord::PiecePtr Bord::getPiece(const IntVector2 & _location) const
{
	return m_bord[_location.y*MAP_SIZE.x + _location.x];
}

bool Bord::isInBord(const IntVector2 & _index) const
{
	if (_index.x < 0)return false;
	if (_index.y < 0)return false;
	if (MAP_SIZE.x <= _index.x)return false;
	if (MAP_SIZE.y <= _index.y)return false;
	return true;
}

bool Bord::isMatchPiece(PiecePtr _piece) const
{
	const int MachingCount = 3;

	// ピースの情報を取得
	auto pos = getPieceBoardPos(_piece);
	auto kind = _piece->kind();

	// 縦方向にマッチするかの判定 :自分自身をカウントするため +1 する
	auto verticalMatchCount = getSameKindPieceNum(kind, pos, IntVector2(0, 1)) + getSameKindPieceNum(kind, pos, IntVector2(0, -1)) + 1;

	// 横方向にマッチするかの判定 : 自分自身をカウントするため +1 する
	auto horizontalMatchCount = getSameKindPieceNum(kind, pos, IntVector2(1, 0)) + getSameKindPieceNum(kind, pos, IntVector2(-1, 0)) + 1;

	return verticalMatchCount >= MachingCount || horizontalMatchCount >= MachingCount;
}

int Bord::getSameKindPieceNum(PIECE_KIND _kind, const IntVector2 & _pos, const IntVector2 & _searchDir) const
{
	auto count = 0;
	auto searchPos = _pos;
	while (true)
	{
		searchPos += _searchDir;
		if (!isKindPiece(searchPos, _kind))
		{
			break;
		}
		count++;
	}
	return count;
}

bool Bord::isKindPiece(const IntVector2 & _index, PIECE_KIND _kind) const
{
	if (!isInBord(_index))return false;
	return getPiece(_index)->kind() == _kind;
}

void Bord::fillPiece(const IntVector2 & _location)
{
	auto& piece = getPiece(_location);
	if (piece != nullptr)return;

	//指定ピースより上にpieceがあるか確認
	const auto up = IntVector2(0, -1);
	auto checkPos = _location + up;
	while (isInBord(checkPos))
	{
		auto checkPiece = getPiece(checkPos);
		if (checkPiece != nullptr)
		{
			m_fillMoveDatas.emplace_back(MoveData(checkPiece, getPieceWorldPos(_location), Fill_PIECE_DURATION));
			setPiece(_location, checkPiece);
			setPiece(checkPos, nullptr);
			return;
		}
		checkPos += up;
	}

	// 有効なピースがなければ新しく作る
	createPiece(_location);
}

void Bord::createPiece(const IntVector2 & _location)
{
	const auto up = IntVector2(0, -1);

	// ピースの生成位置を求める
	auto createLoc = IntVector2(_location.x, -1);
	while (std::find_if(m_createLocation.begin(), m_createLocation.end(),
		[&](const IntVector2& _loc) {return _loc.x == createLoc.x&&_loc.y == createLoc.y; }) != m_createLocation.end())
	{
		createLoc += up;
	}

	m_createLocation.emplace_back(createLoc);
	auto pieceCreateWorldPos = getPieceWorldPos(createLoc);

	// ピースを生成

	auto piece = std::make_shared<Piece>(pieceCreateWorldPos, getRandomKind());

	// 盤面にピースの情報をセットする
	setPiece(_location, piece);

	// ピースの位置を求める
	auto piecePos = getPieceWorldPos(_location);

	m_fillMoveDatas.emplace_back(MoveData(piece, piecePos, Fill_PIECE_DURATION));
}

PIECE_KIND Bord::getRandomKind() const
{
	const int SIZE = 5;
	PIECE_KIND table[SIZE] = { PIECE_KIND::RED,PIECE_KIND::BLUE,PIECE_KIND::GREEN,PIECE_KIND::PURPLE, PIECE_KIND::YELLOW };
	auto rnd = rand() % SIZE;
	return table[rnd];
}

void Bord::deadMatchPiece(const IntVector2 & _location, PIECE_KIND _kind, int _deadPriority)
{
	if (!isInBord(_location))return;
	auto& piece = getPiece(_location);
	//存在しているか
	if (piece == nullptr)return;
	//種類が同じか"
	if (piece->kind() != _kind)return;
	//死亡しているか
	if (piece->isDead())return;


	// マッチしているか
	if (!isMatchPiece(piece))return;

	//死亡させる
	piece->dead(_deadPriority);
	//右、左、上、下
	for (const auto& dir : { IntVector2(1,0),IntVector2(-1,0),IntVector2(0,-1),IntVector2(0,1) })
	{
		deadMatchPiece(_location + dir, _kind, _deadPriority);
	}
}

void Bord::destroyPiece(float _deltaTime, UIManager* _ui, std::function<void()> _callback)
{
	m_destroySpan.update(_deltaTime);
	if (m_destroySpan.isStart())return;

	m_destroySpan.start(DESTROY_SPAN, true, [&]()
	{
		if (destroyPiece())
		{
			_ui->addCombo();
			return;
		}
		if (_callback != nullptr)
		{
			_callback();
		}
	});
}

std::vector<Bord::PiecePtr> Bord::highPriorityPieces() const
{
	std::vector<PiecePtr> pieces;
	pieces.clear();

	std::copy_if(m_bord.begin(), m_bord.end(), std::back_inserter(pieces), [](PiecePtr _p)
	{
		if (_p == nullptr)return false;
		return _p->isDead();
	});
	if (pieces.empty())
	{
		return pieces;
	}

	auto min = std::min_element(pieces.begin(), pieces.end(), [](PiecePtr _p1, PiecePtr _p2)
	{
		return _p1->deadPriority() < _p2->deadPriority();
	});
	int min_priority = (*min)->deadPriority();

	auto itr = std::remove_if(pieces.begin(), pieces.end(), [min_priority](PiecePtr _p)
	{
		return _p->deadPriority() != min_priority;
	});
	pieces.erase(itr, pieces.end());
	return pieces;
}

void Bord::samePieceDestroy(const std::vector<PiecePtr>& _pieces)
{
	for (auto& dp : _pieces)
	{
		for (auto& p : m_bord)
		{
			if (p == dp)
			{
				p.reset();
				p = nullptr;
			}
		}
	}
}

bool Bord::destroyPiece()
{
	auto deletePiece = highPriorityPieces();

	samePieceDestroy(deletePiece);
	return !deletePiece.empty();
}
