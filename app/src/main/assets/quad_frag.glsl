#version 310 es
#extension GL_EXT_gpu_shader5 : require

layout(location = 0) out vec4 color;

in vec2 v_texCoord;
in vec4 v_color;
in float v_texIndex;

precision mediump float;

uniform sampler2D u_texture;

void main()
{
    color = texture(u_textures[int(v_texIndex)], v_texCoord) * v_color;
}