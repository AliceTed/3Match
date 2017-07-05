#include "SpriteRenderCommand.h"
#include "../RendererUtil.h"
SpriteRenderCommand::SpriteRenderCommand(const SpriteRenderDesc & _desc)
	:m_desc(_desc)
{
}

void SpriteRenderCommand::render()
{
	// 各種レンダリングモードの退避
	glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// 面カリングを無効にする
	glDisable(GL_CULL_FACE);
	// ライティングを無効にする
	glDisable(GL_LIGHTING);
	// ｚバッファを無効にする
	glDisable(GL_DEPTH_TEST);

	// ブレンド方法の設定
	RendererUtil::setBlendFunc(m_desc.blendFunc);

	GScolor currentColor;
	// カレントカラーを取得する
	glGetFloatv(GL_CURRENT_COLOR, (float*)&currentColor);

	// 透視変換行列の退避
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	// ビューポートの取得
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	// 正射影の変換行列を設定
	glLoadIdentity();
	gluOrtho2D(0.0f, (float)viewport[2], (float)viewport[3], 0.0f);

	// モデルビュー変換行列の退避
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	// 変換行列の初期化
	glLoadIdentity();

	glMultMatrixf(m_desc.matrix);
	glTranslatef(-m_desc.center.x, -m_desc.center.y, 0);

	if (m_desc.isClip)
	{
		float width = m_desc.rect.right - m_desc.rect.left;
		float height = m_desc.rect.bottom - m_desc.rect.top;
		GSrect rect(0, 0, width, height);
		RendererUtil::drawTexture(m_desc.textureID,rect,m_desc.rect,m_desc.color);
	}
	else
	{
		RendererUtil::drawTexture(m_desc.textureID, m_desc.color);
	}	

	// モデルビュー変換行列を復帰
	glPopMatrix();
	// 透視変換行列を復帰
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	// モデルビュー変換行列に設定
	glMatrixMode(GL_MODELVIEW);
	// カレントカラーを復帰する
	glColor4fv((float*)&currentColor);
	// レンダリングステートの復帰
	glPopAttrib();
}
