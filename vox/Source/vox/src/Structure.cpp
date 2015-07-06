#pragma once

#include "Structure.h"
#include "Box2DSprite.h"
#include "Box2DWorld.h"
#include "shader/Shader.h"
#include "Scene.h"
#include "BitmapFont.h"

#include "Texture.h"

Structure::Structure(Box2DWorld * _world, int16 _categoryBits, int16 _maskBits, int16 _groupIndex) :
	Box2DSuperSprite(_world, _categoryBits, _maskBits, _groupIndex)
{
	componentScale = 0.0025f;
}