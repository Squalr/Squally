varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform float luminanceThreshold = 0.2;
uniform float colorAmplification= 8.0;

void main ()
{
	vec4 originalColor = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);
	vec4 finalColor;
	
	vec3 c = texture2D(CC_Texture0, v_texCoord).rgb;

	float lum = dot(vec3(0.30, 0.59, 0.11), c);
	
	if (lum < luminanceThreshold)
	{
		c *= colorAmplification; 
	}
	
	vec3 visionColor = vec3(0.1, 0.95, 0.2);
	finalColor.rgb = c * visionColor;
	
	// Removes very dark colors
	if (abs(finalColor.r - finalColor.g) < 0.2 && abs(finalColor.g - finalColor.b) < 0.2 && abs(finalColor.b - finalColor.r) < 0.2)
	{
		//finalColor.r = 0.0;
		//finalColor.g = 1.0;
		//finalColor.b = 0.0;
	}
	
	// Removes very light colors
	if (abs(finalColor.r - finalColor.g) > 0.8 && abs(finalColor.g - finalColor.b) < 0.8 && abs(finalColor.b - finalColor.r) < 0.8)
	{
		//finalColor.r = 0.0;
		//finalColor.g = 1.0;
		//finalColor.b = 0.0;
	}
	
	gl_FragColor.rgb = finalColor.rgb;
	gl_FragColor.a = originalColor.w;
}	