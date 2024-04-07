#include <OGL3D/Game/OGame.h>
#include <OGL3D/Window/OWindow.h>
#include <OGL3D/Math/OMat4.h>
#include <OGL3D/Math/OVec2.h>
#include <OGL3D/Camera/OCamera.h>
#include <OGL3D/Entity/OGraphicsEntity.h>
#include <math.h>

struct UniformData
{
    OMat4 world;
    OMat4 view;
    OMat4 proj;
};



OGame::OGame()
{
    m_inputManager = std::make_unique<OInputManager>();
    m_graphicsEngine = std::make_unique<OGraphicsEngine>();
    m_display = std::make_unique<OWindow>();


    m_display->makeCurrentContext();

    m_graphicsEngine->setViewport(m_display->getInnerSize());
    m_graphicsEngine->setFaceCulling(BackFace); // draw only the front faces, the back faces are discarded
    m_graphicsEngine->setWindingOrder(ClockWise); //consider the position of vertices in clock wise way.

    getInputManager()->setScreenArea(m_display->getInnerSize());


    m_uniform = m_graphicsEngine->createUniformBuffer({
        sizeof(UniformData) // size in bytes of the data structure we want to pass to shaders
        });


    m_shader = m_graphicsEngine->createShader(
        {
            L"Assets/Shaders/Shader.vert",
            L"Assets/Shaders/Shader.frag"
        });
}



OGame::~OGame()
{
}

void OGame::onCreate()
{
}

void OGame::onUpdate(f32 deltaTime)
{
}

void OGame::onUpdateInternal()
{
    m_inputManager->update();

    //computing delta time-------------------
    auto now = std::chrono::system_clock::now(); // take the current time
    std::chrono::duration<double> elapsedSeconds = now - m_oldTime; // let's take the difference between the current time and the time taken in the previous frame in seconds (the so called delta time)
    if (!m_oldTime.time_since_epoch().count()) //if m_oldTime has not been set yet, simply set elapsedSeconds to 0
        elapsedSeconds = std::chrono::duration<double>();
    m_oldTime = now; // store the current time in order to be used in the next frame

    f32 deltaTime = (f32)elapsedSeconds.count();
    //---------------------------------------------

    //destroy the entities that have been release in the previous iteration
    // we destroy the entities here in order to not create issues during the loop over the main map (m_entities)
    //--------------------------------
    for (auto entity : m_entitiesToDestroy)
    {
        auto id = typeid(entity).hash_code();
        m_entities[id].erase(entity);
    }
    m_entitiesToDestroy.clear();
    //----------------------------------


    //update game and entities
    //----------------------------------
    onUpdate(deltaTime);

    for (auto& [key, entities] : m_entities)
    {
        for (auto& [key, entity] : entities)
        {
            entity->onUpdate(deltaTime);
        }
    }
    //----------------------------------

    //update the graphics part
    onGraphicsUpdate(deltaTime);



}

void OGame::onQuit()
{
}


void OGame::quit()
{
    m_isRunning = false;
}

void OGame::onGraphicsUpdate(f32 deltaTime)
{
    m_graphicsEngine->clear(OVec4(0, 0, 0, 1));

    UniformData data = {};



    auto camId = typeid(OCamera).hash_code();
    auto it = m_entities.find(camId);


    //let's set the camera data to the uniformdata structure, in order to pass them to the shaders for the final rendering
    if (it != m_entities.end())
    {
        for (auto& [key, camera] : it->second)
        {
            //the camera data are the view and projection
            //view is simply the world matrix of the camera inverted
            OMat4 w;
            auto cam = dynamic_cast<OCamera*>(camera.get());
            cam->getViewMatrix(data.view);
            cam->setScreenArea(this->m_display->getInnerSize());
            cam->getProjectionMatrix(data.proj);
        }
    }

    for (auto& [key, entities] : m_entities)
    {
        //for each graphics entity
        for (auto& [key, entity] : entities)
        {
            auto e = dynamic_cast<OGraphicsEntity*>(entity.get());

            if (e)
            {
                //let's retrive the world matrix and let's pass it to the uniform buffer
                e->getWorldMatrix(data.world);

                m_uniform->setData(&data);
                m_graphicsEngine->setShader(m_shader); //bind shaders to graphics pipeline
                m_graphicsEngine->setUniformBuffer(m_uniform, 0); // bind uniform buffer

                //call internal graphcis update of the entity in order to handle specific graphics data/functions 
                e->onGraphicsUpdate(deltaTime);
            }
            else
            {
                break;
            }
        }
    }

    m_display->present(false);
}

void OGame::createEntityConcrete(OEntity* entity, size_t id)
{
    auto entityPtr = std::unique_ptr<OEntity>(entity);
    auto camId = typeid(OCamera).hash_code();
    entity->m_game = this;
    if (id == camId)
    {
        auto it = m_entities.find(camId);
        if (it != m_entities.end())
        {
            if (it->second.size()) return;
            it->second.emplace(entity, std::move(entityPtr));
        }
        else
        {
            m_entities[camId].emplace(entity, std::move(entityPtr));
        }
    }
    else
    {
        m_entities[id].emplace(entity, std::move(entityPtr));
    }
    entity->onCreate();
}

void OGame::removeEntity(OEntity* entity)
{
    m_entitiesToDestroy.emplace(entity);
}