#include "AlchemyMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Sound/Sound.h"
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

AlchemyMenu::AlchemyMenu() : super(Strings::Menus_Crafting_Crafting::create())
{
	this->anvil = Sprite::create(UIResources::Menus_CraftingMenu_Table);
	this->icon = Sprite::create(UIResources::Menus_CraftingMenu_PlantIcon);
	this->craftSound = Sound::create(SoundResources::Menus_Crafting_Alchemy);

	this->filterMenu->addFilter(AllAlchemyFilter::create());

	this->backDecorNode->addChild(this->anvil);
	this->craftIconNode->addChild(this->icon);
	this->addChild(this->craftSound);
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

void AlchemyMenu::onCraftStart()
{
	this->craftSound->stop();
	this->craftSound->play();
}

void AlchemyMenu::onCraftEnd(bool viaCancel)
{
	if (viaCancel)
	{
		this->craftSound->stop();
	}
}
