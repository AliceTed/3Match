#pragma once
/**
* @file Renderer.h
* @brief レンダラー
* @author 松尾裕也
* @date 2016/3/2
*/

#include "IRenderer.h"
#include "command\IRenderCommand.h"

class Renderer:public IRenderer
{
public:
	Renderer();
	//画面消去
	virtual void clear(const GScolor& _color)const override;
	//カメラ
	virtual void lookAt(const LookAtDesc& _desc)const override;
	//描画(コマンドの追加)
	virtual void draw(const MeshRenderDesc& _desc)const override;
	//スプライト描画
	virtual void draw(const SpriteRenderDesc& _desc)const override;
	//文字列描画
	virtual void draw(const StringRenderDesc& _desc)const override;
	//スカイボックス描画
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