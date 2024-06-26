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
	auto wood = std::dynamic_pointer_cast<OTexture>(getResourceManager()->createResourceFromFile(L"Assets/Textures/cutie_patootie_doggy.jpg"));
	auto wall = std::dynamic_pointer_cast<OTexture>(getResourceManager()->createResourceFromFile(L"Assets/Textures/cutie_patootie_doggy.jpg"));

	//creating the floor
	auto cube = createEntity<OCubeEntity>();
	cube->setScale(OVec3(6.8f, 0.1f, 6.8f));
	cube->setPosition(OVec3(0, -1, 0));
	cube->setTexture(wall);


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
			cube->setTexture(wood);
		}
	}

	//creating the player
	//all the input managements, creation of camera etc. are moved inside Player class
	auto player = createEntity<Player>();
	player->setPosition(OVec3(0, 0, 0));

	//enabling play mode
	getInputManager()->enablePlayMode(true);
}

void MyGame::onUpdate(f32 deltaTime)
{
}
