#pragma once

#include <iostream>
#include "Game.h"
#include "PuppetResourceManager.h"

class PuppetController;
class AccelerometerParser;

class PuppetGame:public Game{
public:
	AccelerometerParser * arduino;

	unsigned long int lastScene;

	std::vector<PuppetController *> puppetControllers;

	explicit PuppetGame(bool _running);
	~PuppetGame();
	virtual void update(Step * _step) override;
	void draw() override;
	
	void loadRandomScene();

	enum BOX2D_CATEGORY{
		kBOUNDARY = 0x0001,
		kSTRUCTURE = 0x0002,
		kITEM = 0x0004,		
		kGROUND = 0x0008,	
		kPLAYER = 0x00010,
		kBEHAVIOUR = 0x00020,
		kDEAD_ZONE = 0x00040,
		kCAT8 = 0x00080,
		kCAT9 = 0x00100,
		kCAT10 = 0x00200,
		kCAT11 = 0x00400,
		kCAT12 = 0x00800
	};
};