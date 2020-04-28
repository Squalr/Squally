#include "TutorialEntry.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Config/ConfigManager.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/ScrollPane.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

TutorialEntry* TutorialEntry::create()
{
	TutorialEntry* instance = new TutorialEntry();

	instance->autorelease();

	return instance;
}

TutorialEntry::TutorialEntry()
{
	this->back = Sprite::create();
	this->frame = Sprite::create();
	this->lockIcon = Sprite::create();
	this->completeIcon = Sprite::create();

	this->addChild(this->back);
	this->addChild(this->frame);
	this->addChild(this->lockIcon);
	this->addChild(this->completeIcon);
}

TutorialEntry::~TutorialEntry()
{
}

void TutorialEntry::onEnter()
{
	super::onEnter();
}

void TutorialEntry::initializeListeners()
{
	super::initializeListeners();
}

void TutorialEntry::initializePositions()
{
	super::initializePositions();
}
