#ifdef GL_ES
precision mediump float;
#endif

varying vec2 v_texCoord;
varying vec4 v_fragmentColor;

void main(void)
{
	vec2 texCoord = v_texCoord;
	texCoord.x += 0.01 * sin(10.0 * texCoord.y + CC_Time[0] * 15.0);

	gl_FragColor = v_fragmentColor * texture2D(CC_Texture0, texCoord);
}
