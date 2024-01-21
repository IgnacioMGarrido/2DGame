#include <Logger.h>
#include <SDL.h>
#include <cstdlib>

//TODO(Nacho): remove glovals

uint16_t g_width = 1280;
uint16_t g_heigh = 720;
SDL_Window* g_window = nullptr;
SDL_GLContext g_context = nullptr;
bool g_running = true;

///////////////////////////////////////////////////////////////////////////////

void InitProgram()
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG_ERROR("Couldn't Initialize SDL");
		exit(EXIT_FAILURE);
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	g_window =  SDL_CreateWindow("Game",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, g_width,
                              g_heigh, SDL_WINDOW_OPENGL);

	LOG_ASSERT(g_window, "Failed to Create Window");

	g_context = SDL_GL_CreateContext(g_window);

	LOG_ASSERT(g_context, "Failed to create Opengl Context");
}

///////////////////////////////////////////////////////////////////////////////


void Input()
{
	SDL_Event e;

	while(SDL_PollEvent(&e) != 0)
	{
		 if(e.type == SDL_QUIT)
		 {
			 g_running = false;
		 }
	}

}

void PreRender()
{

}

void Render()
{

}


void MainLoop()
{
	while(g_running)
	{
		Input();
		PreRender();
		Render();
		SDL_GL_SwapWindow(g_window);
	}
}

///////////////////////////////////////////////////////////////////////////////

void Cleanup()
{
	SDL_DestroyWindow(g_window);
	SDL_Quit();
}

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
	InitProgram();
	MainLoop();
	Cleanup();
	return 0;
}
