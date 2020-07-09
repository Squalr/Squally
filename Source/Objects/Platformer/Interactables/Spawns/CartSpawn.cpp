#include "CartSpawn.h"

#include "Engine/Sound/Sound.h"

#include "Resources/SoundResources.h"

using namespace cocos2d;

const std::string CartSpawn::MapKey = "spawn-cart";

CartSpawn* CartSpawn::create(ValueMap& properties)
{
	CartSpawn* instance = new CartSpawn(properties);

	instance->autorelease();

	return instance;
}

CartSpawn::CartSpawn(ValueMap& properties) : super(properties)
{
}

CartSpawn::~CartSpawn()
{
}

void CartSpawn::onPlayerSpawn()
{
	super::onPlayerSpawn();
}
