#pragma once

/**
* @file DataManager.h
* @brief データ管理用クラス
* @author 松尾裕也
* @date 2016/2/15
*/
#include<gslib.h>
#include <string>
#include "../id/CastID.h"
struct TextureLoadDesc;
struct MeshLoadDesc;
struct ShaderLoadDesc;
class DataManager
{
public:
	DataManager()=default;
	~DataManager()=default;
	static void load(const TextureLoadDesc& _desc);
	static void load(const MeshLoadDesc& _desc);
	static void load(const ShaderLoadDesc& _desc);
	static void release();
private:
	template<class Desc,class Loader>
	static void load(const Desc& _desc, Loader _loader, const std::string& _errMes)
	{
		std::string name = _desc.getName();
		if (_loader(CastID::id2uint(_desc.m_id), name.c_str()) == GS_TRUE)return;
		Message::send(_errMes, name);
	}

	/**
	* @fn
	* @brief 指定関数でデータを開放
	* @param (_func) 指定関数
	* @param (_size) 開放するデータのサイズ
	*/
	template<class Func,class DataEnum> 
	static void eachRelease(Func _func, DataEnum _size);
private:
	//CriticalSection m_lock;
};

template<class Func, class DataEnum>
void DataManager::eachRelease(Func _func, DataEnum _size)
{
	for (auto i = 0U; i < CastID::id2uint(_size); i++)
	{
		_func(i);
	}
}
