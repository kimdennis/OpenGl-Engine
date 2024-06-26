#include <OGL3D/Resource/OResourceManager.h>
#include <OGL3D/Resource/OTexture.h>
#include <filesystem>


OResourceManager::OResourceManager(OGame* game):m_game(game)
{
}

OResourceManager::~OResourceManager()
{
}

OResourcePtr OResourceManager::createResourceFromFile(const wchar_t* path)
{
	//check if the texture we want to load has been already loaded.
	auto it = m_mapResources.find(path);

	if (it != m_mapResources.end())
	{
		return it->second;
	}

	//the texture has not been loaded yet. Let's load it.
	std::filesystem::path resPath = path;
	if (!std::filesystem::exists(resPath)) return OResourcePtr(); // check if the file exists
	
	auto ext = resPath.extension();

	// if the resource we want to load has one of these extensions
	if (ext.compare(L".jpg") || ext.compare(L".png") || ext.compare(L".bmp") || ext.compare(L".tga")) 	
	{
		//let's create a texture resource
		auto texturePtr = std::make_shared<OTexture>(resPath.c_str(),this);
		if (texturePtr)
		{
			m_mapResources.emplace(path, texturePtr);
			return texturePtr;
		}
	}

	return OResourcePtr();
}

OGame* OResourceManager::getGame()
{
	return m_game;
}
