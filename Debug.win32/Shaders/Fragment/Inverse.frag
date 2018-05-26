varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

void main() 
{
	vec4 c = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);
	// float lum = length(texture2D(CC_Texture0, v_texCoord).rgb);

	vec4 inverse = vec4(1.0, 1.0, 1.0, 2.0) - c;
	
	// Restore opacity
	inverse.w = c.w;

	gl_FragColor = inverse;
}