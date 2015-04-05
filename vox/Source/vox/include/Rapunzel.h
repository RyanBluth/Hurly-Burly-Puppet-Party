#pragma once

#include "PuppetScene.h"

#define RAPUNZEL_GHOST_HEIGHT 12.0f

class StructureGoldPile;
class MeshEntity;
class Lever;
class PuppetCharacterGuard;
class PuppetCharacterThief;
class PuppetCharacterRapunzel;
class StructureBoxingGlove;
class ItemGold;

class Rapunzel : public PuppetScene{
public:

	MeshEntity * sky;
	
	Box2DSprite * castleCatwalk;
	Box2DSprite * tower;

	Lever * lever1;
	Lever * lever2;
	Lever * lever3;
	StructureGoldPile * goldPile;
	PuppetCharacterGuard * guard;

	PuppetCharacterThief * playerCharacter1;
	PuppetCharacterThief * playerCharacter2;
	PuppetCharacterThief * playerCharacter3;
	PuppetCharacterRapunzel * playerCharacter4;

	StructureBoxingGlove * glove;

	explicit Rapunzel(PuppetGame * _game);
	~Rapunzel();

	virtual void update(Step * _step) override;
	virtual void render(vox::MatrixStack* _matrixStack, RenderOptions* _renderOptions) override;
	virtual void load() override;
	virtual void unload() override;
};