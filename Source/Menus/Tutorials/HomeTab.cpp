#include "HomeTab.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Config/ConfigManager.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/ScrollPane.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

HomeTab* HomeTab::create()
{
	HomeTab* instance = new HomeTab();

	instance->autorelease();

	return instance;
}

HomeTab::HomeTab()
{
	this->disclaimer = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Tutorials_Home_Disclaimer::create(), Size(640.0f, 0.0f));

	this->disclaimer->enableOutline(Color4B::BLACK, 2);

	this->addChild(this->disclaimer);
}

HomeTab::~HomeTab()
{
}

void HomeTab::onEnter()
{
	super::onEnter();
}

void HomeTab::initializeListeners()
{
	super::initializeListeners();
}

void HomeTab::initializePositions()
{
	super::initializePositions();

	this->disclaimer->setPosition(Vec2(0.0f, 144.0f));
}
