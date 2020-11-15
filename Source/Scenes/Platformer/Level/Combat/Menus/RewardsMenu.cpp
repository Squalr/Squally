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
#include "Engine/Inventory/DropPool.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Sound/Sound.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/StatsTables/StatsTables.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/CombatEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityDropTableBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Combat/FriendlyExpBarBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityEqBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityManaBehavior.h"
#include "Scenes/Platformer/Level/Combat/Timeline.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

RewardsMenu* RewardsMenu::create(Timeline* timelineRef)
{
	RewardsMenu* instance = new RewardsMenu(timelineRef);

	instance->autorelease();

	return instance;
}

RewardsMenu::RewardsMenu(Timeline* timelineRef)
{
	this->victoryMenu = Sprite::create(UIResources::Combat_VictoryMenu);
	this->expNode = Node::create();
	this->victorySound = Sound::create(SoundResources::Platformer_Combat_Victory);
	this->emblemCount = 0;
	this->timelineRef = timelineRef;

	this->victoryLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::M2, Strings::Platformer_Combat_Victory::create());

	LocalizedLabel*	returnLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Return::create());
	LocalizedLabel*	returnLabelHover = returnLabel->clone();

	returnLabel->enableOutline(Color4B::BLACK, 2);
	returnLabelHover->enableOutline(Color4B::BLACK, 2);

	this->returnButton = ClickableTextNode::create(returnLabel, returnLabelHover, Sprite::create(UIResources::Menus_Buttons_WoodButton), Sprite::create(UIResources::Menus_Buttons_WoodButtonSelected));

	this->victoryLabel->enableOutline(Color4B::BLACK, 2);

	this->addChild(this->victoryMenu);
	this->addChild(this->victoryLabel);
	this->addChild(this->expNode);
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

	this->returnButton->setMouseClickCallback([=](MouseEventArgs*)
	{
		CombatEvents::TriggerBeforeReturnToMap(CombatEvents::BeforeReturnToMapArgs(false));
		CombatEvents::TriggerReturnToMap();
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_SPACE }, [=](KeyboardEventArgs* args)
	{
		if (!GameUtils::isVisible(this))
		{
			return;
		}

		CombatEvents::TriggerBeforeReturnToMap(CombatEvents::BeforeReturnToMapArgs(false));
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
	this->clearEmblems();

	ObjectEvents::QueryObjects(QueryObjectsArgs<PlatformerEntity>([&](PlatformerEntity* entity)
	{
		entity->getAttachedBehavior<FriendlyExpBarBehavior>([&](FriendlyExpBarBehavior* friendlyExpBarBehavior)
		{
			entity->getAttachedBehavior<EntityEqBehavior>([&](EntityEqBehavior* eqBehavior)
			{
				const int intendedLevel = SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeyLevelRubberband, Value(1)).asInt();
				const int currentLevel = eqBehavior->getEq();
				const int levelDelta = intendedLevel - currentLevel;
				int expGain = 0;
				
				for (auto next : timelineRef->getEntries())
				{
					if (!next->isPlayerEntry())
					{
						expGain += StatsTables::getKillExp(next->getEntity());
					}
				}

				// This determines how drastic penalties and losses are for being outside of the intended level. Higher is more drastic.
				static const float GainFactor = 1.25f;

				// Apply rubber banding to keep the player near the intended level for the current map
				const int adjustedGain = intendedLevel == currentLevel
					? expGain
					// Exponential by gain factor, to the power of intended level delta. Cap at 3x exp gain.
					: std::min(expGain * 3, int(float(expGain) * std::pow(GainFactor, levelDelta)));

				const float startProgress = float(eqBehavior->getEqExperience()) / float(StatsTables::getExpRequiredAtLevel(entity));
				const bool didLevelUp = eqBehavior->addEqExperience(adjustedGain);
				const float endProgress = float(eqBehavior->getEqExperience()) / float(StatsTables::getExpRequiredAtLevel(entity));

				friendlyExpBarBehavior->giveExp(startProgress, endProgress, didLevelUp, adjustedGain);

				if (didLevelUp)
				{
					entity->getAttachedBehavior<EntityHealthBehavior>([&](EntityHealthBehavior* healthBehavior)
					{
						healthBehavior->setHealth(healthBehavior->getMaxHealth(), false);
					});

					entity->getAttachedBehavior<EntityManaBehavior>([&](EntityManaBehavior* manaBehavior)
					{
						manaBehavior->setMana(manaBehavior->getMaxMana());
					});
				}

				this->addExpEmblem(entity->getEmblemResource(), adjustedGain);
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
			DropPool* dropPool = entityDropTableBehavior->getDropPool();

			if (dropPool != nullptr)
			{
				PlatformerEvents::TriggerGiveCurrenciesFromPool(PlatformerEvents::GiveCurrenciesFromPoolArgs(dropPool->getCurrencyPool(), nullptr, true));
				PlatformerEvents::TriggerGiveItemsFromPool(PlatformerEvents::GiveItemsFromPoolArgs(dropPool, nullptr, true));
			}
		});
	}), PlatformerEnemy::PlatformerEnemyTag);
}

void RewardsMenu::clearEmblems()
{
	this->expNode->removeAllChildren();
	this->emblemCount = 0;
}

void RewardsMenu::addExpEmblem(std::string emblemResource, int gain)
{
	const float LeftShift = -16.0f;

	Sprite* emblem = Sprite::create(emblemResource);
	LocalizedString* expGainString = Strings::Platformer_Combat_ExpGain::create()->setStringReplacementVariables(ConstantString::create(std::to_string(gain)));
	LocalizedLabel* expGainLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, expGainString);

	const Vec2 offset = Vec2(-64.0f, 48.0f);

	emblem->setPosition(Vec2(LeftShift, -64.0f * float(this->emblemCount)) + offset);
	expGainLabel->setPosition(Vec2(LeftShift + 48.0f, -64.0f * float(this->emblemCount)) + offset);
	expGainLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	expGainLabel->enableOutline(Color4B::BLACK, 2);

	this->expNode->addChild(emblem);
	this->expNode->addChild(expGainLabel);

	this->emblemCount++;
}
