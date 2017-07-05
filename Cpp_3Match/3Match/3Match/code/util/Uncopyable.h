#pragma once
/**
* @file Uncopyable.h
* @brief コピー禁止用親クラス
* @author 松尾裕也
* @date 2016/1/19
*/
class Uncopyable
{
public:
	Uncopyable() {}
	~Uncopyable() {}
private:
	Uncopyable(const Uncopyable&) = delete;
	Uncopyable& operator=(const Uncopyable&) = delete;
};
