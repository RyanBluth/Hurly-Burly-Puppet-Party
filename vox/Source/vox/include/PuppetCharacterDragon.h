#pragma once

#include <PuppetCharacter.h>

class ParticleSystem;
class PuppetTexturePack;

class PuppetCharacterDragon : public PuppetCharacter{
public:
	Item * fireball;
	PuppetCharacter * playerOnFire;
	ParticleSystem * fireParticles;
	float altitude;

	PuppetCharacterDragon(bool _ai, Box2DWorld * _world, int16 _categoryBits, int16 _maskBits = -1, int16 _groupIndex = 0);
	virtual PuppetCharacter * clone(Box2DWorld * _world, PuppetScene * _scene) override;

	void render(vox::MatrixStack* _matrixStack, RenderOptions* _renderOptions) override;
	void update(Step * _step) override;
    void action(bool _forceDrop = false) override;
	void pickupItem(Item * _item) override;

	void die() override;

	virtual void setShader(Shader * _shader, bool _default) override;
};