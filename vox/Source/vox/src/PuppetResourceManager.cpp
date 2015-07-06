#pragma once

#include <PuppetResourceManager.h>
#include <Texture.h>
#include <Box2DSuperSprite.h>
#include <RaidTheCastleResourceManager.h>
#include <RapunzelResourceManager.h>
#include <SlayTheDragonResourceManager.h>
#include <FightYourFriendsResourceManager.h>
#include <SoundManager.h>
#include <TextureSampler.h>
#include <NumberUtils.h>

Scenario * PuppetResourceManager::puppetScenario = new Scenario("../assets/puppetScenario.json");

Texture * PuppetResourceManager::startupSplash = new Texture("../assets/hurly-burly/SplashMessages/Startup.png", 2096, 2096, true, false);
Texture * PuppetResourceManager::blank = new Texture("../assets/hurly-burly/blank.png", 1, 1, true, false);
TextureSampler * PuppetResourceManager::itemNone = new TextureSampler(new Texture("../assets/hurly-burly/blank.png", 1, 1, true, false), 1, 1);

Texture * PuppetResourceManager::stageFloor = new Texture("../assets/hurly-burly/StageFloor.png", 1024, 1024, true, false);
Texture * PuppetResourceManager::stageFront = new Texture("../assets/hurly-burly/StageFront.png", 1024, 1024, true, false);
Texture * PuppetResourceManager::sky		= new Texture("../assets/hurly-burly/Sky.png", 1024, 1024, true, false);

Texture * PuppetResourceManager::tree1  = new Texture("../assets/hurly-burly/Foliage/Tree1.png", 1024, 1024, true, false);
Texture * PuppetResourceManager::tree2	= new Texture("../assets/hurly-burly/Foliage/Tree2.png", 1024, 1024, true, false);
Texture * PuppetResourceManager::bush1	= new Texture("../assets/hurly-burly/Foliage/Bush1.png", 1024, 1024, true, false);
Texture * PuppetResourceManager::bush2	= new Texture("../assets/hurly-burly/Foliage/Bush2.png", 1024, 1024, true, false);
Texture * PuppetResourceManager::sun	= new Texture("../assets/hurly-burly/Sun.png", 1024, 1024, true, false);

Texture * PuppetResourceManager::cloud1 = new Texture("../assets/hurly-burly/Clouds/Cloud1.png", 1024, 1024, true, false);
Texture * PuppetResourceManager::cloud2 = new Texture("../assets/hurly-burly/Clouds/Cloud2.png", 1024, 1024, true, false);
Texture * PuppetResourceManager::cloud3 = new Texture("../assets/hurly-burly/Clouds/Cloud3.png", 1024, 1024, true, false);
Texture * PuppetResourceManager::cloud4 = new Texture("../assets/hurly-burly/Clouds/Cloud4.png", 1024, 1024, true, false);


TextureSampler * PuppetResourceManager::stageCurtain		= new TextureSampler("../assets/hurly-burly/StageAssets/", "curtain.png.def", false);
TextureSampler * PuppetResourceManager::stageCurtainCenter	= new TextureSampler("../assets/hurly-burly/StageAssets/", "curtainCenter.png.def", false);
TextureSampler * PuppetResourceManager::stageCurtainTop		= new TextureSampler("../assets/hurly-burly/StageAssets/", "topCurtain.png.def", false);
TextureSampler * PuppetResourceManager::stageSpotlight		= new TextureSampler("../assets/hurly-burly/StageAssets/", "spotlight.png.def", false);

TextureSampler * PuppetResourceManager::dustParticle = new TextureSampler("../assets/hurly-burly/", "dustParticle.png.def", false);
std::vector<TextureSampler *> PuppetResourceManager::scoreParticles;

