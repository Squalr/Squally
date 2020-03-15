#include "AlchemyMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Menus/Crafting/CraftFilterMenu/CraftFilterEntry.h"
#include "Menus/Crafting/CraftFilterMenu/CraftFilterMenu.h"
#include "Menus/Crafting/CraftFilterMenu/Alchemy/AllAlchemyFilter.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

AlchemyMenu* AlchemyMenu::create()
{
	AlchemyMenu* instance = new AlchemyMenu();

	instance->autorelease();

	return instance;
}

AlchemyMenu::AlchemyMenu()
{
	this->anvil = Sprite::create(UIResources::Menus_CraftingMenu_Anvil);
	this->icon = Sprite::create(UIResources::Menus_CraftingMenu_PlantIcon);

	this->filterMenu->addFilter(AllAlchemyFilter::create());

	this->backDecorNode->addChild(this->anvil);
	this->craftIconNode->addChild(this->icon);
}

AlchemyMenu::~AlchemyMenu()
{
}

void AlchemyMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	const Vec2 AnvilOffset = Vec2(-72.0f, 0.0f);

	this->anvil->setPosition(Vec2(visibleSize.width / 2.0f + 359.0f, visibleSize.height / 2.0f + 54.0f) + AnvilOffset);
}
