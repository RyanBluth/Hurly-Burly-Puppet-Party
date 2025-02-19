#pragma once 

#include "ShaderComponent.h"

class ShaderComponentDiffuse : public ShaderComponent{
public:
	ShaderComponentDiffuse(Shader * _shader);
	~ShaderComponentDiffuse() override;
	std::string getVertexVariablesString() override;
	std::string getFragmentVariablesString() override;
	std::string getVertexBodyString() override;
	std::string getFragmentBodyString() override;
	std::string getOutColorMod() override;
	void configureUniforms(vox::MatrixStack* _matrixStack, RenderOptions* _renderOption, NodeRenderable* _nodeRenderable) override;
};