#include "Timeline.h"

#include "cocos/2d/CCClippingRectangleNode.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/ProgressBar.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/PlatformerFriendly.h"
#include "Events/CombatEvents.h"
#include "Scenes/Maps/Platformer/Combat/TimelineEntry.h"

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

void Timeline::onExit()
{
	super::onExit();

	this->timelineNode->removeAllChildren();
	this->timelineEntries.clear();
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

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventSelectCastTarget, [=](EventCustom* args)
	{
		CombatEvents::CastTargetArgs* targetArgs = static_cast<CombatEvents::CastTargetArgs*>(args->getUserData());

		if (this->timelineEntryAwaitingUserAction != nullptr)
		{
			this->timelineEntryAwaitingUserAction->stageTarget(targetArgs->target);
		}

		CombatEvents::TriggerResumeTimeline();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventPauseTimeline, [=](EventCustom* args)
	{
		this->isTimelinePaused = true;
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventResumeTimeline, [=](EventCustom* args)
	{
		this->isTimelinePaused = false;
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventInterruptTimeline, [=](EventCustom* args)
	{
		this->isTimelineInterrupted = true;
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventChangeMenuState, [=](EventCustom* args)
	{
		CombatEvents::MenuStateArgs* combatArgs = static_cast<CombatEvents::MenuStateArgs*>(args->getUserData());

		if (combatArgs != nullptr && combatArgs->entry != nullptr)
		{
			this->timelineEntryAwaitingUserAction = combatArgs->entry;

			switch (combatArgs->currentMenu)
			{
				case CombatEvents::MenuStateArgs::CurrentMenu::DefendSelect:
				{
					if (this->timelineEntryAwaitingUserAction != nullptr)
					{
						// TODO: Trigger defend event
					}

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
		allEnemiesDead &= entity->isDead();
	}));

	ObjectEvents::QueryObjects(QueryObjectsArgs<PlatformerFriendly>([&](PlatformerFriendly* entity)
	{
		allPlayersDead &= entity->isDead();
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

			if (!entry->getEntity()->isDead())
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

	ObjectEvents::QueryObjects(QueryObjectsArgs<PlatformerFriendly>([&](PlatformerFriendly* entity)
	{
		TimelineEntry* entry = TimelineEntry::create(entity);

		this->timelineEntries.push_back(entry);
		this->timelineNode->addChild(entry);

		entry->setProgress(RandomHelper::random_real((isPlayerFirstStrike ? 0.25f : 0.0f), (isPlayerFirstStrike ? 0.5f : 0.25f)));
	}));

	ObjectEvents::QueryObjects(QueryObjectsArgs<PlatformerEnemy>([&](PlatformerEnemy* entity)
	{
		TimelineEntry* entry = TimelineEntry::create(entity);

		this->timelineEntries.push_back(entry);
		this->timelineNode->addChild(entry);

		entry->setProgress(RandomHelper::random_real((!isPlayerFirstStrike ? 0.25f : 0.0f), (!isPlayerFirstStrike ? 0.5f : 0.25f)));
	}));
}
