#include "QuickWarp.h"

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
#include "Events/NotificationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityRuneBehavior.h"

#include "Resources/ItemResources.h"
#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

QuickWarp* QuickWarp::create()
{
	QuickWarp* instance = new QuickWarp();

	instance->autorelease();

	return instance;
}

QuickWarp::QuickWarp()
{
	this->clickableNode = ClickableNode::create(UIResources::HUD_FrameSquare, UIResources::HUD_FrameSquareSelected);
	Sprite* icon = Sprite::create(UIResources::Menus_Icons_Tornado);

	this->clickableNode->addChild(icon);
	this->addChild(this->clickableNode);
}

QuickWarp::~QuickWarp()
{
}

void QuickWarp::onEnter()
{
	super::onEnter();
}

void QuickWarp::initializePositions()
{
	super::initializePositions();
}

void QuickWarp::initializeListeners()
{
	super::initializeListeners();

	this->clickableNode->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		this->clickableNode->deselect();
		
		if (true)
		{
			NotificationEvents::TriggerConfirmation(NotificationEvents::ConfirmationArgs(
				Strings::Menus_Hud_QuickWarp_AreYouSureMagesGuild::create()
					->setStringReplacementVariables(Strings::Platformer_MapNames_EndianForest_MagesGuild::create()),
				[=]()
				{
					PlatformerEvents::TriggerOpenQuickWarp();

					return true;
				},
				[=]()
				{
					return false;
				}
			));
		}
		else
		{
			NotificationEvents::TriggerConfirmation(NotificationEvents::ConfirmationArgs(
				Strings::Menus_Hud_QuickWarp_AreYouSureMagesGuild::create(),
				[=]()
				{
					PlatformerEvents::TriggerOpenQuickWarp();

					return true;
				},
				[=]()
				{
					return false;
				}
			));
		}
	});
}
