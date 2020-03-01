#include "MetalChest.h"

#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string MetalChest::MapKeyMetalChest = "metal-chest";

MetalChest* MetalChest::create(cocos2d::ValueMap& properties)
{
	MetalChest* instance = new MetalChest(properties);

	instance->autorelease();

	return instance;
}

MetalChest::MetalChest(cocos2d::ValueMap& properties) : super(properties, Size(128.0f, 96.0f))
{
	Sprite* chestOpenFrontSprite = Sprite::create(ObjectResources::Collectables_Chests_MetalChestOpen);
	Sprite* chestClosedSprite = Sprite::create(ObjectResources::Collectables_Chests_MetalChestClosed);

	this->chestOpen->addChild(chestOpenFrontSprite);
	this->chestClosed->addChild(chestClosedSprite);
}

MetalChest::~MetalChest()
{
}
