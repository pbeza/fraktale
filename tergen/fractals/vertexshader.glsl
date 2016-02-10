#version 330

in vec4 vertex;
uniform mat4 mvpMatrix;
out vec4 vertex_out;

void main() {
    vertex_out = vertex;
    gl_Position = mvpMatrix * vertex;
}
