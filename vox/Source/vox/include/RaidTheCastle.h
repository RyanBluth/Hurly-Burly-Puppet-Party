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

	bool camTargetsRemoved;

	PuppetCharacterKnight * playerCharacter1;
	PuppetCharacterKnight * playerCharacter2;
	PuppetCharacterKnight * playerCharacter3;
	PuppetCharacterKnight * playerCharacter4;

	explicit RaidTheCastle(PuppetGame * _game);

	virtual void update(Step * _step) override;
};