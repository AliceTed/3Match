#pragma once
/**
* @file StringRenderCommand.h
* @brief •¶š—ñ•`‰æƒRƒ}ƒ“ƒh
* @author ¼”ö—T–ç
* @date 2016/3/3
*/
#include "IRenderCommand.h"
#include "../desc/StringRenderDesc.h"
class StringRenderCommand:public IRenderCommand
{
public:
	StringRenderCommand(const StringRenderDesc& _desc);
	virtual void render() override;
private:
	StringRenderDesc m_desc;
};