TextureSampler * PuppetResourceManager::head = new TextureSampler("../assets/hurly-burly/", "Head1.png.def", false); 
TextureSampler * PuppetResourceManager::hand = new TextureSampler("../assets/hurly-burly/", "Hand1.png.def", false);
TextureSampler * PuppetResourceManager::popsicleStick = new TextureSampler("../assets/hurly-burly/", "popsicleStick.png.def", false);
std::vector<TextureSampler *> PuppetResourceManager::faces;


TextureSampler * PuppetResourceManager::whiteHead = new TextureSampler("../assets/hurly-burly/white/", "head.png.def", false); 
TextureSampler * PuppetResourceManager::whiteTorso = new TextureSampler("../assets/hurly-burly/white/", "torso.png.def", false); 
TextureSampler * PuppetResourceManager::whiteArm = new TextureSampler("../assets/hurly-burly/white/", "arm.png.def", false); 

TextureSampler * PuppetResourceManager::countDown0 = new TextureSampler(new Texture("../assets/hurly-burly/Countdown/0.png", 1024, 1024, true, false), 1024, 1024);
TextureSampler * PuppetResourceManager::countDown1 = new TextureSampler(new Texture("../assets/hurly-burly/Countdown/1.png", 1024, 1024, true, false), 1024, 1024);
TextureSampler * PuppetResourceManager::countDown2 = new TextureSampler(new Texture("../assets/hurly-burly/Countdown/2.png", 1024, 1024, true, false), 1024, 1024);
TextureSampler * PuppetResourceManager::countDown3 = new TextureSampler(new Texture("../assets/hurly-burly/Countdown/3.png", 1024, 1024, true, false), 1024, 1024);
TextureSampler * PuppetResourceManager::countDown4 = new TextureSampler(new Texture("../assets/hurly-burly/Countdown/4.png", 1024, 1024, true, false), 1024, 1024);
TextureSampler * PuppetResourceManager::countDown5 = new TextureSampler(new Texture("../assets/hurly-burly/Countdown/5.png", 1024, 1024, true, false), 1024, 1024);


std::vector<TextureSampler *> PuppetResourceManager::indicators;

std::vector<Texture *> PuppetResourceManager::scoreIndicators;

//TextureSampler * PuppetResourceManager::redWins = new TextureSampler(new Texture("../assets/hurly-burly/VictorySplashMessages/redWins.png", 1024, 1024, true, true), 1024, 1024);
//TextureSampler * PuppetResourceManager::yellowWins = new TextureSampler(new Texture("../assets/hurly-burly/VictorySplashMessages/yellowWins.png", 1024, 1024, true, true), 1024, 1024);
//TextureSampler * PuppetResourceManager::greenWins = new TextureSampler(new Texture("../assets/hurly-burly/VictorySplashMessages/greenWins.png", 1024, 1024, true, true), 1024, 1024);
//TextureSampler * PuppetResourceManager::blueWins = new TextureSampler(new Texture("../assets/hurly-burly/VictorySplashMessages/blueWins.png", 1024, 1024, true, true), 1024, 1024);
std::vector<TextureSampler *> PuppetResourceManager::winSplashes;


std::vector<TextureSampler *> PuppetResourceManager::itemMeleeWeapons;

SoundManager * PuppetResourceManager::jumpSounds   = new SoundManager(-1);
SoundManager * PuppetResourceManager::hitSounds    = new SoundManager(-1);
SoundManager * PuppetResourceManager::splashSounds = new SoundManager(-1);
SoundManager * PuppetResourceManager::cheerSounds = new SoundManager(-1);
std::vector<SoundManager *> PuppetResourceManager::miscCheerSounds;
SoundManager * PuppetResourceManager::fallingSounds = new SoundManager(-1);

