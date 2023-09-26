#include "RenderSystem_SDL.h"
#include <SDL.h>
#include <iostream>

//We're globally instancing our subsystems!
//But maybe you think Globals are bad
//There might be other ways to approach this.
#ifdef RENDERSYSTEM_SDL
    Spite::RenderSystem_SDL grRenderSystemSDL;
    Spite::RenderSystem* Spite::grRenderSystem = &grRenderSystemSDL;
#endif

Spite::RenderSystem_SDL::RenderSystem_SDL()
{
}

Spite::RenderSystem_SDL::~RenderSystem_SDL()
{
}

int Spite::RenderSystem_SDL::Initialise()
{
	int result = 0;
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        result = -1;
    }
    return result;
}

int Spite::RenderSystem_SDL::Shutdown()
{
    //Destroy render systems
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    m_Renderer = nullptr;
    m_Window = nullptr;
	return 0;
}

int Spite::RenderSystem_SDL::OpenWindow(int width, int height)
{
    int result = 0;

    m_ScreenWidth = width;
    m_ScreenHeight = height;

    m_Window = SDL_CreateWindow("My first video grame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_ScreenWidth, m_ScreenHeight, SDL_WINDOW_SHOWN);
    if (m_Window == nullptr)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        result = -1;
    }
    return result;
}

int Spite::RenderSystem_SDL::CreateRenderer()
{
    int result = 0;
    if (m_Window == nullptr)
    {
        printf("There is no window!\n");
        return -1;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
    if (m_Renderer == NULL)
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        result = -1;
    }
    else
    {
        //Initialize renderer color
        SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    }
}

void Spite::RenderSystem_SDL::Clear()
{
}

void Spite::RenderSystem_SDL::Display()
{
}

void Spite::RenderSystem_SDL::HandleWindowEvent(GR_WindowEvent& e)
{
    switch (e.event) {
    case GR_WINDOWEVENT::WINDOWEVENT_SHOWN:
        SDL_Log("Window %d shown", e.windowID);
        break;
    case GR_WINDOWEVENT::WINDOWEVENT_HIDDEN:
        SDL_Log("Window %d hidden", e.windowID);
        break;
    case GR_WINDOWEVENT::WINDOWEVENT_EXPOSED:
        SDL_Log("Window %d exposed", e.windowID);
        break;
    case GR_WINDOWEVENT::WINDOWEVENT_MOVED:
        SDL_Log("Window %d moved to %d,%d",
            e.windowID, e.data1,
            e.data2);
        break;
    case GR_WINDOWEVENT::WINDOWEVENT_RESIZED:
        SDL_Log("Window %d resized to %dx%d",
            e.windowID, e.data1,
            e.data2);
        break;
    case GR_WINDOWEVENT::WINDOWEVENT_SIZE_CHANGED:
        SDL_Log("Window %d size changed to %dx%d",
            e.windowID, e.data1,
            e.data2);
        break;
    case GR_WINDOWEVENT::WINDOWEVENT_MINIMIZED:
        SDL_Log("Window %d minimized", e.windowID);
        break;
    case GR_WINDOWEVENT::WINDOWEVENT_MAXIMIZED:
        SDL_Log("Window %d maximized", e.windowID);
        break;
    case GR_WINDOWEVENT::WINDOWEVENT_RESTORED:
        SDL_Log("Window %d restored", e.windowID);
        break;
    case GR_WINDOWEVENT::WINDOWEVENT_ENTER:
        SDL_Log("Mouse entered window %d",
            e.windowID);
        break;
    case GR_WINDOWEVENT::WINDOWEVENT_LEAVE:
        SDL_Log("Mouse left window %d", e.windowID);
        break;
    case GR_WINDOWEVENT::WINDOWEVENT_FOCUS_GAINED:
        SDL_Log("Window %d gained keyboard focus",
            e.windowID);
        break;
    case GR_WINDOWEVENT::WINDOWEVENT_FOCUS_LOST:
        SDL_Log("Window %d lost keyboard focus",
            e.windowID);
        break;
    case GR_WINDOWEVENT::WINDOWEVENT_CLOSE:
        SDL_Log("Window %d closed", e.windowID);
        break;

    default:
        SDL_Log("Window %d got unknown event %d",
            e.windowID, e.event);
        break;
    }
}
