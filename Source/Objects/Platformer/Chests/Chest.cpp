#include "Chest.h"

#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

Chest::Chest(cocos2d::ValueMap& properties) : super(properties, Size(128.0f, 96.0f))
{
	Sprite* chestOpenFrontSprite = Sprite::create(ObjectResources::Collectables_Chests_ChestOpen);
	Sprite* chestClosedSprite = Sprite::create(ObjectResources::Collectables_Chests_ChestClosed);

	this->chestOpen->addChild(chestOpenFrontSprite);
	this->chestClosed->addChild(chestClosedSprite);
}

Chest::~Chest()
{
}
