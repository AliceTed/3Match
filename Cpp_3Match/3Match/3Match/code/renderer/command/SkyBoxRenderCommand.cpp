#include "SkyBoxRenderCommand.h"
#include <gslib.h>
#include "../../id/CastID.h"
#include "../../id/SHADER_ID.h"
SkyBoxRenderCommand::SkyBoxRenderCommand(const SkyBoxRenderDesc & _desc)
	:m_desc(_desc)
{
}

void SkyBoxRenderCommand::render()
{
	// 各種レンダリングモードの退避
	glPushAttrib(GL_ENABLE_BIT);
	// 視野変換行列を退避する
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glRotatef(m_desc.time*0.1f,0,1,0);
	gsDrawSkyBox(m_desc.meshID);
	//uvがおかしい
	//gsBeginShader(CastID::id2uint(SHADER_ID::SKYBOX));
	////gsDrawSkyBoxEx内でバインドしている
	//gsSetShaderParamTexture("u_baseMap",0);
	////時間経過でuvスクロールの
	//gsSetShaderParam1f("u_time",m_desc.time);
	//gsDrawSkyBoxEx(m_desc.meshID);
	//gsEndShader();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glPopAttrib();
}
