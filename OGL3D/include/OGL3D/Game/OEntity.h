#pragma once
#include <OGL3D/OPrerequisites.h>
#include <OGL3D/Math/OVec3.h>
#include <OGL3D/Math/OMat4.h>


class OGame;
//the entity class is the main class of the entitysystem
//it handles the trasnform of all the entities through the world matrix
class OEntity
{
public:
	OEntity();
	virtual ~OEntity();

public:
	void getWorldMatrix(OMat4& world);
	void setPosition(const OVec3& position);
	void setRotation(const OVec3& rotation);
	void setScale(const OVec3& scale);

	OVec3 getPosition();
	OVec3 getRotation();
	OVec3 getScale();

	virtual void onCreate() {}
	virtual void onUpdate(f32 deltaTime) {}
	virtual void release();
protected:
	void processWorldMatrix();
protected:
	OMat4 m_world;

	OVec3 m_position;
	OVec3 m_rotation;
	OVec3 m_scale = OVec3(1, 1, 1);

	OGame* m_game = nullptr;

	friend class OGame;
};