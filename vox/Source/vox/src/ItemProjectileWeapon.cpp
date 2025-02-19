#pragma once

#include <ItemProjectileWeapon.h>
#include <Box2DWorld.h>
#include <Box2DSprite.h>
#include <LayeredScene.h>
#include <PuppetScene.h>
#include <shader\BaseComponentShader.h>

ItemProjectileWeapon::ItemProjectileWeapon(TextureSampler * _projectileTex, TextureSampler * _weaponTex, Box2DWorld * _world, int16 _categoryBits, int16 _maskBits, int16 _groupIndex, float _damage, float _projectileDamage, float _handleX, float _handleY):
	Item(false, _world, _categoryBits, _maskBits, _groupIndex, _damage, _handleX, _handleY),
	NodeTransformable(new Transform()),
	NodeChild(nullptr),
	NodeRenderable(),
	projectileTex(_projectileTex),
	projectileDamage(_projectileDamage)
{
	rootComponent = new Box2DSprite(_world, _weaponTex, b2_dynamicBody, false, nullptr, new Transform(), componentScale);
	components.push_back(&rootComponent);
	
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

ItemProjectileWeapon::~ItemProjectileWeapon(){
}

Item * ItemProjectileWeapon::getProjectile(bool _forceDrop){
	//Item * projectile = new Item(true, projectileTemplate->world, projectileTemplate->categoryBits, projectileTemplate->maskBits, projectileTemplate->groupIndex, projectileTemplate->damage, projectileTemplate->handleX, projectileTemplate->handleY);
    if (_forceDrop){
        return Item::getProjectile(_forceDrop);
    }
    
	Item * projectile = new Item(true, world, categoryBits, maskBits, groupIndex, projectileDamage, handleX, handleY);
	
	Box2DSprite ** test = new Box2DSprite*[1];
	test[0] = projectile->rootComponent = new Box2DSprite(world, projectileTex, b2_dynamicBody, false, nullptr, new Transform(), componentScale);

	projectile->components.push_back(test);

	b2Filter sf;
	sf.categoryBits = projectile->categoryBits;
	if(projectile->maskBits != (int16)-1){
		sf.maskBits = projectile->maskBits;
	}else{
		sf.maskBits = 0;
	}
	sf.groupIndex = projectile->groupIndex;
	
	for(Box2DSprite ** c : projectile->components){
		(*c)->createFixture(sf);
		(*c)->body->GetFixtureList()->SetDensity(0.01f);
		(*c)->body->ResetMassData();
	}

	projectile->setUserData(projectile);

	static_cast<PuppetScene *>(scene)->addChild(projectile, 1);
	static_cast<PuppetScene *>(scene)->items.push_back(projectile);
	//projectile->addToLayeredScene(static_cast<PuppetScene *>(scene), 1);
	projectile->setShader(static_cast<PuppetScene *>(scene)->shader, true);

	projectile->snapComponents(this->rootComponent);
	//projectile->translateComponents(glm::vec3(20,20,0));

	projectile->owner = owner;
	projectile->thrown = true;
	projectile->held = false;

	return projectile;
}