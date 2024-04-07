#include <OGL3D/Window/OWindow.h>
#include <OGL3D/Game/OGame.h>
#include <glad/glad_wgl.h>
#include <glad/glad.h>
#include <assert.h>
#include <stdexcept>
#include <functional>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		break;
	}
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return NULL;
}


OWindow::OWindow()
{
	static const ATOM windowClassId = std::invoke(
		[]() -> ATOM
		{
			WNDCLASSEX wc = {};
			wc.cbSize = sizeof(WNDCLASSEX);
			wc.lpszClassName = L"OGL3DWindow";
			wc.lpfnWndProc = &WndProc;
			wc.style = CS_OWNDC;
			return RegisterClassEx(&wc);
		}
	);

	assert(windowClassId);

	RECT rc = { 0,0,m_size.width,m_size.height };
	AdjustWindowRect(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, false);

	m_handle = CreateWindowEx(NULL, MAKEINTATOM(windowClassId), L"This took me several weeks ", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT,
		rc.right - rc.left, rc.bottom - rc.top, HWND(), HMENU(), HINSTANCE(), NULL);

	assert(m_handle);


	SetWindowLongPtr((HWND)m_handle, GWLP_USERDATA, (LONG_PTR)this);

	ShowWindow(HWND(m_handle), SW_SHOW);
	UpdateWindow(HWND(m_handle));



	HDC hDC = (HDC)GetDC(HWND(m_handle));

	int pixel_format_attribs[] = {
		WGL_DRAW_TO_WINDOW_ARB,     GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB,     GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB,      GL_TRUE,
		WGL_ACCELERATION_ARB,       WGL_FULL_ACCELERATION_ARB,
		WGL_PIXEL_TYPE_ARB,         WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB,         32,
		WGL_DEPTH_BITS_ARB,         24,
		WGL_STENCIL_BITS_ARB,       8,
		0
	};

	int pixel_format;
	UINT num_formats;
	wglChoosePixelFormatARB(hDC, pixel_format_attribs, 0, 1, &pixel_format, &num_formats);
	assert(num_formats);

	PIXELFORMATDESCRIPTOR pfd = {};
	DescribePixelFormat(hDC, pixel_format, sizeof(pfd), &pfd);
	SetPixelFormat(hDC, pixel_format, &pfd);

	int gl_attribs[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 6,
		WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,0,
	};

	m_context = wglCreateContextAttribsARB(hDC, 0, gl_attribs);
	assert(m_context);
}

OWindow::~OWindow()
{
	//release opengl context and window
	wglDeleteContext((HGLRC)m_context);
	DestroyWindow(HWND(m_handle));
}

ORect OWindow::getInnerSize()
{
	RECT rc = {};
	GetClientRect((HWND)m_handle, &rc);
	return ORect(rc.right - rc.left, rc.bottom - rc.top);
}

void OWindow::makeCurrentContext()
{
	HDC hDC = (HDC)GetDC(HWND(m_handle));
	wglMakeCurrent(hDC, (HGLRC)m_context);
}

void OWindow::present(bool vsync)
{
	wglSwapIntervalEXT(vsync);
	wglSwapLayerBuffers((HDC)GetDC(HWND(m_handle)), WGL_SWAP_MAIN_PLANE);
}