varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

void main ()
{
	vec4 c = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);
  
  c += texture2D(CC_Texture0, v_texCoord + 0.001);
  c += texture2D(CC_Texture0, v_texCoord + 0.003);
  c += texture2D(CC_Texture0, v_texCoord + 0.005);
  c += texture2D(CC_Texture0, v_texCoord + 0.007);
  c += texture2D(CC_Texture0, v_texCoord + 0.009);
  c += texture2D(CC_Texture0, v_texCoord + 0.011);
  
  c += texture2D(CC_Texture0, v_texCoord - 0.001);
  c += texture2D(CC_Texture0, v_texCoord - 0.003);
  c += texture2D(CC_Texture0, v_texCoord - 0.005);
  c += texture2D(CC_Texture0, v_texCoord - 0.007);
  c += texture2D(CC_Texture0, v_texCoord - 0.009);
  c += texture2D(CC_Texture0, v_texCoord - 0.011);

  c = c / 9.5;
  c.rgb = vec3((c.r+c.g+c.b)/3.0);
  gl_FragColor = c;
}	