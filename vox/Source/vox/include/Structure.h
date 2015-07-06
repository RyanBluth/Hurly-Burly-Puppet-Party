#pragma once

#include <Box2DSuperSprite.h>
#include <Box2DSprite.h>

class Structure : public Box2DSuperSprite {
public:

	explicit Structure(Box2DWorld * _world, int16 _categoryBits, int16 _maskBits = -1, int16 _groupIndex = 0);
	~Structure();
};