#version 330 core

in vec2 VertexPosition;

void main(void) {
	gl_Position = vec4(VertexPosition, 0.0, 1.0);
}
