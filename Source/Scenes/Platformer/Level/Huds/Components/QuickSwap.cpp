#include "QuickSwap.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/NavigationEvents.h"
#include "Engine/Events/SceneEvents.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Sound/Sound.h"
#include "Engine/Utils/MathUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Engine/Input/ClickableNode.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/NotificationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityRuneBehavior.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ItemResources.h"
#include "Resources/FXResources.h"
#include "Resources/MapResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

QuickSwap* QuickSwap::create()
{
	QuickSwap* instance = new QuickSwap();

	instance->autorelease();

	return instance;
}

QuickSwap::QuickSwap()
{
	this->clickableNode = ClickableNode::create(UIResources::HUD_FrameSquare, UIResources::HUD_FrameSquareSelected);
	Sprite* icon = Sprite::create(UIResources::Menus_Icons_Clones);

	this->clickableNode->addChild(icon);
	this->addChild(this->clickableNode);
}

QuickSwap::~QuickSwap()
{
}

void QuickSwap::onEnter()
{
	super::onEnter();
}

void QuickSwap::initializePositions()
{
	super::initializePositions();
}

void QuickSwap::initializeListeners()
{
	super::initializeListeners();

	this->clickableNode->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		PlatformerEvents::TriggerOpenQuickSwap();
	});
}
