#include "GlassDisplayBase.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string GlassDisplayBase::SaveKeyIsDisplayOpened = "SAVE_KEY_IS_DISPLAY_OPENED";

GlassDisplayBase::GlassDisplayBase(ValueMap& properties, Size interactSize) : super(properties, interactSize)
{
	this->displayContentNode = Node::create();
	this->displayNormal = Node::create();
	this->displayOpened = Node::create();
	this->displayLooted = Node::create();
	this->isDisplayOpened = false;
	this->isLocked = false;		// Interact objects set isLocked based on the presence of a listen event -- we do not want that.
	
	this->glassDisplayFrontNormal = Sprite::create(ObjectResources::Interactive_Chests_GlassDisplayFront);
	this->glassDisplayFrontOpened = Sprite::create(ObjectResources::Interactive_Chests_GlassDisplayFront);
	this->glassDisplayFrontLooted = Sprite::create(ObjectResources::Interactive_Chests_GlassDisplayFront);

	this->displayNormal->addChild(Sprite::create(ObjectResources::Interactive_Chests_GlassDisplay));
	this->displayOpened->addChild(Sprite::create(ObjectResources::Interactive_Chests_GlassDisplay));
	this->displayLooted->addChild(Sprite::create(ObjectResources::Interactive_Chests_GlassDisplay));
	this->displayNormal->addChild(this->glassDisplayFrontNormal);
	this->displayOpened->addChild(this->glassDisplayFrontOpened);
	this->displayLooted->addChild(this->glassDisplayFrontLooted);
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

	if (this->loadObjectStateOrDefault(GlassDisplayBase::SaveKeyIsDisplayOpened, Value(false)).asBool())
	{
		this->openDisplay(false);
	}
	else
	{
		this->closeDisplay(false);
	}
}

void GlassDisplayBase::initializeListeners()
{
	super::initializeListeners();

	this->listenForMapEventOnce(this->getListenEvent(), [=](ValueMap)
	{
		this->openDisplay(true);
	});
}

void GlassDisplayBase::closeDisplay(bool animate)
{
	this->saveObjectState(GlassDisplayBase::SaveKeyIsDisplayOpened, Value(false));

	this->isDisplayOpened = false;

	this->displayOpened->setVisible(false);
	this->displayNormal->setVisible(true);

	if (animate)
	{
		this->glassDisplayFrontNormal->runAction(MoveTo::create(1.0f, Vec2::ZERO));
		this->glassDisplayFrontOpened->runAction(MoveTo::create(1.0f, Vec2::ZERO));
		this->glassDisplayFrontLooted->runAction(MoveTo::create(1.0f, Vec2::ZERO));
	}
	else
	{
		this->glassDisplayFrontNormal->setPositionY(0.0f);
		this->glassDisplayFrontOpened->setPositionY(0.0f);
		this->glassDisplayFrontLooted->setPositionY(0.0f);
	}
}

void GlassDisplayBase::openDisplay(bool animate)
{
	this->saveObjectState(GlassDisplayBase::SaveKeyIsDisplayOpened, Value(true));
	
	this->isDisplayOpened = true;

	this->displayOpened->setVisible(true);
	this->displayNormal->setVisible(false);
	
	if (animate)
	{
		this->glassDisplayFrontNormal->runAction(MoveTo::create(1.0f, Vec2(0.0f, 192.0f)));
		this->glassDisplayFrontOpened->runAction(MoveTo::create(1.0f, Vec2(0.0f, 192.0f)));
		this->glassDisplayFrontLooted->runAction(MoveTo::create(1.0f, Vec2(0.0f, 192.0f)));
	}
	else
	{
		this->glassDisplayFrontNormal->setPositionY(192.0f);
		this->glassDisplayFrontOpened->setPositionY(192.0f);
		this->glassDisplayFrontLooted->setPositionY(192.0f);
	}
}
