#version 150
#extension GL_ARB_explicit_attrib_location : enable

layout(location = 1) in vec3 aVertexPosition;
layout(location = 2) in vec4 aVertexColor;
layout(location = 3) in vec3 aVertexNormals;
layout(location = 4) in vec2 aVertexUVs; 

uniform mat4 MVP;
uniform mat4 depthMVP;

out vec3 fragVertGeo;
out vec3 fragNormalGeo;
out vec4 fragColorGeo;
out vec2 fragUVGeo;
out vec4 shadowCoordIn;

void main(){
	fragVertGeo = aVertexPosition;
	fragNormalGeo = aVertexNormals;
	fragColorGeo = aVertexColor;
	fragUVGeo = aVertexUVs;
	gl_Position = vec4(aVertexPosition, 1.0);
	shadowCoordIn = depthMVP * vec4(aVertexPosition, 1);
}