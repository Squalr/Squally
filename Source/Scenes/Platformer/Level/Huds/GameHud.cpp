#include "GameHud.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/HelpArrow.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/PlatformerEvents.h"
#include "Events/NotificationEvents.h"
#include "Menus/Dialogue/PlatformerDialogueBox.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Level/Huds/Components/CinematicIndicator.h"
#include "Scenes/Platformer/Level/Huds/Components/CurrencyDisplay.h"
#include "Scenes/Platformer/Level/Huds/Components/ObjectiveDisplay.h"
#include "Scenes/Platformer/Level/Huds/Components/QuickPotion.h"
#include "Scenes/Platformer/Level/Huds/Components/QuickSwap.h"
#include "Scenes/Platformer/Level/Huds/Components/QuickWarp.h"
#include "Scenes/Platformer/Level/Huds/Components/StatsBars.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

GameHud* GameHud::create()
{
	GameHud* instance = new GameHud();

	instance->autorelease();

	return instance;
}

GameHud::GameHud()
{
	CSize visibleSize = Director::getInstance()->getVisibleSize();

	this->flashLayer = LayerColor::create(Color4B(0, 0, 0, 0), visibleSize.width, visibleSize.height);
	this->currencyDisplay = CurrencyDisplay::create();
	this->objectiveDisplay = ObjectiveDisplay::create();
	this->statsBars = StatsBars::create();
	this->cinematicIndicator = CinematicIndicator::create();
	this->dialogueBox = PlatformerDialogueBox::create();
	this->backdrop = LayerColor::create(Color4B(0, 0, 0, 0), visibleSize.width, visibleSize.height);
	this->quickPotion = QuickPotion::create();
	this->quickWarp = QuickWarp::create();
	this->quickSwap = QuickSwap::create();
	this->helpArrow = HelpArrow::create();

	this->helpArrow->setRotation(90.0f);

	this->statsBars->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->statsBars->setVisible(false);
	this->currencyDisplay->setVisible(false);
	this->quickPotion->setVisible(false);
	this->quickWarp->setVisible(false);
	this->quickSwap->setVisible(false);

	this->addChild(this->flashLayer);
	this->addChild(this->objectiveDisplay);
	this->addChild(this->statsBars);
	this->addChild(this->currencyDisplay);
	this->addChild(this->backdrop);
	this->addChild(this->quickPotion);
	this->addChild(this->quickWarp);
	this->addChild(this->quickSwap);
	this->addChild(this->helpArrow);
	this->addChild(this->dialogueBox);
	this->addChild(this->cinematicIndicator);
}

GameHud::~GameHud()
{
}

void GameHud::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void GameHud::initializePositions()
{
	super::initializePositions();

	CSize visibleSize = Director::getInstance()->getVisibleSize();

	static const Vec2 offset = Vec2(24.0f, -96.0f);
	static const float Spacing = 128.0f;

	bool quickPotionUnlocked = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyQuickPotionUnlocked, Value(false)).asBool();

	this->objectiveDisplay->setPosition(visibleSize.width - 48.0f, visibleSize.height - 24.0f);
	this->statsBars->setPosition(offset.x, visibleSize.height + offset.y);
	this->currencyDisplay->setPosition(offset.x + quickPotionUnlocked ? 172.0f : 64.0f, visibleSize.height + offset.y - 96.0f);
	this->quickPotion->setPosition(offset.x + 64.0f, visibleSize.height + offset.y - 128.0f - Spacing * 0.0f);
	this->quickWarp->setPosition(offset.x + 64.0f, visibleSize.height + offset.y - 128.0f - Spacing * 1.0f);
	this->quickSwap->setPosition(offset.x + 64.0f, visibleSize.height + offset.y - 128.0f - Spacing * 2.0f);

	switch(this->helpArrowTarget)
	{
		case HelpArrowTarget::QuickPotion:
		{
			this->helpArrow->setPosition(offset.x + 192.0f, visibleSize.height + offset.y - 128.0f - Spacing * 0.0f);
			break;
		}
		case HelpArrowTarget::QuickWarp:
		{
			this->helpArrow->setPosition(offset.x + 192.0f, visibleSize.height + offset.y - 128.0f - Spacing * 1.0f);
			break;
		}
		case HelpArrowTarget::QuickSwap:
		{
			this->helpArrow->setPosition(offset.x + 192.0f, visibleSize.height + offset.y - 128.0f - Spacing * 2.0f);
			break;
		}
	}

	this->dialogueBox->setPosition(Vec2(visibleSize.width / 2.0f, 192.0f));
	this->cinematicIndicator->setPosition(48.0f, 48.0f);
}

