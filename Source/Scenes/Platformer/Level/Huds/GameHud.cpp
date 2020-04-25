#include "GameHud.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/PlatformerEvents.h"
#include "Menus/Dialogue/PlatformerDialogueBox.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Level/Huds/Components/CinematicIndicator.h"
#include "Scenes/Platformer/Level/Huds/Components/CurrencyDisplay.h"
#include "Scenes/Platformer/Level/Huds/Components/ObjectiveDisplay.h"
#include "Scenes/Platformer/Level/Huds/Components/StatsBars.h"

using namespace cocos2d;

GameHud* GameHud::create()
{
	GameHud* instance = new GameHud();

	instance->autorelease();

	return instance;
}

GameHud::GameHud()
{
	this->currencyDisplay = CurrencyDisplay::create();
	this->objectiveDisplay = ObjectiveDisplay::create();
	this->statsBars = StatsBars::create();
	this->cinematicIndicator = CinematicIndicator::create();
	this->dialogueBox = PlatformerDialogueBox::create();

	this->statsBars->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->statsBars->setVisible(false);
	this->currencyDisplay->setVisible(false);

	this->addChild(this->objectiveDisplay);
	this->addChild(this->statsBars);
	this->addChild(this->currencyDisplay);
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

	Size visibleSize = Director::getInstance()->getVisibleSize();

	static const Vec2 offset = Vec2(24.0f, -96.0f);
	
	this->objectiveDisplay->setPosition(visibleSize.width - 48.0f, visibleSize.height - 24.0f);
	this->statsBars->setPosition(offset.x, visibleSize.height + offset.y);
	this->currencyDisplay->setPosition(offset.x + 64.0f, visibleSize.height + offset.y - 96.0f);
	this->dialogueBox->setPosition(Vec2(visibleSize.width / 2.0f, 192.0f));
	this->cinematicIndicator->setPosition(48.0f, 48.0f);
}

void GameHud::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventHudTrackEntity, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::HudTrackEntityArgs* args = static_cast<PlatformerEvents::HudTrackEntityArgs*>(eventCustom->getUserData());
		
		if (args != nullptr)
		{
			this->statsBars->setStatsTarget(args->entity);

			args->entity->getAttachedBehavior<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
			{
				this->currencyDisplay->setCurrencyInventory(entityInventoryBehavior->getCurrencyInventory());
			});

			this->statsBars->setVisible(true);
			this->currencyDisplay->setVisible(true);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventHudUntrackEntity, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::HudTrackEntityArgs* args = static_cast<PlatformerEvents::HudTrackEntityArgs*>(eventCustom->getUserData());
		
		if (args != nullptr)
		{
			this->statsBars->setStatsTarget(nullptr);
			this->currencyDisplay->setCurrencyInventory(nullptr);

			this->statsBars->setVisible(false);
			this->currencyDisplay->setVisible(false);
		}
	}));
}

void GameHud::update(float dt)
{
	super::update(dt);
}
