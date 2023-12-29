#include "pch.h"
#include "RenderSystem_SDL.h"
#include "SpriteBatch_GL.h"
#include "Atlas_GL.h"

//We're globally instancing our subsystems!
//But maybe you think Globals are bad
//There might be other ways to approach this.
#ifdef RENDERSYSTEM_SDL
Spite::RenderSystem_SDL grRenderSystemSDL;
Spite::RenderSystem* Spite::render = &grRenderSystemSDL;
#endif


Spite::RenderSystem_SDL::RenderSystem_SDL() : camera{ glm::vec2{0, 0} }, backgroundColour{ 0,0,0 }, blackBars{false}
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
        std::cout << std::format("SDL could not initialize! SDL_Error: {}", SDL_GetError()) << std::endl;
        
        result = -1;
    }
    return result;
}

int Spite::RenderSystem_SDL::Shutdown()
{
    //Destroy render systems
    SDL_DestroyWindow(m_Window);
    m_Window = nullptr;
	return 0;
}

int Spite::RenderSystem_SDL::OpenWindow(int width, int height)
{
    int result = 0;
    m_ScreenWidth = width;
    m_ScreenHeight = height;
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    m_Window = SDL_CreateWindow("My first video game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_ScreenWidth, m_ScreenHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (m_Window == nullptr)
    {
        std::cout << std::format("Window could not be created! SDL_Error: {}", SDL_GetError()) << std::endl;
        return -1;
    }
    return 0;
}

void DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    std::string sourceString = "UNKNOWN";
    switch(source) {
        case GL_DEBUG_SOURCE_API: sourceString = "API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM: sourceString = "WINDOW_SYSTEM"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: sourceString = "COMPILER"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY: sourceString = "THIRD_PARTY"; break;
        case GL_DEBUG_SOURCE_APPLICATION: sourceString = "APPLICATION"; break;
        case GL_DEBUG_SOURCE_OTHER: sourceString = "OTHER"; break;
    }
    std::string typeString = "UNKNOWN";
    switch(type) {
        case GL_DEBUG_TYPE_ERROR: typeString = "ERROR"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: typeString = "DEPRECATED_BEHAVIOR"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: typeString = "UNDEFINED_BEHAVIOR"; break;
        case GL_DEBUG_TYPE_PORTABILITY: typeString = "PORTABILITY"; break;
        case GL_DEBUG_TYPE_PERFORMANCE: typeString = "PERFORMANCE"; break;
        case GL_DEBUG_TYPE_OTHER: typeString = "OTHER"; break;
        case GL_DEBUG_TYPE_MARKER: typeString = "MARKER"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP: typeString = "PUSH_GROUP"; break;
        case GL_DEBUG_TYPE_POP_GROUP: typeString = "POP_GROUP"; break;
    }
    std::string severityString = "UNKNOWN";
    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH: severityString = "HIGH"; break;
        case GL_DEBUG_SEVERITY_MEDIUM: severityString = "MEDIUM"; break;
        case GL_DEBUG_SEVERITY_LOW: severityString = "LOW"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: severityString = "NOTIFICATION"; break;
    }
    std::cout << std::format("SOURCE={} TYPE={} SEVERITY={}:\n{}", sourceString, typeString, severityString, message) << std::endl;
}

int Spite::RenderSystem_SDL::CreateRenderer()
{
    int result = 0;
    if (m_Window == nullptr)
    {
        std::cout << "There is no window!" << std::endl;
        return -1;
    }
    //Create opengl context
    SDL_GLContext openglContext = SDL_GL_CreateContext(m_Window);
    glewExperimental = GL_TRUE;
    auto init_res = glewInit();
    if (init_res != GLEW_OK) {
        std::cout << glewGetErrorString(glewInit()) << std::endl;
        return -1;
    }
    //Debug
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(DebugCallback, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);

    if(!defaultSpriteBatch) {
        defaultSpriteBatch.reset(new SpriteBatch_GL(this));
    }
    return 0;
}

