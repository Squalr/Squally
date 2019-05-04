#include "HexusArcade.h"

#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string HexusArcade::MapKeyHexusArcade = "hexus-arcade";

HexusArcade* HexusArcade::create(ValueMap& properties)
{
	HexusArcade* instance = new HexusArcade(properties);

	instance->autorelease();

	return instance;
}

HexusArcade::HexusArcade(ValueMap& properties) : HackableObject(properties)
{
	this->arcadeMachine = Sprite::create();
	
	this->setZSorted(true);

	this->addChild(this->arcadeMachine);
}

HexusArcade::~HexusArcade()
{
}

Vec2 HexusArcade::getButtonOffset()
{
	return Vec2(0, -128.0f);
}
