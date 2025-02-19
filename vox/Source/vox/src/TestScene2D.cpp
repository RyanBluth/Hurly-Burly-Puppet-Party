#pragma once

#include <Box2D\Box2D.h>

#include "Arduino.h"

#include "TestScene2D.h"
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

#include <array>
#include <libzplay.h>
#include <Box2D/Box2D.h>
#include <Box2DDebugDraw.h>
#include "Box2DMeshEntity.h"
#include "MeshFactory.h"
#include "FollowCamera.h"
#include "MousePerspectiveCamera.h"
#include "RenderOptions.h"

#include "Resource.h"

#include "CylinderScreen.h"

MeshEntity * me;
TestScene2D::TestScene2D(Game * _game):
	world(new Box2DWorld(b2Vec2(0, -60))),
	Scene(_game),
	sprite(new Box2DSprite(world, b2_dynamicBody, true, nullptr, new Transform())),
	ground(new Box2DMeshEntity(world, MeshFactory::getCubeMesh(), b2_staticBody)),
	frame(new Sprite()),
	tex(new Texture("../assets/spritesheet.png", 1024, 1024, true, true)),
	shader(new BaseComponentShader()),
	soundManager(new SoundManager(-1)),
	layer1(new Sprite()),
	layer2(new Sprite())
{
	renderOptions->alphaSorting = true;
	Box2DDebugDraw * drawer = new Box2DDebugDraw(this, world);

	//static_cast<ControllableOrthographicCamera*>(camera)->follow(sprite);

	activeCamera->transform->rotate(90, 0, 1, 0, kWORLD);
	

	soundManager->addNewSound("green_chair", "../assets/test.wav");
	soundManager->play("green_chair");
	
	shader->components.push_back(new ShaderComponentTexture(shader));
	shader->compileShader();

	sprite->setShader(shader, true);
	ground->setShader(shader, true);
	frame->setShader(shader, true);
	
	frame->transform->scale(20, 10, 1);
	frame->transform->translate(0.f, 5.f, -1.f);

	//addChild(frame);
	
	//spriteSheet = new SpriteSheetAnimation(tex, 0.05);
	//spriteSheet->pushFramesInRange(0, 26, 130, 150, 130 * 7);
	//sprite->addAnimation("run", spriteSheet, true);
	sprite->mesh->pushTexture2D(new Texture("../assets/MichaelScale.png", 1024, 1024, true, true));

	ground->setTranslationPhysical(0, -10, 0);
	ground->transform->scale(200, 10, 2);
	ground->mesh->pushTexture2D(new Texture("../assets/uv-test.jpg", 1000, 1000, true, true));

	sprite->transform->scale(4, 4, 1);
	sprite->setTranslationPhysical(0, 10, 0);

	sprite->maxVelocity = b2Vec2(10, NO_VELOCITY_LIMIT);

	world->addToWorld(sprite);
	world->addToWorld(ground);

	arduino = new Arduino("COM3");
	
	//camera = new MousePerspectiveCamera();
	activeCamera = new FollowCamera(50, glm::vec3(0, 10, 0), 5, 0);
	((FollowCamera*)activeCamera)->addTarget(sprite);
	activeCamera->transform->translate(5.0f, 0.0f, 20.0f);
	activeCamera->yaw = 90.0f;
	activeCamera->pitch = -10.0f;

	layer1->setShader(shader, true);
	layer2->setShader(shader, true);

	layer1->mesh->pushTexture2D(tex);
	layer2->mesh->pushTexture2D(tex);

	layer1->transform->scale(10.f, 10.f, 1.f);
	layer2->transform->scale(10.f, 10.f, 1.f);

	layer1->transform->translate(0.f, 0.f, -0.5f);
	layer2->transform->translate(2.f, 0.f, -1.f);
	ground->transform->translate(0.f, 0.f, -1.1f);
	
	addChild(layer2);
	addChild(sprite);
	addChild(layer1);
	addChild(ground);




	/*Box2DSprite * s = new Box2DSprite(world, b2BodyType::b2_dynamicBody, false);

	s->setShader(shader, true);
	
	b2Vec2 verts[4];
	verts[0] = b2Vec2(3, 0);
	verts[1] = b2Vec2(0, 6);
	verts[2] = b2Vec2(-3, 0);
	verts[3] = b2Vec2(-3, 3);

	b2PolygonShape shape;
	shape.Set(verts, 4);
	
	s->body->CreateFixture(&shape, 1);
	world->addToWorld(s);
	addChild(s);

	b2RevoluteJointDef j;
	j.bodyA = s->body;
	j.bodyB = sprite->body;
	world->b2world->CreateJoint(&j);

	world->b2world->SetDebugDraw(drawer);
	drawer->SetFlags(b2Draw::e_shapeBit);*/


	
	//me->mesh->dirty = true;

}
TestScene2D::~TestScene2D(){
}

void TestScene2D::load(){
	Scene::load();
}

