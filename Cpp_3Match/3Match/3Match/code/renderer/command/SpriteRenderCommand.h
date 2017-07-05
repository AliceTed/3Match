#pragma once
/**
* @file SpriteRenderCommand.h
* @brief スプライト描画コマンド
* @author 松尾裕也
* @date 2016/3/3
*/
#include "IRenderCommand.h"
#include "../desc/SpriteRenderDesc.h"
class SpriteRenderCommand:public IRenderCommand
{
public:
	SpriteRenderCommand(const SpriteRenderDesc& _desc);
	
	virtual void render() override;
private:
	SpriteRenderDesc m_desc;
};