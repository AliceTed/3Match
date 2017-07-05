#pragma once
/**
* @file IRenderer.h
* @brief レンダラー用インターフェイス
* @author 松尾裕也
* @date 2016/3/3
*/
#include <gslib.h>
struct MeshRenderDesc;
struct SpriteRenderDesc;
struct LookAtDesc;
struct StringRenderDesc;
struct SkyBoxRenderDesc;
class IRenderer
{
public:
	virtual ~IRenderer() {}
	
	virtual void clear(const GScolor& _color) const= 0;
	//カメラ
	virtual void lookAt(const LookAtDesc& _desc) const = 0;
	//描画(コマンドの追加)
	virtual void draw(const MeshRenderDesc& _desc)const = 0;
	//スプライト描画
	virtual void draw(const SpriteRenderDesc& _desc) const = 0;
	//文字列描画
	virtual void draw(const StringRenderDesc& _desc) const = 0;
	//スカイボックス描画
	virtual void draw(const SkyBoxRenderDesc& _desc)const = 0;
};