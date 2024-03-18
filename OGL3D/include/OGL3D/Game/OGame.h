#pragma once
#include <memory>

class OGraphicsEngine;
class OWindow;
class OGame
{
public:
	OGame();
	~OGame();

	virtual void onCreate();
	virtual void onUpdate();
	virtual void onQuit();

	void run();
	void quit();
protected:
	bool m_isRunning = true;
	std::unique_ptr<OGraphicsEngine> m_graphicsEngine;
	std::unique_ptr<OWindow> m_display;
};

