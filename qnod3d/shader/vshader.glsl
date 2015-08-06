#version 130

#ifdef GL_ES
precision mediump int;
precision mediump float;
#endif


uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec2 node_size;

in vec4 a_position;
in vec2 a_texcoord;
in mat4 a_modelMatrix;

varying vec2 v_texcoord;

void main()
{
    vec4 pos2 = a_position;
    pos2.xy = a_position.xy * node_size;
    gl_Position = projectionMatrix * viewMatrix * a_modelMatrix * pos2;
    v_texcoord = a_texcoord;
}
