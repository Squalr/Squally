#ifdef GL_ES
precision highp float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform float u_ctime = 1.0f;
uniform float u_gtime = 1.0f;

float easeOutCubic(float t, float b, float c, float d) {
	t /= d;
	t--;
	return c*(t*t*t + 1.0) + b;
}

void main() {
	vec4 tex = texture2D(CC_Texture0, v_texCoord);
	vec4 u_color = vec4(1,1,0,1);
	
	//float cctime = mod(CC_Time[1],1.0);
	float ctime = mod(u_ctime*CC_Time[1],1.0);
	float progress = easeOutCubic(ctime, -2.0, 3.0, u_gtime);
	
	progress += v_texCoord.y;
	
	float diff = v_texCoord.x - progress;
	if (diff <= 0.8 && diff > 0.0) {
		tex = tex + (u_color * diff) * tex.a * u_color.a;
	}
	gl_FragColor = tex * v_fragmentColor;
}