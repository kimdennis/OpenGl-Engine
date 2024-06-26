#pragma once
#include <memory>
#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <OGL3D/Input/OInputManager.h>
#include <OGL3D/Resource/OResourceManager.h>
#include <OGL3D/Game/OEntity.h>
#include <OGL3D/Game/OMeshEntity.h>
#include <chrono>
#include <map>
#include <set>
class OWindow;
class OGame
{
public:
	OGame();
	~OGame();

	virtual void onCreate();
	virtual void onUpdate(f32 deltaTime);
	virtual void onQuit();


	//one of the main method of the entity system
	// this function allows to create any kind of entity by passing the type of entity we want to create as template argument
	template <typename T>
	T* createEntity()
	{
		static_assert(std::is_base_of<OEntity, T>::value, "T must derive from OEntity");
		auto id = typeid(T).hash_code();
		auto e = new T();
		createEntityConcrete(e, id);
		return e;
	}


	OGraphicsEngine* getGraphicsEngine();
	OInputManager* getInputManager();
	OResourceManager* getResourceManager();

	void run();
	void quit();
private:

	//various internal methods of entity system------------

	//function that allows to update all the data/entities etc. of the game
	void onUpdateInternal();

	//function that allows to update only the graphics part of the game
	void onGraphicsUpdate(f32 deltaTime);


	void createEntityConcrete(OEntity* entity, size_t id);
	void removeEntity(OEntity* entity);
	//---------------------------------------------------------

private:
	//various internal methods of graphics system------------

	void drawMesh(OMeshEntity* entity);




protected:
	bool m_isRunning = true;



	//take care of the order of smart pointers
	//the first one defined (m_display) is the last to be deallocated
	//the last one defined (m_triShader) is the first to be deallocated
	std::unique_ptr<OInputManager> m_inputManager;
	std::unique_ptr<OGraphicsEngine> m_graphicsEngine;
	std::unique_ptr<OWindow> m_display;
	std::unique_ptr<OResourceManager> m_resourceManager;

	//the core of entity system--------------
	//this map handles all the types of entities we add to the game.
	//for each type of entity (type retrieved with typeid function) we have a map
	//that handles the smart pointers (uniqueptr) of all the entities of that type.
	//By using unique_ptr memory management is handled easily.
	std::map<size_t, std::map<OEntity*, std::unique_ptr<OEntity>>> m_entities;

	//m_entitiesToDestroy set handles the entities that have been marked for destroy.
	std::set<OEntity*> m_entitiesToDestroy;
	//------------------------------------------



	OUniformBufferPtr m_uniform;
	OShaderPtr m_shader;
	OShaderPtr m_meshShader;

	std::chrono::system_clock::time_point m_oldTime;

	friend class OEntity;
};