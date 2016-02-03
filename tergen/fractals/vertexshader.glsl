#version 300 es

precision highp vec4;
precision highp vec3;
precision highp mat4;
precision highp mat3;

in vec4 vertex;
in vec3 normal;
out vec3 vert;
out vec3 vertNormal;
uniform mat4 projMatrix;
uniform mat4 mvMatrix;
uniform mat3 normalMatrix;

void main() {
   vert = vertex.xyz;
   vertNormal = normalMatrix * normal;
   gl_Position = projMatrix * mvMatrix * vertex;
}
