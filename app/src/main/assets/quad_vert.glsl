#version 310 es

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_texCoord;
layout(location = 3) in float a_texIndex;

uniform mat4 u_viewProjection;

out vec2 v_texCoord;
out vec4 v_color;
out float v_texIndex;

void main()
{
    v_texCoord = a_texCoord;
    v_color = a_color;
    v_texIndex = a_texIndex;

    gl_Position = u_viewProjection * a_position;
}