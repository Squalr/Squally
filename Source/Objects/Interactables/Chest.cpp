#include "Chest.h"

Chest* Chest::create()
{
	Chest* instance = new Chest();

	instance->autorelease();

	return instance;
}

Chest::Chest()
{
	this->contentNode = Node::create();
	Sprite* chestOpenLidSprite;
	Sprite* chestOpenFrontSprite;
	Sprite* chestOpenSprite;
	this->chestOpenLidSprite = Sprite::create(Resources::Objects_ChestLid);
	this->chestOpenFrontSprite = Sprite::create(Resources::Objects_ChestBaseFront);
	this->chestOpenSprite = Sprite::create(Resources::Objects_ChestBaseFront);
	this->chestClosedSprite = Sprite::create(Resources::Objects_ChestClosed);

	this->size = this->chestClosedSprite->getContentSize();

	this->close();

	this->addChild(this->contentNode);
	this->addChild(this->chestOpenSprite);
	this->addChild(this->chestClosedSprite);
}

Chest::~Chest()
{
}

void Chest::update(float dt)
{

}

void Chest::open()
{
	this->contentNode->setVisible(true);
	this->chestOpenLidSprite->setVisible(true);
	this->chestOpenFrontSprite->setVisible(true);
	this->chestOpenSprite->setVisible(true);
	this->chestClosedSprite->setVisible(false);
}

void Chest::close()
{
	this->contentNode->setVisible(false);
	this->chestOpenLidSprite->setVisible(false);
	this->chestOpenFrontSprite->setVisible(false);
	this->chestOpenSprite->setVisible(false);
	this->chestClosedSprite->setVisible(true);
}
