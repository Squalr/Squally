#include "GlassDisplayBase.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string GlassDisplayBase::SaveKeyIsDisplayOpened = "SAVE_KEY_IS_DISPLAY_OPENED";
const std::string GlassDisplayBase::PropertyIsOpened = "is-opened";
const std::string GlassDisplayBase::PropertyDelay = "delay";

GlassDisplayBase::GlassDisplayBase(ValueMap& properties, Size interactSize) : super(properties, interactSize)
{
	this->displayContentNode = Node::create();
	this->displayNormal = Node::create();
	this->displayOpened = Node::create();
	this->displayLooted = Node::create();
	this->isDisplayOpened = GameUtils::getKeyOrDefault(this->properties, GlassDisplayBase::PropertyIsOpened, Value(false)).asBool();
	this->isLocked = false; // Interact objects set isLocked based on the presence of a listen event -- we do not want that. NOTE: LOCKED != OPENED.
	this->glassDisplayFrontNormal = Sprite::create(ObjectResources::Interactive_Chests_GlassDisplayFront);
	this->glassDisplayFrontOpened = Sprite::create(ObjectResources::Interactive_Chests_GlassDisplayFront);
	this->glassDisplayFrontLooted = Sprite::create(ObjectResources::Interactive_Chests_GlassDisplayFront);
	this->normalGlow = Sprite::create(UIResources::HUD_EmblemGlow);
	this->openGlow = Sprite::create(ObjectResources::Collectables_Animals_CollectShine);
	this->openSound = WorldSound::create(SoundResources::Platformer_Objects_Machines_GlassSlide1);
	this->closeSound = WorldSound::create(SoundResources::Platformer_Objects_Machines_GlassSlide1);
	this->notifySound = WorldSound::create(SoundResources::Notifications_Reveal1);
	this->openDelay = GameUtils::getKeyOrDefault(this->properties, GlassDisplayBase::PropertyDelay, Value(0.0f)).asFloat();
	
	this->displayContentNode->addChild(this->openGlow);
	this->displayContentNode->addChild(this->normalGlow);
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
	this->addChild(this->openSound);
	this->addChild(this->closeSound);
	this->addChild(this->notifySound);
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

	this->openGlow->runAction(RepeatForever::create(RotateBy::create(5.0f, 360.0f)));

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
		// Add redundant save to prevent timing issue where player quits before openDelay elapses
		this->saveObjectState(GlassDisplayBase::SaveKeyIsDisplayOpened, Value(true));

		this->runAction(Sequence::create(
			DelayTime::create(this->openDelay),
			CallFunc::create([=]()
			{
				this->openDisplay(true);
			}),
			nullptr
		));
	});
}

void GlassDisplayBase::closeDisplay(bool animate)
{
	this->saveObjectState(GlassDisplayBase::SaveKeyIsDisplayOpened, Value(false));

	this->isDisplayOpened = false;

	this->displayOpened->setVisible(false);
	this->displayNormal->setVisible(true);
	this->normalGlow->setVisible(true);
	this->openGlow->setVisible(false);

	if (animate)
	{
		this->glassDisplayFrontNormal->runAction(MoveTo::create(1.5f, Vec2::ZERO));
		this->glassDisplayFrontOpened->runAction(MoveTo::create(1.5f, Vec2::ZERO));
		this->glassDisplayFrontLooted->runAction(MoveTo::create(1.5f, Vec2::ZERO));
		this->closeSound->play();
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
	this->normalGlow->setVisible(false);
	this->openGlow->setVisible(true);
	
	if (animate)
	{
		this->glassDisplayFrontNormal->runAction(MoveTo::create(1.5f, Vec2(0.0f, 192.0f)));
		this->glassDisplayFrontOpened->runAction(MoveTo::create(1.5f, Vec2(0.0f, 192.0f)));
		this->glassDisplayFrontLooted->runAction(MoveTo::create(1.5f, Vec2(0.0f, 192.0f)));
		this->openSound->play();
		this->notifySound->play();
	}
	else
	{
		this->glassDisplayFrontNormal->setPositionY(192.0f);
		this->glassDisplayFrontOpened->setPositionY(192.0f);
		this->glassDisplayFrontLooted->setPositionY(192.0f);
	}
}
