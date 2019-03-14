#include "Chest.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string Chest::MapKeyChest = "chest";

Chest* Chest::create(cocos2d::ValueMap& initProperties)
{
	Chest* instance = new Chest(initProperties);

	instance->autorelease();

	return instance;
}

Chest::Chest(cocos2d::ValueMap& initProperties) : super(initProperties)
{
	this->chestOpen = Node::create();
	this->chestClosed = Node::create();

	Sprite* chestOpenFrontSprite = Sprite::create(ObjectResources::ChestBaseFront);
	Sprite* chestOpenLidSprite = Sprite::create(ObjectResources::ChestLid);
	Sprite* chestClosedSprite = Sprite::create(ObjectResources::ChestClosed);

	this->chestOpen->addChild(chestOpenLidSprite);
	this->chestOpen->addChild(chestOpenFrontSprite);
	this->chestClosed->addChild(chestClosedSprite);

	this->close();

	this->addChild(this->chestClosed);
	this->addChild(this->chestOpen);
}

Chest::~Chest()
{
}

void Chest::open()
{
	this->chestClosed->setVisible(false);
	this->chestOpen->setVisible(true);
}

void Chest::close()
{
	this->chestClosed->setVisible(true);
	this->chestOpen->setVisible(false);
}
