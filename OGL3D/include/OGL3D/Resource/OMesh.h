#pragma once
#include <map>
#include <string>
#include <OGL3D/OPrerequisites.h>
#include <OGL3D/Resource/OResource.h>


class OMesh : public OResource
{
public:
	OMesh(const wchar_t* path, OResourceManager* manager);
	virtual ~OMesh();

	OVertexArrayObjectPtr getVertexArrayObject();

private:
	OVertexArrayObjectPtr m_vao;
};