#pragma once

#include <SlayTheDragon.h>
#include <SlayTheDragonContactListener.h>
#include <SlayTheDragonResourceManager.h>
#include <PuppetGame.h>
#include <Fortification.h>
#include <PuppetCharacter.h>
#include <FollowCamera.h>
#include <BehaviourManager.h>
#include <Behaviour.h>
#include <BehaviourFollow.h>
#include <BehaviourPatrol.h>
#include <BehaviourAttack.h>
#include <BehaviourAttackThrow.h>
#include <Box2DSprite.h>
#include <Box2DWorld.h>
#include <MeshEntity.h>
#include <MeshInterface.h>
#include <MeshFactory.h>
#include <shader/ComponentShaderBase.h>
#include <keyboard.h>
#include <Texture.h>
#include <TextureSampler.h>
#include <PuppetCharacterDragon.h>
#include <PuppetCharacterArcher.h>
#include <PuppetTexturePack.h>
#include <PuppetController.h>
#include <ItemSimpleWeapon.h>
#include <ItemProjectileWeapon.h>
#include <ItemFireballLauncher.h>
#include <NumberUtils.h>

#include <glfw\glfw3.h>
#include <SoundManager.h>
#include <Box2DMeshEntity.h>


SlayTheDragon::SlayTheDragon(PuppetGame* _game):
	PuppetScene(_game, 30, 170.f, 120.f),
	fort(new Fortification(world, PuppetGame::kSTRUCTURE, PuppetGame::kITEM | PuppetGame::kPLAYER)),
    fortForeground(new Box2DSprite(world, SlayTheDragonResourceManager::fortForeground, b2_staticBody, false, nullptr, 0.03f)),
	playerCharacter1(new PuppetCharacterArcher(false, world, PuppetGame::kPLAYER, PuppetGame::kGROUND | PuppetGame::kSTRUCTURE | PuppetGame::kITEM | PuppetGame::kPLAYER | PuppetGame::kBEHAVIOUR | PuppetGame::kBOUNDARY | PuppetGame::kDEAD_ZONE, -1)),
	playerCharacter2(new PuppetCharacterArcher(false, world, PuppetGame::kPLAYER, PuppetGame::kGROUND | PuppetGame::kSTRUCTURE | PuppetGame::kITEM | PuppetGame::kPLAYER | PuppetGame::kBEHAVIOUR | PuppetGame::kBOUNDARY | PuppetGame::kDEAD_ZONE, -2)),
	playerCharacter3(new PuppetCharacterArcher(false, world, PuppetGame::kPLAYER, PuppetGame::kGROUND | PuppetGame::kSTRUCTURE | PuppetGame::kITEM | PuppetGame::kPLAYER | PuppetGame::kBEHAVIOUR | PuppetGame::kBOUNDARY | PuppetGame::kDEAD_ZONE, -3)),
	playerCharacter4(new PuppetCharacterDragon(false, world, PuppetGame::kPLAYER, PuppetGame::kGROUND | PuppetGame::kITEM | PuppetGame::kPLAYER | PuppetGame::kBEHAVIOUR | PuppetGame::kBOUNDARY, -4))
{
	ghostPosition = 30.0f;
	cl = new SlayTheDragonContactListener(this);
	cl->damageScoreMult = 1;
	
	Sprite * fortBg = new Sprite();
	fort->addToLayeredScene(this, 1);
	addChild(fortBg, 0);
	fortBg->setShader(shader, true);
	fortBg->pushTextureSampler(SlayTheDragonResourceManager::fortBackground);
	fortBg->parents.at(0)->translate(65.0f, 20.0f, 0.0f);
	fortBg->parents.at(0)->scale(2.6f, 2.6f, 1.0f);

	splashMessage = new Sprite();
	splashMessage->mesh->pushTexture2D(SlayTheDragonResourceManager::splashMessage->texture);
	splashMessage->setShader(shader, true);
	splashMessage->childTransform->translate(1920.f*0.5, 1080.f*0.5f, 0);
	
	// dragon needs to be first bc the fire particles should draw underneath other players
	
	players.push_back(playerCharacter1);
	players.push_back(playerCharacter2);
	players.push_back(playerCharacter3);
	players.push_back(playerCharacter4);

    b2Filter sf;
    sf.categoryBits = PuppetGame::kGROUND;
    sf.groupIndex = 0;
    sf.maskBits = PuppetGame::kITEM | PuppetGame::kPLAYER;

    fortForeground->createFixture(sf, b2Vec2(0, 0), fortForeground);
	
	for(unsigned long int i = 0; i < fortForeground->mesh->vertices.size(); ++i){
		fortForeground->mesh->vertices.at(i).y += 2.0f;
	}
	fortForeground->mesh->dirty = true;

    fortForeground->setShader(shader, true);
    addChild(fortForeground, 2);

    fortForeground->setTranslationPhysical(glm::vec3(0, fortForeground->getCorrectedHeight(), 0));

    fort->translateComponents(glm::vec3(0.f, fortForeground->getCorrectedHeight() + 31.f, 0.f));
	
	addChild(playerCharacter4, 1);
	playerCharacter4->addToLayeredScene(this, 1);
	addChild(playerCharacter1, 1);
	playerCharacter1->addToLayeredScene(this, 1);
	addChild(playerCharacter2, 1);
	playerCharacter2->addToLayeredScene(this, 1);
	addChild(playerCharacter3, 1);
	playerCharacter3->addToLayeredScene(this, 1);

	playerCharacter4->score = 10000;
	playerCharacter4->lastUpdateScore = playerCharacter4->score;
	


	assignControllers();

	
	dragon = static_cast<PuppetCharacterDragon * >(playerCharacter4);

	TextureSampler * bowTex = SlayTheDragonResourceManager::itemBow;
	TextureSampler * arrowTex = SlayTheDragonResourceManager::itemArrow;
	TextureSampler * fireballTex = SlayTheDragonResourceManager::itemFireball;

	unsigned int pCnt = 0;
	for(PuppetCharacter * p : players){
		ItemProjectileWeapon * weapon;
		if(p == dragon){
			weapon = new ItemFireballLauncher(dragon, world);
		}else{
			weapon = new ItemProjectileWeapon(arrowTex, bowTex, world, PuppetGame::kITEM, PuppetGame::kPLAYER | PuppetGame::kBOUNDARY | PuppetGame::kGROUND | PuppetGame::kSTRUCTURE, p->groupIndex, 0.1, 3, 0, -bowTex->height);
		}
		weapon->addToLayeredScene(this, 1);
		weapon->setShader(shader, true);
		p->itemToPickup = weapon;
		addChild(weapon, 1);
		p->translateComponents(glm::vec3(40.f + (pCnt * 20), fortForeground->getCorrectedHeight() * 2, 0));
		p->setShader(shader, true);
	}
	
	playerCharacter1->translateComponents(glm::vec3(20.f, fort->rootComponent->getCorrectedHeight() * 1.2, 0.f));
	playerCharacter2->translateComponents(glm::vec3(30.f, fort->rootComponent->getCorrectedHeight() * 1.2, 0.f));
	playerCharacter3->translateComponents(glm::vec3(40.f, fort->rootComponent->getCorrectedHeight() * 1.2, 0.f));
	
	fort->setShader(shader, true);
	fort->addToLayeredScene(this, 1);
	addChild(fort, 1);
    fort->translateComponents(glm::vec3(80.0f, 0.f, 0.f));
    fortForeground->setTranslationPhysical(glm::vec3(80.0f, 0.f, 0.f), true);

	Box2DMeshEntity * deathBounds = new Box2DMeshEntity(world, MeshFactory::getPlaneMesh(), b2_staticBody);
	addChild(deathBounds, 2);
	deathBounds->parents.at(0)->scale(100.f, 18.f, 1.f);
	deathBounds->setTranslationPhysical(60.f, -18.f, 0.f);
	world->addToWorld(deathBounds);
	b2Filter sfd;
	sfd.categoryBits = PuppetGame::kDEAD_ZONE;
	//sfd.maskBits = -1;
	deathBounds->body->GetFixtureList()->SetFilterData(sfd);
	deathBounds->setShader(shader, true);

	playRandomBackgroundMusic();

	populateClouds();

	
	// create indicators and add to followcam
	for(PuppetCharacter * p : players){
		p->createIndicator(p->id);
		gameCam->addTarget(p->indicator);
	}

	gameCam->useBounds = true;
	gameCam->minBounds.y = sceneHeight/8.f;
	gameCam->minBounds.height = sceneHeight/2.f;
}

SlayTheDragon::~SlayTheDragon(){
	delete stageFloor; // have to do this here because the ground is never added and therefore not deleted as one of the scene children
	delete stageFront; // have to do this here because the ground is never added and therefore not deleted as one of the scene children
}

void SlayTheDragon::update(Step* _step){
	PuppetScene::update(_step);

	if(!splashSoundPlayed){
		PuppetResourceManager::splashSounds->play("SlayTheDragon");
		splashSoundPlayed = true;
	}

    // handle archer's victory state
    if (dragon->dead){
        triggerVictoryState();
    }
    else{
        // handle dragon victory
        bool archersDead = true;
        for (unsigned long int i = 0; i < players.size() - 1; ++i){
            if (!players.at(i)->dead){
                archersDead = false;
                break;
            }
        }
        if (archersDead){
            triggerVictoryState();
        }
    }
}

void SlayTheDragon::render(vox::MatrixStack* _matrixStack, RenderOptions* _renderOptions){
	PuppetScene::render(_matrixStack, _renderOptions);
}

void SlayTheDragon::load(){
	PuppetScene::load();
}

void SlayTheDragon::unload(){
	PuppetScene::unload();
}