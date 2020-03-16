#include "BlacksmithingMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Sound/Sound.h"
#include "Menus/Crafting/CraftFilterMenu/CraftFilterEntry.h"
#include "Menus/Crafting/CraftFilterMenu/CraftFilterMenu.h"
#include "Menus/Crafting/CraftFilterMenu/Smithing/AllWeaponsFilter.h"
#include "Menus/Crafting/CraftFilterMenu/Smithing/AxesFilter.h"
#include "Menus/Crafting/CraftFilterMenu/Smithing/BowsFilter.h"
#include "Menus/Crafting/CraftFilterMenu/Smithing/MacesFilter.h"
#include "Menus/Crafting/CraftFilterMenu/Smithing/SpearsFilter.h"
#include "Menus/Crafting/CraftFilterMenu/Smithing/SwordsFilter.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

BlacksmithingMenu* BlacksmithingMenu::create()
{
	BlacksmithingMenu* instance = new BlacksmithingMenu();

	instance->autorelease();

	return instance;
}

BlacksmithingMenu::BlacksmithingMenu()
{
	this->anvil = Sprite::create(UIResources::Menus_CraftingMenu_Anvil);
	this->icon = Sprite::create(UIResources::Menus_CraftingMenu_AnvilIcon);
	this->craftSound = Sound::create(SoundResources::Menus_Crafting_Blacksmithing);

	this->filterMenu->addFilter(AllWeaponsFilter::create());
	this->filterMenu->addFilter(AxesFilter::create());
	this->filterMenu->addFilter(BowsFilter::create());
	this->filterMenu->addFilter(MacesFilter::create());
	this->filterMenu->addFilter(SpearsFilter::create());
	this->filterMenu->addFilter(SwordsFilter::create());

	this->backDecorNode->addChild(this->anvil);
	this->craftIconNode->addChild(this->icon);
	this->addChild(this->craftSound);
}

BlacksmithingMenu::~BlacksmithingMenu()
{
}

void BlacksmithingMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	const Vec2 AnvilOffset = Vec2(-72.0f, 0.0f);

	this->anvil->setPosition(Vec2(visibleSize.width / 2.0f + 359.0f, visibleSize.height / 2.0f + 54.0f) + AnvilOffset);
}

void BlacksmithingMenu::onCraftStart()
{
	this->craftSound->stop();
	this->craftSound->play();
}

void BlacksmithingMenu::onCraftEnd(bool viaCancel)
{
	if (viaCancel)
	{
		this->craftSound->stop();
	}
}
