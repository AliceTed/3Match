#include "MeshRenderCommand.h"

MeshRenderCommand::MeshRenderCommand(const MeshRenderDesc & _desc)
	:m_desc(_desc)
{
}

void MeshRenderCommand::render()
{
	//各種レンダリングモード退避
	glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//カラーの設定
	glColor4fv((GLfloat*)&m_desc.color);

	//透視変換行列の設定
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadName(GL_PROJECTION_MATRIX);

	//視野変換行列の設定
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadName(GL_MODELVIEW_MATRIX);

	//メッシュ描画
	glMultMatrixf((GLfloat*)&m_desc.matrix);
	gsDrawMesh(m_desc.meshID);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	//視野変換行列の設定
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	//レンダリングモード復帰
	glPopAttrib();
}
