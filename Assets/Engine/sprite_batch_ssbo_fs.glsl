#version 330 core
in vec2 uv;
in vec4 colour;

out vec4 FragColor;

uniform sampler2D tex;

void main()
{
    vec4 c = texelFetch(tex, ivec2(uv), 0) * colour;
    if(c.a < 0.1) {
        discard;
    }
    FragColor = c;
} 