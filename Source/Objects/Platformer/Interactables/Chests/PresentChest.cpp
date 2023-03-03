#include "PresentChest.h"

#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string PresentChest::MapKey = "present-chest";

PresentChest* PresentChest::create(ValueMap& properties)
{
	PresentChest* instance = new PresentChest(properties);

	instance->autorelease();

	return instance;
}

PresentChest::PresentChest(ValueMap& properties) : super(properties, CSize(128.0f, 112.0f))
{
	Sprite* chestOpenFrontSprite = Sprite::create(ObjectResources::Interactive_Chests_PresentChestOpen);
	Sprite* chestClosedSprite = Sprite::create(ObjectResources::Interactive_Chests_PresentChestClosed);

	this->chestOpen->addChild(chestOpenFrontSprite);
	this->chestClosed->addChild(chestClosedSprite);
}

PresentChest::~PresentChest()
{
}
