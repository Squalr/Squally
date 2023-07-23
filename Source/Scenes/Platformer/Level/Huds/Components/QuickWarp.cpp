#include "QuickWarp.h"

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

QuickWarp* QuickWarp::create()
{
	QuickWarp* instance = new QuickWarp();

	instance->autorelease();

	return instance;
}

QuickWarp::QuickWarp()
{
	ValueMap emptyProperties;
	this->internalPortal = Portal::create(emptyProperties);
	this->clickableNode = ClickableNode::create(UIResources::HUD_FrameSquare, UIResources::HUD_FrameSquareSelected);
	Sprite* icon = Sprite::create(UIResources::Menus_Icons_Tornado);

	this->internalPortal->setTransiton("quick-warp");

	this->clickableNode->addChild(icon);
	this->addChild(this->internalPortal);
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
		std::string currentMap = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyMap, Value("")).asString();
		const bool ignoreCase = true;

		this->clickableNode->deselect();
		
		if (StrUtils::contains(currentMap, "MagesGuild", ignoreCase))
		{
			NotificationEvents::TriggerConfirmation(NotificationEvents::ConfirmationArgs(
				Strings::Menus_Hud_QuickWarp_AreYouSureReturn::create(),
				[=]()
				{
					std::string returnMap = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyQuickWarpReturnMap, Value("")).asString();

					if (returnMap == "")
					{
						returnMap = MapResources::EndianForest_Town_Main;
					}

					this->internalPortal->setMapFile(returnMap);
					this->internalPortal->loadMap();

					return false;
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
				Strings::Menus_Hud_QuickWarp_AreYouSureMagesGuild::create()
					->setStringReplacementVariables(Strings::Platformer_MapNames_EndianForest_MagesGuild::create()),
				[=]()
				{
					SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyQuickWarpReturnMap, Value(currentMap));

					this->internalPortal->setMapFile(MapResources::MagesGuild_Mages_Warp);
					this->internalPortal->loadMap();

					return false;
				},
				[=]()
				{
					return false;
				}
			));
		}
	});
}
