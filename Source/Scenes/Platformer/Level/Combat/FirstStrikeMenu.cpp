#include "FirstStrikeMenu.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Sound/Sound.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

FirstStrikeMenu* FirstStrikeMenu::create()
{
	FirstStrikeMenu* instance = new FirstStrikeMenu();

	instance->autorelease();

	return instance;
}

FirstStrikeMenu::FirstStrikeMenu()
{
	this->background = Sprite::create(UIResources::Combat_ItemFrame);
	this->firstStrikeLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Platformer_Combat_FirstStrike::create());
	this->sfx = Sound::create(SoundResources::Platformer_Combat_Victory);

	this->firstStrikeLabel->enableOutline(Color4B::BLACK, 2);

	this->addChild(this->background);
	this->addChild(this->firstStrikeLabel);
	this->addChild(this->sfx);
}

FirstStrikeMenu::~FirstStrikeMenu()
{
}

void FirstStrikeMenu::onEnter()
{
	super::onEnter();

	this->setOpacity(0);
}

void FirstStrikeMenu::initializePositions()
{
	super::initializePositions();
	
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 256.0f));
}

void FirstStrikeMenu::initializeListeners()
{
	super::initializeListeners();
}

void FirstStrikeMenu::show(bool playerFirstStrike)
{
	if (playerFirstStrike)
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();

		this->runAction(Sequence::create(
			FadeTo::create(0.25f, 255),
			DelayTime::create(2.0f),
			EaseSineInOut::create(MoveTo::create(0.75f, Vec2(visibleSize.width / 2.0f, visibleSize.height + 256.0f))),
			nullptr
		));
	}
}
