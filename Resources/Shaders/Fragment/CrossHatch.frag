varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

float granularity = 64.0;
float stitching_size = 3.0;
float lum1 = 2.0;
float lum2 = 0.7;
float lum3 = 0.5;
float lum4 = 0.3;

void main() 
{
	vec4 c = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);
	vec4 tc = vec4(1.0, 1.0, 1.0, c.w);

	float lum = length(texture2D(CC_Texture0, v_texCoord).rgb);

	if (lum < lum1 && mod(gl_FragCoord.x + gl_FragCoord.y, stitching_size) == 0.0) 
	{
		tc = c;//vec4(0.0, 0.0, 0.0, c.w);
	}  

	if (lum < lum2 && mod(gl_FragCoord.x - gl_FragCoord.y, stitching_size) == 0.0) 
	{
		tc = c;
	}  

	if (lum < lum3 && mod(gl_FragCoord.x + gl_FragCoord.y - granularity, stitching_size) == 0.0) 
	{
		tc = c;
	}  

	if (lum < lum4 && mod(gl_FragCoord.x - gl_FragCoord.y - granularity, stitching_size) == 0.0) 
	{
		tc = c;
	}
  
	gl_FragColor = tc;
}