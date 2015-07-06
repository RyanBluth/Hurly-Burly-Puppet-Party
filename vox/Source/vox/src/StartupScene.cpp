#pragma once

#include <StartupScene.h>
#include <PuppetGame.h>
#include <PuppetResourceManager.h>
#include <Sprite.h>
#include <MeshInterface.h>
#include <shader\ComponentShaderBase.h>
#include <SoundManager.h>
#include <PuppetController.h>
#include <FollowCamera.h>
#include <PuppetCharacterKnight.h>
#include <Box2DSprite.h>
#include <BehaviourAttack.h>
#include <BehaviourManager.h>

StartupScene::StartupScene(PuppetGame * _game) :
	PuppetScene(_game, 20.f, 30.f, 20.f, 100.f, true),
	playerCharacter1(new PuppetCharacterKnight(false, 0, world, PuppetGame::kPLAYER, PuppetGame::kGROUND | PuppetGame::kSTRUCTURE | PuppetGame::kITEM | PuppetGame::kPLAYER | PuppetGame::kBEHAVIOUR | PuppetGame::kBOUNDARY, -1)),
	playerCharacter2(new PuppetCharacterKnight(false, 1, world, PuppetGame::kPLAYER, PuppetGame::kGROUND | PuppetGame::kSTRUCTURE | PuppetGame::kITEM | PuppetGame::kPLAYER | PuppetGame::kBEHAVIOUR | PuppetGame::kBOUNDARY, -2)),
	playerCharacter3(new PuppetCharacterKnight(false, 2, world, PuppetGame::kPLAYER, PuppetGame::kGROUND | PuppetGame::kSTRUCTURE | PuppetGame::kITEM | PuppetGame::kPLAYER | PuppetGame::kBEHAVIOUR | PuppetGame::kBOUNDARY, -3)),
	playerCharacter4(new PuppetCharacterKnight(false, 3, world, PuppetGame::kPLAYER, PuppetGame::kGROUND | PuppetGame::kSTRUCTURE | PuppetGame::kITEM | PuppetGame::kPLAYER | PuppetGame::kBEHAVIOUR | PuppetGame::kBOUNDARY, -4))
{
	splashMessage = new Sprite();
	splashMessage->mesh->pushTexture2D(PuppetResourceManager::startupSplash);
	splashMessage->setShader(shader, true);
	splashMessage->childTransform->translate(1920.f*0.5, 1080.f*0.5f, 0);

	populateBackground();

	//Do we want some guys in here?
	
	playerCharacter1->setShader(shader, true);
	addChild(playerCharacter1, 1);
	playerCharacter1->addToLayeredScene(this, 1);
	playerCharacter1->behaviourManager->addBehaviour(new BehaviourAttack(playerCharacter1, 3, PuppetGame::kPLAYER));
	playerCharacter1->ai = true;

	playerCharacter2->setShader(shader, true);
	addChild(playerCharacter2, 1);
	playerCharacter2->addToLayeredScene(this, 1);
	playerCharacter2->behaviourManager->addBehaviour(new BehaviourAttack(playerCharacter2, 3, PuppetGame::kPLAYER));
	playerCharacter2->ai = true;

	playerCharacter3->setShader(shader, true);
	addChild(playerCharacter3, 1);
	playerCharacter3->addToLayeredScene(this, 1);
	playerCharacter3->behaviourManager->addBehaviour(new BehaviourAttack(playerCharacter4, 3, PuppetGame::kPLAYER));
	playerCharacter3->ai = true;

	playerCharacter4->setShader(shader, true);
	addChild(playerCharacter4, 1);
	playerCharacter4->addToLayeredScene(this, 1);
	playerCharacter4->behaviourManager->addBehaviour(new BehaviourAttack(playerCharacter3, 3, PuppetGame::kPLAYER));
	playerCharacter4->ai = true;

	/*gameCam->addTarget(playerCharacter1->torso);
	gameCam->addTarget(playerCharacter2->torso);
	gameCam->addTarget(playerCharacter3->torso);
	gameCam->addTarget(playerCharacter4->torso);*/

	playerCharacter1->translateComponents(glm::vec3(0.5f * sceneWidth*0.25f, 35, 0.f));
	playerCharacter2->translateComponents(glm::vec3(1.5f * sceneWidth*0.25f, 35, 0.f));
	playerCharacter3->translateComponents(glm::vec3(2.5f * sceneWidth*0.25f, 35, 0.f));
	playerCharacter4->translateComponents(glm::vec3(3.5f * sceneWidth*0.25f, 35, 0.f));

	gameCam->offset = glm::vec3(sceneWidth*0.5f, sceneHeight*0.5f, 0);
}
void StartupScene::complete(std::string _switchTo){
	if (_switchTo == ""){
		PuppetGame * pg = static_cast<PuppetGame *>(game);
		pg->loadRandomScene();
	}else{
		PuppetScene::complete(_switchTo);
	}
}

void StartupScene::update(Step * _step){
	PuppetScene::update(_step);
	if(!splashSoundPlayed){
		PuppetResourceManager::splashSounds->play("Startup-alt");
		splashSoundPlayed = true;
	}
}
void StartupScene::triggerVictoryState(){
	// intentionally left blank: since there are no players, this function will be called automatically at the start of the scene
}

void StartupScene::populateBackground(){

}