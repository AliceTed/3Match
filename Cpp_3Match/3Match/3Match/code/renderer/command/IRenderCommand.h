#pragma once

/**
* @file IRenderCommand.h
* @brief 描画コマンド用インターフェイス
* @author 松尾裕也
* @date 2016/3/2
*/
class IRenderCommand
{
public:
	virtual ~IRenderCommand() {}
	/*
	描画命令
	*/
	virtual void render()=0;
};