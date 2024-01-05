#include <iostream>
#include <Windows.h>
#include <Logger.h>
#include <window/EWindow.h>

static bool running = true;

///////////////////////////////////////////////////////////////////////////////


int main(int argc, char** argv)
{
	core::platform::EWindow window {{.width = 1280, .height = 720, .name = "2DGame"}};
	window.UpdateWindow();
	return 0;
}
