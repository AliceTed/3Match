#pragma once
/**
* @file Bord.h
* @brief�@�s�[�X�Ǘ�
* @author �����T��
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
	//!�w��s�[�X�̈ʒu���{�[�h��̈ʒu�ɏC��
	void resetPosition(PiecePtr _piece);
	void switchPiece(PiecePtr _p1, PiecePtr _p2);

	bool hasMatch()const;
	void deleteMatchPiece(std::function<void()> _callback = nullptr);
	//!�s�[�X�������Ă���ꏊ���l�߂āA�V�����s�[�X�𐶐�����
	void  fillPiece(std::function<void()> _callback = nullptr);

	//�D��x���Ŏ��S��Ԃ�piece���폜
	void destroyPiece(float _deltaTime, UIManager* _ui, std::function<void()> _callback = nullptr);
private:
	void instantiatePiece(const IntVector2& _location);
	void setPiece(const IntVector2& _location, PiecePtr _piece);
	//!�s�[�X����{�[�h��̈ʒu�擾
	IntVector2 getPieceBoardPos(PiecePtr _piece)const;
	//!�{�[�h��̈ʒu���烏�[���h���W�擾
	GSvector2 getPieceWorldPos(const IntVector2& _location)const;
	const PiecePtr getPiece(const IntVector2& _location)const;
	bool isInBord(const IntVector2& _index)const;

	//!
	bool isMatchPiece(PiecePtr _piece)const;

	//! �Ώۂ̕����Ɉ����Ŏw�肵���̎�ނ̃s�[�X���������邩��Ԃ�
	int getSameKindPieceNum(PIECE_KIND _kind, const IntVector2& _pos, const IntVector2& _searchDir)const;

	bool isKindPiece(const IntVector2& _index, PIECE_KIND _kind)const;

	//!����̃s�[�X�̂��폜����Ă��邩�𔻒f���A�폜����Ă���Ȃ�l�߂邩�A���ꂪ�ł��Ȃ���ΐV������������
	void fillPiece(const IntVector2& _location);

	void createPiece(const IntVector2& _location);

	PIECE_KIND getRandomKind()const;

	//!�w���piece���}�b�`���Ă���ꍇ�A�ق��̃}�b�`�����s�[�X�ƂƂ��Ɏ��S��Ԃɂ���
	void deadMatchPiece(const IntVector2& _location, PIECE_KIND _kind,int _deadPriority);
	
	//�D��x�̍������̂�z��Ŏ擾
	std::vector<PiecePtr> highPriorityPieces()const;
	//�d�����Ă���s�[�X���폜
	void samePieceDestroy(const std::vector<PiecePtr>& _pieces);
	//!���span�ŌĂ΂��폜���� �폜����s�[�X���Ȃ��Ȃ����� false���Ԃ��Ă���
	bool destroyPiece();
private:
	Conatiner m_bord;
	MoveToManager m_moveToManager;
	//!�����߂���s�[�X�̈ړ����i�[
	std::vector<MoveData> m_fillMoveDatas;
	//!�V������������s�[�X�̈ʒu���i�[
	std::vector<IntVector2> m_createLocation;

	Timer m_destroySpan;

	static const IntVector2 MAP_SIZE;
	static const float SWITCH_PIECE_DURATION;
	static const float Fill_PIECE_DURATION;
	static const float DESTROY_SPAN;

public:
	//Play�Ŏg������
	static const float PIECE_SIZE;
};
