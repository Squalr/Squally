#include "IntroPage.h"

#include "cocos/2d/CCSprite.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

IntroPage* IntroPage::create()
{
	IntroPage* instance = new IntroPage();

	instance->autorelease();

	return instance;
}

IntroPage::IntroPage()
{
	this->chapterSprite = Sprite::create(UIResources::Menus_LexiconMenu_Chapter);

	this->addChild(this->chapterSprite);
}

IntroPage::~IntroPage()
{
}

void IntroPage::initializePositions()
{
	super::initializePositions();

	this->chapterSprite->setPosition(Vec2(16.0f, 16.0f));
}

void IntroPage::initializeListeners()
{
	super::initializeListeners();
}
