#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4x4 viewProjection;
uniform mat4x4 transforms[4];
uniform vec4 uvs[4];

out vec2 uv;

void main()
{
    gl_Position =  viewProjection * transforms[gl_InstanceID] * vec4(aPos, 1);
    uv = uvs[gl_InstanceID].xy + uvs[gl_InstanceID].zw * aPos.xy;
}