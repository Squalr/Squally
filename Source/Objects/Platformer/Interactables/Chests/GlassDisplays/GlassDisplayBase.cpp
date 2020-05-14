#include "GlassDisplayBase.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

GlassDisplayBase::GlassDisplayBase(ValueMap& properties, Size interactSize) : super(properties, interactSize)
{
	this->displayContentNode = Node::create();
	this->displayNormal = Node::create();
	this->displayOpened = Node::create();
	this->displayLooted = Node::create();
	this->isDisplayOpened = false;
	
	Sprite* glassDisplayFrontNormal = Sprite::create(ObjectResources::Interactive_Chests_GlassDisplayFront);
	Sprite* glassDisplayFrontOpened = Sprite::create(ObjectResources::Interactive_Chests_GlassDisplayFront);
	Sprite* glassDisplayFrontLooted = Sprite::create(ObjectResources::Interactive_Chests_GlassDisplayFront);

	glassDisplayFrontOpened->setPositionY(64.0f);
	glassDisplayFrontLooted->setPositionY(64.0f);

	this->displayNormal->addChild(Sprite::create(ObjectResources::Interactive_Chests_GlassDisplay));
	this->displayOpened->addChild(Sprite::create(ObjectResources::Interactive_Chests_GlassDisplay));
	this->displayLooted->addChild(Sprite::create(ObjectResources::Interactive_Chests_GlassDisplay));
	this->displayNormal->addChild(glassDisplayFrontNormal);
	this->displayOpened->addChild(glassDisplayFrontOpened);
	this->displayLooted->addChild(glassDisplayFrontLooted);
	this->chestOpen->addChild(this->displayLooted);
	this->chestClosed->addChild(this->displayContentNode);
	this->chestClosed->addChild(this->displayNormal);
	this->chestClosed->addChild(this->displayOpened);
}

GlassDisplayBase::~GlassDisplayBase()
{
}

void GlassDisplayBase::onEnter()
{
	super::onEnter();

	this->displayContentNode->runAction(RepeatForever::create(Sequence::create(
		EaseSineInOut::create(MoveTo::create(1.5f, Vec2(0.0f, 48.0f))),
		EaseSineInOut::create(MoveTo::create(1.5f, Vec2(0.0f, 16.0f))),
		nullptr
	)));

	this->closeDisplay();
}

void GlassDisplayBase::closeDisplay()
{
	this->isDisplayOpened = false;

	this->displayOpened->setVisible(false);
	this->displayNormal->setVisible(true);
}

void GlassDisplayBase::openDisplay()
{
	this->isDisplayOpened = true;

	this->displayOpened->setVisible(true);
	this->displayNormal->setVisible(false);
}
