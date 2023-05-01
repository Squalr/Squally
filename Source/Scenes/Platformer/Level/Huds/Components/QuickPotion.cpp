#include "QuickPotion.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/SceneEvents.h"
#include "Engine/Sound/Sound.h"
#include "Engine/Utils/MathUtils.h"
#include "Engine/Input/ClickableNode.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityRuneBehavior.h"

#include "Resources/ItemResources.h"
#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

QuickPotion* QuickPotion::create()
{
	QuickPotion* instance = new QuickPotion();

	instance->autorelease();

	return instance;
}

QuickPotion::QuickPotion()
{
	this->clickableNode = ClickableNode::create(UIResources::HUD_FrameSquare, UIResources::HUD_FrameSquareSelected);
	Sprite* icon = Sprite::create(ItemResources::Consumables_Potions_DualElixir);

	this->clickableNode->addChild(icon);
	this->addChild(this->clickableNode);
}

QuickPotion::~QuickPotion()
{
}

void QuickPotion::onEnter()
{
	super::onEnter();
}

void QuickPotion::initializePositions()
{
	super::initializePositions();
}

void QuickPotion::initializeListeners()
{
	super::initializeListeners();

	this->clickableNode->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		this->clickableNode->deselect();
		PlatformerEvents::TriggerOpenQuickPotion();
	});
}

void QuickPotion::setInventory(Inventory* inventory)
{
	this->inventory = inventory;
}
