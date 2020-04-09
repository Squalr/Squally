#include "MetalChest.h"

#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string MetalChest::MapKey = "metal-chest";

MetalChest* MetalChest::create(ValueMap& properties)
{
	MetalChest* instance = new MetalChest(properties);

	instance->autorelease();

	return instance;
}

MetalChest::MetalChest(ValueMap& properties) : super(properties, Size(128.0f, 96.0f))
{
	Sprite* chestOpenFrontSprite = Sprite::create(ObjectResources::Interactive_Chests_MetalChestOpen);
	Sprite* chestClosedSprite = Sprite::create(ObjectResources::Interactive_Chests_MetalChestClosed);

	this->chestOpen->addChild(chestOpenFrontSprite);
	this->chestClosed->addChild(chestClosedSprite);
}

MetalChest::~MetalChest()
{
}
