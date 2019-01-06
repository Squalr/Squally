#include "HackButton.h"

#include "cocos/2d/CCSprite.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

HackButton* HackButton::create()
{
	HackButton* instance = new HackButton();

	instance->autorelease();

	return instance;
}

HackButton::HackButton() : ClickableNode(Sprite::create(UIResources::Menus_Buttons_HackButton), Sprite::create(UIResources::Menus_Buttons_HackButtonHover))
{
}

HackButton::~HackButton()
{
}

void HackButton::addEventListener(cocos2d::EventListener* listener)
{
	// Here's the magic trick -- we want the hackable button to be clickable no matter what
	this->addEventListenerIgnorePause(listener);
}
