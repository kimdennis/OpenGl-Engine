#pragma once
#include <OGL3D/All.h>


//Player Entity
class Player : public OEntity
{
public:
	Player();
	virtual ~Player();

	virtual void onCreate();
	virtual void onUpdate(f32 deltaTime);

private:
	f32 m_camRotX = 0;
	f32 m_camRotY = 0;

	OCamera* m_cam = nullptr;
	//f32 m_roty = 0;
};