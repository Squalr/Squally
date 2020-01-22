#include "WoodDoorSpawn.h"

#include "Engine/Sound/Sound.h"

#include "Resources/SoundResources.h"

using namespace cocos2d;

const std::string WoodDoorSpawn::MapKeyWoodDoorSpawn = "spawn-wood-door";

WoodDoorSpawn* WoodDoorSpawn::create(ValueMap& properties)
{
	WoodDoorSpawn* instance = new WoodDoorSpawn(properties);

	instance->autorelease();

	return instance;
}

WoodDoorSpawn::WoodDoorSpawn(ValueMap& properties) : super(properties)
{
	this->doorSound = Sound::create(SoundResources::Platformer_Objects_Doors_WoodDoorOpen1);

	this->addChild(this->doorSound);
}

WoodDoorSpawn::~WoodDoorSpawn()
{
}

void WoodDoorSpawn::onPlayerSpawn()
{
	super::onPlayerSpawn();

	this->doorSound->play();
}
