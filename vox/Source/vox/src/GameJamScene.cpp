#pragma once

#include "GameJamScene.h"

#include "Texture.h"
#include "Sprite.h"
#include "shader/BaseComponentShader.h"
#include "shader/ShaderComponentTexture.h"
#include "shader/ShaderComponentShadow.h"
#include "shader/ShaderComponentPhong.h"
#include "Keyboard.h"
#include "SpriteSheet.h"
#include "Rectangle.h"
#include "SpriteSheetAnimation.h"
#include "Vox.h"
#include "SoundManager.h"
#include "Box2DSprite.h"
#include "Box2DWorld.h"
#include "ControllableOrthographicCamera.h"
#include "Resource.h"
#include "RenderOptions.h"

#include <array>
#include <libzplay.h>
#include <Box2D/Box2D.h>
#include <Box2DDebugDraw.h>
#include "Box2DMeshEntity.h"
#include "MeshFactory.h"
#include "FollowCamera.h"
#include "MousePerspectiveCamera.h"
#include "BitmapFont.h"
#include "CylinderScreen.h"
#include "TestCharacter.h"
#include "CharacterComponent.h"
#include "Character1.h"
#include "Character2.h"
#include "Character3.h"
#include "Character4.h"
#include "DialogHandler.h"
#include "SayAction.h"
#include "RandomCharacter.h"
#include "GameJamContactListener.h"
#include "Game.h"

GameJamContactListener cl;

