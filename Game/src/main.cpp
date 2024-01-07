#include <iostream>
#include <Windows.h>
#include <Logger.h>
#include <window/EWindow.h>

int main(int argc, char** argv)
{
	core::platform::EWindow window {1280, 720, "2DGame"};
	window.UpdateWindowMessages();
	return 0;
}
