varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
//CC_Time[1] is time

void main()
{
	vec4 c = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);
	
	c = (c + vec4(0.07, 0.07, 0.07, 0.0)) * vec4(1.6,abs(cos(CC_Time[1])), abs(sin(CC_Time[1])), 1.0);
	
	gl_FragColor = c;
}
