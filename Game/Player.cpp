#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::onCreate()
{
	m_cam = m_game->createEntity<OCamera>();
	m_cam->setPosition(OVec3(0, 0, 0));
}

void Player::onUpdate(f32 deltaTime)
{
	auto input = m_game->getInputManager();

	m_camRotY += input->getMouseXAxis() * 0.01f;
	m_camRotX += input->getMouseYAxis() * 0.01f;

	if (m_camRotX > 1.57f)
		m_camRotX = 1.57f;
	else if (m_camRotX < -1.57f)
		m_camRotX = -1.57f;

	m_cam->setRotation(OVec3(m_camRotX, m_camRotY, 0));



	//camera movement
	OMat4 worldMatCam;
	m_cam->getWorldMatrix(worldMatCam);


	auto forwardDir = worldMatCam.getForwardDirection();
	auto rightwardDir = worldMatCam.getRightwardDirection();
	auto upDir = worldMatCam.getUpDirection();


	auto speed = 2.0f;
	f32 moveForward = 0, moveRightward = 0, moveUpward = 0;
	if (input->isKeyDown(OKey::KeyShift))
	{
		//Press shift to run!
		speed *= 2.0f;
	}
	if (input->isKeyDown(OKey::KeyW))
	{
		moveForward = 1;
	}
	if (input->isKeyDown(OKey::KeyS))
	{
		moveForward = -1;
	}
	if (input->isKeyDown(OKey::KeyA))
	{
		moveRightward = -1;
	}
	if (input->isKeyDown(OKey::KeyD))
	{
		moveRightward = 1;
	}
	if (input->isKeyDown(OKey::KeySpace))
	{
		moveUpward = 1;
	}
	if (input->isKeyDown(OKey::KeyCtrl))
	{
		moveUpward = -1;
	}

	auto pos = m_cam->getPosition() + (forwardDir * moveForward) * speed * deltaTime;
	pos = pos + (rightwardDir * moveRightward) * speed * deltaTime;
	pos = pos + (upDir * moveUpward) * speed * deltaTime;

	m_cam->setPosition(pos);
}