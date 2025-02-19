#pragma once 

#include "shader/ShaderComponentDiffuse.h"
#include "shader/ShaderVariables.h"
#include "MatrixStack.h"
#include "RenderOptions.h"
#include "shader/SharedComponentShaderMethods.h"

ShaderComponentDiffuse::ShaderComponentDiffuse(Shader * _shader) :
	ShaderComponent(_shader)
{
}

ShaderComponentDiffuse::~ShaderComponentDiffuse(){
}

std::string ShaderComponentDiffuse::getVertexVariablesString(){
	return DEFINE + SHADER_COMPONENT_DIFFUSE + ENDL;
}

std::string ShaderComponentDiffuse::getFragmentVariablesString(){
	return 
		DEFINE + SHADER_COMPONENT_DIFFUSE + ENDL +
		SHADER_INCLUDE_LIGHT;
}

std::string ShaderComponentDiffuse::getVertexBodyString(){
	return EMPTY;
}

std::string ShaderComponentDiffuse::getFragmentBodyString(){
	return
		IF_NOT_DEFINED + SHADER_COMPONENT_BLINN + ENDL +
		IF_NOT_DEFINED + SHADER_COMPONENT_PHONG + ENDL + 
		"mat3 normalMatrix = transpose(inverse(mat3(model)))" + SEMI_ENDL +
		"vec3 normal = normalize(normalMatrix * fragNormal)" + SEMI_ENDL +
		"vec3 fragWorldPosition = vec3(model * vec4(fragVert, 1))" + SEMI_ENDL +
		"float brightness = 0" + SEMI_ENDL +
		"vec3 outIntensities = vec3(0,0,0)" + SEMI_ENDL +

		"for(int i = 0; i < numLights; i++){" + ENDL +
			"vec3 surfaceToLight = lights[i].position - fragWorldPosition" + SEMI_ENDL +
			"brightness += dot(normal, surfaceToLight) / (length(surfaceToLight) * length(normal))" + SEMI_ENDL +
			"outIntensities += vec3(lights[i].intensities)" + SEMI_ENDL +
		"}" + ENDL +

		"brightness = clamp(brightness, 0.1, 1)" + SEMI_ENDL + 
		END_IF + ENDL +
		END_IF + ENDL;
}

std::string ShaderComponentDiffuse::getOutColorMod(){
	return 
		IF_NOT_DEFINED + SHADER_COMPONENT_BLINN + ENDL +
		IF_NOT_DEFINED + SHADER_COMPONENT_PHONG + ENDL + 
		GL_OUT_OUT_COLOR + " *= vec4(vec3(outIntensities), 1) * vec4(brightness, brightness, brightness, 1)" + SEMI_ENDL +
		END_IF + ENDL + 
		END_IF + ENDL;
}

void ShaderComponentDiffuse::configureUniforms(vox::MatrixStack* _matrixStack, RenderOptions* _renderOption, NodeRenderable* _nodeRenderable){
	SharedComponentShaderMethods::configureLights(_matrixStack, _renderOption, _nodeRenderable);
}

