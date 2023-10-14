#version 330 core
in vec2 uv;
in vec4 colour;

out vec4 FragColor;

uniform sampler2D tex;

void main()
{
    FragColor = texture(tex, uv) * colour;
} 