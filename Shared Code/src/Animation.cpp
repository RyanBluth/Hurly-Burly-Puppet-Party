#pragma once

#include "Animation.h"
#include "Step.h"
//#include "cinder/app/AppBasic.h"

float Animation::getTweenEndTime(unsigned long int _idx){
	if(_idx < tweens.size()){
		float tempTime = 0;
		for(unsigned long int i = 0; i <= _idx; ++i){
			tempTime += tweens.at(i)->deltaTime;
		}
		return tempTime;
	}else{
		throw "index outside bounds of tween array";
	}
}

float Animation::getTweenEndValue(unsigned long int _idx){
	if(_idx < tweens.size()){
		float value = startValue;
		for(unsigned long int i = 0; i <= _idx; ++i){
			value += tweens.at(i)->deltaValue;
		}
		return value;
	}else{
		throw "index outside bounds of tween array";
	}
}


Animation::Animation(float * const _prop) :
	prop(_prop),
	currentAnimationTime(0),
	currentTweenTime(0),
	currentTween(0),
	loopType(LoopType::kLOOP),
	referenceValue(*_prop),
	startValue(*_prop),
	hasStart(false)
{
}

void Animation::update(Step * _step){
	if(hasStart){
		currentAnimationTime += (float)_step->getDeltaTime();
		//ci::app::console() << "Animation.update() time: " << time << std::endl;
	}
	if(tweens.size() > 0){
		currentTweenTime += (float)_step->getDeltaTime();
		if(_step->getReverse()){
			while(currentTweenTime <= 0){
				if(currentTween > 0){
					currentTweenTime += tweens.at(currentTween-1)->deltaTime;
					referenceValue -= tweens.at(currentTween-1)->deltaValue;
					--currentTween;
				}else{
					currentTweenTime += tweens.at(tweens.size()-1)->deltaTime;
					referenceValue -= tweens.at(tweens.size()-1)->deltaValue;
					switch (loopType){
						case Animation::kLOOP:
						case Animation::kCONSTANT:
							referenceValue = startValue;
							for(unsigned long int i = 0; i+1 < tweens.size(); ++i){
								referenceValue += tweens.at(i)->deltaValue;
							}
						case Animation::kLOOP_WITH_OFFSET:
							currentTween = tweens.size() - 1;
							break;
						default:
							break;
					}
				}
			}
		}else{
			while(currentTweenTime > tweens.at(currentTween)->deltaTime){
				currentTweenTime -= tweens.at(currentTween)->deltaTime;
				referenceValue += tweens.at(currentTween)->deltaValue;
				if(currentTween < tweens.size()-1){
					++currentTween;
				}else{
					switch (loopType){
						case Animation::kLOOP:
						case Animation::kCONSTANT:
							referenceValue = startValue;
						case Animation::kLOOP_WITH_OFFSET:
							currentTween = 0;
							break;
						default:
							break;
					}
				}
			}
		}
		
		*prop = Easing::call(tweens.at(currentTween)->interpolation, currentTweenTime, referenceValue, tweens.at(currentTween)->deltaValue, tweens.at(currentTween)->deltaTime);
		
		// The time > sum-delta-time bit is inefficient since we don't keep a record of the total animation length (which we should), but it works
		if(loopType == kCONSTANT){
			if(currentAnimationTime < 0){
				*prop = startValue;
				//referenceValue = startValue;
			}else if(currentAnimationTime > getTweenEndTime(tweens.size()-1)){
				*prop = getTweenEndValue(tweens.size()-1);
				//referenceValue = getTweenEndValue(tweens.size()-2);
			}
		}

		// Display the start-frame value on the start frame (ordinarily it would show the last frame-value if looping)
		if(currentAnimationTime == 0){
			*prop = startValue;
			referenceValue = startValue;
			currentTween = 0;
			currentTweenTime = 0;
		}
	}
}

Animation::~Animation(){
	while(tweens.size() > 0){
		delete tweens.back();
		tweens.pop_back();
	}
}