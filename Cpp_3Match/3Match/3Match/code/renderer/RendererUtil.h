#pragma once
/**
* @file RendererUtil.h
* @brief レンダラーユーティリティー
* @author 松尾裕也
* @date 2016/3/3
*/
#include <gslib.h>
#include "BlendFunc.h"
class RendererUtil
{
public:
	RendererUtil()=default;
	~RendererUtil()=default;
	static void setBlendFunc(BlendFunc _func);
	static void drawQuad(const GSrect& _rect,const GSrect& _texCoord,const GScolor& _color);
	static void drawTexture(unsigned int _id, const GScolor& _color);
	static void drawTexture(unsigned int _id, const GSrect& rect, const GSrect& srcRect, const GScolor& _color);
private:
	//バインド中のテクスチャのサイズ(幅、高さ)を取得
	static GSvector2 getTextureSize();
};