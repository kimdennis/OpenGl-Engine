#include "MyGame.h"
#include "Player.h"

#include <time.h>

MyGame::MyGame()
{
}

MyGame::~MyGame()
{
}

void MyGame::onCreate()
{
	//loading texture resource
	auto dog = std::dynamic_pointer_cast<OTexture>(getResourceManager()->createResourceFromFile(L"Assets/Textures/cutie_patootie_doggy.jpg"));
	auto teapot = std::dynamic_pointer_cast<OMesh>(getResourceManager()->createResourceFromFile(L"Assets/Meshes/teapot.obj"));

	//creating the floor
	{
		auto entity = createEntity<OCubeEntity>();
		entity->setScale(OVec3(10.0f, 0.1f, 10.0f));
		entity->setPosition(OVec3(0, 0, 0));
		entity->setTexture(dog);
	}


	//creating teapot
	{
		auto entity = createEntity<OMeshEntity>();
		entity->setScale(OVec3(1, 1, 1));
		entity->setPosition(OVec3(0, 0, 0));
		entity->setTexture(dog);
		entity->setMesh(teapot);
	}

	/*
	srand((unsigned int)time(NULL));

	for (auto y = -2; y < 3; y++)
	{
		for (auto x = -2; x < 3; x++)
		{
			auto cube = createEntity<OCubeEntity>();
			auto height = 0.5f;
			auto roty = (rand() % 600) + (200.0f);
			roty /= 1000.0f;
			auto width = 0.5f;

			cube->setScale(OVec3(width, height, width));
			cube->setPosition(OVec3(x * 1.4f, (height / 2.0f) - 0.94f, y * 1.4f));
			cube->setRotation(OVec3(0, roty, 0));
			cube->setTexture(dog);
		}
	}
	*/

	//creating the player
	//all the input managements, creation of camera etc. are moved inside Player class
	m_player = createEntity<Player>();
	
	//enabling play mode
	getInputManager()->enablePlayMode(true);
}

void MyGame::onUpdate(f32 deltaTime)
{  



}