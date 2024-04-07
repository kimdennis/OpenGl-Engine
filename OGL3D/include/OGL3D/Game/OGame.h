#pragma once
#include <memory>
#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <OGL3D/Input/OInputManager.h>
#include <OGL3D/Entity/OEntity.h>
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

	// tfunction - creates any kind of entity by passing the type of entity we want to create as template argument
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


	void run();
	void quit();
private:

	//updates all the data/entities etc.
	void onUpdateInternal();

	//updates all graphics
	void onGraphicsUpdate(f32 deltaTime);


	void createEntityConcrete(OEntity* entity, size_t id);
	void removeEntity(OEntity* entity);

protected:
	bool m_isRunning = true;



	//ORDER OF SMART POINTERS IMPORTANT!!!!!!
	//the first one defined (m_display) is the last to be deallocated
	//the last one defined (m_triShader) is the first to be deallocated
	std::unique_ptr<OInputManager> m_inputManager;
	std::unique_ptr<OGraphicsEngine> m_graphicsEngine;
	std::unique_ptr<OWindow> m_display;

	//map handles all the types of entities we add to the game.
	//map need per each type of entity (type retrieved with typeid function)
	//map needed to handle the smart pointers (uniqueptr) of all the entities of that type
	//uses unique_ptr to handle memory
	std::map<size_t, std::map<OEntity*, std::unique_ptr<OEntity>>> m_entities;

	//kill entity
	std::set<OEntity*> m_entitiesToDestroy;
	//------------------------------------------



	OUniformBufferPtr m_uniform;
	OShaderPtr m_shader;

	std::chrono::system_clock::time_point m_oldTime;

	friend class OEntity;
};