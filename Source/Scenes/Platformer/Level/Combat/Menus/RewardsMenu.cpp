#include "RewardsMenu.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Inventory/MinMaxPool.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Sound/Sound.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/StatsTables/StatsTables.h"
#include "Events/CombatEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityDropTableBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Combat/FriendlyExpBarBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityEqBehavior.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

RewardsMenu* RewardsMenu::create()
{
	RewardsMenu* instance = new RewardsMenu();

	instance->autorelease();

	return instance;
}

RewardsMenu::RewardsMenu()
{
	this->victoryMenu = Sprite::create(UIResources::Combat_VictoryMenu);
	this->expSprite = Sprite::create(UIResources::Menus_Icons_Stars);
	this->expValue = ConstantString::create(std::to_string(0));
	this->expLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, this->expValue);
	this->victorySound = Sound::create(SoundResources::Platformer_Combat_Victory);

	this->victoryLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::M2, Strings::Platformer_Combat_Victory::create());

	LocalizedLabel*	returnLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Return::create());
	LocalizedLabel*	returnLabelHover = returnLabel->clone();

	returnLabel->enableOutline(Color4B::BLACK, 2);
	returnLabelHover->enableOutline(Color4B::BLACK, 2);

	this->returnButton = ClickableTextNode::create(returnLabel, returnLabelHover, Sprite::create(UIResources::Menus_Buttons_WoodButton), Sprite::create(UIResources::Menus_Buttons_WoodButtonSelected));

	this->expLabel->enableOutline(Color4B::BLACK, 2);
	this->victoryLabel->enableOutline(Color4B::BLACK, 2);

	this->expLabel->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->addChild(this->victoryMenu);
	this->addChild(this->expSprite);
	this->addChild(this->expLabel);
	this->addChild(this->victoryLabel);
	this->addChild(this->returnButton);
	this->addChild(this->victorySound);
}

RewardsMenu::~RewardsMenu()
{
}

void RewardsMenu::onEnter()
{
	super::onEnter();

	this->setOpacity(0);
}

void RewardsMenu::initializePositions()
{
	super::initializePositions();

	this->victoryLabel->setPosition(Vec2(0.0f, 176.0f));
	this->victoryMenu->setPosition(Vec2(0.0f, 0.0f));
	this->expSprite->setPosition(Vec2(-48.0f, 32.0f));
	this->expLabel->setPosition(Vec2(16.0f, 32.0f));
	this->returnButton->setPosition(Vec2(16.0f, -160.0f));
}

void RewardsMenu::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventGiveExp, [=](EventCustom* args)
	{
		this->giveExp();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventGiveRewards, [=](EventCustom* args)
	{
		this->loadRewards();
	}));

	this->returnButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		CombatEvents::TriggerReturnToMap();
	});
}

void RewardsMenu::show()
{
	this->runAction(FadeTo::create(1.0f, 255));
	this->victorySound->play();
}

void RewardsMenu::giveExp()
{
	ObjectEvents::QueryObjects(QueryObjectsArgs<PlatformerEntity>([&](PlatformerEntity* entity)
	{
		entity->getAttachedBehavior<FriendlyExpBarBehavior>([=](FriendlyExpBarBehavior* friendlyExpBarBehavior)
		{
			entity->getAttachedBehavior<EntityEqBehavior>([=](EntityEqBehavior* eqBehavior)
			{
				const int intendedLevel = SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeyLevelRubberband, Value(1)).asInt();
				const int currentLevel = eqBehavior->getEq();
				int expGain = 0;
				
				ObjectEvents::QueryObjects(QueryObjectsArgs<PlatformerEnemy>([&](PlatformerEnemy* enemy)
				{
					expGain += StatsTables::getKillExp(enemy);
				}), PlatformerEnemy::PlatformerEnemyTag);

				// This determins how drastic penalties and losses are for being outside of the intended level. Higher is more drastic.
				static const float GainFactor = 1.25f;

				// Apply rubber banding to keep the player near the intended level for the current map
				const int adjustedGain = intendedLevel == currentLevel
					? expGain
					: int(float(expGain) * std::pow(GainFactor, intendedLevel - currentLevel));

				friendlyExpBarBehavior->giveExp(adjustedGain);
			});
		});
	}), PlatformerEntity::PlatformerEntityTag);
}

void RewardsMenu::loadRewards()
{
	ObjectEvents::QueryObjects(QueryObjectsArgs<PlatformerEnemy>([&](PlatformerEnemy* enemy)
	{
		enemy->getAttachedBehavior<EntityDropTableBehavior>([=](EntityDropTableBehavior* entityDropTableBehavior)
		{
			MinMaxPool* dropPool = entityDropTableBehavior->getDropPool();

			if (dropPool != nullptr)
			{
				PlatformerEvents::TriggerGiveItemsFromPool(PlatformerEvents::GiveItemsFromPoolArgs(dropPool));
			}
		});
	}), PlatformerEnemy::PlatformerEnemyTag);
}
