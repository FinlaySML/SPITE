#include "pch.h"
#include "SpriteBatch_GL.h"
#include "RenderSystem_SDL.h"

//Vertex data
glm::vec2 spriteVertexData[6] = {
     {-.5f,-.5f},
     { .5f,-.5f},
     {-.5f, .5f},
     {-.5f, .5f},
     { .5f, .5f},
     { .5f,-.5f}
};

unsigned int spriteVAO{0};
unsigned int spriteVBO{0};

unsigned int program{0};
bool programCreationFailed{false};

Spite::Texture_GL texture;

unsigned int LoadShader(std::string path, int shaderType) {
    //https://stackoverflow.com/a/2912614
    std::ifstream ifs(path);
    if (!ifs.is_open()) {
        std::cout << "Could not open file: " + path << std::endl;
        return 0;
    }
    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    const char* pContent = content.c_str();

    unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &pContent, nullptr);
    glCompileShader(shader);
    int i = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &i);
    if (i == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
        std::cout << errorLog.data();
    }
    return shader;
}

Spite::SpriteBatch_GL::SpriteBatch_GL(Spite::RenderSystem_SDL* render) : dataChanged{false}, renderSystem{render} {
    if (programCreationFailed) {
        std::cout << "Can't create sprite batch, shader program creation failed!" << std::endl;
        return;
    }
    if (program == 0) {
        //Shader
        auto vs = LoadShader("sprite_batch_ssbo_vs.glsl", GL_VERTEX_SHADER);
        auto fs = LoadShader("sprite_batch_ssbo_fs.glsl", GL_FRAGMENT_SHADER);
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
            programCreationFailed = true;
        }
        //Validate
        glValidateProgram(program);
        glGetProgramiv(program, GL_VALIDATE_STATUS, &i);
        if (i == GL_FALSE) {
            std::cout << "Program failed validation!" << std::endl;
            programCreationFailed = true;
        }
    }
    if(spriteVAO == 0) {
        //VAO
        glGenVertexArrays(1, &spriteVAO);
        glBindVertexArray(spriteVAO);
        //VBO
        glGenBuffers(1, &spriteVBO);
        glBindBuffer(GL_ARRAY_BUFFER, spriteVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(spriteVertexData), spriteVertexData, GL_STATIC_DRAW);
        //Attributes
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);
        //Unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    if(!texture.IsLoaded()) {
        //Texture
        texture.LoadFromFile("test.png");
    }
    //SSBO
    glGenBuffers(1, &ssbo);
}

Spite::SpriteBatch_GL::~SpriteBatch_GL() {}

void Spite::SpriteBatch_GL::Add(const Sprite& sprite) {
    spriteBatch.push_back({});
    spriteBatch.back().translation = sprite.position;
    spriteBatch.back().scale = sprite.scale;
    spriteBatch.back().rotation = sprite.rotation;
    spriteBatch.back().z = sprite.z;
    spriteBatch.back().colour = sprite.colour;
    dataChanged = true;
}

void Spite::SpriteBatch_GL::Clear() {
    spriteBatch.clear();
    dataChanged = true;
}

void Spite::SpriteBatch_GL::Draw() {
    if (programCreationFailed) {
        return;
    }
    if(spriteBatch.size() == 0) {
        return;
    }
    //Use Program
    glUseProgram(program);
    //Matrix
    auto mat = renderSystem->CalculateCameraMatrix();
    glUniformMatrix4fv(glGetUniformLocation(program, "viewProjection"), 1, GL_FALSE, glm::value_ptr(mat));
    //SSBO
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    if(dataChanged) glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(spriteBatch[0]) * spriteBatch.size(), spriteBatch.data(), GL_STREAM_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, ssbo);
    //Texture
    glBindTexture(GL_TEXTURE_2D, texture.GetHandle());
    //VAO
    glBindVertexArray(spriteVAO);
    //Draw
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, spriteBatch.size());
}