#pragma once
#include <OGL3D/Game/OEntity.h>
#include <OGL3D/Math/OMat4.h>
#include <OGL3D/Math/ORect.h>

class OGame;

//the OGraphicsEntity class is the enity class of the entitysystem made specifically for graphcis objects
class OGraphicsEntity : public OEntity
{
public:
	OGraphicsEntity();
	virtual ~OGraphicsEntity();

protected:
	virtual void onGraphicsUpdate(f32 deltaTime) {}
	friend class OGame;
};