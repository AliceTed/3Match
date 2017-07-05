#include "StringRenderCommand.h"

StringRenderCommand::StringRenderCommand(const StringRenderDesc & _desc)
	:m_desc(_desc)
{
}

void StringRenderCommand::render()
{
	GScolor currentColor;
	// カレントカラーを取得する
	glGetFloatv(GL_CURRENT_COLOR, (float*)&currentColor);

	//文字色の設定
	glColor4fv((GLfloat*)&m_desc.color);

	//文字フォントの設定
	gsFontParameter(
		m_desc.font.code,
		m_desc.font.size,
		m_desc.font.name.c_str());

	//表示位置の設定
	gsTextPos(m_desc.position.x, m_desc.position.y);

	//文字列の描画
	gsDrawText(m_desc.string.c_str());

	// カレントカラーを復帰する
	glColor4fv((float*)&currentColor);
}
