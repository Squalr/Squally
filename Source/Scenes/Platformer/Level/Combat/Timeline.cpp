#include "Timeline.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/SceneEvents.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/ProgressBar.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/PlatformerFriendly.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"
#include "Scenes/Platformer/Level/Combat/TimelineEventGroup.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

Timeline* Timeline::create()
{
	Timeline* instance = new Timeline();

	instance->autorelease();

	return instance;
}

Timeline::Timeline()
{
	this->isTimelinePaused = true;
	this->isTimelineCinematicPaused = false;
	this->isTimelineInterrupted = false;
	this->isCombatComplete = false;
	this->hasInit = false;
	this->timelineEntryAwaitingUserAction = nullptr;

	this->swordFill = ProgressBar::create(Sprite::create(UIResources::Combat_SwordFillRed), Sprite::create(UIResources::Combat_SwordFill), Vec2::ZERO);
	this->swordTop = Sprite::create(UIResources::Combat_SwordTop);
	this->eventsNode = Node::create();
	this->entriesNode = Node::create();
	this->timelineEntries = std::vector<TimelineEntry*>();
	this->timelineEventGroups = std::vector<TimelineEventGroup*>();
	this->timelineWidth = this->swordFill->getContentSize().width;
	this->waitLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Platformer_Combat_Wait::create());
	this->castLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Platformer_Combat_Cast::create());

	this->waitLabel->enableOutline(Color4B::BLACK, 2);
	this->castLabel->enableOutline(Color4B::BLACK, 2);

	this->waitLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->castLabel->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->swordFill->setProgress(TimelineEntry::CastPercentage);

	this->addChild(this->swordFill);
	this->addChild(this->swordTop);
	this->addChild(this->eventsNode);
	this->addChild(this->entriesNode);
	this->addChild(this->waitLabel);
	this->addChild(this->castLabel);
}

Timeline::~Timeline()
{
}

void Timeline::onEnter()
{
	super::onEnter();

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
		this->eventsNode->removeAllChildren();
		this->entriesNode->removeAllChildren();
		this->timelineEntries.clear();
		this->timelineEventGroups.clear();
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

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventPauseTimelineCinematic, [=](EventCustom* eventCustom)
	{
		this->isTimelineCinematicPaused = true;
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventResumeTimelineCinematic, [=](EventCustom* eventCustom)
	{
		this->isTimelineCinematicPaused = false;
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventInterruptTimeline, [=](EventCustom* eventCustom)
	{
		this->isTimelineInterrupted = true;
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventRegisterTimelineEventGroup, [=](EventCustom* eventCustom)
	{
		CombatEvents::RegisterTimelineEventGroupArgs* args = static_cast<CombatEvents::RegisterTimelineEventGroupArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->registerTimelineEventGroup(args->eventGroup);
		}
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

	if (this->hasInit)
	{
		this->checkCombatComplete();
		this->updateTimeline(dt);
	}
}

void Timeline::checkCombatComplete()
{
	if (isCombatComplete)
	{
		return;
	}

	static bool anyEnemyAlive = false;
	static bool anyPlayerAlive = false;

	anyEnemyAlive = false;
	anyPlayerAlive = false;

	for (auto next : this->timelineEntries)
	{
		PlatformerEntity* entity = next->getEntity();

		if (dynamic_cast<PlatformerEnemy*>(entity) != nullptr)
		{
			anyEnemyAlive |= entity->getStateOrDefaultBool(StateKeys::IsAlive, true);
		}
		else if (dynamic_cast<PlatformerFriendly*>(entity) != nullptr)
		{
			anyPlayerAlive |= entity->getStateOrDefaultBool(StateKeys::IsAlive, true);
		}
	}

	if (!anyEnemyAlive)
	{
		this->isCombatComplete = true;
		CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::Closed, nullptr));
		CombatEvents::TriggerCombatFinished(CombatEvents::CombatFinishedArgs(true));
	}
	else if (!anyPlayerAlive)
	{
		this->isCombatComplete = true;
		CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::Closed, nullptr));
		CombatEvents::TriggerCombatFinished(CombatEvents::CombatFinishedArgs(false));
	}
}

