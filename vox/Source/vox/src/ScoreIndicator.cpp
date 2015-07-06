#pragma once

#include <ScoreIndicator.h>
#include <PuppetResourceManager.h>
#include <MeshInterface.h>
#include <TextureSampler.h>
#include <shader\ComponentShaderBase.h>
#include <shader\ShaderComponentHsv.h>
#include <RenderOptions.h>
#include <ParticleSystem.h>

ScoreIndicator::ScoreIndicator(unsigned long int _id, Box2DWorld * _world) :
	id(_id),
	scoreParticles(new ParticleSystem(PuppetResourceManager::scoreParticles.at(0), _world, 0, 0, 0))
{
	float pixels = 100;

	 // this might be wrong
	childTransform->scale(pixels, pixels, 1);
	childTransform->translate((3.5f-id) * 1920.f*0.25f, pixels*1.1f, 10.f);

	mesh->pushTexture2D(PuppetResourceManager::scoreIndicators.at(id));
}

ScoreIndicator::~ScoreIndicator(){
	delete scoreParticles;
}

void ScoreIndicator::render(vox::MatrixStack* _matrixStack, RenderOptions* _renderOptions){
	ShaderComponentHsv * hsvShader = static_cast<ShaderComponentHsv *>(static_cast<ComponentShaderBase *>(getShader())->getComponentAt(1));
	float hue = hsvShader->getHue();
	float sat = hsvShader->getSaturation();
	float newHue = hue, newSat = 1;
	if(id == 0){
		newSat = 1 + 0.8f;
		newHue = 0.125f;
	}else if(id == 1){
		newHue = 0.3056f;
	}else if(id == 2){
		newHue = 0.64f;
		newSat = 1 +0.55f;
	}else if(id == 3){
		newHue = 0.f;
	}

	// change the shader settings based player id
	hsvShader->setHue(newHue);
	hsvShader->setSaturation(newSat);

	Sprite::render(_matrixStack, _renderOptions);
	scoreParticles->render(_matrixStack, _renderOptions);
	
	// revert the shader settings
	hsvShader->setHue(hue);
	hsvShader->setSaturation(sat);
}

void ScoreIndicator::update(Step * _step){
	Sprite::update(_step);
	scoreParticles->update(_step);
}
void ScoreIndicator::setShader(Shader * _shader, bool _configure){
	Sprite::setShader(_shader, _configure);
	scoreParticles->setShader(_shader, _configure);
}

void ScoreIndicator::load(){
	Sprite::load();
	scoreParticles->load();
}

void ScoreIndicator::unload(){
	Sprite::unload();
	scoreParticles->unload();
}