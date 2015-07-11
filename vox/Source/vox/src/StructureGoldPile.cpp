#pragma once

#include <StructureGoldPile.h>
#include <PuppetGame.h>
#include <RapunzelResourceManager.h>
#include <MeshInterface.h>
#include <SpriteSheetAnimation.h>
#include <PuppetScene.h>
#include <ItemGold.h>
#include <PuppetCharacter.h>
#include <shader\ComponentShaderBase.h>

StructureGoldPile::StructureGoldPile(Box2DWorld* _world):
	StructureInteractable(_world, PuppetGame::kSTRUCTURE, PuppetGame::kPLAYER, -25),
	totalGold(20),
	goldTaken(0)
{
	componentScale = 0.005f;
	
	TextureSampler * baseTex = RapunzelResourceManager::goldBrick;
	Texture * baseSpriteSheetTex = RapunzelResourceManager::goldSpriteSheet;

	rootComponent = new Box2DSprite(_world, baseTex, b2_staticBody, false, nullptr, componentScale);
	addComponent(&rootComponent);
	
	b2Filter sf;
	sf.categoryBits = categoryBits;
	if(maskBits != (int16)-1){
		sf.maskBits = maskBits;
	}

	sf.groupIndex = groupIndex;
	for(Box2DSprite ** c : components){
		(*c)->createFixture(sf);
	}
	setUserData(this);
	
	rootComponent->body->GetFixtureList()->SetSensor(true);

	// sprite sheet animation
	rootComponent->mesh->popTexture2D();
	spriteSheet = new SpriteSheetAnimation(baseSpriteSheetTex, 0);
	spriteSheet->pushFramesInRange(0, 5, 512, 209, baseSpriteSheetTex->width);
	rootComponent->addAnimation("brickStates", spriteSheet, true);
	rootComponent->playAnimation = true;
	rootComponent->currentAnimation->currentFrame = 0;
	rootComponent->update(&vox::step);
}

void StructureGoldPile::actuallyInteract(){
	if(playerWhoTriggered->heldItem == nullptr){

		if(goldTaken < totalGold){
			goldTaken++;
		
			int goldPerState = totalGold / 5;
			int frame = goldTaken/goldPerState;
			if(frame <= 5) {
				rootComponent->currentAnimation->currentFrame = frame;
				rootComponent->update(&vox::step);
			}

			PuppetScene * pScene = static_cast<PuppetScene *>(scene);
			ItemGold * gold = new ItemGold(pScene->world);
			gold->setShader(pScene->shader, true);
			gold->snapComponents(playerWhoTriggered->itemHolder);
			pScene->addChild(gold, 1);
			pScene->items.push_back(gold);
			playerWhoTriggered->pickupItem(gold);
			triggering = false;
		}
	}
}
void StructureGoldPile::evaluateState(){
	if(goldTaken < totalGold){
		ready = true;
		prepared = true;
	}else{
		ready = false;
		prepared = false;
	}
}