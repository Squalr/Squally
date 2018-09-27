#ifdef GL_ES
precision mediump float;
#endif
uniform sampler2D u_texture;
varying vec2 v_texCoord;
varying vec4 v_fragmentColor;
uniform vec4 u_paramColor;

void main(void)
{
	float gray = dot(texture2D(u_texture, v_texCoord).rgba,u_paramColor.rgba);
	gl_FragColor = vec4(gray,gray,gray,1.0);
}