#pragma once

#include <ResourceManager.h>

class SoundManager;
class Texture;
class TextureSampler;

class PuppetResourceManager abstract : public ResourceManager{
public:	
	static Texture * startupSplash;

	static Texture * blank;
	static TextureSampler * itemNone;
	static Texture * stageFloor;
	static Texture * sky;
	static TextureSampler * paper;
	static Texture * tree1; 
	static Texture * tree2;	
	static Texture * bush1;
	static Texture * bush2;

	static Texture * cloud1;
	static Texture * cloud2;
	static Texture * cloud3;
	static Texture * cloud4;
	
	static TextureSampler * dustParticle;
	static std::vector<TextureSampler *> scoreParticles;
	static TextureSampler * getRandomScoreParticles();

	static TextureSampler * head1;
	static std::vector<TextureSampler *> faces;
	static TextureSampler * hand1;
	static TextureSampler * getRandomFace();
	
	static TextureSampler * countDown0;
	static TextureSampler * countDown1;
	static TextureSampler * countDown2;
	static TextureSampler * countDown3;
	static TextureSampler * countDown4;
	static TextureSampler * countDown5;
	
	static std::vector<TextureSampler *> indicators;
	
	//static TextureSampler * redWins;
	//static TextureSampler * yellowWins;
	//static TextureSampler * greenWins;
	//static TextureSampler * blueWins;
	static std::vector<TextureSampler *> winSplashes;

	static SoundManager * jumpSounds;
	static SoundManager * hitSounds;
	static SoundManager * splashSounds;
	static SoundManager * cheerSounds;
	static SoundManager * fallingSounds;
	
	static void init();
};