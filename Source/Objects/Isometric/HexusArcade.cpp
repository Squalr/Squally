#include "HexusArcade.h"

HexusArcade* HexusArcade::create(ValueMap* initProperties)
{
	HexusArcade* instance = new HexusArcade(initProperties);

	instance->autorelease();

	return instance;
}

HexusArcade::HexusArcade(ValueMap* initProperties) : HackableObject(initProperties)
{
	this->arcadeMachine = Sprite::create(Resources::Objects_Isometric_HexusArcade);

	this->addChild(this->arcadeMachine);
}

HexusArcade::~HexusArcade()
{
}

void HexusArcade::registerHackables()
{
}

Vec2 HexusArcade::getButtonOffset()
{
	return Vec2(0, -128.0f);
}
