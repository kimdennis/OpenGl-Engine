#include <OGL3D/Camera/OCamera.h>


void OCamera::getViewMatrix(OMat4& view)
{
	//invert the world matrix in order to get the view matrix
	m_view = m_world;
	m_view.inverse();
	view = m_view;
}

void OCamera::getProjectionMatrix(OMat4& proj)
{
	proj = m_projection;
}


//changes the projection each time we set the farplane and the screenarea
void OCamera::setFarPlane(f32 farPlane)
{
	m_farPlane = farPlane;

	m_projection.setOrthoLH((f32)m_screenArea.width * 0.013f, (f32)m_screenArea.height * 0.013f, 0.1f, m_farPlane);
}

void OCamera::setScreenArea(const ORect& screen)
{
	m_screenArea = screen;
	m_projection.setOrthoLH((f32)m_screenArea.width * 0.013f, (f32)m_screenArea.height * 0.013f, 0.1f, m_farPlane);
}