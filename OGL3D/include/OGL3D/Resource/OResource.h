#pragma once
#include <map>
#include <string>
#include <OGL3D/OPrerequisites.h>

class OResourceManager;
class OResource
{
public:
	OResource(const wchar_t* path,OResourceManager* manager);
	virtual ~OResource();

	std::wstring getPath();
protected:
	std::wstring m_path;

};