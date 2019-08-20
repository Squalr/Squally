#version 330 core

uniform sampler2D image;

out vec4 FragmentColor;

void main(void)
{
	FragmentColor = texelFetch( image, ivec2(gl_FragCoord), 0 );
}
