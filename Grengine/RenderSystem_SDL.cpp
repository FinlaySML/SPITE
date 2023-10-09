#include "pch.h"
#include "RenderSystem_SDL.h"

//We're globally instancing our subsystems!
//But maybe you think Globals are bad
//There might be other ways to approach this.
#ifdef RENDERSYSTEM_SDL
    Spite::RenderSystem_SDL grRenderSystemSDL;
    Spite::RenderSystem* Spite::render = &grRenderSystemSDL;
#endif

Spite::RenderSystem_SDL::RenderSystem_SDL() : camera{glm::vec2{0, 0}}, backgroundColour{0,0,0}
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
    m_Window = SDL_CreateWindow("My first video game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_ScreenWidth, m_ScreenHeight, SDL_WINDOW_OPENGL);
    if (m_Window == nullptr)
    {
        std::cout << std::format("Window could not be created! SDL_Error: {}", SDL_GetError()) << std::endl;
        return -1;
    }
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
    //Texture
    testTexture.LoadFromFile("test.png");
    //Viewport
    int width, height;
    SDL_GetWindowSize(m_Window, &width, &height);
    glViewport(0, 0, width, height);
    //Vertex data
    glm::vec2 vertexData[6] = {
         {-.5f,-.5f},
         { .5f,-.5f},
         {-.5f, .5f},
         {-.5f, .5f},
         { .5f, .5f},
         { .5f,-.5f}
    };
    //VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    //VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    //Attributes
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    //Shader
    auto vs = LoadShader("basic_vs.glsl", GL_VERTEX_SHADER);
    auto fs = LoadShader("basic_fs.glsl", GL_FRAGMENT_SHADER);
    program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glDeleteShader(vs);
    glDeleteShader(fs);
    //Link
    int i = 0;
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &i);
    if (i == GL_FALSE) {
        std::cout << "Program failed linking!" << std::endl;
    }
    //Validate
    glValidateProgram(program);
    glGetProgramiv(program, GL_VALIDATE_STATUS, &i);
    if(i == GL_FALSE) {
        std::cout << "Program failed validation!" << std::endl;
    }
    //GLint textureLoc = glGetUniformLocation(program, "texture");
    //Use Program
    glUseProgram(program);
    //Uniforms
    viewProjectionLoc = glGetUniformLocation(program, "viewProjection");
    //ssbo
    GLuint ssbo;
    glGenBuffers(1, &ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, ssbo);
}

void Spite::RenderSystem_SDL::Clear()
{
    glClearColor(backgroundColour.r, backgroundColour.g, backgroundColour.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    spriteBatch.clear();
}

void Spite::RenderSystem_SDL::DrawSprite(const Sprite& sprite) {
    spriteBatch.push_back({});
    spriteBatch.back().translation = sprite.position;
    spriteBatch.back().scale = sprite.scale;
    spriteBatch.back().rotation = sprite.rotation;
    spriteBatch.back().z = sprite.z;
}

void Spite::RenderSystem_SDL::Display()
{
    //Window size
    int w, h;
    SDL_GetWindowSize(m_Window, &w, &h);
    float aspect = w / (float)h;
    //View Projection
    glm::mat4 vp = glm::ortho<float>(-aspect, aspect, -1, 1);
    vp = glm::scale(vp, glm::vec3{2/camera.unitHeight});
    vp = glm::rotate(vp, camera.rotation, glm::vec3{0,0,1});
    vp = glm::translate(vp, glm::vec3{-camera.position, 0});
    glUniformMatrix4fv(viewProjectionLoc, 1, GL_FALSE, glm::value_ptr(vp));
    //Send sprite data to GPU
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(spriteBatch[0]) * spriteBatch.size(), spriteBatch.data(), GL_STREAM_DRAW);
    //Bind Texture
    glBindTexture(GL_TEXTURE_2D, testTexture.GetHandle());
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, spriteBatch.size());
    //Swap buffers to display the frame
    SDL_GL_SwapWindow(m_Window);
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

Spite::Camera& Spite::RenderSystem_SDL::Camera() {
    return camera;
}

glm::vec3& Spite::RenderSystem_SDL::BackgroundColour() {
    return backgroundColour;
}

unsigned int Spite::RenderSystem_SDL::LoadShader(std::string path, int shaderType) {
    //https://stackoverflow.com/a/2912614
    std::ifstream ifs(path);
    if(!ifs.is_open()) {
        std::cout << "Could not open file: " + path << std::endl;
    }
    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    const char* pContent = content.c_str();

    unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &pContent, nullptr);
    glCompileShader(shader);
    int i = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &i);
    if(i == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
        std::cout << errorLog.data();
    }
    return shader;
}


