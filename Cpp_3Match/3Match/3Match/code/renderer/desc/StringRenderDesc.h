#pragma once
/**
* @file StringRenderDesc.h
* @brief 文字列描画記述子
* @author 松尾裕也
* @date 2016/3/3
*/
#include <string>
#include <gslib.h>
//フォントの指定
struct  Font
{
	//修飾コード
	static const unsigned int CODE_NOMAL = 0; //指定なし
	static const unsigned int CODE_BOLD = (1 << 0);  //強調
	static const unsigned int CODE_ITALIC = (1 << 1);//イタリック
	static const unsigned int CODE_UNDERLINE = (1 << 2);//アンダーライン
	static const unsigned int CODE_STRIKEOUT = (1 << 3);//取り消し線

	Font() :
		code(CODE_NOMAL),
		size(16),
		name("ＭＳ ゴシック")
	{}
	//修飾コード
	int code;
	int size;
	//フォント名
	std::string name;
};

struct StringRenderDesc
{
	StringRenderDesc() :
		font(),
		string(""),
		position(0, 0),
		color(1, 1, 1, 1)
	{}
	//フォント
	Font font; 
	//文字列
	std::string string;
	GSvector2 position;
	GScolor color;
};