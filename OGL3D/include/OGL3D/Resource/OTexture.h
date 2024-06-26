#pragma once
#include <map>
#include <string>
#include <OGL3D/OPrerequisites.h>
#include <OGL3D/Resource/OResource.h>

class OTexture : public OResource
{
public:
	OTexture(const wchar_t* path, OResourceManager* manager);
	virtual ~OTexture();

	OTexture2DPtr getTexture2D();

private:
	OTexture2DPtr m_texture2D;
};