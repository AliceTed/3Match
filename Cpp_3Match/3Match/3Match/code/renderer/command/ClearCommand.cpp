#include "ClearCommand.h"

ClearCommand::ClearCommand(const GScolor & _color)
	:m_color(_color)
{
}

void ClearCommand::render()
{
	glClearColor(m_color.r, m_color.g, m_color.b, m_color.a);
	glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
}
