#pragma once

#include "PuppetScene.h"

class MeshEntity;
class Castle;
class Catapult;
class PuppetCharacterCastleChampion;
class PuppetCharacterKnight;

class RaidTheCastle : public PuppetScene{
public:

	MeshEntity * sky;
	Castle * castle;
	Catapult * catapult;
	PuppetCharacterCastleChampion * champion;

	

	PuppetCharacterKnight * playerCharacter;
	PuppetCharacterKnight * playerCharacter2;
	PuppetCharacterKnight * playerCharacter3;
	PuppetCharacterKnight * playerCharacter4;

	explicit RaidTheCastle(PuppetGame * _game);
	~RaidTheCastle();

	virtual void update(Step * _step) override;
	virtual void render(vox::MatrixStack* _matrixStack, RenderOptions* _renderStack) override;
	virtual void load() override;
	virtual void unload() override;

	void loadCatapult();
};