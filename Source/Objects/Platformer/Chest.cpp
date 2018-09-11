#include "Chest.h"

Chest* Chest::create(Node* contentNode)
{
	Chest* instance = new Chest(contentNode);

	instance->autorelease();

	return instance;
}

Chest::Chest(Node* contentNode) : Node()
{
	this->content = contentNode;
	this->chestOpen = Node::create();
	this->chestClosed = Node::create();

	Sprite* chestOpenFrontSprite = Sprite::create(Resources::Objects_Platformer_ChestBaseFront);
	Sprite* chestOpenLidSprite = Sprite::create(Resources::Objects_Platformer_ChestLid);
	Sprite* chestClosedSprite = Sprite::create(Resources::Objects_Platformer_ChestClosed);

	this->chestOpen->addChild(chestOpenLidSprite);
	this->chestOpen->addChild(this->content);
	this->chestOpen->addChild(chestOpenFrontSprite);
	this->chestClosed->addChild(chestClosedSprite);

	this->content->setCascadeOpacityEnabled(true);

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
	this->content->runAction(FadeOut::create(2.0f));
	this->content->runAction(MoveBy::create(2.0f, Vec2(0.0f, 128.0f)));
}

void Chest::close()
{
	this->chestClosed->setVisible(true);
	this->chestOpen->setVisible(false);
}