void Spite::RenderSystem_SDL::Clear()
{
    //Black bars
    if (blackBars) {
        glClearColor(0, 0, 0, 1.0f);
        SetupFullViewPort();
        glClear(GL_COLOR_BUFFER_BIT);
    }
    //background color and depth
    glClearColor(backgroundColour.r, backgroundColour.g, backgroundColour.b, 1.0f);
    SetupCameraViewPort(blackBars);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    //data structures
    defaultSpriteBatch->Clear();
}

std::unique_ptr<Spite::SpriteBatch> Spite::RenderSystem_SDL::CreateSpriteBatch() {
    return std::make_unique<Spite::SpriteBatch_GL>(this);
}

std::unique_ptr<Spite::Texture> Spite::RenderSystem_SDL::CreateTexture() {
    return std::make_unique<Spite::Texture_GL>();
}

std::unique_ptr<Spite::Atlas> Spite::RenderSystem_SDL::CreateAtlas() {
    return std::make_unique<Spite::Atlas_GL>();
}

void Spite::RenderSystem_SDL::Display()
{
    defaultSpriteBatch->Draw();
    //Swap buffers to display the frame
    SDL_GL_SwapWindow(m_Window);
}

void Spite::RenderSystem_SDL::HandleWindowEvent(GR_WindowEvent& e)
{
    switch (e.event) {
    case GR_WINDOWEVENT::WINDOWEVENT_SHOWN:
        //SDL_Log("Window %d shown", e.windowID);
        break;
    case GR_WINDOWEVENT::WINDOWEVENT_HIDDEN:
        //SDL_Log("Window %d hidden", e.windowID);
        break;
    case GR_WINDOWEVENT::WINDOWEVENT_EXPOSED:
        //SDL_Log("Window %d exposed", e.windowID);
        break;
    case GR_WINDOWEVENT::WINDOWEVENT_MOVED:
        /*SDL_Log("Window %d moved to %d,%d",
            e.windowID, e.data1,
            e.data2);*/
        break;
    case GR_WINDOWEVENT::WINDOWEVENT_RESIZED:
        /*SDL_Log("Window %d resized to %dx%d",
            e.windowID, e.data1,
            e.data2);*/
        break;
    case GR_WINDOWEVENT::WINDOWEVENT_SIZE_CHANGED:
        /*SDL_Log("Window %d size changed to %dx%d",
            e.windowID, e.data1,
            e.data2);*/
        break;
    case GR_WINDOWEVENT::WINDOWEVENT_MINIMIZED:
        //SDL_Log("Window %d minimized", e.windowID);
        break;
    case GR_WINDOWEVENT::WINDOWEVENT_MAXIMIZED:
        //SDL_Log("Window %d maximized", e.windowID);
        break;
    case GR_WINDOWEVENT::WINDOWEVENT_RESTORED:
        //SDL_Log("Window %d restored", e.windowID);
        break;
    case GR_WINDOWEVENT::WINDOWEVENT_ENTER:
        /*SDL_Log("Mouse entered window %d",
            e.windowID);*/
        break;
    case GR_WINDOWEVENT::WINDOWEVENT_LEAVE:
        //SDL_Log("Mouse left window %d", e.windowID);
        break;
    case GR_WINDOWEVENT::WINDOWEVENT_FOCUS_GAINED:
        /*SDL_Log("Window %d gained keyboard focus",
            e.windowID);*/
        break;
    case GR_WINDOWEVENT::WINDOWEVENT_FOCUS_LOST:
        /*SDL_Log("Window %d lost keyboard focus",
            e.windowID);*/
        break;
    case GR_WINDOWEVENT::WINDOWEVENT_CLOSE:
        //SDL_Log("Window %d closed", e.windowID);
        break;
    default:
        /*SDL_Log("Window %d got unknown event %d",
            e.windowID, e.event);*/
        break;
    }
}

