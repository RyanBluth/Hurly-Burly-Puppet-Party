#pragma once

#include <PuppetCharacter.h>

class PuppetTexturePack;

class PuppetCharacterRapunzel : public PuppetCharacter{
public:

	PuppetCharacterRapunzel(bool _ai, Box2DWorld * _world, int16 _categoryBits, int16 _maskBits = -1, int16 _groupIndex = 0);
};