#pragma once

#include "ResourceManager.h"
#include "Texture.h"

class SoundManager;
class TextureSampler;
class Texture;

class FightYourFriendsResourceManager abstract : public ResourceManager{
public:
	static TextureSampler * splashMessage;
	static Texture * arena1;
	static Texture * arena2Bg;
	static TextureSampler * arena2Fg;

	static void init();
};