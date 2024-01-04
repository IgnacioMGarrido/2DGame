#include <iostream>
#include <Windows.h>
#include "../include/Logger.h"

static HWND hwnd;
static bool running = true;

LRESULT CALLBACK WinWindowsCb(HWND i_wnd, UINT i_msg, WPARAM i_wParam, LPARAM i_lParam)
{
	LRESULT result = 0;

	switch(i_msg)
	{
		case WM_CLOSE:
		{
			running = false;
			break;
		}
		default:
		{
			result = DefWindowProcA(i_wnd, i_msg, i_wParam, i_lParam);
		}
	}

	return result;
}

///////////////////////////////////////////////////////////////////////////////

bool InstanceWindow(int i_width, int i_height, const char* i_name)
{
	HINSTANCE instance = GetModuleHandleA(0);

	WNDCLASSA wc = {};
	wc.hInstance = instance;
	wc.hIcon = LoadIcon(instance, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.lpszClassName = i_name;
	wc.lpfnWndProc = DefWindowProcA;

	if (!RegisterClassA(&wc))
	{
		return false;
	}

	hwnd = CreateWindowExA(
		0,
		i_name,
		i_name,
		WS_OVERLAPPEDWINDOW,
		100, 100, i_width, i_height,
		NULL,
		NULL,
		instance,
		NULL
	);
	if (hwnd == nullptr)
	{
		return false;
	}

	ShowWindow(hwnd, SW_SHOW);
	return true;
}

///////////////////////////////////////////////////////////////////////////////

void UpdateWindow()
{
	MSG msg;

	while(PeekMessageA(&msg, hwnd, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

int main(int argc, char** argv)
{
	if(!InstanceWindow(1280, 720, "2DGame"))
	{
		std::cout << "Failed to Create window\n";
		return EXIT_FAILURE;
	}

	while (running)
	{
		Core::LOG_TRACE("This is a trace");
		Core::LOG_WARNING("This is a warning");
		Core::LOG_ERROR("This is an error");
		UpdateWindow();
	}
	return 0;
}
