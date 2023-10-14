#version 430 core
layout (location = 0) in vec2 aPos;

uniform mat4x4 viewProjection;

struct SpriteData {
    vec2 translation;
    vec2 scale;
    float rotation;
    float z;
    vec2 padding;
    vec2 uvOrigin;
    vec2 uvDimension;
    vec4 colour;
};

layout(std430, binding = 1) buffer ssbo1 {
    SpriteData spriteData[]; 
};

out vec2 uv;
out vec4 colour;

void main()
{
    SpriteData data = spriteData[gl_InstanceID];
    vec2 p = aPos * data.scale;
    p = vec2(p.x*cos(data.rotation)+p.y*sin(data.rotation), p.y*cos(data.rotation)-p.x*sin(data.rotation));
    gl_Position =  viewProjection * vec4(p + data.translation, data.z, 1);
    uv = data.uvOrigin + data.uvDimension * (aPos+0.5);
    colour = data.colour;
}