#pragma once
#include <OGL3D/Entity/OEntity.h>
#include <OGL3D/Math/OMat4.h>
#include <OGL3D/Math/ORect.h>

//the OCamera class is the entity class that allows to add a camera in the scene 
class OCamera : public OEntity
{
public:

	void getViewMatrix(OMat4& view);
	void getProjectionMatrix(OMat4& proj);

	void setFarPlane(f32 farPlane);
	void setScreenArea(const ORect& screen);

private:
	OMat4 m_view;
	OMat4 m_projection;

	f32 m_farPlane = 100.0f;
	ORect m_screenArea;
};