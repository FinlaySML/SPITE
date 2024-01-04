#version 430 core
layout (location = 0) in vec2 aPos;

uniform mat4x4 viewProjection;

struct SpriteData {
    mat3 transform;
    float z;
    vec4 colour;
    vec2 uvOrigin;
    vec2 uvDimension;
};

layout(std430, binding = 1) buffer ssbo1 {
    SpriteData spriteData[]; 
};

out vec2 uv;
out vec4 colour;

void main()
{
    SpriteData data = spriteData[gl_InstanceID];
    vec3 p =  vec3(aPos, 1) * data.transform;
    p /= p.z; 
    gl_Position = viewProjection * vec4(p.xy, data.z, 1);
    uv = (data.uvOrigin + 0.125) + (data.uvDimension - 0.25) * (aPos+0.5);
    colour = data.colour;
}