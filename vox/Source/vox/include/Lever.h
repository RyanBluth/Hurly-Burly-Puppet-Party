#pragma once

#include <StructureInteractable.h>

class Lever : public StructureInteractable{
public:
	bool pullingLever;
	float cooldownCnt;
	
	static glm::vec3 towerPos;

	Box2DSprite * base;
	Box2DSprite * handle;
	int type;

	Lever(Box2DWorld* _world, int16 _categoryBits, int16 _maskBits, int16 _groupIndex);
	
	void evaluateState() override;
	void actuallyInteract() override;
};