#pragma once

#include "RaidTheCastleResourceManager.h"

Texture * RaidTheCastleResourceManager::castleSpriteSheet    = new Texture("../assets/structure components/castle/Castle_SpriteSheet.png", 2048, 2048, true, true);

TextureSampler * RaidTheCastleResourceManager::catapultArm   = new TextureSampler(new Texture("../assets/structure components/catapult/CatapultFlinger.png", 512, 512, true, true), 429, 76);;
TextureSampler * RaidTheCastleResourceManager::catapultBody  = new TextureSampler(new Texture("../assets/structure components/catapult/CatapultBase.png", 512, 512, true, true), 418, 264);
TextureSampler * RaidTheCastleResourceManager::boulder		 = new TextureSampler(new Texture("../assets/structure components/catapult/Boulder1.png", 512, 512, true, true), 108, 103);
TextureSampler * RaidTheCastleResourceManager::castleBase    = new TextureSampler(new Texture("../assets/structure components/castle/CastleNorm_State1.png", 1024, 1024, true, true), 973, 619);

TextureSampler * RaidTheCastleResourceManager::knightRedTorso	= new TextureSampler(new Texture("../assets/hurly-burly/NormalKnightAssets/redKnightBreastplate.png", 1024, 1024, true, true), 268, 776);
TextureSampler * RaidTheCastleResourceManager::knightRedArm		= new TextureSampler(new Texture("../assets/hurly-burly/NormalKnightAssets/redKnightArm.png", 1024, 1024, true, true), 92, 327);
TextureSampler * RaidTheCastleResourceManager::knightRedHelmet	= new TextureSampler(new Texture("../assets/hurly-burly/NormalKnightAssets/redKnightHelmet.png", 1024, 1024, true, true), 233, 254);

TextureSampler * RaidTheCastleResourceManager::knightGreenTorso	= new TextureSampler(new Texture("../assets/hurly-burly/NormalKnightAssets/greenKnightBreastplate.png", 1024, 1024, true, true), 268, 776);
TextureSampler * RaidTheCastleResourceManager::knightGreenArm		= new TextureSampler(new Texture("../assets/hurly-burly/NormalKnightAssets/greenKnightArm.png", 1024, 1024, true, true), 92, 327);
TextureSampler * RaidTheCastleResourceManager::knightGreenHelmet	= new TextureSampler(new Texture("../assets/hurly-burly/NormalKnightAssets/greenKnightHelmet.png", 1024, 1024, true, true), 233, 254);

TextureSampler * RaidTheCastleResourceManager::knightBlueTorso	= new TextureSampler(new Texture("../assets/hurly-burly/NormalKnightAssets/blueKnightBreastplate.png", 1024, 1024, true, true), 268, 776);
TextureSampler * RaidTheCastleResourceManager::knightBlueArm		= new TextureSampler(new Texture("../assets/hurly-burly/NormalKnightAssets/blueKnightArm.png", 1024, 1024, true, true), 92, 327);
TextureSampler * RaidTheCastleResourceManager::knightBlueHelmet	= new TextureSampler(new Texture("../assets/hurly-burly/NormalKnightAssets/blueKnightHelmet.png", 1024, 1024, true, true), 233, 254);

TextureSampler * RaidTheCastleResourceManager::knightYellowTorso	= new TextureSampler(new Texture("../assets/hurly-burly/NormalKnightAssets/yellowKnightBreastplate.png", 1024, 1024, true, true), 268, 776);
TextureSampler * RaidTheCastleResourceManager::knightYellowArm		= new TextureSampler(new Texture("../assets/hurly-burly/NormalKnightAssets/yellowKnightArm.png", 1024, 1024, true, true), 92, 327);
TextureSampler * RaidTheCastleResourceManager::knightYellowHelmet	= new TextureSampler(new Texture("../assets/hurly-burly/NormalKnightAssets/yellowKnightHelmet.png", 1024, 1024, true, true), 233, 254);

TextureSampler * RaidTheCastleResourceManager::castleChampionTorso	= new TextureSampler(new Texture("../assets/hurly-burly/CastleChampionAssets/CCBody.png", 1024, 1024, true, true), 275, 806);
TextureSampler * RaidTheCastleResourceManager::castleChampionArm	= new TextureSampler(new Texture("../assets/hurly-burly/CastleChampionAssets/CCArm.png", 1024, 1024, true, true), 67, 200);
TextureSampler * RaidTheCastleResourceManager::castleChampionHelmet	= new TextureSampler(new Texture("../assets/hurly-burly/CastleChampionAssets/CCHelmet.png", 1024, 1024, true, true), 229, 295);


/*
TextureSampler * RaidTheCastleResourceManager::goldenBreastPlateStick = new TextureSampler(new Texture("../assets/hurly-burly/KnightAssets/BreastplateStick1.png", 512, 512, true, true),	145, 405); 
TextureSampler * RaidTheCastleResourceManager::goldenArm     = new TextureSampler(new Texture("../assets/hurly-burly/KnightAssets/Arm1.png", 512, 512, true, true), 40, 105); 
TextureSampler * RaidTheCastleResourceManager::goldenHelmet  = new TextureSampler(new Texture("../assets/hurly-burly/KnightAssets/Helmet1.png", 512,512, true, true), 114, 165);
*/
void RaidTheCastleResourceManager::init(){
	resources.push_back(catapultArm);
	resources.push_back(catapultBody);
	resources.push_back(boulder);

	/*resources.push_back(goldenArm);
	resources.push_back(hand1);
	resources.push_back(face1);
	resources.push_back(goldenHelmet);*/
	
	resources.push_back(knightRedTorso);
	resources.push_back(knightRedArm);
	resources.push_back(knightRedHelmet);
	
	resources.push_back(knightGreenTorso);
	resources.push_back(knightGreenArm);
	resources.push_back(knightGreenHelmet);
	
	resources.push_back(knightBlueTorso);
	resources.push_back(knightBlueArm);
	resources.push_back(knightBlueHelmet);
	
	resources.push_back(knightYellowTorso);
	resources.push_back(knightYellowArm);
	resources.push_back(knightYellowHelmet);
	
	resources.push_back(castleChampionTorso);
	resources.push_back(castleChampionArm);
	resources.push_back(castleChampionHelmet);
}