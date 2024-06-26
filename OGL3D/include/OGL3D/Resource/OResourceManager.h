#pragma once
#include <map>
#include <string>
#include <OGL3D/OPrerequisites.h>

class OGame;
class OResourceManager
{
public:
	OResourceManager(OGame* game);
	virtual ~OResourceManager();

	OResourcePtr createResourceFromFile(const wchar_t* path);

	OGame* getGame();
protected:
	std::map<std::wstring, OResourcePtr> m_mapResources;
	OGame* m_game = nullptr;
};