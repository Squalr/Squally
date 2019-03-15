#include "InteractMenu.h"

#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

InteractMenu* InteractMenu::create(LocalizedString* displayString)
{
	InteractMenu* instance = new InteractMenu(displayString);

	instance->autorelease();

	return instance;
}

InteractMenu::InteractMenu(LocalizedString* displayString)
{
	this->uiElements = Node::create();
	this->uiElementsBinding = UIBoundObject::create(this->uiElements);
	this->displayString = displayString;
	this->displayLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, this->displayString);
	this->backdrop = LayerColor::create(Color4B(0, 0, 0, 196), 128, 48);

	this->uiElements->setOpacity(0);

	this->uiElements->addChild(this->backdrop);
	this->uiElements->addChild(this->displayLabel);
	this->addChild(this->uiElements);
	this->addChild(this->uiElementsBinding);
}

InteractMenu::~InteractMenu()
{
}

void InteractMenu::onEnter()
{
	super::onEnter();

	// Move the UI elements to the top-most layer
	ObjectEvents::TriggerMoveObjectToTopLayer(ObjectEvents::RelocateObjectArgs(
		this->uiElementsBinding
	));

	this->setOpacity(0);
}

void InteractMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->backdrop->setPosition(Vec2(-128.0f / 2.0f, -48.0f / 2.0f));
	this->uiElementsBinding->setPosition(Vec2(0.0f, 144.0f));
}

void InteractMenu::initializeListeners()
{
	super::initializeListeners();
}

void InteractMenu::show()
{
	this->uiElements->stopAllActions();
	this->uiElements->runAction(FadeTo::create(0.15f, 255));
}

void InteractMenu::hide()
{
	this->uiElements->stopAllActions();
	this->uiElements->runAction(FadeTo::create(0.15f, 0));
}