void PuppetResourceManager::init(){
	
	resources.push_back(startupSplash);
	resources.push_back(blank);
	resources.push_back(itemNone);
	resources.push_back(stageFloor);
	resources.push_back(stageFront);
	resources.push_back(sky);
	resources.push_back(tree1);
	resources.push_back(tree2);
	resources.push_back(bush1);
	resources.push_back(bush2);
	resources.push_back(sun);

	resources.push_back(cloud1);
	resources.push_back(cloud2);
	resources.push_back(cloud3);
	resources.push_back(cloud4);

	resources.push_back(stageCurtain);
	resources.push_back(stageCurtainCenter);
	resources.push_back(stageCurtainTop);
	resources.push_back(stageSpotlight);
	
	resources.push_back(dustParticle);
	
	scoreParticles.push_back(new TextureSampler("../assets/hurly-burly/Score/", "plusOne1.png.def", false));
	scoreParticles.push_back(new TextureSampler("../assets/hurly-burly/Score/", "plusOne2.png.def", false));
	scoreParticles.push_back(new TextureSampler("../assets/hurly-burly/Score/", "plusOne3.png.def", false));
	for(auto i : scoreParticles){
		resources.push_back(i);
	}
	
	resources.push_back(head);
	resources.push_back(hand);
	resources.push_back(popsicleStick);
	
	resources.push_back(whiteHead);
	resources.push_back(whiteTorso);
	resources.push_back(whiteArm);
	
	faces.push_back(new TextureSampler("../assets/hurly-burly/Face/", "Face1.png.def", false));
	faces.push_back(new TextureSampler("../assets/hurly-burly/Face/", "Face2.png.def", false));
	faces.push_back(new TextureSampler("../assets/hurly-burly/Face/", "Face3.png.def", false));
	faces.push_back(new TextureSampler("../assets/hurly-burly/Face/", "Face4.png.def", false));
	faces.push_back(new TextureSampler("../assets/hurly-burly/Face/", "Face5.png.def", false));
	faces.push_back(new TextureSampler("../assets/hurly-burly/Face/", "Face6.png.def", false));
	faces.push_back(new TextureSampler("../assets/hurly-burly/Face/", "Face7.png.def", false));
	faces.push_back(new TextureSampler("../assets/hurly-burly/Face/", "blondeHairBigger.png.def", false));
	for(auto i : faces){
		resources.push_back(i);
	}
	
	resources.push_back(countDown0);
	resources.push_back(countDown1);
	resources.push_back(countDown2);
	resources.push_back(countDown3);
	resources.push_back(countDown4);
	resources.push_back(countDown5);
	
	indicators.push_back(new TextureSampler("../assets/hurly-burly/PlayerIndicators/", "indicator1.png.def", false));
	indicators.push_back(new TextureSampler("../assets/hurly-burly/PlayerIndicators/", "indicator2.png.def", false));
	indicators.push_back(new TextureSampler("../assets/hurly-burly/PlayerIndicators/", "indicator3.png.def", false));
	indicators.push_back(new TextureSampler("../assets/hurly-burly/PlayerIndicators/", "indicator4.png.def", false));
	for(auto i : indicators){
		resources.push_back(i);
	}

	
	scoreIndicators.push_back(new Texture("../assets/hurly-burly/PlayerIndicators/indicator1-circle.png", 1024, 1024, true, false));
	scoreIndicators.push_back(new Texture("../assets/hurly-burly/PlayerIndicators/indicator2-circle.png", 1024, 1024, true, false));
	scoreIndicators.push_back(new Texture("../assets/hurly-burly/PlayerIndicators/indicator3-circle.png", 1024, 1024, true, false));
	scoreIndicators.push_back(new Texture("../assets/hurly-burly/PlayerIndicators/indicator4-circle.png", 1024, 1024, true, false));
	for(auto i : scoreIndicators){
		resources.push_back(i);
	}

	winSplashes.push_back(new TextureSampler(new Texture("../assets/hurly-burly/VictorySplashMessages/yellowWins.png", 1024, 1024, true, false), 1024, 1024));
	winSplashes.push_back(new TextureSampler(new Texture("../assets/hurly-burly/VictorySplashMessages/greenWins.png", 1024, 1024, true, false), 1024, 1024));
	winSplashes.push_back(new TextureSampler(new Texture("../assets/hurly-burly/VictorySplashMessages/blueWins.png", 1024, 1024, true, false), 1024, 1024));
	winSplashes.push_back(new TextureSampler(new Texture("../assets/hurly-burly/VictorySplashMessages/redWins.png", 1024, 1024, true, false), 1024, 1024));
	for(auto i : winSplashes){
		resources.push_back(i);
	}
	
	itemMeleeWeapons.push_back(new TextureSampler("../assets/hurly-burly/WeaponAssets/", "Axe.png.def", false));
	itemMeleeWeapons.push_back(new TextureSampler("../assets/hurly-burly/WeaponAssets/", "Club.png.def", false));
	itemMeleeWeapons.push_back(new TextureSampler("../assets/hurly-burly/WeaponAssets/", "Mace.png.def", false));
	itemMeleeWeapons.push_back(new TextureSampler("../assets/hurly-burly/WeaponAssets/", "Sword.png.def", false));
	itemMeleeWeapons.push_back(new TextureSampler("../assets/hurly-burly/WeaponAssets/", "Scimitar.png.def", false));
	itemMeleeWeapons.push_back(new TextureSampler("../assets/hurly-burly/WeaponAssets/", "Katana.png.def", false));
	itemMeleeWeapons.push_back(new TextureSampler("../assets/hurly-burly/WeaponAssets/", "SingleAxe.png.def", false));
	itemMeleeWeapons.push_back(new TextureSampler("../assets/hurly-burly/WeaponAssets/", "eggplant.png.def", false));
	itemMeleeWeapons.push_back(new TextureSampler("../assets/hurly-burly/WeaponAssets/", "carrot.png.def", false));
	itemMeleeWeapons.push_back(new TextureSampler("../assets/hurly-burly/WeaponAssets/", "hamBone.png.def", false));
	itemMeleeWeapons.push_back(new TextureSampler("../assets/hurly-burly/WeaponAssets/", "stringHam.png.def", false));
	itemMeleeWeapons.push_back(new TextureSampler("../assets/hurly-burly/WeaponAssets/", "mandolin.png.def", false));
	itemMeleeWeapons.push_back(new TextureSampler("../assets/hurly-burly/WeaponAssets/", "broom.png.def", false));
	itemMeleeWeapons.push_back(new TextureSampler("../assets/hurly-burly/WeaponAssets/", "foldingChair.png.def", false));
	itemMeleeWeapons.push_back(new TextureSampler("../assets/hurly-burly/WeaponAssets/", "plunger.png.def", false));
	itemMeleeWeapons.push_back(new TextureSampler("../assets/hurly-burly/WeaponAssets/", "lamp.png.def", false));
	for(auto i : itemMeleeWeapons){
		resources.push_back(i);
	}

	jumpSounds->addNewSound("jump1", "../assets/hurly-burly/audio/jump/jumpSound1.ogg");
	jumpSounds->addNewSound("jump2", "../assets/hurly-burly/audio/jump/jumpSound2.ogg");
	jumpSounds->addNewSound("jump3", "../assets/hurly-burly/audio/jump/jumpSound3.ogg");
	jumpSounds->addNewSound("jump4", "../assets/hurly-burly/audio/jump/jumpSound4.ogg");
	jumpSounds->addNewSound("jump5", "../assets/hurly-burly/audio/jump/jumpSound5.ogg");
	jumpSounds->addNewSound("jump6", "../assets/hurly-burly/audio/jump/jumpSound6.ogg");
	jumpSounds->addNewSound("jump7", "../assets/hurly-burly/audio/jump/jumpSound7.ogg");
	jumpSounds->addNewSound("jump8", "../assets/hurly-burly/audio/jump/jumpSound8.ogg");
	jumpSounds->addNewSound("jump9", "../assets/hurly-burly/audio/jump/jumpSound9.ogg");
	jumpSounds->addNewSound("jump10", "../assets/hurly-burly/audio/jump/jumpSound10.ogg");
	resources.push_back(jumpSounds);
	
	hitSounds->addNewSound("hit1", "../assets/hurly-burly/audio/hit/hitSound1.ogg");
	hitSounds->addNewSound("hit2", "../assets/hurly-burly/audio/hit/hitSound2.ogg");
	hitSounds->addNewSound("hit3", "../assets/hurly-burly/audio/hit/hitSound3.ogg");
	hitSounds->addNewSound("hit4", "../assets/hurly-burly/audio/hit/hitSound4.ogg");
	hitSounds->addNewSound("hit5", "../assets/hurly-burly/audio/hit/hitSound5.ogg");
	hitSounds->addNewSound("hit6", "../assets/hurly-burly/audio/hit/hitSound6.ogg");
	hitSounds->addNewSound("hit7", "../assets/hurly-burly/audio/hit/hitSound7.ogg");
	hitSounds->addNewSound("hit8", "../assets/hurly-burly/audio/hit/hitSound8.ogg");
	hitSounds->addNewSound("hit9", "../assets/hurly-burly/audio/hit/hitSound9.ogg");
	hitSounds->addNewSound("hit10", "../assets/hurly-burly/audio/hit/hitSound10.ogg");
	hitSounds->addNewSound("hit11", "../assets/hurly-burly/audio/hit/hitSound11.ogg");
	hitSounds->addNewSound("hit12", "../assets/hurly-burly/audio/hit/hitSound12.ogg");
	hitSounds->addNewSound("hit13", "../assets/hurly-burly/audio/hit/hitSound13.ogg");
	hitSounds->addNewSound("hit14", "../assets/hurly-burly/audio/hit/hitSound14.ogg");
	hitSounds->addNewSound("hit15", "../assets/hurly-burly/audio/hit/hitSound15.ogg");
	hitSounds->addNewSound("hit16", "../assets/hurly-burly/audio/hit/hitSound16.ogg");
	hitSounds->addNewSound("hit17", "../assets/hurly-burly/audio/hit/hitSound17.ogg");
	hitSounds->addNewSound("hit18", "../assets/hurly-burly/audio/hit/hitSound18.ogg");
	hitSounds->addNewSound("hit19", "../assets/hurly-burly/audio/hit/hitSound19.ogg");
	hitSounds->addNewSound("hit10", "../assets/hurly-burly/audio/hit/hitSound20.ogg");
	resources.push_back(hitSounds);

	splashSounds->addNewSound("FightYourFriends", "../assets/hurly-burly/audio/splash/FightYourFriends.ogg");
	splashSounds->addNewSound("Joust", "../assets/hurly-burly/audio/splash/Joust.ogg");
	splashSounds->addNewSound("RaidTheCastle", "../assets/hurly-burly/audio/splash/RaidTheCastle.ogg");
	splashSounds->addNewSound("Rapunzel", "../assets/hurly-burly/audio/splash/Rapunzel.ogg");
	splashSounds->addNewSound("SlayTheDragon", "../assets/hurly-burly/audio/splash/SlayTheDragon.ogg");
	splashSounds->addNewSound("Startup", "../assets/hurly-burly/audio/splash/HurlyBurlyPuppetParty.ogg");
	splashSounds->addNewSound("Startup-alt", "../assets/hurly-burly/audio/splash/HurlyBurlyPuppetParty-processed.ogg");
	resources.push_back(splashSounds);

	cheerSounds->addNewSound("0", "../assets/hurly-burly/audio/yellowCheer/yellowCheerMain.ogg");
	cheerSounds->addNewSound("1", "../assets/hurly-burly/audio/greenCheer/greenCheerMain.ogg");
	cheerSounds->addNewSound("2", "../assets/hurly-burly/audio/blueCheer/blueCheerMain.ogg");
	cheerSounds->addNewSound("3", "../assets/hurly-burly/audio/redCheer/redCheerMain.ogg");
	resources.push_back(cheerSounds);
	
	fallingSounds->addNewSound("1", "../assets/hurly-burly/audio/puppetDialog_Dragon/falling1.ogg");
	fallingSounds->addNewSound("2", "../assets/hurly-burly/audio/puppetDialog_Dragon/falling2.ogg");
	resources.push_back(fallingSounds);

	SoundManager * s = new SoundManager(1);
	s->addNewSound("1", "../assets/hurly-burly/audio/yellowCheer/yellowCheer1.ogg");
	s->addNewSound("2", "../assets/hurly-burly/audio/yellowCheer/yellowCheer2.ogg");
	s->addNewSound("3", "../assets/hurly-burly/audio/yellowCheer/yellowCheer3.ogg");
	resources.push_back(s);
	miscCheerSounds.push_back(s);

	s = new SoundManager(1);
	s->addNewSound("1", "../assets/hurly-burly/audio/greenCheer/greenCheer1.ogg");
	s->addNewSound("2", "../assets/hurly-burly/audio/greenCheer/greenCheer2.ogg");
	s->addNewSound("3", "../assets/hurly-burly/audio/greenCheer/greenCheer3.ogg");
	s->addNewSound("4", "../assets/hurly-burly/audio/greenCheer/greenCheer4.ogg");
	resources.push_back(s);
	miscCheerSounds.push_back(s);

	s = new SoundManager(1);
	s->addNewSound("1", "../assets/hurly-burly/audio/blueCheer/blueCheer1.ogg");
	s->addNewSound("2", "../assets/hurly-burly/audio/blueCheer/blueCheer2.ogg");
	s->addNewSound("3", "../assets/hurly-burly/audio/blueCheer/blueCheer3.ogg");
	s->addNewSound("4", "../assets/hurly-burly/audio/blueCheer/blueCheer4.ogg");
	s->addNewSound("5", "../assets/hurly-burly/audio/blueCheer/blueCheer5.ogg");
	s->addNewSound("6", "../assets/hurly-burly/audio/blueCheer/blueCheer6.ogg");
	s->addNewSound("7", "../assets/hurly-burly/audio/blueCheer/blueCheer7.ogg");
	resources.push_back(s);
	miscCheerSounds.push_back(s);

	s = new SoundManager(1);
	s->addNewSound("1", "../assets/hurly-burly/audio/redCheer/redCheer1.ogg");
	s->addNewSound("2", "../assets/hurly-burly/audio/redCheer/redCheer2.ogg");
	s->addNewSound("3", "../assets/hurly-burly/audio/redCheer/redCheer3.ogg");
	s->addNewSound("4", "../assets/hurly-burly/audio/redCheer/redCheer4.ogg");
	s->addNewSound("5", "../assets/hurly-burly/audio/redCheer/redCheer5.ogg");
	resources.push_back(s);
	miscCheerSounds.push_back(s);


	RaidTheCastleResourceManager::init();
	RapunzelResourceManager::init();
	SlayTheDragonResourceManager::init();
	FightYourFriendsResourceManager::init();
}

TextureSampler * PuppetResourceManager::getRandomScoreParticles(){
	return scoreParticles.at(vox::NumberUtils::randomInt(0, scoreParticles.size()-1));
}

TextureSampler * PuppetResourceManager::getRandomFace(){
	return faces.at(vox::NumberUtils::randomInt(0, faces.size()-1));
}

TextureSampler * PuppetResourceManager::getRandomMeleeWeapon(){
	return itemMeleeWeapons.at(vox::NumberUtils::randomInt(0, itemMeleeWeapons.size()-1));
}