#pragma once
/**
* @file Renderer.h
* @brief �����_���[
* @author �����T��
* @date 2016/3/2
*/

#include "IRenderer.h"
#include "command\IRenderCommand.h"

class Renderer:public IRenderer
{
public:
	Renderer();
	//��ʏ���
	virtual void clear(const GScolor& _color)const override;
	//�J����
	virtual void lookAt(const LookAtDesc& _desc)const override;
	//�`��(�R�}���h�̒ǉ�)
	virtual void draw(const MeshRenderDesc& _desc)const override;
	//�X�v���C�g�`��
	virtual void draw(const SpriteRenderDesc& _desc)const override;
	//������`��
	virtual void draw(const StringRenderDesc& _desc)const override;
	//�X�J�C�{�b�N�X�`��
	virtual void draw(const SkyBoxRenderDesc & _desc)const  override;
private:
	template<class Command,class Desc>
	void drawTemplate(const Desc& _desc)const
	{
		Command command(_desc);
		command.render();
	}
private:

};