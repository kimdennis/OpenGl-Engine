#pragma once
#include <OGL3D/OPrerequisites.h>
#include <OGL3D/Game/OEntity.h>

class OMeshEntity : public OEntity
{
public:
	OMeshEntity();
	virtual ~OMeshEntity();
public:
	void setMesh(const OMeshPtr& mesh);
	OMeshPtr getMesh();

	virtual void setTexture(const OTexturePtr& texture);
	OTexturePtr getTexture();
private:
	OMeshPtr m_mesh;
	OTexturePtr m_texture;

	friend class  OGame;
};