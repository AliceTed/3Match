#include "Renderer.h"

#include "command\MeshRenderCommand.h"
#include "command\LookAtCommand.h"
#include "command\ClearCommand.h"
#include "command\SpriteRenderCommand.h"
#include "command\StringRenderCommand.h"
#include "command\SkyBoxRenderCommand.h"
Renderer::Renderer()
{
}

void Renderer::clear(const GScolor & _color)const
{
	drawTemplate<ClearCommand>(_color);
}

void Renderer::lookAt(const LookAtDesc & _desc)const
{
	drawTemplate<LookAtCommand>(_desc);
}

void Renderer::draw(const MeshRenderDesc & _desc)const
{
	drawTemplate<MeshRenderCommand>(_desc);
}

void Renderer::draw(const SpriteRenderDesc & _desc)const
{
	drawTemplate<SpriteRenderCommand>(_desc);
}

void Renderer::draw(const StringRenderDesc & _desc)const
{
	drawTemplate<StringRenderCommand>(_desc);
}
void Renderer::draw(const SkyBoxRenderDesc & _desc)const
{
	drawTemplate<SkyBoxRenderCommand>(_desc);
}