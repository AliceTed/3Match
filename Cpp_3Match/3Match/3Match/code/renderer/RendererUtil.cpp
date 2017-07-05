#include "RendererUtil.h"

void RendererUtil::drawQuad(const GSrect & _rect, const GSrect & _texCoord, const GScolor & _color)
{
	glBegin(GL_QUADS);
	glColor4fv((GLfloat*)&_color);
	glTexCoord2f(_texCoord.left, _texCoord.top);
	glVertex2f(_rect.left, _rect.top);
	glTexCoord2f(_texCoord.left, _texCoord.bottom);
	glVertex2f(_rect.left, _rect.bottom);
	glTexCoord2f(_texCoord.right, _texCoord.bottom);
	glVertex2f(_rect.right, _rect.bottom);
	glTexCoord2f(_texCoord.right, _texCoord.top);
	glVertex2f(_rect.right, _rect.top);
	glEnd();
}

void RendererUtil::drawTexture(unsigned int _id, const GScolor & _color)
{	
	// テクスチャをバインドする
	gsBindTexture(_id);	
	GSvector2 size=getTextureSize();

	GSrect rect(0, 0, size.x, size.y);
	GSrect texCoord(0.0f, 0.0f, 1.0f, 1.0f);

	drawQuad(rect,texCoord,_color);

	// テクスチャを無効にする
	glBindTexture(GL_TEXTURE_2D, 0);
}

void RendererUtil::drawTexture(unsigned int _id, const GSrect & rect, const GSrect & srcRect, const GScolor & _color)
{
	// テクスチャをバインドする
	gsBindTexture(_id);

	GSvector2 size = getTextureSize();

	// テクスチャ座標の計算を行う
	GSrect texCoord(
		srcRect.left / size.x,
		srcRect.top / size.y,
		srcRect.right / size.x,
		srcRect.bottom / size.y);

	drawQuad(rect,texCoord,_color);

	// テクスチャを無効にする
	glBindTexture(GL_TEXTURE_2D, 0);
}

GSvector2 RendererUtil::getTextureSize()
{
	GLsizei texWidth;
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &texWidth);
	GLsizei	texHeight;
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &texHeight);
	return GSvector2(texWidth, texHeight);
}

void RendererUtil::setBlendFunc(BlendFunc _func)
{//ブレンドを有効に
	glEnable(GL_BLEND);

	switch (_func)
	{
	case BlendFunc::NONE://ブレンドなし
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
		break;
	case BlendFunc::DEFAULT://デフォルト
		glDepthMask(GL_TRUE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		break;
	case BlendFunc::ALPHA://アルファ値による半透明
		glDepthMask(GL_FALSE);
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
		break;
	case BlendFunc::ADD://加算による半透明
		glDepthMask(GL_FALSE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		break;
	case BlendFunc::SUB://減算による半透明
		glDepthMask(GL_FALSE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		break;
	default:
		break;
	}
}
