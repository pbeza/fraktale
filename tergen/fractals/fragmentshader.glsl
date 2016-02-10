#version 330

out vec4 fragColor;
in vec4 vertex_out;

void main() {
   fragColor = vec4(vertex_out.z, 0.0, 0.0, 1.0);
}