GameJamScene::GameJamScene(Game * _game):
	LayeredScene(_game, 3),
	world(new Box2DWorld(b2Vec2(0, -60))),
	drawer(new Box2DDebugDraw(this, world)),

	playerCharacter(new TestCharacter(world, false, PLAYER, PROP | NPC | BOUNDARY, -1)),
	
	ground(new Box2DMeshEntity(world, MeshFactory::getPlaneMesh(), b2_staticBody)),
	shader(new BaseComponentShader()),
	soundManager(new SoundManager(-1)),
	backgroundScreen(new CylinderScreen(75, playerCharacter->torso->transform, 4)),
	midgroundScreen(new CylinderScreen(50, playerCharacter->torso->transform, 4)),
	foregroundScreen(new CylinderScreen(50, playerCharacter->torso->transform, 4))
{
	world->b2world->SetContactListener(&cl);
	shader->components.push_back(new ShaderComponentTexture(shader));
	shader->compileShader();
	renderOptions->alphaSorting = true;

	const int imgCount = 15;
	std::string strings[imgCount] = {
		"../assets/props/Table_657_332.png",		
		"../assets/props/TourDePizza_738_854.png",
		"../assets/props/ArtisticStatue_820_915.png",
		"../assets/props/BullitenBoard_573_353.png",
		"../assets/props/Cat_441_726.png",
		"../assets/props/Creepy_263_470.png",
		"../assets/props/DeadPlant_228_468.png",
		"../assets/props/Garbage_300_374.png",
		"../assets/props/HealthyPlant_272_877.png",
		"../assets/props/JollySkeleton_399_916.png",
		"../assets/props/Lockers_1024_604.png",
		"../assets/props/Pie_667_692.png",
		"../assets/props/GarbageBags_296_247.png",
		"../assets/props/HopHorse_253_511.png",
		"../assets/props/WigHead_228_257.png"
	};

	for(unsigned long int i = 0; i < (unsigned long int)10+std::rand()%20; ++i){
		unsigned long int tex = std::rand()%imgCount;
		Box2DSprite * s = new Box2DSprite(world, b2_staticBody, false, nullptr, new Transform());
		s->mesh->pushTexture2D(new Texture(strings[tex].c_str(), 1024, 1024, true, true));

		unsigned long int width = 0;
		unsigned long int height = 0;

		unsigned long int cc = 0;

		std::string temp = strings[tex];

		for(char c : temp){
			if(c == '_' || c == '.'){
				temp.at(cc) = ' ';
			}
			cc++;
		}
		std::string arr[4];
		int j = 0;
		std::stringstream ssin(temp);
		while (ssin.good() && j < 4){
			ssin >> arr[j];
			++j;
		}

		width =  atoi(arr[1].c_str());
		height =  atoi(arr[2].c_str());

		float scale = 0.002f;

		b2PolygonShape tShape;

		float scaleMult = ((std::rand()%50)/50.f)+0.5f;
		s->transform->scale(scaleMult, scaleMult, scaleMult);

		glm::vec3 scaleVec = s->transform->getScaleVector();

		tShape.SetAsBox(width*std::abs(scaleVec.x)*scale*2.f, height*std::abs(scaleVec.y)*scale*2.f);
		b2PolygonShape tsShape;
		tsShape.SetAsBox(width*std::abs(scaleVec.x)*scale*2.f, height*std::abs(scaleVec.y)*scale*2.f);
		b2Fixture * sfx = s->body->CreateFixture(&tShape, 1); // physical
		b2Fixture * ssfx = s->body->CreateFixture(&tsShape, 1); // sensor
		ssfx->SetSensor(true);

		// physical
		b2Filter t;
		t.groupIndex = -8;
		s->body->GetFixtureList()->SetFilterData(t);
		
		b2Filter ts;
		ts.categoryBits = PROP;
		ts.maskBits = PLAYER;
		s->body->GetFixtureList()->GetNext()->SetFilterData(ts);
		

		b2Vec2 v1 = tShape.GetVertex(0);
		b2Vec2 v2 = tShape.GetVertex(1);
		b2Vec2 v3 = tShape.GetVertex(2);
		b2Vec2 v4 = tShape.GetVertex(3);

		s->mesh->vertices.at(0).x = v1.x;
		s->mesh->vertices.at(0).y = v1.y;
		s->mesh->vertices.at(1).x = v2.x;
		s->mesh->vertices.at(1).y = v2.y;
		s->mesh->vertices.at(2).x = v3.x;
		s->mesh->vertices.at(2).y = v3.y;
		s->mesh->vertices.at(3).x = v4.x;
		s->mesh->vertices.at(3).y = v4.y;
	
		unsigned long int mag = std::max(s->mesh->getTexture(0)->width, s->mesh->getTexture(0)->height);
		s->mesh->vertices.at(3).u = 0;
		s->mesh->vertices.at(3).v = 0;
		s->mesh->vertices.at(2).u = (float)width/mag;
		s->mesh->vertices.at(2).v = 0;
		s->mesh->vertices.at(1).u = (float)width/mag;
		s->mesh->vertices.at(1).v = (float)height/mag;
		s->mesh->vertices.at(0).u = 0;
		s->mesh->vertices.at(0).v = (float)height/mag;
		s->mesh->dirty = true;
		
		s->setTranslationPhysical(std::rand()%1000 - 500.f, height*scale, 0.01f);
		s->setShader(shader, true);
		items.push_back(s);
	}
	ground->setShader(shader, true);
	ground->setTranslationPhysical(0, -5.f, -5.f, true);
	ground->transform->rotate(90.f, 1, 0, 0, kOBJECT);
	ground->transform->scale(1000, 10, 1);
	ground->mesh->setUV(3, 0, 0);
	ground->mesh->setUV(2, 200.f, 0);
	ground->mesh->setUV(1, 200.f, 2.f);
	ground->mesh->setUV(0, 0, 2.f);
	ground->mesh->dirty = true;
	ground->mesh->uvEdgeMode = GL_REPEAT;
	ground->body->SetTransform(b2Vec2(0, -10), 0);
	
	ground->mesh->vertices.at(0).z -= 10;
	ground->mesh->vertices.at(1).z -= 10;
	ground->mesh->vertices.at(2).z -= 10;
	ground->mesh->vertices.at(3).z -= 10;

	world->addToWorld(ground, 2);
	for(Box2DSprite * s : items){
		world->addToWorld(s);
	}

	backgroundScreen->transform->rotate(-90.f, 0.f, 1.f, 0.f, CoordinateSpace::kOBJECT);
	backgroundScreen->transform->scale(25, 100, 100);
	backgroundScreen->transform->translate(0, 0, -50);
	backgroundScreen->setShader(shader, true);
	
	midgroundScreen->transform->rotate(-90.f, 0.f, 1.f, 0.f, CoordinateSpace::kOBJECT);
	midgroundScreen->transform->scale(25, 43, 43);
	midgroundScreen->transform->translate(0, -6, -19);
	midgroundScreen->setShader(shader, true);
	
	foregroundScreen->transform->rotate(-90.f, 0.f, 1.f, 0.f, CoordinateSpace::kOBJECT);
	foregroundScreen->transform->scale(-2, 12.f, 12.f);
	foregroundScreen->transform->translate(0, 0, 6.0f);
	
	for(Vertex & v :foregroundScreen->mesh->vertices){
		//v.x += 0.5f;
		v.u += 0.5f;
	}
	foregroundScreen->mesh->dirty = true;
	foregroundScreen->setShader(shader, true);
	
	for(Box2DSprite * s : items){
		addChild(s, 1);
	}
	//addChild(foregroundScreen);
	//addChild(fontM);
	addChild(backgroundScreen, 0);
	addChild(midgroundScreen, 0);
	addChild(ground, 0);
	//addChild(foregroundScreen, 2);
	FollowCamera * followCam = new FollowCamera(50, glm::vec3(0, 0, 0), 0, 0);
	cameras.push_back(followCam);
	followCam->addTarget(playerCharacter->torso);
	followCam->minimumZoom = 25.f;
	followCam->farClip = 1000.f;
	followCam->transform->rotate(90, 0, 1, 0, kWORLD);
	
	followCam->transform->translate(5.f, 0.f, 15.f);
	followCam->yaw = 90.0f;
	followCam->pitch = -10.0f;

	activeCamera = followCam;

	world->b2world->SetDebugDraw(drawer);
	drawer->SetFlags(b2Draw::e_shapeBit);
	addChild(drawer, 1);

	//keep a vector of the characters, for the dialogHandlert
	std::vector<GameJamCharacter *> sceneCharacters;


	GameJamCharacter * char1 = new Character1(world, true, NPC, NPC | BOUNDARY | PLAYER | PROP, -2);
	char1->setShader(shader, true);
	char1->addToLayeredScene(this, 1);
	addChild(char1, 1);
	char1->translateComponents(glm::vec3(std::rand()%150, std::rand()%1250, 0));

	GameJamCharacter * char2 = new Character2(world, true, NPC, NPC | BOUNDARY | PLAYER | PROP, -3);
	char2->setShader(shader, true);
	char2->addToLayeredScene(this, 1);
	addChild(char2, 1);
	char2->translateComponents(glm::vec3(std::rand()%150, std::rand()%1250, 0));

	GameJamCharacter * char3 = new Character3(world, true, NPC, NPC | BOUNDARY | PLAYER | PROP, -4);
	char3->setShader(shader, true);
	char3->addToLayeredScene(this, 1);
	addChild(char3, 1);
	char3->translateComponents(glm::vec3(std::rand()%150, std::rand()%1250, 0));

	GameJamCharacter * char4 = new Character4(world, true, NPC, NPC | BOUNDARY | PLAYER | PROP, -5);
	char4->setShader(shader, true);
	char4->addToLayeredScene(this, 1);
	char4->translateComponents(glm::vec3(std::rand()%150, std::rand()%1250, 0));
	addChild(char4, 1);

	sceneCharacters.push_back(char1);
	sceneCharacters.push_back(char2);
	sceneCharacters.push_back(char3);
	sceneCharacters.push_back(char4);

	dialogHandler = new DialogHandler(sceneCharacters);
	dialogHandler->makeDialog();

	playerCharacter->text->setText("Howdy Ya'll, My Name's Baby Legs Hetman");
	
	for(signed long int i = 0; i < 10; ++i){
		RandomCharacter * dude1 = new RandomCharacter(world, true, NPC, NPC | BOUNDARY | PLAYER | PROP, -(6+i));
		dude1->setShader(shader, true);
		dude1->addToLayeredScene(this, 1);
		dude1->translateComponents(glm::vec3(std::rand()%200, std::rand()%1250, 0));
		addChild(dude1, 1);

		sceneCharacters.push_back(dude1);
		
		if(std::rand() % 500 / 500.f < 0.5f){
			dude1->reactiveFeet = false;
		}
		if(std::rand() % 500 / 500.f < 0.5f){
			dude1->reactiveBody = false;
		}
	}
	playerCharacter->setShader(shader, true);
	addChild(playerCharacter, 1);
	playerCharacter->addToLayeredScene(this, 1);
	playerCharacter->torso->maxVelocity = b2Vec2(10, NO_VELOCITY_LIMIT);

	int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
	std::cout<<"ds";
}

