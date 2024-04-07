#pragma once

#include <OGL3D/OPrerequisites.h>
#include <OGL3D/Math/OVec2.h>
#include <OGL3D/Math/ORect.h>

class  OInputManager
{
public:
	OInputManager();
	~OInputManager();

	virtual bool isKeyDown(OKey key);
	virtual bool isKeyUp(OKey key);

	virtual bool isMouseDown(OMouseButton button);
	virtual bool isMouseUp(OMouseButton button);

	//getMouseXAxis returns the current mouse movement along x axis: -1 (left), 1 (right).
	virtual f32 getMouseXAxis();
	//getMouseYAxis returns the current mouse movement along y axis: -1 (bottom), 1 (top).
	virtual f32 getMouseYAxis();

	//enablePlayMode allows to hide the cursor and to lock it at the center of the screen.
	virtual void enablePlayMode(bool enable);

	//setScreenArea allows to set the screen area the cursor will be locked into when playmode is enabled.
	void setScreenArea(const ORect& area);
	void update();

private:
	short m_keys_state[256] = {};
	short m_old_keys_state[256] = {};
	short m_keys_state_res[256] = {};

	bool m_playEnable = false;
	OVec2 m_old_mouse_pos;
	bool m_first_time = true;
	ORect m_screenArea;
	OVec2 m_deltaMouse;
	int states_index = 0;
};