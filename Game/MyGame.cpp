#include "MyGame.h"
#include <time.h>

MyGame::MyGame()
{
}

MyGame::~MyGame()
{
}

void MyGame::onCreate()
{
	//FLOOR
	auto floor = createEntity<OCubeEntity>();
	floor->setScale(OVec3(6.8f, 0.1f, 6.8f));
	floor->setPosition(OVec3(0, -1, 0));

	//PLAYER (CUBE)
	m_player = createEntity<OCubeEntity>();
	m_player->setScale(OVec3(1.0f, 1.0f, 1.0f));
	m_player->setPosition(OVec3(0, -0.4f, 0));

	//CAMERA
	m_cam = createEntity<OCamera>();
	m_cam->setPosition(OVec3(0, 0, 0));


	//PLAY
	getInputManager()->enablePlayMode(true);
}

void MyGame::onUpdate(f32 deltaTime)
{
	//adjust camera rotation speed
	f32 cameraRotationSpeed = 0.005f;

	//rotate camera based on mouse pos
	m_camRotY += getInputManager()->getMouseXAxis() * cameraRotationSpeed;
	m_camRotX += getInputManager()->getMouseYAxis() * cameraRotationSpeed;

	if (m_camRotX > 0.707f)
		m_camRotX = 0.707f;
	else if (m_camRotX < -0.707f)
		m_camRotX = -0.707f;

	m_cam->setRotation(OVec3(m_camRotX, m_camRotY, 0));



	//assign WASD movement
	auto pos = m_player->getPosition();

	//adjust movement speed
	f32 movementSpeed = 3.0f;

	if (getInputManager()->isKeyDown(OKey::KeyW))
	{
		pos += OVec3(0, 0, movementSpeed * deltaTime);
	}
	if (getInputManager()->isKeyDown(OKey::KeyS))
	{
		pos += OVec3(0, 0, -movementSpeed * deltaTime);
	}
	if (getInputManager()->isKeyDown(OKey::KeyA))
	{
		pos += OVec3(-movementSpeed * deltaTime, 0, 0);
	}
	if (getInputManager()->isKeyDown(OKey::KeyD))
	{
		pos += OVec3(movementSpeed * deltaTime, 0, 0);
	}

	m_player->setPosition(pos);

}