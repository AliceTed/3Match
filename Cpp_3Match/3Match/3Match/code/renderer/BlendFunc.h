#pragma once
/**
* @file BlendFunc.h
* @brief ブレンド用enum
* @author 松尾裕也
* @date 2016/3/3
*/
enum class BlendFunc:unsigned int
{
	NONE,    //なし
	DEFAULT, //デフォルト
	ALPHA,   //アルファ値による半透明
	ADD,     //加算による半透明
	SUB     //減算による半透明
};