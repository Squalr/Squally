#include "Timeline.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/SceneEvents.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/ProgressBar.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/PlatformerFriendly.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"

#include "Resources/UIResources.h"

#include "Strings/Combat/Cast.h"
#include "Strings/Combat/Wait.h"

using namespace cocos2d;

Timeline* Timeline::create()
{
	Timeline* instance = new Timeline();

	instance->autorelease();

	return instance;
}

Timeline::Timeline()
{
	this->swordFill = ProgressBar::create(Sprite::create(UIResources::Combat_SwordFillRed), Sprite::create(UIResources::Combat_SwordFill), Vec2::ZERO);
	this->swordTop = Sprite::create(UIResources::Combat_SwordTop);
	this->timelineNode = Node::create();
	this->timelineEntries = std::vector<TimelineEntry*>();
	this->timelineWidth = this->swordFill->getContentSize().width;
	this->waitLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Combat_Wait::create());
	this->castLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Combat_Cast::create());

	this->waitLabel->enableOutline(Color4B::BLACK, 2);
	this->castLabel->enableOutline(Color4B::BLACK, 2);

	this->waitLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->castLabel->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->swordFill->setProgress(TimelineEntry::CastPercentage);

	this->addChild(this->swordFill);
	this->addChild(this->swordTop);
	this->addChild(this->timelineNode);
	this->addChild(this->waitLabel);
	this->addChild(this->castLabel);
}

void Timeline::onEnter()
{
	super::onEnter();

	this->isTimelinePaused = false;
	this->isTimelineInterrupted = false;
	this->isCombatComplete = false;
	this->timelineEntryAwaitingUserAction = nullptr;

	this->scheduleUpdate();
}

void Timeline::initializePositions()
{
	super::initializePositions();

	const float fillOffsetX = 46.0f;

	this->swordTop->setPositionX(-fillOffsetX);
	this->waitLabel->setPositionX(-288.0f);
	this->castLabel->setPositionX(224.0f);
}

void Timeline::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(SceneEvents::EventBeforeSceneChange, [=](EventCustom* eventCustom)
	{
		this->timelineNode->removeAllChildren();
		this->timelineEntries.clear();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventSelectCastTarget, [=](EventCustom* eventCustom)
	{
		CombatEvents::CastTargetArgs* args = static_cast<CombatEvents::CastTargetArgs*>(eventCustom->getUserData());

		if (this->timelineEntryAwaitingUserAction != nullptr)
		{
			this->timelineEntryAwaitingUserAction->stageTarget(args->target);
		}

		CombatEvents::TriggerResumeTimeline();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventPauseTimeline, [=](EventCustom* eventCustom)
	{
		this->isTimelinePaused = true;
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventResumeTimeline, [=](EventCustom* eventCustom)
	{
		this->isTimelinePaused = false;
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventInterruptTimeline, [=](EventCustom* eventCustom)
	{
		this->isTimelineInterrupted = true;
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventChangeMenuState, [=](EventCustom* eventCustom)
	{
		CombatEvents::MenuStateArgs* args = static_cast<CombatEvents::MenuStateArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->entry != nullptr)
		{
			this->timelineEntryAwaitingUserAction = args->entry;

			switch (args->currentMenu)
			{
				case CombatEvents::MenuStateArgs::CurrentMenu::DefendSelect:
				{
					if (this->timelineEntryAwaitingUserAction != nullptr)
					{
						this->timelineEntryAwaitingUserAction->defend();
						this->timelineEntryAwaitingUserAction->stageCast(nullptr);
						this->timelineEntryAwaitingUserAction->stageTarget(nullptr);
					}
					
					CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::Closed, nullptr));
					CombatEvents::TriggerResumeTimeline();

					break;
				}
				default:
				{
					break;
				}
			}
		}
	}));
}

void Timeline::update(float dt)
{
	super::update(dt);

	this->checkCombatComplete();
	this->updateTimeline(dt);
}

void Timeline::checkCombatComplete()
{
	if (isCombatComplete)
	{
		return;
	}

	bool allEnemiesDead = true;
	bool allPlayersDead = true;

	ObjectEvents::QueryObjects(QueryObjectsArgs<PlatformerEnemy>([&](PlatformerEnemy* entity)
	{
		abort();
		// allEnemiesDead &= entity->isDead();
	}));

	ObjectEvents::QueryObjects(QueryObjectsArgs<PlatformerFriendly>([&](PlatformerFriendly* entity)
	{
		abort();
		// allPlayersDead &= entity->isDead();
	}));

	if (allEnemiesDead)
	{
		this->isCombatComplete = true;
		CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::Closed, nullptr));
		CombatEvents::TriggerCombatFinished(CombatEvents::CombatFinishedArgs(true));
	}
	else if (allPlayersDead)
	{
		this->isCombatComplete = true;
		CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::Closed, nullptr));
		CombatEvents::TriggerCombatFinished(CombatEvents::CombatFinishedArgs(false));
	}
}

void Timeline::updateTimeline(float dt)
{
	if (!this->isTimelinePaused && !isCombatComplete)
	{
		this->isTimelineInterrupted = false;

		// Update all timeline entries
		for (auto it = this->timelineEntries.begin(); it != this->timelineEntries.end(); it++)
		{
			TimelineEntry* entry = *it;

			abort();
			// if (!entry->getEntity()->isDead())
			{
				if (!this->isTimelineInterrupted)
				{
					entry->addTime(dt);

					entry->setPositionX(-this->timelineWidth / 2.0f + this->timelineWidth * entry->getProgress());
				}
				else
				{
					// An entity is already performing an action during this update call -- add the time to remaining entities without doing anything yet
					entry->addTimeWithoutActions(dt);
				}
			}
		}
	}
}

void Timeline::resumeTimeline()
{
	this->isTimelinePaused = true;
	this->timelineEntryAwaitingUserAction = nullptr;
}

void Timeline::initializeTimeline(bool isPlayerFirstStrike)
{
	this->timelineNode->removeAllChildren();
	this->timelineEntries.clear();

	float nextPlayerBonus = 0.0f;
	float nextEnemyBonus = 0.0f;
	float playerFirstStrikeBonus = isPlayerFirstStrike ? 0.5f : 0.35f;
	float enemyFirstStrikeBonus = !isPlayerFirstStrike ? 0.5f : 0.35f;

	ObjectEvents::QueryObjects(QueryObjectsArgs<PlatformerFriendly>([&](PlatformerFriendly* entity)
	{
		TimelineEntry* entry = TimelineEntry::create(entity);

		this->timelineEntries.push_back(entry);
		this->timelineNode->addChild(entry);

		entry->setProgress(playerFirstStrikeBonus + nextPlayerBonus);
		nextPlayerBonus += 0.1f;
	}));

	ObjectEvents::QueryObjects(QueryObjectsArgs<PlatformerEnemy>([&](PlatformerEnemy* entity)
	{
		TimelineEntry* entry = TimelineEntry::create(entity);

		this->timelineEntries.push_back(entry);
		this->timelineNode->addChild(entry);

		entry->setProgress(enemyFirstStrikeBonus + nextEnemyBonus);
		nextEnemyBonus += 0.1f;
	}));
}
