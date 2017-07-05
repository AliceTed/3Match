#pragma once
/**
* @file CastID.h
* @brief �eID�̕ϊ�
* @author �����T��
* @date 2016/2/8
*/
#include <GScolor.h>
class CastID
{
public:
	CastID()=default;
	~CastID()=default;

	/*�X�^�e�B�b�N�L���X�g*/
	template<class ID>
	static unsigned int id2uint(ID _id);
};

template<class ID>
unsigned int CastID::id2uint(ID _id)
{
	return static_cast<unsigned int>(_id);
}
