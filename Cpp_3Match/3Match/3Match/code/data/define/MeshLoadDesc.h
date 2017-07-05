#pragma once
/**
* @file MeshLoadDesc.h
* @brief メッシュのロード用構造体
* @author 松尾裕也
* @date 2016/2/15
*/
#include<string>
#include "../../id/MESH_ID.h"
struct MeshLoadDesc
{
	MeshLoadDesc(MESH_ID _id, const std::string& _name,bool _isShader=false)
		:m_id(_id),
		m_name(_name),
		m_path("./asset/mesh/"),
		m_extension(".msh"),
		m_isShader(_isShader)
	{}
	//連結
	std::string getName()const
	{
		return m_path + m_name + m_extension;
	}

	MESH_ID m_id;
	std::string m_name;
	std::string m_path;
	std::string m_extension;
	bool m_isShader;
};