GameJamScene::~GameJamScene(){
}

void GameJamScene::load(){
	Scene::load();
}

void GameJamScene::unload(){
	Scene::unload();
}

void GameJamScene::update(Step * _step){
	Scene::update(_step);

	world->update(_step);
	if(keyboard->keyJustDown(GLFW_KEY_W)){
		if(playerCharacter->torso->body->GetPosition().y < 12){
			playerCharacter->torso->applyLinearImpulseUp(400);
		}
	}
	if(keyboard->keyDown(GLFW_KEY_S)){
		//playerCharacter->transform->rotate(1, 0, 1, 0, kOBJECT);
		playerCharacter->reactiveFeet = false;
		playerCharacter->reactiveBody = false;
	}else{
		playerCharacter->reactiveFeet = true;
		playerCharacter->reactiveBody = true;
	}
	if(keyboard->keyDown(GLFW_KEY_A)){
		playerCharacter->torso->applyLinearImpulseLeft(25);
		if(playerCharacter->transform->getScaleVector().x < 0){
			playerCharacter->transform->scale(-1, 0, 0);
		}
		//playerCharacter->playAnimation = true;
		//playerCharacter->setCurrentAnimation("run");

		if(playerCharacter->reactiveFeet){
			b2ContactEdge * stuff = playerCharacter->leftLowerLeg->body->GetContactList();
			if(stuff != nullptr && stuff->contact->IsTouching()){
				int type1 = (int)stuff->contact->GetFixtureA()->GetUserData();
				int type2 = (int)stuff->contact->GetFixtureB()->GetUserData();

				if(type1 != type2){
					if(playerCharacter->leftLowerLeg->body->GetLinearVelocity().y <= 0.1){
						playerCharacter->leftLowerLeg->applyLinearImpulseLeft(5);
						playerCharacter->leftLowerLeg->applyLinearImpulseUp(125);	
						playerCharacter->torso->applyLinearImpulseUp(125);	
					}
				}
			}
			stuff = playerCharacter->rightLowerLeg->body->GetContactList();
			if(stuff != nullptr && stuff->contact->IsTouching()){
				int type1 = (int)stuff->contact->GetFixtureA()->GetUserData();
				int type2 = (int)stuff->contact->GetFixtureB()->GetUserData();

				if(type1 != type2){
					if(playerCharacter->rightLowerLeg->body->GetLinearVelocity().y <= 0.1){
						playerCharacter->rightLowerLeg->applyLinearImpulseLeft(5);
						playerCharacter->rightLowerLeg->applyLinearImpulseUp(125);
						playerCharacter->torso->applyLinearImpulseUp(125);	
					}
				}
			}
		}

	}
	if(keyboard->keyDown(GLFW_KEY_D)){
		playerCharacter->torso->applyLinearImpulseRight(25);
		if(playerCharacter->transform->getScaleVector().x > 0){
			playerCharacter->transform->scale(-1, 0, 0);
		}
		//playerCharacter->setCurrentAnimation("run");
		//playerCharacter->playAnimation = true;

		if(playerCharacter->reactiveFeet){
		b2ContactEdge * stuff = playerCharacter->leftLowerLeg->body->GetContactList();
		if(stuff != nullptr && stuff->contact->IsTouching()){
			int type1 = (int)stuff->contact->GetFixtureA()->GetUserData();
			int type2 = (int)stuff->contact->GetFixtureB()->GetUserData();

			if(type1 != type2){
				if(playerCharacter->leftLowerLeg->body->GetLinearVelocity().y <= 0.1){
					playerCharacter->leftLowerLeg->applyLinearImpulseRight(5);
					playerCharacter->leftLowerLeg->applyLinearImpulseUp(50);	
					playerCharacter->torso->applyLinearImpulseUp(100);	
				}
			}
		}
		stuff = playerCharacter->rightLowerLeg->body->GetContactList();
		if(stuff != nullptr && stuff->contact->IsTouching()){
			int type1 = (int)stuff->contact->GetFixtureA()->GetUserData();
			int type2 = (int)stuff->contact->GetFixtureB()->GetUserData();

			if(type1 != type2){
				if(playerCharacter->rightLowerLeg->body->GetLinearVelocity().y <= 0.1){
					playerCharacter->rightLowerLeg->applyLinearImpulseRight(5);
					playerCharacter->rightLowerLeg->applyLinearImpulseUp(50);
					playerCharacter->torso->applyLinearImpulseUp(100);	
				}
			}
		}

		}
	}

	// move the ground and background with the player
	//ground->setTranslationPhysical(playerCharacter->transform->translationVector.x, ground->transform->translationVector.y, ground->transform->translationVector.z);

	// camera controls
	if(keyboard->keyDown(GLFW_KEY_UP)){
		activeCamera->transform->translate((activeCamera->forwardVectorRotated) * static_cast<MousePerspectiveCamera *>(activeCamera)->speed);
	}
	if(keyboard->keyDown(GLFW_KEY_DOWN)){
		activeCamera->transform->translate((activeCamera->forwardVectorRotated) * -static_cast<MousePerspectiveCamera *>(activeCamera)->speed);	
	}
	if(keyboard->keyDown(GLFW_KEY_LEFT)){
		activeCamera->transform->translate((activeCamera->rightVectorRotated) * -static_cast<MousePerspectiveCamera *>(activeCamera)->speed);		
	}
	if(keyboard->keyDown(GLFW_KEY_RIGHT)){
		activeCamera->transform->translate((activeCamera->rightVectorRotated) * static_cast<MousePerspectiveCamera *>(activeCamera)->speed);	
	}
	if(keyboard->keyJustUp(GLFW_KEY_F11)){
		game->toggleFullScreen();
	}
	if(keyboard->keyJustUp(GLFW_KEY_2)){
		drawer->drawing = !drawer->drawing;
	}
	
	int count;
	const unsigned char* axes = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &count);

	//std::cout<<axes;
	for(int i = 0; i < count; i++){
		std::cout<<i<<std::string(" ")<<(int)axes[i]<<std::endl;
	}

	//DIALOG
	dialogHandler->update(_step);
}

void GameJamScene::render(vox::MatrixStack* _matrixStack, RenderOptions* _renderOptions){
	LayeredScene::render(_matrixStack, _renderOptions);
}