#pragma once

#include "DialogHandler.h"
#include "DialogEvent.h"
#include "Transform.h"
#include "BitmapFont.h"

DialogHandler::DialogHandler(std::vector<Character *> _sceneCharacters):
	NodeUpdatable(),
	sceneCharacters(_sceneCharacters),
	dialogEvent(new DialogEvent())
{
	
}

DialogHandler::~DialogHandler(){
}

void DialogHandler::makeDialog(){
	int charVecSize = sceneCharacters.size();
	int randDialog = rand() % charVecSize;
	for(unsigned long int i = 0; i < charVecSize; i++){
		dialogEvent->addAction(new SayAction(sceneCharacters[i], dialogBits[randDialog], dialogBits[randDialog].length()/2));
	}
	dialogEvent->running = true;
}

void DialogHandler::update(Step* _step){
	dialogEvent->update(_step);
}