void Timeline::updateTimeline(float dt)
{
	if (!(this->isTimelinePaused || this->isTimelineCinematicPaused) && !isCombatComplete)
	{
		this->isTimelineInterrupted = false;

		// Update all timeline entries
		for (auto entry : this->timelineEntries)
		{
			if (entry->getEntity()->getStateOrDefaultBool(StateKeys::IsAlive, true))
			{
				float currentTime = entry->getProgress();

				if (!this->isTimelineInterrupted)
				{
					entry->addTimeWithoutActions(dt);
					entry->setPositionX(-this->timelineWidth / 2.0f + this->timelineWidth * entry->getProgress());

					entry->tryPerformActions();
				}
				else
				{
					// An entity is already performing an action during this update call -- add the time to remaining entities without doing anything yet
					entry->addTimeWithoutActions(dt);
				}

				for (auto eventGroup : this->timelineEventGroups)
				{
					if (eventGroup->getOwner() == entry->getEntity())
					{
						if (eventGroup->processEvents(currentTime, entry->getProgress()))
						{
							this->unregisterTimelineEventGroup(eventGroup);
						}
					}
				}
			}
		}
	}
}

void Timeline::resumeTimeline()
{
	this->hasInit = true;
	this->isTimelinePaused = false;
}

std::vector<TimelineEntry*> Timeline::getEntries()
{
	return this->timelineEntries;
}

std::vector<TimelineEntry*> Timeline::initializeTimelineFriendly(bool isPlayerFirstStrike, std::vector<PlatformerEntity*> friendlyEntities)
{
	std::vector<TimelineEntry*> entries = std::vector<TimelineEntry*>();
	float playerFirstStrikeBonus = isPlayerFirstStrike ? 0.5f : 0.35f;
	float nextPlayerBonus = 0.0f;
	int index = 0;

	for (auto it = friendlyEntities.begin(); it != friendlyEntities.end(); it++)
	{
		TimelineEntry* entry = TimelineEntry::create(*it, index++);

		this->timelineEntries.push_back(entry);
		this->entriesNode->addChild(entry);

		entry->setProgress(playerFirstStrikeBonus + nextPlayerBonus);
		nextPlayerBonus += 0.1f;

		entries.push_back(entry);
	}

	return entries;
}

std::vector<TimelineEntry*> Timeline::initializeTimelineEnemies(bool isPlayerFirstStrike, std::vector<PlatformerEntity*> enemyEntities)
{
	std::vector<TimelineEntry*> entries = std::vector<TimelineEntry*>();
	float nextEnemyBonus = 0.0f;
	float enemyFirstStrikeBonus = !isPlayerFirstStrike ? 0.5f : 0.35f;
	int index = 0;

	for (auto it = enemyEntities.begin(); it != enemyEntities.end(); it++)
	{
		TimelineEntry* entry = TimelineEntry::create(*it, index++);

		this->timelineEntries.push_back(entry);
		this->entriesNode->addChild(entry);

		entry->setProgress(enemyFirstStrikeBonus + nextEnemyBonus);
		nextEnemyBonus += 0.1f;
		
		entries.push_back(entry);
	}

	return entries;
}

void Timeline::registerTimelineEventGroup(TimelineEventGroup* timelineEventGroup)
{
	if (timelineEventGroup == nullptr)
	{
		return;
	}

	for (auto next : this->timelineEntries)
	{
		if (next->getEntity() == timelineEventGroup->getOwner())
		{
			timelineEventGroup->offsetByTimelineTime(next->getProgress());
			timelineEventGroup->setPositions(this->timelineWidth);
		}
	}

	this->timelineEventGroups.push_back(timelineEventGroup);

	this->eventsNode->addChild(timelineEventGroup);
}

void Timeline::unregisterTimelineEventGroup(TimelineEventGroup* timelineEventGroup)
{
	if (timelineEventGroup == nullptr)
	{
		return;
	}

	this->timelineEventGroups.erase(std::remove(this->timelineEventGroups.begin(), this->timelineEventGroups.end(), timelineEventGroup), this->timelineEventGroups.end());
	this->eventsNode->removeChild(timelineEventGroup);
}
