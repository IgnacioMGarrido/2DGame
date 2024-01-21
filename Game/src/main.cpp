#include <Logger.h>
#include <SDL.h>
#include <cstdlib>

//TODO(Nacho): remove glovals

uint16_t g_Width = 1280;
uint16_t g_Heigh = 720;
SDL_Window* g_window = nullptr;
SDL_GLContext* g_context = nullptr;


void InitProgram()
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG_ERROR("Couldn't Initialize SDL");
		exit(EXIT_FAILURE);
	}

	

}

void Cleanup()
{
	SDL_Quit();
}

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
	InitProgram();
	Cleanup();
	return 0;
}
