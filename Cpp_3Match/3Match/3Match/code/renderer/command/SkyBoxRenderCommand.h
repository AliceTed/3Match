#pragma once
/**
* @file SkyBoxRenderCommand.h
* @brief スカイボックス描画コマンド(shader)
* @author 松尾裕也
* @date 2016/3/5
*/
#include "IRenderCommand.h"
#include "../desc/SkyBoxRenderDesc.h"
class SkyBoxRenderCommand:public IRenderCommand
{
public:
	SkyBoxRenderCommand(const SkyBoxRenderDesc& _desc);
	virtual void render() override;
private:
	SkyBoxRenderDesc m_desc;
};
