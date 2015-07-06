#pragma once

#include <Rapunzel.h>
#include <RapunzelContactListener.h>
#include <RapunzelResourceManager.h>
#include <Castle.h>
#include <PuppetGame.h>
#include <PuppetCharacter.h>
#include <FollowCamera.h>
#include <BehaviourManager.h>
#include <Behaviour.h>
#include <BehaviourFollow.h>
#include <BehaviourPatrol.h>
#include <BehaviourAttack.h>
#include <Boulder.h>
#include <Catapult.h>
#include <Box2DSprite.h>
#include <Box2DWorld.h>
#include <MeshEntity.h>
#include <MeshInterface.h>
#include <MeshFactory.h>
#include <shader/ComponentShaderBase.h>
#include <keyboard.h>
#include <Texture.h>
#include <TextureSampler.h>
#include <PuppetCharacterGuard.h>
#include <PuppetCharacterRapunzel.h>
#include <PuppetCharacterThief.h>
#include <PuppetTexturePack.h>
#include <PuppetController.h>
#include <Item.h>
#include <ItemFlail.h>
#include <ItemSimpleWeapon.h>
#include <ItemProjectileWeapon.h>
#include <Hair.h>
#include <Lever.h>
#include <ItemGold.h>
#include <NumberUtils.h>
#include <StructureBoxingGlove.h>

#include <glfw\glfw3.h>
#include <SoundManager.h>
#include <StructureGoldPile.h>

