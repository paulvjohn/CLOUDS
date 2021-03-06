#version 120
#extension GL_ARB_texture_rectangle : enable

uniform vec4 fogColor;
uniform float fogDist;
uniform float useFog;
uniform float fogExpo;

uniform float edgeSmoothing;
uniform vec4 edgeColor;
uniform vec4 fillColor;
uniform vec4 specularColor;

uniform vec4 groundColor;// = vec4( .4, 1., .6, 1.);
uniform vec4 undergroundColor;// = vec4( .6 ,.2, .1, 1.);
uniform vec4 cloudShadowColor;
uniform float cloudShadow;

uniform float specExpo;
uniform float specScale;

uniform float drawCenters;
uniform float noiseCutoff;
uniform float edgeThreshold;

varying vec3 vertex;
varying vec3 vNormal;

varying float nScl;

varying vec4 color;
varying vec3 norm;
varying vec3 ePos;
varying vec2 uv;

varying float camDelta;
varying float doDiscard;
varying float isGround;
varying float isCloud;

varying vec4 groundSample;
varying float underSky;


float mapLinear( float x, float a1, float a2, float b1, float b2 ) {
	return b1 + ( x - a1 ) * ( b2 - b1 ) / ( a2 - a1 );
}

void main(void)
{
	//cull boxes based on noise and camera distance
	if( doDiscard > .5)	discard;
	
	//normal rendering
	vec3 normal = normalize(norm);
	float fr = pow( abs(dot( ePos, normal )) * specScale, specExpo);
	
	gl_FragColor = mix( specularColor, groundSample, fr);
	
	if( isGround > .5)
	{
		if(vNormal.y > .5)
		{
			gl_FragColor *= groundColor;
		}
		else{
			gl_FragColor *= mix(undergroundColor, groundColor, pow(max( vertex.y*1.5, 0. ), 2.) );
		}
		
		if(underSky>.5){
			gl_FragColor = mix( gl_FragColor, cloudShadowColor, cloudShadow);
		}
	}
	
	else if( isCloud > .5)
	{
		gl_FragColor = fogColor * fr;
	}
	
	
	//fog
	if(useFog > .5)
	{
		gl_FragColor = mix( gl_FragColor, fogColor, min(1., pow( 1.25 * camDelta / (fogDist*fogDist), fogExpo) ) );
	}
}

