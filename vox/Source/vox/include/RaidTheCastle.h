#pragma once

#include "PuppetScene.h"

class MeshEntity;
class Castle;
class Catapult;

class RaidTheCastle : public PuppetScene{
public:

	MeshEntity * sky;
	Castle * castle;
	Catapult * catapult;

	explicit RaidTheCastle(Game * _game);
	~RaidTheCastle();

	virtual void update(Step * _step) override;
	virtual void render(vox::MatrixStack* _matrixStack, RenderOptions* _renderStack) override;
	virtual void load() override;
	virtual void unload() override;

	void loadCatapult();
};