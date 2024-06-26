#include <OGL3D/Game/OCamera.h>


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


//let's chnage the projection each time we set the farplane and the screenarea
void OCamera::setFarPlane(f32 farPlane)
{
	m_farPlane = farPlane;
	computeProjectionMatrix();
}

void OCamera::setNearPlane(f32 nearPlane)
{
	m_nearPlane = nearPlane;
	computeProjectionMatrix();
}

void OCamera::setFieldOfView(f32 fov)
{
	m_fov = fov;
	computeProjectionMatrix();
}

void OCamera::setCameraType(const OCameraType& type)
{
	m_type = type;
	computeProjectionMatrix();
}

void OCamera::setScreenArea(const ORect& screen)
{
	m_screenArea = screen;
	computeProjectionMatrix();
}

void OCamera::computeProjectionMatrix()
{
	if (m_type == OCameraType::Perspective)
		m_projection.setPerspectiveFovLH(m_fov, (f32)m_screenArea.width / (f32)m_screenArea.height, m_nearPlane, m_farPlane);
	else if (m_type == OCameraType::Orthogonal)
		m_projection.setOrthoLH((f32)m_screenArea.width * 0.013f, (f32)m_screenArea.height * 0.013f, m_nearPlane, m_farPlane);
}