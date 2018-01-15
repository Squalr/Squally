varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

void main ()
{
  vec4 c = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);
  
  c += texture2D(CC_Texture0, v_texCoord + 0.001);
  c += texture2D(CC_Texture0, v_texCoord + 0.003);
  
  c += texture2D(CC_Texture0, v_texCoord - 0.001);
  c += texture2D(CC_Texture0, v_texCoord - 0.003);

  c = c / 2.5;
  gl_FragColor = c;
}	