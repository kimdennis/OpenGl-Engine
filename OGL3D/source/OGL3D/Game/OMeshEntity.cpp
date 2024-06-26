#include <OGL3D/Game/OMeshEntity.h>

OMeshEntity::OMeshEntity()
{
}

OMeshEntity::~OMeshEntity()
{
}

void OMeshEntity::setMesh(const OMeshPtr& mesh)
{
    m_mesh = mesh;
}

OMeshPtr OMeshEntity::getMesh()
{
    return m_mesh;
}

void OMeshEntity::setTexture(const OTexturePtr& texture)
{
    m_texture = texture;
}

OTexturePtr OMeshEntity::getTexture()
{
    return m_texture;
}