void TestScene2D::unload(){
	Scene::unload();
}
void TestScene2D::update(Step * _step){
	float oldX = sprite->transform->getTranslationVector().x;

	Scene::update(_step);

	world->update(_step);
	//sprite->playAnimation = false;

	if(keyboard->keyDown(GLFW_KEY_W)){
		if(!sprite->movingVertically(0.05f)){
			sprite->applyLinearImpulseUp(500);	
		}
	}
	if(keyboard->keyDown(GLFW_KEY_S)){
		sprite->transform->rotate(1, 0, 1, 0, kOBJECT);
	}
	if(keyboard->keyDown(GLFW_KEY_A)){
		sprite->applyLinearImpulseLeft(50);
		if(sprite->transform->getScaleVector().x < 0){
			sprite->transform->scale(-1, 0, 0);
		}
		//sprite->playAnimation = true;
		//sprite->setCurrentAnimation("run");
	}
	if(keyboard->keyDown(GLFW_KEY_D)){
		sprite->applyLinearImpulseRight(50);
		if(sprite->transform->getScaleVector().x > 0){
			sprite->transform->scale(-1, 0, 0);
		}
		//sprite->setCurrentAnimation("run");
		//sprite->playAnimation = true;
	}

	//Add movement to the camera
	/*if(keyboard->keyDown(GLFW_KEY_W)){
		camera->transform->translate((activeCamera->forwardVectorRotated) * static_cast<MousePerspectiveCamera *>(camera)->speed);
	}
	if(keyboard->keyDown(GLFW_KEY_S)){
		camera->transform->translate((activeCamera->forwardVectorRotated) * -static_cast<MousePerspectiveCamera *>(camera)->speed);	
	}
	if(keyboard->keyDown(GLFW_KEY_A)){
		camera->transform->translate((activeCamera->rightVectorRotated) * -static_cast<MousePerspectiveCamera *>(camera)->speed);		
	}
	if(keyboard->keyDown(GLFW_KEY_D)){
		camera->transform->translate((activeCamera->rightVectorRotated) * static_cast<MousePerspectiveCamera *>(camera)->speed);	
	}*/

	/*if(arduino->IsConnected()) {
		char incomingData[256] = "";
		int readResult = arduino->ReadData(incomingData, 256);
		std::string test(incomingData);
		std::cout << test;
	}*/

	
	me->update(_step);
	
	
}

void TestScene2D::render(vox::MatrixStack* _matrixStack, RenderOptions* _renderOptions){
	Scene::render(_matrixStack, _renderOptions);
	world->b2world->DrawDebugData();
}

//Arduino Sketch
/*
const int  buttonPin0 = 2;  // the pin that the pushbutton is attached to
const int  buttonPin1 = 3;  // the pin that the pushbutton is attached to
const int  buttonPin2 = 4;  // the pin that the pushbutton is attached to
const int  buttonPin3 = 5;  // the pin that the pushbutton is attached to

int buttonState0 = 0;         // current state of the button
int buttonState1 = 0;         // current state of the button
int buttonState2 = 0;         // current state of the button
int buttonState3 = 0;         // current state of the button

void setup() {
  // initialize the button pin as a input:
  pinMode(buttonPin0, INPUT);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  
  // initialize serial communication:
  Serial.begin(9600);
}

// A printf function, taken from...
// https://gist.github.com/EleotleCram/eb586037e2976a8d9884
int aprintf(char *str, ...) {
	int i, j, count = 0;
 
	va_list argv;
	va_start(argv, str);
	for(i = 0, j = 0; str[i] != '\0'; i++) {
		if (str[i] == '%') {
			count++;
 
			Serial.write(reinterpret_cast<const uint8_t*>(str+j), i-j);
 
			switch (str[++i]) {
				case 'd': Serial.print(va_arg(argv, int));
					break;
				case 'l': Serial.print(va_arg(argv, long));
					break;
				case 'f': Serial.print(va_arg(argv, double));
					break;
				case 'c': Serial.print((char) va_arg(argv, int));
					break;
				case 's': Serial.print(va_arg(argv, char *));
					break;
				case '%': Serial.print("%");
					break;
				default:;
			};
 
			j = i+1;
		}
	};
	va_end(argv);
 
	if(i > j) {
		Serial.write(reinterpret_cast<const uint8_t*>(str+j), i-j);
	}
 
	return count;
}

void loop() {
  // read the pushbutton input pin:
  buttonState0 = digitalRead(buttonPin0);
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  int pressed[4] = {0, 0, 0, 0};
  if(buttonState0 == HIGH) {
    pressed[0] = 1;
  } 
  if(buttonState1 == HIGH) {
    pressed[1] = 2;
  } 
  if(buttonState2 == HIGH) {
    pressed[2] = 3;
  } 
  if(buttonState3 == HIGH) {
    pressed[3] = 4;
  }   
  aprintf("%d %d %d %d \n",
    pressed[0], pressed[1],
    pressed[2], pressed[3]);
}

*/