#include "EgyptianChest.h"

#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string EgyptianChest::MapKey = "egyptian-chest";

EgyptianChest* EgyptianChest::create(ValueMap& properties)
{
	EgyptianChest* instance = new EgyptianChest(properties);

	instance->autorelease();

	return instance;
}

EgyptianChest::EgyptianChest(ValueMap& properties) : super(properties, Size(128.0f, 96.0f))
{
	Sprite* chestOpenFrontSprite = Sprite::create(ObjectResources::Interactive_Chests_EgyptianChestOpen);
	Sprite* chestClosedSprite = Sprite::create(ObjectResources::Interactive_Chests_EgyptianChestClosed);

	this->chestOpen->addChild(chestOpenFrontSprite);
	this->chestClosed->addChild(chestClosedSprite);
}

EgyptianChest::~EgyptianChest()
{
}
