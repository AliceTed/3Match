#include "LookAtCommand.h"

LookAtCommand::LookAtCommand(const LookAtDesc & _desc)
	:m_desc(_desc)
{
}

void LookAtCommand::render()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt
	(
		m_desc.eye.x, m_desc.eye.y, m_desc.eye.z,
		m_desc.at.x, m_desc.at.y, m_desc.at.z,
		m_desc.up.x, m_desc.up.y, m_desc.up.z
	);
}
