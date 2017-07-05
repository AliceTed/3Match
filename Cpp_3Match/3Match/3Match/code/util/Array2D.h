#pragma once
/**
* @file Array2D.h
* @brief 配列を2次元配列として扱う
* @author 松尾裕也
* @date 2016/1/19
*/

#include <cassert>
#include <memory>
#include <functional>
#include "Uncopyable.h"
template<class T>
class Array2D:public Uncopyable
{
public:
	Array2D(unsigned int _size0, unsigned int _size1);
	Array2D(Array2D&&) = default;
	void clear();
	/*0=w,1=h*/
	void setSize(unsigned int _size0, unsigned int _size1);
	/*0=w,1=h*/
	T& operator()(unsigned int _index0,unsigned int _index1) 
	{
		assert(isInSide(_index0,_index1));
		return m_array.get()[_index1 * m_size0 + _index0];
	}
	/*0=w,1=h*/
	const T& operator()(unsigned int _index0, unsigned int _index1) const {
		assert(isInSide(_index0, _index1));
		return m_array.get()[_index1 * m_size0 + _index0];
	}

	void foreach(std::function<void(T&)> _func)
	{
		for (unsigned int i = 0;i < m_size0;i++)
		{
			for (unsigned int n = 0;n < m_size1;n++)
			{
				_func((*this)(i,n));
			}
		}
	}
	/**
	* @fn
	* @brief 配列が所有権を保持しているか
	* @return true 保持している false 保持していない
	*/
	bool isHold()const;
	bool isInSide(unsigned int _index0, unsigned int _index1)const;
	unsigned int getSize0()const;
	unsigned int getSize1()const;
private:
	using ArrayPtr=std::unique_ptr<T>;
	ArrayPtr m_array;

	unsigned int m_size0;
	unsigned int m_size1;
};

template<class T>
Array2D<T>::Array2D(unsigned int _size0,unsigned int _size1)
	:m_array(nullptr),
	m_size0(0),
	m_size1(0)
{
	setSize(_size0,_size1);
}

template<class T>
void Array2D<T>::clear()
{
	m_array.reset();
	m_array = nullptr;
}

template<class T>
void Array2D<T>::setSize(unsigned int _size0, unsigned int _size1)
{
	clear();
	m_size0 = _size0;
	m_size1 = _size1;
	m_array =ArrayPtr(new T[m_size0 * m_size1]);
}

template<class T>
 bool Array2D<T>::isHold() const
 {
	 return m_array;
 }


template<class T>
 bool Array2D<T>::isInSide(unsigned int index0, unsigned int index1) const
 {
	 if (index1 < 0)return false;
	 if (index0 < 0)return false;
	 if (m_size0 <=index0)return false;
	 if (m_size1 <=index1)return false;
	 return true;
 }

 template<class T>
 unsigned int Array2D<T>::getSize0() const
 {
	 return m_size0;
 }

 template<class T>
 unsigned int Array2D<T>::getSize1() const
 {
	 return m_size1;
 }
