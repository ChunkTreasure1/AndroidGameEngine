#version 310 es
#extension GL_EXT_gpu_shader5 : require
precision mediump float;

layout(location = 0) out vec4 o_color;

in vec2 v_texCoord;
in vec4 v_color;
in float v_texIndex;

uniform sampler2D u_textures[5];

void main()
{
    o_color = v_color;
}