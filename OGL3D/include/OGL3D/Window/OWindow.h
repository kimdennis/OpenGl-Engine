#pragma once

class OWindow
{
public:
	OWindow();
	~OWindow();

	void makeCurrentContact();
	void present(bool vsync);
private:
	void* m_handle = nullptr;
	void* m_context = nullptr;
};