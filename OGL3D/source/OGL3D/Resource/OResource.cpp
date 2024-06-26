#include <OGL3D/Resource/OResource.h>

OResource::OResource(const wchar_t* path, OResourceManager* manager):m_path(path)
{
}

OResource::~OResource()
{
}

std::wstring OResource::getPath()
{
	return m_path;
}
