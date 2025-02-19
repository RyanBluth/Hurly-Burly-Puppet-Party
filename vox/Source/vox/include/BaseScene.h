#pragma once

#include "Scene.h"

class Sprite;
class Shader;
class MeshInterface;
class MeshEntity;
class DirectionalLight;
class PointLight;
class Material;
class Plane;
class Cube;
class BaseComponentShader;

class BaseScene : public Scene{
public:

	//Entities
	Cube * ground;
	Cube * cube;
	MeshEntity * monkey;

	Sprite * sprite; 

	//Shaders
	BaseComponentShader * shader;
	Shader * renderSurfaceShader;

	//Materials
	Material * material;

	//Lights
	PointLight * pointLight;
	DirectionalLight * keyLight;

	//Meshes
	MeshInterface * monkeyMesh;

	RenderSurface * renderSurface;
	StandardFrameBuffer * frameBuffer;

	explicit BaseScene(Game* _game);
	virtual ~BaseScene();

	virtual void update(Step * _step) override;
	virtual void render(vox::MatrixStack * _matrixStack, RenderOptions * _renderOptions) override;

	virtual void load() override;
	virtual void unload() override;
};