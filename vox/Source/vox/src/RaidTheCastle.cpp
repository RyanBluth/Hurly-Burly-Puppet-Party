#pragma once

#include <RaidTheCastle.h>
#include <RaidTheCastleContactListener.h>
#include <RaidTheCastleResourceManager.h>
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
#include <PuppetCharacterCastleChampion.h>
#include <PuppetCharacterKnight.h>
#include <PuppetTexturePack.h>
#include <PuppetController.h>
#include <ParticleSystem.h>
#include <Item.h>
#include <ItemFlail.h>
#include <ItemSimpleWeapon.h>
#include <ItemProjectileWeapon.h>
#include <SoundManager.h>
#include <glfw\glfw3.h>
#include <NumberUtils.h>
#include <Particle.h>

RaidTheCastle::RaidTheCastle(PuppetGame* _game):
	PuppetScene(_game, 30),
	castle(new Castle(world, PuppetGame::kSTRUCTURE, PuppetGame::kITEM, 120)),
	catapult(new Catapult(world, PuppetGame::kSTRUCTURE, PuppetGame::kITEM | PuppetGame::kPLAYER, -10)),
	champion(new PuppetCharacterCastleChampion(world, PuppetGame::kPLAYER, PuppetGame::kGROUND | PuppetGame::kSTRUCTURE | PuppetGame::kITEM | PuppetGame::kPLAYER | PuppetGame::kBEHAVIOUR | PuppetGame::kBOUNDARY, -20)),
	camTargetsRemoved(false),
	playerCharacter1(new PuppetCharacterKnight(false, 0, world, PuppetGame::kPLAYER, PuppetGame::kGROUND | PuppetGame::kSTRUCTURE | PuppetGame::kITEM | PuppetGame::kPLAYER | PuppetGame::kBEHAVIOUR | PuppetGame::kBOUNDARY, -1)),
	playerCharacter2(new PuppetCharacterKnight(false, 1, world, PuppetGame::kPLAYER, PuppetGame::kGROUND | PuppetGame::kSTRUCTURE | PuppetGame::kITEM | PuppetGame::kPLAYER | PuppetGame::kBEHAVIOUR | PuppetGame::kBOUNDARY, -2)),
	playerCharacter3(new PuppetCharacterKnight(false, 2, world, PuppetGame::kPLAYER, PuppetGame::kGROUND | PuppetGame::kSTRUCTURE | PuppetGame::kITEM | PuppetGame::kPLAYER | PuppetGame::kBEHAVIOUR | PuppetGame::kBOUNDARY, -3)),
	playerCharacter4(new PuppetCharacterKnight(false, 3, world, PuppetGame::kPLAYER, PuppetGame::kGROUND | PuppetGame::kSTRUCTURE | PuppetGame::kITEM | PuppetGame::kPLAYER | PuppetGame::kBEHAVIOUR | PuppetGame::kBOUNDARY, -4))
{

	ghostPosition = 12.0f;
	populateBackground();
	cl = new RaidTheCastleContactListener(this);
	
	castle->translateComponents(glm::vec3(120.f, 0.f, 0.f));
	castle->setShader(shader, true);
	castle->addToLayeredScene(this, 0);
	addChild(castle, 0);

	TextureSampler * splashMessageTextureSampler = RaidTheCastleResourceManager::splashMessage;
	splashMessage = new Sprite();
	splashMessage->mesh->pushTexture2D(splashMessageTextureSampler->texture);
	splashMessage->setShader(shader, true);
	splashMessage->childTransform->translate(1920.f*0.5, 1080.f*0.5f, 0);

	players.push_back(playerCharacter1);
	players.push_back(playerCharacter2);
	players.push_back(playerCharacter3);
	players.push_back(playerCharacter4);

	addChild(playerCharacter1, 1);
	playerCharacter1->addToLayeredScene(this, 1);

	addChild(playerCharacter2, 1);
	playerCharacter2->addToLayeredScene(this, 1);

	addChild(playerCharacter3, 1);
	playerCharacter3->addToLayeredScene(this, 1);

	addChild(playerCharacter4, 1);
	playerCharacter4->addToLayeredScene(this, 1);

	assignControllers();

	champion->setShader(shader, true);
	addChild(champion, 0);
	champion->addToLayeredScene(this, 1);
	
	champion->itemToPickup = new ItemFlail(world, PuppetGame::kITEM, PuppetGame::kPLAYER | PuppetGame::kGROUND | PuppetGame::kBOUNDARY, champion->groupIndex, 5, 0, -RaidTheCastleResourceManager::itemFlailGrip->height/2.f);
	addChild(champion->itemToPickup, 1);
	champion->itemToPickup->addToLayeredScene(this, 1);
	champion->itemToPickup->setShader(shader, true);


	catapult->setShader(shader, true);
	catapult->addToLayeredScene(this, 1);
	addChild(catapult, 1);
	catapult->translateComponents(glm::vec3(14.0f, 0.f, 0.f));
	
	//playerCharacter3->behaviourManager->addBehaviour(new BehaviourPatrol(glm::vec3(50,0,0), glm::vec3(100,0,0), playerCharacter3, 10));
	//playerCharacter3->behaviourManager->addBehaviour(new BehaviourAttack(playerCharacter3, 3, PuppetGame::kPLAYER));
	//playerCharacter3->ai = true;

	//playerCharacter4->behaviourManager->addBehaviour(new BehaviourPatrol(glm::vec3(50,0,0), glm::vec3(100,0,0), playerCharacter4, 10));
	//playerCharacter4->behaviourManager->addBehaviour(new BehaviourAttack(playerCharacter4, 3, PuppetGame::kPLAYER));
	//playerCharacter4->ai = true;

	for(PuppetCharacter * p : players){
		TextureSampler * weaponTex = PuppetResourceManager::getRandomMeleeWeapon();
		TextureSampler * projTex = PuppetResourceManager::getRandomMeleeWeapon();
		
		//ItemProjectileWeapon * weapon = new ItemProjectileWeapon(projTex, weaponTex, world, PuppetGame::kITEM, PuppetGame::kPLAYER | PuppetGame::kSTRUCTURE | PuppetGame::kBOUNDARY | PuppetGame::kGROUND, p->groupIndex, 0, 0, -weaponTex->height);
        ItemSimpleWeapon * weapon = new ItemSimpleWeapon(weaponTex, false, world, PuppetGame::kITEM, PuppetGame::kPLAYER | PuppetGame::kBOUNDARY | PuppetGame::kGROUND | PuppetGame::kSTRUCTURE, p->groupIndex, 1, 0, -weaponTex->height);

        weapon->addToLayeredScene(this, 1);
		weapon->setShader(shader, true);
		p->itemToPickup = weapon;
        addChild(weapon, 1);
		p->setShader(shader, true);
	}
	
	playerCharacter1->translateComponents(glm::vec3(0.5f* sceneWidth*0.065f + 20.f, 35, 0.f));
	playerCharacter2->translateComponents(glm::vec3(1.5f* sceneWidth*0.065f + 20.f, 35, 0.f));
	playerCharacter3->translateComponents(glm::vec3(2.5f* sceneWidth*0.065f + 20.f, 35, 0.f));
	playerCharacter4->translateComponents(glm::vec3(3.5f* sceneWidth*0.065f + 20.f, 35, 0.f));
	champion->translateComponents(glm::vec3(100.f, 35, 0));

	playRandomBackgroundMusic();
	catapult->prepare();

	populateClouds();
	
	
	// create indicators and add to followcam
	for(PuppetCharacter * p : players){
		p->createIndicator(p->id);
		gameCam->addTarget(p->indicator);
	}

	gameCam->addTarget(catapult);
	gameCam->addTarget(castle);

	gameCam->useBounds = true;
	gameCam->minBounds.x = 0;
	gameCam->minBounds.width = sceneWidth;
	gameCam->minBounds.y = -3;
	gameCam->minBounds.height = sceneHeight;
}

RaidTheCastle::~RaidTheCastle(){
}

void RaidTheCastle::update(Step* _step){
	PuppetScene::update(_step);
	/*if(keyboard->keyDown(GLFW_KEY_F)){
		catapult->fireCatapult();
	}*/

	if(!camTargetsRemoved && _step->time - sceneStart > 15.0) {
		gameCam->removeTarget(castle);
		gameCam->removeTarget(catapult);
		camTargetsRemoved = true;
	}

	if(!splashSoundPlayed){
		PuppetResourceManager::splashSounds->play("RaidTheCastle");
		splashSoundPlayed = true;
	}


	if(castle->state == Castle::state_t::kDEAD){
		gameCam->addTarget(castle->rootComponent);
		/*if(gameCam->targets.size() != 1){
			gameCam->targets.clear();
		}*/
		
		triggerVictoryState();
	}
}

void RaidTheCastle::render(vox::MatrixStack* _matrixStack, RenderOptions* _renderOptions){
	PuppetScene::render(_matrixStack, _renderOptions);
}

void RaidTheCastle::load(){
	PuppetScene::load();
}

void RaidTheCastle::unload(){
	PuppetScene::unload();
}