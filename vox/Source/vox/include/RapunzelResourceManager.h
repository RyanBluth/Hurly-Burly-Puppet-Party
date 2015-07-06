#pragma once

#include "ResourceManager.h"
#include "Texture.h"

class TextureSampler;
class Texture;
class SoundManager;

class RapunzelResourceManager abstract : public ResourceManager{
public:
	static TextureSampler * splashMessage;
	
	static Texture * goldSpriteSheet;
	static TextureSampler * goldBrick;
	
	static TextureSampler * glove;
	static TextureSampler * spring;
	static TextureSampler * itemSpear;

	static TextureSampler * leverHandle;
	static TextureSampler * leverBase;

	static TextureSampler * towerBackground;
	static TextureSampler * towerCatwalk;	
	static TextureSampler * towerTower;

	static TextureSampler * hair;
	static TextureSampler * hairLink;
	static TextureSampler * hairEnd;
	
	static TextureSampler * thiefTorso;
	static TextureSampler * thiefArm;
	static TextureSampler * thiefHelmet;

	static TextureSampler * rapunzelTorso;
	static TextureSampler * rapunzelArm;
	static TextureSampler * rapunzelHelmet;
	
	static TextureSampler * guard1Torso;
	static TextureSampler * guard1Arm;
	static TextureSampler * guard1Helmet;
	static TextureSampler * guard2Torso;
	static TextureSampler * guard2Arm;
	static TextureSampler * guard2Helmet;

	
	static SoundManager * gloveSounds;
	static SoundManager * spearSounds;
	static SoundManager * tauntSounds;
	
	static void init();
};