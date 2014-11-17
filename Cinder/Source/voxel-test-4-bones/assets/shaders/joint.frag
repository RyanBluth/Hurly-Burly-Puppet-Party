#version 120

uniform vec3 pickingColor;

varying vec3 faceNormals;
varying vec3 vVertexPosition;

uniform vec3 camEye;

void main(){		
	// write final color in first color target 
	gl_FragData[0] = gl_Color;

	// write picking color code in second color target
	gl_FragData[1] = vec4(pickingColor, 1.0);
	
	// write normals in third color target
	gl_FragData[2] = vec4(faceNormals,1.0);
	
	// write position in fourth color target
	//gl_FragData[3] = vec4(vVertexPosition, 1.0f);
	gl_FragData[3] = vec4(0.5f*vVertexPosition+0.5f, 1.0f);
}