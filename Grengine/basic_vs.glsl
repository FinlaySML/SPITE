#version 430 core
layout (location = 0) in vec2 aPos;

uniform mat4x4 viewProjection;

struct SpriteData {
    vec2 translation;
    vec2 scale;
    float rotation;
    float z;
    vec2 uvOrigin;
    vec2 uvDimension;
};

layout(std430, binding = 1) buffer ssbo1 {
    SpriteData spriteData[]; 
};

out vec2 uv;

void main()
{
    SpriteData data = spriteData[gl_InstanceID];
    gl_Position =  viewProjection * vec4(aPos * data.scale + data.translation, data.z, 1);
    uv = data.uvOrigin + data.uvDimension * (aPos+0.5);
}