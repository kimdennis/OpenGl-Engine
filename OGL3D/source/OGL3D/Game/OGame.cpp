#include <OGL3D/Game/OGame.h>
#include <OGL3D/Window/OWindow.h>
#include <OGL3D/Graphics/OVertexArrayObject.h>
#include <OGL3D/Graphics/OShaderProgram.h>
#include <OGL3D/Graphics/OUniformBuffer.h>
#include <OGL3D/Math/OMat4.h>
#include <OGL3D/Math/OVec3.h>
#include <OGL3D/Math/OVec2.h>

struct UniformData
{
	OMat4 world;
};

OGame::OGame()
{
	m_graphicsEngine = std::make_unique<OGraphicsEngine>();
	m_display = std::make_unique<OWindow>();

	m_display->makeCurrentContact();

	m_graphicsEngine->setViewport(m_display->getInnerSize());
}

OGame::~OGame()
{
}

void OGame::onCreate()
{
	OVec3 positionList[] =
	{
		//front face
		OVec3(-0.5f, -0.5f, -0.5f),
		OVec3(-0.5f, 0.5f, -0.5f),
		OVec3(0.5f, 0.5f, -0.5f),
		OVec3(0.5f, -0.5f, -0.5f),

		//back face
		OVec3(0.5f, -0.5f, 0.5f),
		OVec3(0.5f, 0.5f, 0.5f),
		OVec3(-0.5f, 0.5f, 0.5f),
		OVec3(-0.5f, -0.5f, 0.5f)
	};

	ui32 indicesList[] =
	{
		//front
		0, 1, 2,
		2, 3, 0,

		//back
		4, 5, 6,
		6, 7, 4,

		//top
		1, 6, 5,
		5, 2, 1,

		//bottom
		7, 0, 3,
		3, 4, 7,

		//right
		3, 2 ,5,
		5, 4, 3,

		//left
		7, 6, 1,
		1, 0, 7

	};

	//const f32 polygonVertices[] = {
	//	-0.5f,-0.5f,0.0f,
	//	1    ,0    ,0   ,

	//	-0.5f, 0.5f,0.0f,
	//	0    ,1    ,0   ,

	//	0.5f, -0.5f,0.0f,
	//	0   ,0    ,1  ,

	//	0.5f, 0.5f,0.0f,
	//	1   ,1   ,0
	//};


	OVertexAttribute attribsList[] = {
		sizeof(OVec3)/sizeof(f32) //position
		//3 //colour
	};

	m_polygonVAO = m_graphicsEngine->createVertexArrayObject(
		{
			(void*)positionList,
			sizeof(OVec3),
			sizeof(positionList)/sizeof(OVec3),

			attribsList,
			sizeof(attribsList) / sizeof(OVertexAttribute)
		},

		{
			(void*) indicesList, 
			sizeof(indicesList)
		}
	);


	m_uniform = m_graphicsEngine->createUniformBuffer({
		sizeof(UniformData)
		});

	

	m_shader = m_graphicsEngine->createShaderProgram(
		{
			L"Assets/Shaders/BasicShader.vert",
			L"Assets/Shaders/BasicShader.frag"
		});

	m_shader->setUniformBufferSlot("UniformData", 0);
}

void OGame::onUpdate()
{

	// computing delta time
	auto currentTime = std::chrono::system_clock::now();
	auto elapsedSeconds = std::chrono::duration<double>();

	if (m_previousTime.time_since_epoch().count())
		elapsedSeconds = currentTime - m_previousTime;
	m_previousTime = currentTime;

	auto deltaTime = (f32)elapsedSeconds.count();


	m_scale += 1.14f * deltaTime;
	auto currentScale = abs(sin(m_scale));



	OMat4 world, temp;

	temp.setIdentity();
	world.setScale(OVec4(1, 1, 1, 1));
	world *= temp;

	temp.setIdentity();
	temp.setRotationZ(m_scale);
	world *= temp;

	temp.setIdentity();
	temp.setRotationY(m_scale);
	world *= temp;

	temp.setIdentity();
	temp.setRotationX(m_scale);
	world *= temp;

	temp.setIdentity();
	temp.setTranslation(OVec4(0, 0, 0, 1));
	world *= temp;

	UniformData data = { world };
	m_uniform->setData(&data);


	m_graphicsEngine->clear(OVec4(0, 0, 0, 1));

	m_graphicsEngine->setVertexArrayObject(m_polygonVAO);
	m_graphicsEngine->setUniformBuffer(m_uniform, 0);
	m_graphicsEngine->setShaderProgram(m_shader); 
	m_graphicsEngine->drawIndexedTriangles(TriangleStrip, 36);

	m_display->present(false);
}

void OGame::onQuit()
{
}

void OGame::quit()
{
	m_isRunning = false;
}



