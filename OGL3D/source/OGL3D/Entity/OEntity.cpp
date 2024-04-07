#include <OGL3D/Entity/OEntity.h>
#include <OGL3D/Game/OGame.h>

OEntity::OEntity()
{
}
OEntity::~OEntity()
{
}

void OEntity::getWorldMatrix(OMat4& world)
{
	world = m_world;
}


//each time position/rotation or scale is set world matrix is recalculated
void OEntity::setPosition(const OVec3& position)
{

	m_position = position;
	processWorldMatrix();
}

void OEntity::setRotation(const OVec3& rotation)
{
	m_rotation = rotation;
	processWorldMatrix();
}

void OEntity::setScale(const OVec3& scale)
{
	m_scale = scale;
	processWorldMatrix();
}

OVec3 OEntity::getPosition()
{
	return m_position;
}

OVec3 OEntity::getRotation()
{
	return m_rotation;
}

OVec3 OEntity::getScale()
{
	return m_scale;
}

void OEntity::release()
{
	m_game->removeEntity(this);
}

void OEntity::processWorldMatrix()
{
	OMat4 temp;

	m_world.setIdentity();

	temp.setIdentity();
	temp.setScale(m_scale);
	m_world *= temp;


	temp.setIdentity();
	temp.setRotationX(m_rotation.x);
	m_world *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rotation.y);
	m_world *= temp;

	temp.setIdentity();
	temp.setRotationZ(m_rotation.z);
	m_world *= temp;


	temp.setIdentity();
	temp.setTranslation(m_position);
	m_world *= temp;
}