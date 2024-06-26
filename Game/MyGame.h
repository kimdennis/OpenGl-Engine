#pragma once
#include <OGL3D/All.h>



class MyGame: public OGame
{

public:
	MyGame();
	~MyGame();


	virtual void onCreate();
	virtual void onUpdate(f32 deltaTime);


private:

	OCubeEntity* m_player = nullptr;

};

