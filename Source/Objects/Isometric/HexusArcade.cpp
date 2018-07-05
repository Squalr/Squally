#include "HexusArcade.h"

HexusArcade* HexusArcade::create(ValueMap* initProperties)
{
	HexusArcade* instance = new HexusArcade(initProperties);

	instance->autorelease();

	return instance;
}

HexusArcade::HexusArcade(ValueMap* initProperties) : HackableObject(initProperties)
{
	// TODO: Swap in arcade machine art once created
	this->arcadeMachine = Sprite::create(Resources::Entities_Isometric_Squally_SquallyNW);

	this->addChild(this->arcadeMachine);
}

HexusArcade::~HexusArcade()
{
}

void HexusArcade::registerHackables()
{
	this->setButtonOffset(Vec2(0, -128.0f));
}