void GameHud::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventHudTrackEntity, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::HudTrackEntityArgs* args = static_cast<PlatformerEvents::HudTrackEntityArgs*>(eventCustom->getData());
		
		if (args != nullptr)
		{
			this->statsBars->setStatsTarget(args->entity);

			args->entity->getComponent<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
			{
				this->currencyDisplay->setCurrencyInventory(entityInventoryBehavior->getCurrencyInventory());
				this->quickPotion->setInventory(entityInventoryBehavior->getInventory());
			});

			this->statsBars->setVisible(true);
			this->currencyDisplay->setVisible(true);

			bool quickPotionUnlocked = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyQuickPotionUnlocked, Value(false)).asBool();
			this->quickPotion->setVisible(quickPotionUnlocked);
			
			bool quickWarpUnlocked = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeySpellBookWind, Value(false)).asBool();
			this->quickWarp->setVisible(quickWarpUnlocked);
			
			bool quickSwapUnlocked = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeySpellBookShadow, Value(false)).asBool();
			this->quickSwap->setVisible(quickSwapUnlocked);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventHudUntrackEntity, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::HudTrackEntityArgs* args = static_cast<PlatformerEvents::HudTrackEntityArgs*>(eventCustom->getData());
		
		if (args != nullptr)
		{
			this->statsBars->setStatsTarget(nullptr);
			this->currencyDisplay->setCurrencyInventory(nullptr);
			this->quickPotion->setInventory(nullptr);

			this->statsBars->setVisible(false);
			this->currencyDisplay->setVisible(false);
			this->quickPotion->setVisible(false);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventRunFlashFx, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::FlashFxArgs* args = static_cast<PlatformerEvents::FlashFxArgs*>(eventCustom->getData());
		
		if (args != nullptr)
		{
			this->flashLayer->setColor(args->flashColor);

			this->flashLayer->runAction(Repeat::create(Sequence::create(
				FadeTo::create(args->duration, 255),
				FadeTo::create(args->duration, 0),
				nullptr
			), (args->repeatCount <= 0) ? 1 : args->repeatCount));
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventUnlockQuickPotion, [=](EventCustom* eventCustom)
	{
		bool quickPotionUnlocked = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyQuickPotionUnlocked, Value(false)).asBool();

		if (quickPotionUnlocked)
		{
			return;
		}

		// Re-initialize positions
		this->helpArrowTarget = HelpArrowTarget::QuickPotion;
		this->initializePositions();

		PlatformerEvents::TriggerCinematicHijack();
		this->helpArrow->showPointer();
		this->quickPotion->setVisible(true);
		
		this->backdrop->runAction(Sequence::create(
			FadeTo::create(0.25f, 192),
			CallFunc::create([=]()
			{
				NotificationEvents::TriggerNotificationTakeover(NotificationEvents::NotificationTakeoverArgs(
					Strings::Menus_Hud_QuickPotion_QuickPotionExplainerTitle::create(),
					Strings::Menus_Hud_QuickPotion_QuickPotionExplainer::create(),
					"",
					false
				));
			}),
			DelayTime::create(1.0f),
			FadeTo::create(0.25f, 0),
			CallFunc::create([=]()
			{
				this->helpArrow->hidePointer();
				PlatformerEvents::TriggerCinematicRestore();
			}),
			nullptr
		));

		SaveManager::SaveProfileData(SaveKeys::SaveKeyQuickPotionUnlocked, Value(true));

		// Re-initialize
		this->initializePositions();
	}));
	
	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventUnlockQuickWarp, [=](EventCustom* eventCustom)
	{
		// Re-initialize positions
		this->helpArrowTarget = HelpArrowTarget::QuickWarp;
		this->initializePositions();

		PlatformerEvents::TriggerCinematicHijack();
		this->helpArrow->showPointer();
		this->quickWarp->setVisible(true);
		
		this->backdrop->runAction(Sequence::create(
			FadeTo::create(0.25f, 192),
			CallFunc::create([=]()
			{
				NotificationEvents::TriggerNotificationTakeover(NotificationEvents::NotificationTakeoverArgs(
					Strings::Menus_Hud_QuickWarp_QuickWarpTitle::create(),
					Strings::Menus_Hud_QuickWarp_QuickWarpExplainer::create()
						->setStringReplacementVariables(Strings::Platformer_MapNames_EndianForest_MagesGuild::create()),
					SoundResources::Notifications_NotificationGood1,
					false
				));
			}),
			DelayTime::create(1.0f),
			FadeTo::create(0.25f, 0),
			CallFunc::create([=]()
			{
				this->helpArrow->hidePointer();
				PlatformerEvents::TriggerCinematicRestore();
			}),
			nullptr
		));

		// Re-initialize
		this->initializePositions();
	}));
	
	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventUnlockQuickSwap, [=](EventCustom* eventCustom)
	{
		// Re-initialize positions
		this->helpArrowTarget = HelpArrowTarget::QuickSwap;
		this->initializePositions();

		PlatformerEvents::TriggerCinematicHijack();
		this->helpArrow->showPointer();
		this->quickSwap->setVisible(true);
		
		this->backdrop->runAction(Sequence::create(
			FadeTo::create(0.25f, 192),
			CallFunc::create([=]()
			{
				NotificationEvents::TriggerNotificationTakeover(NotificationEvents::NotificationTakeoverArgs(
					Strings::Menus_Hud_QuickSwap_QuickSwapTitle::create(),
					Strings::Menus_Hud_QuickSwap_QuickSwapExplainer::create(),
					SoundResources::Notifications_NotificationGood1,
					false
				));
			}),
			DelayTime::create(1.0f),
			FadeTo::create(0.25f, 0),
			CallFunc::create([=]()
			{
				this->helpArrow->hidePointer();
				PlatformerEvents::TriggerCinematicRestore();
			}),
			nullptr
		));

		// Re-initialize
		this->initializePositions();
	}));
}

void GameHud::update(float dt)
{
	super::update(dt);
}
