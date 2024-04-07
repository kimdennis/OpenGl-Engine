#pragma once
#include <OGL3D/All.h>



class MyGame : public OGame
{

public:
	MyGame();
	~MyGame();


	virtual void onCreate();
	virtual void onUpdate(f32 deltaTime);


private:
	f32 m_camRotX = 0;
	f32 m_camRotY = 0;
	OCamera* m_cam = nullptr;

	OCubeEntity* m_player = nullptr;

};