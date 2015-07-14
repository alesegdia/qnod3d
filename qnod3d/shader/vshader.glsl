#ifdef GL_ES
precision mediump int;
precision mediump float;
#endif

uniform mat4 mvp_matrix;
uniform vec2 node_size;

in vec4 a_position;
in vec2 a_texcoord;
in mat4 a_modelMatrix;

varying vec2 v_texcoord;

void main()
{
    a_position.xy = a_position.xy * node_size;
    gl_Position = mvp_matrix * a_position;

    v_texcoord = a_texcoord;
}