Rapunzel::Rapunzel(PuppetGame* _game):
	PuppetScene(_game, 50.f, 68.f),
	tower(new Box2DSprite(world, RapunzelResourceManager::towerTower, b2_staticBody, false, nullptr, 0.03f)),
	castleCatwalk(new Box2DSprite(world, RapunzelResourceManager::towerCatwalk, b2_staticBody, false, nullptr, 0.03f)),
	playerCharacter1(new PuppetCharacterThief(false, world, PuppetGame::kPLAYER, PuppetGame::kGROUND | PuppetGame::kSTRUCTURE | PuppetGame::kITEM | PuppetGame::kPLAYER | PuppetGame::kBEHAVIOUR | PuppetGame::kBOUNDARY, -1)),
	playerCharacter2(new PuppetCharacterThief(false, world, PuppetGame::kPLAYER, PuppetGame::kGROUND | PuppetGame::kSTRUCTURE | PuppetGame::kITEM | PuppetGame::kPLAYER | PuppetGame::kBEHAVIOUR | PuppetGame::kBOUNDARY, -2)),
	playerCharacter3(new PuppetCharacterThief(false, world, PuppetGame::kPLAYER, PuppetGame::kGROUND | PuppetGame::kSTRUCTURE | PuppetGame::kITEM | PuppetGame::kPLAYER | PuppetGame::kBEHAVIOUR | PuppetGame::kBOUNDARY, -3)),
	playerCharacter4(new PuppetCharacterRapunzel(false, world, PuppetGame::kPLAYER, PuppetGame::kGROUND | PuppetGame::kSTRUCTURE | PuppetGame::kITEM | PuppetGame::kPLAYER | PuppetGame::kBEHAVIOUR | PuppetGame::kBOUNDARY, -4))
{
	ghostPosition = 12.0f;

	populateBackground();
	cl = new RapunzelContactListener(this);

	splashMessage = new Sprite();
	splashMessage->mesh->pushTexture2D(RapunzelResourceManager::splashMessage->texture);
	splashMessage->setShader(shader, true);
	splashMessage->childTransform->translate(1920.f*0.5, 1080.f*0.5f, 0.f);

	Sprite * towerBg = new Sprite();
	addChild(towerBg, 0);
	towerBg->setShader(shader, true);
	towerBg->pushTextureSampler(RapunzelResourceManager::towerBackground);
	towerBg->parents.at(0)->translate(2.f, 0.f, 0.f);
	towerBg->parents.at(0)->scale(2.6f, 2.6f, 1.f);

	players.push_back(playerCharacter1);
	players.push_back(playerCharacter2);
	players.push_back(playerCharacter3);
	players.push_back(playerCharacter4);

	b2Filter tf;
    tf.categoryBits = PuppetGame::kGROUND;
    tf.groupIndex = 0;
    tf.maskBits = 0;

	b2Filter sf;
    sf.categoryBits = PuppetGame::kGROUND;
    sf.groupIndex = 0;
    sf.maskBits = PuppetGame::kITEM | PuppetGame::kPLAYER;

	tower->createFixture(tf, b2Vec2(0, 0), tower);
    tower->setShader(shader, true);
    addChild(tower, 1);

	castleCatwalk->createFixture(sf, b2Vec2(0, 0), castleCatwalk);
    castleCatwalk->setShader(shader, true);
	
	addChild(playerCharacter1, 1);
	playerCharacter1->addToLayeredScene(this, 1);

	addChild(playerCharacter2, 1);
	playerCharacter2->addToLayeredScene(this, 1);

	addChild(playerCharacter3, 1);
	playerCharacter3->addToLayeredScene(this, 1);

	addChild(playerCharacter4, 1);
	playerCharacter4->addToLayeredScene(this, 1);
	// start Rapunzel with a ridiculous score so if the time runs out they win regardless of how well the thieves play
	playerCharacter4->score = 1000000;
	playerCharacter4->lastUpdateScore = 1000000;
	
	assignControllers();

	// create indicators and add to followcam
	for(PuppetCharacter * p : players){
		p->createIndicator(p->id);
		gameCam->addTarget(p->indicator);
	}

	for(PuppetCharacter * p : players){
		if(p != playerCharacter4){
			TextureSampler * weaponTex = PuppetResourceManager::getRandomMeleeWeapon();
			ItemSimpleWeapon * weapon = new ItemSimpleWeapon(weaponTex, false, world, PuppetGame::kITEM, PuppetGame::kPLAYER | PuppetGame::kSTRUCTURE | PuppetGame::kBOUNDARY | PuppetGame::kGROUND, p->groupIndex, 1, 0, -weaponTex->height);
			weapon->addToLayeredScene(this, 1);
			weapon->setShader(shader, true);
			p->itemToPickup = weapon;
			addChild(weapon, 1);
		}else{
			TextureSampler * weaponTex = PuppetResourceManager::itemMeleeWeapons.at(11);
			ItemSimpleWeapon * weapon = new ItemSimpleWeapon(weaponTex, false, world, PuppetGame::kITEM, PuppetGame::kPLAYER | PuppetGame::kSTRUCTURE | PuppetGame::kBOUNDARY | PuppetGame::kGROUND, p->groupIndex, 1, 0, -weaponTex->height);
			weapon->addToLayeredScene(this, 1);
			weapon->setShader(shader, true);
			p->itemToPickup = weapon;
			addChild(weapon, 1);
		}
		p->setShader(shader, true);
	}
	
	tower->setTranslationPhysical(glm::vec3(glm::vec3(60.f, tower->getCorrectedHeight(), 0.f)));
    castleCatwalk->setTranslationPhysical(glm::vec3(tower->getWorldPos().x - castleCatwalk->getCorrectedWidth() - 3.5f, tower->getWorldPos().y - tower->getCorrectedHeight() * 0.08, 0));
	
	glm::vec3 catwalkPos = glm::vec3(castleCatwalk->getWorldPos().x, castleCatwalk->getWorldPos().y + castleCatwalk->getCorrectedHeight(), 0.f);

	playerCharacter1->translateComponents(glm::vec3(10.f, 5.f, 0.f));
	playerCharacter2->translateComponents(glm::vec3(20.f, 5.f, 0.f));
	playerCharacter3->translateComponents(glm::vec3(30.f, 5.f, 0.f));
	playerCharacter4->translateComponents(catwalkPos + glm::vec3(0.f, 5.f, 0.f));
	
	Lever::towerPos = tower->getWorldPos(false);

	Hair * hair = new Hair(world, PuppetGame::kGROUND, PuppetGame::kPLAYER, 0);
	addChild(hair, 1);
	hair->setShader(shader, true);
	hair->translateComponents(glm::vec3(Lever::towerPos.x, Lever::towerPos.y - tower->getCorrectedHeight() * 0.75, 0.f));

	lever1 = new Lever(world, PuppetGame::kSTRUCTURE, PuppetGame::kPLAYER, 0);
	addChild(lever1, 1);
	lever1->addToLayeredScene(this, 1);
	lever1->setShader(shader, true);
	lever1->translateComponents(catwalkPos + glm::vec3(-10.f, -0.25f, 0));
	lever1->type = 1;
	
	lever2 = new Lever(world, PuppetGame::kSTRUCTURE, PuppetGame::kPLAYER, 0);
	addChild(lever2, 1);
	lever2->addToLayeredScene(this, 1);
	lever2->setShader(shader, true);
	lever2->translateComponents(catwalkPos + glm::vec3(0.f, -0.1f, 0));
	lever2->type = 2;

	lever3 = new Lever(world, PuppetGame::kSTRUCTURE, PuppetGame::kPLAYER, 0);
	addChild(lever3, 1);
	lever3->addToLayeredScene(this, 1);
	lever3->setShader(shader, true);
	lever3->translateComponents(catwalkPos + glm::vec3(10.f, -0.25f, 0.f));
	lever3->type = 3;

	glove = new StructureBoxingGlove(world);
	glove->translateComponents(Lever::towerPos + glm::vec3(3.f, -12.f, 0.f));
	addChild(glove, 1);
	glove->setShader(shader, true);
	glove->addToLayeredScene(this, 1);

	goldPile = new StructureGoldPile(world);
	addChild(goldPile, 1);
	goldPile->setShader(shader, true);
	goldPile->translateComponents(catwalkPos - glm::vec3(20.f, -1.5f, 0.f));
	goldPile->addToLayeredScene(this, 1);
	goldPile->rootComponent->parents.at(0)->scale(10.0f, 10.0f, 1.0f);
	gameCam->addTarget(goldPile);
	playRandomBackgroundMusic();
	
	gameCam->useBounds = true;
	gameCam->minBounds.x = 4;
	gameCam->minBounds.y = -10;
	gameCam->minBounds.height = 0;//sceneHeight;
	gameCam->minBounds.width = sceneWidth-8;
	gameCam->minimumZoom = 30;
	gameCam->buffer = 0;
	
    addChild(castleCatwalk, 1);
}

void Rapunzel::update(Step* _step){
	PuppetScene::update(_step);

	if(!splashSoundPlayed){
		PuppetResourceManager::splashSounds->play("Rapunzel");
		splashSoundPlayed = true;
	}

	// trigger victory (thieves should win, since gold is gone)
	if(goldPile->goldTaken >= goldPile->totalGold){
		playerCharacter4->score = 0;
        triggerVictoryState();
	}else{
		PuppetCharacter * p;
		unsigned long int survivors = 0;
		for (unsigned long int i = 0; i < players.size(); ++i){
			if (!players.at(i)->dead){
				++survivors;
				p = players.at(i);
			}
		}
		if(survivors == 1){
			p->score += 100000;
			p->lastUpdateScore = p->score;
			triggerVictoryState();
		}
	}
}

void Rapunzel::render(vox::MatrixStack* _matrixStack, RenderOptions* _renderOptions){
	PuppetScene::render(_matrixStack, _renderOptions);
}

void Rapunzel::load(){
	PuppetScene::load();
}

void Rapunzel::unload(){
	PuppetScene::unload();
}