#pragma once
#include <OGL3D/Game/OEntity.h>
#include <OGL3D/Math/OMat4.h>
#include <OGL3D/Math/ORect.h>

//the OCamera class is the entity class that allows to add a camera in the scene 
class OCamera : public OEntity
{
public:

	void getViewMatrix(OMat4& view);
	void getProjectionMatrix(OMat4& proj);

	void setFarPlane(f32 farPlane);
	void setNearPlane(f32 nearPlane);
	void setFieldOfView(f32 fov);
	void setCameraType(const OCameraType& type);
	void setScreenArea(const ORect& screen);
private:
	void computeProjectionMatrix();
private:
	OMat4 m_view;
	OMat4 m_projection;

	f32 m_farPlane = 100.0f;
	f32 m_nearPlane = 0.001f;
	f32 m_fov = 1.3f;
	OCameraType m_type = OCameraType::Perspective;
	ORect m_screenArea;
};
