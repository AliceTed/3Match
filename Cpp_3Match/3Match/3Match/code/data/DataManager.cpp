#include "DataManager.h"
#include "define\TextureLoadDesc.h"
#include "define\MeshLoadDesc.h"
#include "define\ShaderLoadDesc.h"
#include "../util/Message.h"

void DataManager::load(const TextureLoadDesc & _desc)
{
	load(_desc, gsLoadTexture, "テクスチャの読み込みエラー");
	
	//CriticalSection::Lock guard(m_lock);
	//std::string name = _desc.m_path + _desc.m_name + _desc.m_extension;
	//if (gsLoadTexture(CastID::id2uint(_desc.m_id), name.c_str()) == GS_TRUE)return;
	//Message::send("テクスチャの読み込みエラー",name);
}

void DataManager::load(const MeshLoadDesc & _desc)
{
	auto loader = _desc.m_isShader ? gsLoadMeshEx : gsLoadMesh;
	load(_desc, loader, "メッシュの読み込みエラー");
}

void DataManager::load(const ShaderLoadDesc & _desc)
{
	std::string nameV =_desc.getNameV();
	std::string nameF = _desc.getNameF();

	if (gsLoadShader(CastID::id2uint(_desc.m_id), nameV.c_str(),nameF.c_str()) == GS_TRUE)return;
	Message::send("シェーダの読み込みエラー", nameV+":"+nameF);
}

void DataManager::release()
{
	//全てのリソース解放
	gsFinishGraphics();
	/*eachRelease(gsDeleteTexture,TEXTURE_ID::SIZE);
	eachRelease(gsDeleteMesh, MESH_ID::SIZE);*/
}
