#include <OGL3D/Input/OInputManager.h>
#include <Windows.h>

OInputManager::OInputManager()
{
}

OInputManager::~OInputManager()
{
}

bool OInputManager::isKeyDown(OKey key)
{
	short keyWin = 0;

	if (key >= KeyA && key <= KeyZ)
		keyWin = 'A' + (key - KeyA);
	else if (key >= Key0 && key <= Key9)
		keyWin = '0' + (key - Key0);
	else if (key == KeyShift)
		keyWin = VK_SHIFT;
	else if (key == KeyEscape)
		keyWin = VK_ESCAPE;
	else if (key == KeySpace)
		keyWin = VK_SPACE;
	else if (key == KeyCtrl)
		keyWin = VK_CONTROL;

	return (m_keys_state_res[keyWin] == 0);
}

bool OInputManager::isKeyUp(OKey key)
{
	short keyWin = 0;

	if (key >= KeyA && key <= KeyZ)
		keyWin = 'A' + (key - KeyA);
	else if (key >= Key0 && key <= Key9)
		keyWin = '0' + (key - Key0);
	else if (key == KeyShift)
		keyWin = VK_SHIFT;
	else if (key == KeyEscape)
		keyWin = VK_ESCAPE;
	else if (key == KeySpace)
		keyWin = VK_SPACE;
	else if (key == KeyCtrl)
		keyWin = VK_CONTROL;

	return (m_keys_state_res[keyWin] == 1);
}

bool OInputManager::isMouseDown(OMouseButton button)
{
	if (button == MouseButtonLeft)
	{
		auto state = m_keys_state_res[VK_LBUTTON];
		return (state == 0);

	}
	else if (button == MouseButtonMiddle)
	{
		auto state = m_keys_state_res[VK_MBUTTON];
		return (state == 0);
	}
	else if (button == MouseButtonRight)
	{
		auto state = m_keys_state_res[VK_RBUTTON];
		return (state == 0);
	}

	return false;
}

bool OInputManager::isMouseUp(OMouseButton button)
{
	if (button == MouseButtonLeft)
	{
		auto state = m_keys_state_res[VK_LBUTTON];
		return  (state == 1);

	}
	else if (button == MouseButtonMiddle)
	{
		auto state = m_keys_state_res[VK_MBUTTON];
		return  (state == 1);
	}
	else if (button == MouseButtonRight)
	{
		auto state = m_keys_state_res[VK_RBUTTON];
		return (state == 1);
	}
	return false;
}

f32 OInputManager::getMouseXAxis()
{
	return m_deltaMouse.x;
}

f32 OInputManager::getMouseYAxis()
{
	return m_deltaMouse.y;
}

void OInputManager::enablePlayMode(bool enable)
{
	m_playEnable = enable;
	ShowCursor(!enable);
}

void OInputManager::setScreenArea(const ORect& area)
{
	m_screenArea = area;
}

void OInputManager::update()
{
	POINT current_mouse_pos = {};
	::GetCursorPos(&current_mouse_pos);
	
	if (current_mouse_pos.x != (i32)m_old_mouse_pos.x || current_mouse_pos.y != (i32)m_old_mouse_pos.y)
	{
		m_deltaMouse = OVec2((f32)current_mouse_pos.x - (f32)m_old_mouse_pos.x, (f32)current_mouse_pos.y - (f32)m_old_mouse_pos.y);
	}
	else
	{
		m_deltaMouse = OVec2(0, 0);
	}


	if (!m_playEnable)
	{
		m_old_mouse_pos = OVec2((f32)current_mouse_pos.x, (f32)current_mouse_pos.y);
	}
	else
	{
		OVec2 center_screen = OVec2(m_screenArea.left + (f32)m_screenArea.width / 2.0f, m_screenArea.top + (f32)m_screenArea.height / 2.0f);
		::SetCursorPos((i32)center_screen.x, (i32)center_screen.y);
		m_old_mouse_pos = center_screen;
	}


	for (unsigned int i = 0; i < 256; i++)
	{
		m_keys_state[i] = ::GetAsyncKeyState(i);


		if (m_keys_state[i] & 0x8001)
		{
			m_keys_state_res[i] = 0;
		}
		else // KEY IS UP
		{
			if (m_keys_state[i] != m_old_keys_state[i])
			{
				m_keys_state_res[i] = 1;
			}
			else
			{
				m_keys_state_res[i] = 2;
			}
		}
	}

	::memcpy(m_old_keys_state, m_keys_state, sizeof(short) * 256);
}
