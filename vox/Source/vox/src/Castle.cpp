#pragma once

#include "Castle.h"
#include <Box2DSprite.h>
#include "MeshInterface.h"
#include <Texture.h>
#include <TextureSampler.h>
#include "Box2DWorld.h"
#include "Boulder.h"
#include "PuppetScene.h"
#include "SpriteSheet.h"
#include "SpriteSheetAnimation.h"
#include <iostream>
#include <SoundManager.h>

#include <RaidTheCastleResourceManager.h>

Castle::Castle(Box2DWorld* _world, int16 _categoryBits, int16 _maskBits, int16 _groupIndex):
	StructureBreakable(100.f, _world, _categoryBits, _maskBits, _groupIndex)
{
	componentScale = 0.03f;
	
	TextureSampler * baseTex = RaidTheCastleResourceManager::castleBase;
	Texture * baseSpriteSheetTex = RaidTheCastleResourceManager::castleSpriteSheet;

	rootComponent = new Box2DSprite(_world, baseTex, b2_staticBody, false, nullptr, componentScale);
	components.push_back(&rootComponent);
	
	b2Filter sf;
	sf.categoryBits = categoryBits;
	if(maskBits != (int16)-1){
		sf.maskBits = maskBits;
	}
	sf.groupIndex = groupIndex;
	for(Box2DSprite ** c : components){
		b2Fixture * f = (*c)->createFixture(sf);
		f->SetSensor(true);
	}

	setUserData(this);
	
	rootComponent->mesh->popTexture2D();
	spriteSheet = new SpriteSheetAnimation(baseSpriteSheetTex, 0);

	// sprite sheet animation
	spriteSheet->pushFramesInRange(0, 3, baseTex->width, baseTex->height, baseSpriteSheetTex->width);
	rootComponent->addAnimation("castleStates", spriteSheet, true);
	rootComponent->setTranslationPhysical(0.f, rootComponent->getCorrectedHeight(), 0.f);
	rootComponent->mesh->uvEdgeMode = GL_MIRRORED_REPEAT_ARB;

	for(unsigned long int i = 0; i < rootComponent->mesh->vertices.size(); ++i){
		rootComponent->mesh->vertices.at(i).x *= 1.1f;
		rootComponent->mesh->vertices.at(i).y *= 1.1f;
	}
}

Castle::~Castle(){
	delete spriteSheet;
}


void Castle::takeDamage(float _damage){
	RaidTheCastleResourceManager::catapultHitSounds->playRandomSound();
	StructureBreakable::takeDamage(_damage);
	switch (state){
	default:
	case StructureBreakable::kNORMAL:
		rootComponent->currentAnimation->currentFrame = 0;
		break;
	case StructureBreakable::kDAMAGED:
		rootComponent->currentAnimation->currentFrame = 1;
		break;
	case StructureBreakable::kDEAD:
		rootComponent->currentAnimation->currentFrame = 3;
		break;
	}
}