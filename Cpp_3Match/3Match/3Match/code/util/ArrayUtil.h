#pragma once
/**
* @file ArrayUtil.h
* @brief 配列用ユーティリティー
* @author 松尾裕也
* @date 2016/2/15
*/
#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>
class ArrayUtil
{
public:
	ArrayUtil()=default;
	~ArrayUtil()=default;
	/**
	* @fn
	* @brief 指定要素より前の要素を後ろに連結する
	* @param (_out) sortする配列
	* @param (_element) 指定要素
	*/
	template<class T>
	static void sort(std::vector<T>& _out, const T& _element);

private:

};

template<class T>
void ArrayUtil::sort(std::vector<T>& _out, const T & _element)
{
	auto itr = std::find_if(_out.begin(), _out.end(), [_element](const T& _ele) {return _element == _ele;});
	assert(itr != _out.end());
	std::vector<T> tmp;
	std::move(_out.begin(), itr, std::back_inserter(tmp));
	_out.erase(_out.begin(), itr);
	std::move(tmp.begin(), tmp.end(), std::back_inserter(_out));
}
