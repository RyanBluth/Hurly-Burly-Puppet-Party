#pragma once

#include <Box2DSuperSprite.h>
#include <Box2DSprite.h>

#include "PuppetGame.h"

class PuppetCharacter;

class Item : public Box2DSuperSprite {
public:
	float damage;
	float handleX;
	float handleY;

	// Whether the item is destroyed after the first throw
	bool singleUse;

	// Whether the item is currently held by a character
	bool held;

	// Owner of the item if held
	PuppetCharacter * owner;

	// Whether the item has been thrown and has not landed yet
	bool thrown;

	// Whether the item should be destroyed in the next update
	bool destroy;

	explicit Item(bool _singleUse, Box2DWorld * _world, int16 _categoryBits = PuppetGame::kITEM, int16 _maskBits = -1, int16 _groupIndex = 0, float _damage = 0, float _handleX = 0.f, float _handleY = 0.f);
	~Item();

	virtual void hitStructure();
	virtual void hitPlayer();
	virtual void hitGround();
	
	b2WeldJoint * playerJoint;
	// for a default item, this will destroy the player's item joint and return the item itself
    virtual Item * getProjectile(bool _forceDrop);
};