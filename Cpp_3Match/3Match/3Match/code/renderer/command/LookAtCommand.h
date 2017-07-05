#pragma once
/**
* @file LookAtCommand.h
* @brief LookAtƒRƒ}ƒ“ƒh
* @author ¼”ö—T–ç
* @date 2016/3/2
*/
#include "IRenderCommand.h"
#include "../desc/LookAtDesc.h"
class LookAtCommand:public IRenderCommand
{
public:
	LookAtCommand(const LookAtDesc& _desc);
	virtual void render() override;
private:
	LookAtDesc m_desc;
};