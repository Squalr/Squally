#include "EaxCrystal.h"

#include "cocos/2d/CCSprite.h"

#include "Resources/IsometricObjectResources.h"

using namespace cocos2d;

const std::string EaxCrystal::MapKeyEaxCrystal = "eax-crystal";

EaxCrystal* EaxCrystal::create(ValueMap& initProperties)
{
	EaxCrystal* instance = new EaxCrystal(initProperties);

	instance->autorelease();

	return instance;
}

EaxCrystal::EaxCrystal(ValueMap& initProperties) : HackableObject(initProperties)
{
	this->crystal = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EaxCrystal);

	this->addChild(this->crystal);
}

EaxCrystal::~EaxCrystal()
{
}
