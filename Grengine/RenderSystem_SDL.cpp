#include "RenderSystem_SDL.h"
#include <iostream>
#include <array>
#include <fstream>
#include <vector>
#include "stb_image.h"

#include <glew.h>
#include <SDL.h>

#include <vec3.hpp>
#include <mat4x4.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

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
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    m_Window = SDL_CreateWindow("My first video game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_ScreenWidth, m_ScreenHeight, SDL_WINDOW_OPENGL);
    if (m_Window == nullptr)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }
}


void DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
        (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
        type, severity, message);
}

int Spite::RenderSystem_SDL::CreateRenderer()
{
    int result = 0;
    if (m_Window == nullptr)
    {
        printf("There is no window!\n");
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
    //Viewport
    int width, height;
    SDL_GetWindowSize(m_Window, &width, &height);
    glViewport(0, 0, width, height);
    //Vertex data
    glm::vec2 vertexData[6] = {
         {0.0f,  0.0f},
         {1.0f,  0.0f},
         {0.0f,  1.0f},
         {0.0f,  1.0f},
         {1.0f,  1.0f},
         {1.0f,  0.0f}
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
    //Texture
    stbi_set_flip_vertically_on_load(true);
    int x, y, n;
    stbi_uc* pixelData = stbi_load("test.png", &x, &y, &n, 3);
    if(pixelData == nullptr) {
        std::cout << "Image failed to load: test.png" << std::endl;
    }
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, pixelData);
    stbi_image_free(pixelData);
    //Window size
    int w, h;
    SDL_GetWindowSize(m_Window, &w, &h);
    float aspect = w/(float)h;
    //Uniforms
    unsigned int viewProjectionLoc = glGetUniformLocation(program, "viewProjection");
    unsigned int transformsLoc = glGetUniformLocation(program, "transforms");
    unsigned int uvOriginsLoc = glGetUniformLocation(program, "uvOrigins");
    unsigned int uvDimensionsLoc = glGetUniformLocation(program, "uvDimensions");
    glm::mat4 vp = glm::ortho<float>(-2* aspect,2*aspect,-2,2);
    glm::mat4 tfs[4] = {
        glm::translate(glm::identity<glm::mat4>(),{ 0.5, 0.5, 0}),
        glm::translate(glm::identity<glm::mat4>(),{-1.5, 0.5, 0}),
        glm::translate(glm::identity<glm::mat4>(),{ 0.5,-1.5, 0}),
        glm::translate(glm::identity<glm::mat4>(),{-1.5,-1.5, 0})
    };
    glm::vec2 uvOrigins[4] = {
        {0,0},
        {0,0},
        {0,0},
        {0,0}
    };
    glm::vec2 uvDimensions[4] = {
        {1,1},
        {1,1},
        {1,1},
        {1,1}
    };
    glUniformMatrix4fv(viewProjectionLoc, 1, GL_FALSE, glm::value_ptr(vp));
    glUniformMatrix4fv(transformsLoc, 4, GL_FALSE, glm::value_ptr(tfs[0]));
    glUniform2fv(uvOriginsLoc, 4, glm::value_ptr(uvOrigins[0]));
    glUniform2fv(uvDimensionsLoc, 4, glm::value_ptr(uvDimensions[0]));
}

void Spite::RenderSystem_SDL::Clear()
{
    glClearColor(1.0f,0.5f,0.5f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Spite::RenderSystem_SDL::Display()
{
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 4);
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


