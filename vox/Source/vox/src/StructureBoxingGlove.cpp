#pragma once

#include <StructureBoxingGlove.h>
#include <PuppetGame.h>
#include <RapunzelResourceManager.h>
#include <Box2DWorld.h>

StructureBoxingGlove::StructureBoxingGlove(Box2DWorld * _world) :
	Structure(_world, PuppetGame::kSTRUCTURE, PuppetGame::kPLAYER, -25)
{
	
	componentScale = 0.016f;
	
	glove = new Box2DSprite(world, RapunzelResourceManager::glove, b2_dynamicBody, false, nullptr, componentScale/4.f);
	spring = new Box2DSprite(world, PuppetResourceManager::itemNone, b2_staticBody, false, nullptr, componentScale);
	
	addComponent(&glove);
	addComponent(&spring);
	rootComponent = spring;
	
	b2Filter sf;
	sf.categoryBits = categoryBits;
	if(maskBits != (int16)-1){
		sf.maskBits = maskBits;
	}
	sf.groupIndex = groupIndex;

	glove->createFixture(sf);

	sf.maskBits = 0;

	spring->createFixture(sf);

	setUserData(this);
	
	/*b2PolygonShape tShape;
	tShape.SetAsBox(base->width*std::abs(transform->scaleVector.x)*base->scale*2.f, std::abs(base->height*transform->scaleVector.y)*base->scale*2.f);
	
	b2Fixture * sensor = base->body->CreateFixture(&tShape, 1);
	sensor->SetSensor(true);
	sensor->SetUserData(this);

	sensor->SetFilterData(sf);*/
	
	spring->body->GetFixtureList()->SetDensity(10000000.f);

	// axel
	b2PrismaticJointDef jth;
	jth.bodyA = spring->body;
	jth.bodyB = glove->body;
	jth.localAnchorA.Set(0.0f * spring->getCorrectedWidth(), 0.f * spring->getCorrectedHeight());
	jth.localAnchorB.Set(-0.0f * glove->getCorrectedWidth(), 0.f * glove->getCorrectedHeight());
	jth.collideConnected = false;
	jth.enableLimit = true;
	jth.enableMotor = true;
	jth.lowerTranslation = -10.f;
	jth.upperTranslation = 0;
	jth.localAxisA = b2Vec2(1, 0);
	jth.maxMotorForce = 1000.f;
	jth.motorSpeed = 1000.f;
	jth.referenceAngle = 0.f;
	world->b2world->CreateJoint(&jth);
}

void StructureBoxingGlove::punch(){
	glove->applyLinearImpulseLeft(2000000000000000.0f);
}