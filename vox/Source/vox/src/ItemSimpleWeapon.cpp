#pragma once

#include <ItemSimpleWeapon.h>
#include <Box2DWorld.h>
#include <Box2DSprite.h>

ItemSimpleWeapon::ItemSimpleWeapon(TextureSampler * _tex, bool _singleUse, Box2DWorld * _world, int16 _categoryBits, int16 _maskBits, int16 _groupIndex, int _damage, float _handleX, float _handleY):
	Item(_singleUse, _world, _categoryBits, _maskBits, _groupIndex, _damage, _handleX, _handleY)
{
	rootComponent = new Box2DSprite(_world, _tex, b2_dynamicBody, false, nullptr, componentScale);
	addComponent(&rootComponent);
	
	b2Filter sf;
	sf.categoryBits = categoryBits;
	if(maskBits != (int16)-1){
		sf.maskBits = maskBits;
	}else{
		sf.maskBits = 0;
	}
	sf.groupIndex = groupIndex;
	
	for(Box2DSprite ** c : components){
		(*c)->createFixture(sf);
		(*c)->body->GetFixtureList()->SetDensity(0.01f);
		(*c)->body->ResetMassData();
	}

	setUserData(this);
}

ItemSimpleWeapon::~ItemSimpleWeapon(){
}
