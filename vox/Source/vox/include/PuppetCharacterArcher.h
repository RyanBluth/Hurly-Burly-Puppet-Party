#pragma once

#include <PuppetCharacter.h>

class PuppetTexturePack;

class PuppetCharacterArcher : public PuppetCharacter{
public:
	bool onFire;
	PuppetCharacterArcher(bool _ai, Box2DWorld * _world, int16 _categoryBits, int16 _maskBits = -1, int16 _groupIndex = 0);

	void update(Step * _step) override;
};