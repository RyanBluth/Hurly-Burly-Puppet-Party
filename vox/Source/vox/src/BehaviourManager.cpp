#pragma once

#include "BehaviourManager.h"
#include "Behaviour.h"

#include "PuppetScene.h"
#include "PuppetCharacter.h"
#include "Box2DSprite.h"

BehaviourManager::BehaviourManager(PuppetCharacter * _target) :
	target(_target)
{
}

BehaviourManager::~BehaviourManager(){
	while(behaviours.size() > 0){
		delete behaviours.back();
		behaviours.pop_back();
	}
}

void BehaviourManager::update(Step * _step){
	for(unsigned long int i = 0; i < behaviours.size(); ++i){
		if(behaviours.at(i)->active){
			//std::cout << behaviours.at(i)->targets.size() << std::endl;
			behaviours.at(i)->update(_step);
		}
	}
}

void BehaviourManager::addBehaviour(Behaviour * _behaviour){
	behaviours.push_back(_behaviour);
}