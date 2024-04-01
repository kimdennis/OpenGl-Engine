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
	OMat4 projection;
};

struct Vertex
{
	OVec3 position;
	OVec2 texcoord;
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

	OVec2 texcoordsList[] =
	{
		OVec2(0,0), //black
		OVec2(0,1), //green
		OVec2(1,0), //red
		OVec2(1,1) //yellow
	};

	Vertex verticesList[] =
	{
		//front face
		{ positionList[0],texcoordsList[1] },
		{ positionList[1],texcoordsList[0] },
		{ positionList[2],texcoordsList[2] },
		{ positionList[3],texcoordsList[3] },

		//back face
		{ positionList[4],texcoordsList[1] },
		{ positionList[5],texcoordsList[0] },
		{ positionList[6],texcoordsList[2] },
		{ positionList[7],texcoordsList[3] },

		//top face
		{ positionList[1],texcoordsList[1] },
		{ positionList[6],texcoordsList[0] },
		{ positionList[5],texcoordsList[2] },
		{ positionList[2],texcoordsList[3] },

		//bottom face
		{ positionList[7],texcoordsList[1] },
		{ positionList[0],texcoordsList[0] },
		{ positionList[3],texcoordsList[2] },
		{ positionList[4],texcoordsList[3] },

		//right face
		{ positionList[3],texcoordsList[1] },
		{ positionList[2],texcoordsList[0] },
		{ positionList[5],texcoordsList[2] },
		{ positionList[4],texcoordsList[3] },

		//left face
		{ positionList[7],texcoordsList[1] },
		{ positionList[6],texcoordsList[0] },
		{ positionList[1],texcoordsList[2] },
		{ positionList[0],texcoordsList[3] }
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
		8, 9, 10,
		10, 11, 8,

		//bottom
		12, 13, 14,
		14, 15, 12,

		//right
		16, 17 , 18,
		18, 19, 16,

		//left
		20, 21, 22,
		22, 23, 20

	};

	OVertexAttribute attribsList[] = {
		sizeof(OVec3)/sizeof(f32), //position
		sizeof(OVec2)/sizeof(f32) //texcoord
	};

	m_polygonVAO = m_graphicsEngine->createVertexArrayObject(
		{
			(void*)verticesList,
			sizeof(Vertex),
			sizeof(verticesList)/sizeof(Vertex),

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



	OMat4 world, temp, projection;

	temp.setIdentity();
	world.setScale(OVec3(1, 1, 1));
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
	temp.setTranslation(OVec3(0, 0, 0));
	world *= temp;

	auto displaySize = m_display->getInnerSize();
	projection.setOrthoLH(displaySize.width*0.004f, displaySize.height * 0.004f, 0.01f, 100.0f );




	UniformData data = { world, projection};
	m_uniform->setData(&data);


	m_graphicsEngine->clear(OVec4(0, 0, 0, 1));

	m_graphicsEngine->setFaceCulling(OCullType::BackFace);
	m_graphicsEngine->setWindingOrder(OWindingOrder::Clockwise);
	m_graphicsEngine->setVertexArrayObject(m_polygonVAO);
	m_graphicsEngine->setUniformBuffer(m_uniform, 0);
	m_graphicsEngine->setShaderProgram(m_shader); 
	m_graphicsEngine->drawIndexedTriangles(OTriangleType::TriangleList, 36);


	m_display->present(false);
}

void OGame::onQuit()
{
}

void OGame::quit()
{
	m_isRunning = false;
}



