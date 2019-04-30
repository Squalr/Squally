#include "HexusArcade.h"

#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string HexusArcade::MapKeyHexusArcade = "hexus-arcade";

HexusArcade* HexusArcade::create(ValueMap& initProperties)
{
	HexusArcade* instance = new HexusArcade(initProperties);

	instance->autorelease();

	return instance;
}

HexusArcade::HexusArcade(ValueMap& initProperties) : HackableObject(initProperties)
{
	this->arcadeMachine = Sprite::create();

	this->addChild(this->arcadeMachine);
}

HexusArcade::~HexusArcade()
{
}

Vec2 HexusArcade::getButtonOffset()
{
	return Vec2(0, -128.0f);
}