void Spite::RenderSystem_SDL::SetFullscreen(bool value) {
    SDL_SetWindowFullscreen(m_Window, value ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
}

bool Spite::RenderSystem_SDL::GetFullscreen() {
    return SDL_GetWindowFlags(m_Window) & SDL_WINDOW_FULLSCREEN_DESKTOP;
}

Spite::Camera& Spite::RenderSystem_SDL::Camera() {
    return camera;
}

Spite::SpriteBatch* Spite::RenderSystem_SDL::GetDefaultSpriteBatch() {
    return defaultSpriteBatch.get();
}

glm::vec3& Spite::RenderSystem_SDL::BackgroundColour() {
    return backgroundColour;
}

bool& Spite::RenderSystem_SDL::BlackBars()
{
    return blackBars;
}

std::shared_ptr<Spite::Texture> Spite::RenderSystem_SDL::GetTexture(const std::string& path) {
    //Try and get the existing texture if it is already loaded
    auto it = textures.find(path);
    if(it != textures.end() && !it->second.expired()) {
        return it->second.lock();
    }
    //Load texture from file
    std::shared_ptr<Spite::Texture_GL> texture = std::make_shared<Spite::Texture_GL>();
    texture->LoadFromFile(path);
    //Add to cache
    textures.insert({path, std::weak_ptr(texture)});
    return texture;
}

glm::mat4x4 Spite::RenderSystem_SDL::CalculateCameraMatrix() {
    //Window size
    int w, h;
    SDL_GetWindowSize(m_Window, &w, &h);
    float winAspect = w / (float)h;
    float camAspect = camera.dimensions.x / camera.dimensions.y;
    //View Projection
    glm::mat4 vp = glm::ortho<float>(-1, 1, -1, 1, -1024.0f, 1024.0f);
    if (blackBars) {
        vp = glm::scale(vp, 1.0f / glm::vec3{ camera.dimensions.x * 0.5f, camera.dimensions.y * 0.5f, 1 });
    }
    else {
        if (winAspect > camAspect) {
            vp = glm::scale(vp, 1.0f / glm::vec3{ camera.dimensions.y * winAspect * 0.5f, camera.dimensions.y * 0.5f, 1 });
        }
        else {
            vp = glm::scale(vp, 1.0f / glm::vec3{ camera.dimensions.x * 0.5f, camera.dimensions.x * (1.0f / winAspect) * 0.5f, 1 });
        }
    }
    vp = glm::rotate(vp, camera.rotation, glm::vec3{ 0,0,1 });
    vp = glm::translate(vp, glm::vec3{ -camera.position, 0 });
    return vp;
}

void Spite::RenderSystem_SDL::SetupCameraViewPort(bool blackBars)
{
    int w, h;
    SDL_GetWindowSize(m_Window, &w, &h);
    float winAspect = w / (float)h;
    float camAspect = camera.dimensions.x / camera.dimensions.y;
    if (blackBars) {
        glEnable(GL_SCISSOR_TEST);
        if (winAspect > camAspect) {
            //Side bars
            int bar = (w - camAspect * h) / 2;
            glViewport(bar, 0, w - 2 * bar, h);
            glScissor(bar, 0, w - 2 * bar, h);
        }
        else {
            //Top and bottom bars
            int bar = (h - w / camAspect) / 2;
            glViewport(0, bar, w, h - 2 * bar);
            glScissor(0, bar, w, h - 2 * bar);

        }
    } else {
        glDisable(GL_SCISSOR_TEST);
        glViewport(0, 0, w, h);
    }
}

void Spite::RenderSystem_SDL::SetupFullViewPort()
{
    int w, h;
    SDL_GetWindowSize(m_Window, &w, &h);
    glDisable(GL_SCISSOR_TEST);
    glViewport(0, 0, w, h);
}




