#version 110
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect posTexture;
uniform sampler2DRect velTexture;
uniform float bound;
varying vec2 uv;

void main()
{
	vec3 pos = texture2DRect( posTexture, uv).xyz;
	vec3 vel = texture2DRect( velTexture, uv).xyz;
	
	pos += vel;
	
//	if (pos.x > bound) {
//		pos.x = -bound;
//	}
	
	if (pos.y > bound) {
		pos.y = -bound;
	}
//	
//	if (pos.z > bound) {
//		pos.z = -bound;
//	}
//	
//	if (pos.x < -bound) {
//		pos.x = bound;
//	}
//	
//	if (pos.y < -bound) {
//		pos.y = bound;
//	}
//	
//	if (pos.z < -bound) {
//		pos.z = bound;
//	}
	
   	gl_FragColor = vec4(pos, 1.0);
}