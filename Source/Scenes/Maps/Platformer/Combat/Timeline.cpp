#include "Timeline.h"

#include "cocos/2d/CCClippingRectangleNode.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/CProgressBar.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Scenes/Maps/Platformer/Combat/TimelineEntry.h"

#include "Resources/UIResources.h"

#include "Strings/Combat/Cast.h"
#include "Strings/Combat/Wait.h"

using namespace cocos2d;

const float Timeline::TimelineSpeed = 0.00025f;

Timeline* Timeline::create()
{
	Timeline* instance = new Timeline();

	instance->autorelease();

	return instance;
}

Timeline::Timeline()
{
	this->swordFill = CProgressBar::create(Sprite::create(UIResources::Combat_SwordFillRed), Sprite::create(UIResources::Combat_SwordFill), Vec2::ZERO);
	this->swordTop = Sprite::create(UIResources::Combat_SwordTop);
	this->timelineNode = Node::create();
	this->timelineEntries = std::vector<TimelineEntry*>();
	this->timelineWidth = this->swordFill->getContentSize().width;
	this->timelineEntryAwaitingUserAction = nullptr;
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

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventRequestUserAction, [=](EventCustom* eventCustom)
	{
		CombatEvents::RequestUserActionArgs* args = static_cast<CombatEvents::RequestUserActionArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->timelineEntryAwaitingUserAction = args->entry;
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventDefendSelected, [=](EventCustom* eventCustom)
	{
		if (this->timelineEntryAwaitingUserAction != nullptr)
		{
			this->timelineEntryAwaitingUserAction->defend();
		}

		CombatEvents::TriggerUserActionMade();
	}));
}

void Timeline::update(float dt)
{
	super::update(dt);

	if (this->timelineEntryAwaitingUserAction == nullptr)
	{
		// Update all timeline entries
		for (auto it = this->timelineEntries.begin(); it != this->timelineEntries.end(); it++)
		{
			TimelineEntry* entry = *it;
			float progress = entry->addProgress(dt * entry->getSpeed() * Timeline::TimelineSpeed * this->timelineWidth);

			entry->setPositionX(-this->timelineWidth / 2.0f + this->timelineWidth * progress);
		}
	}
}

void Timeline::actionMade()
{
	this->timelineEntryAwaitingUserAction = nullptr;
}

void Timeline::initializeTimeline(std::vector<PlatformerEntity*> playerEntities, std::vector<PlatformerEntity*> enemyEntities, bool isPlayerFirstStrike)
{
	this->playerEntities = playerEntities;
	this->enemyEntities = enemyEntities;

	this->timelineNode->removeAllChildren();
	this->timelineEntries.clear();

	for (auto it = this->playerEntities.begin(); it != this->playerEntities.end(); it++)
	{
		TimelineEntry* entry = TimelineEntry::create(*it, true);

		this->timelineEntries.push_back(entry);
		this->timelineNode->addChild(entry);

		entry->addProgress(RandomHelper::random_real(0.0f, 0.5f));
	}

	for (auto it = this->enemyEntities.begin(); it != this->enemyEntities.end(); it++)
	{
		TimelineEntry* entry = TimelineEntry::create(*it, false);

		this->timelineEntries.push_back(entry);
		this->timelineNode->addChild(entry);

		entry->addProgress(RandomHelper::random_real(0.0f, 0.5f));
	}
}
