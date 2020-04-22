#include "CombatHud.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/ObjectEvents.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/PlatformerFriendly.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/CombatEvents.h"
#include "Menus/Dialogue/PlatformerDialogueBox.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"
#include "Scenes/Platformer/Level/Huds/Components/StatsBars.h"

using namespace cocos2d;

CombatHud* CombatHud::create()
{
	CombatHud* instance = new CombatHud();

	instance->autorelease();

	return instance;
}

CombatHud::CombatHud()
{
	this->playerPartyStatsNode = Node::create();
	this->enemyPartyStatsNode = Node::create();
	this->dialogueBox = PlatformerDialogueBox::create();
	this->playerPartyStatsBars = std::vector<StatsBars*>();
	this->enemyPartyStatsBars = std::vector<StatsBars*>();

	this->addChild(this->playerPartyStatsNode);
	this->addChild(this->enemyPartyStatsNode);
	this->addChild(this->dialogueBox);
}

CombatHud::~CombatHud()
{
}

void CombatHud::onEnter()
{
	super::onEnter();
}

void CombatHud::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->dialogueBox->setPosition(Vec2(visibleSize.width / 2.0f, 192.0f));
	this->playerPartyStatsNode->setPosition(32.0f, visibleSize.height - 96.0f);
	this->enemyPartyStatsNode->setPosition(visibleSize.width - 396.0f, visibleSize.height - 96.0f);
}

void CombatHud::initializeListeners()
{
	super::initializeListeners();
	
	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventSelectionChanged, [=](EventCustom* eventCustom)
	{
		CombatEvents::SelectionArgs* args = static_cast<CombatEvents::SelectionArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			for (auto next : this->playerPartyStatsBars)
			{
				next->setSelected(next->getStatsTarget() == args->target);
				next->getStatsTargetAsTimelineEntry()->setSelected(next->getStatsTarget() == args->target);
			}

			for (auto next : this->enemyPartyStatsBars)
			{
				next->setSelected(next->getStatsTarget() == args->target);
				next->getStatsTargetAsTimelineEntry()->setSelected(next->getStatsTarget() == args->target);
			}
		}
	}));
	
	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventResumeTimeline, [=](EventCustom* eventCustom)
	{
		for (auto next : this->playerPartyStatsBars)
		{
			next->setSelected(false);
			next->getStatsTargetAsTimelineEntry()->setSelected(false);
		}

		for (auto next : this->enemyPartyStatsBars)
		{
			next->setSelected(false);
			next->getStatsTargetAsTimelineEntry()->setSelected(false);
		}
	}));
}

void CombatHud::bindStatsBars(std::vector<TimelineEntry*> friendlyEntries, std::vector<TimelineEntry*> enemyEntries)
{
	this->playerPartyStatsNode->removeAllChildren();
	this->enemyPartyStatsNode->removeAllChildren();
	this->playerPartyStatsBars.clear();
	this->enemyPartyStatsBars.clear();

	for (auto next : friendlyEntries)
	{
		StatsBars* statsBars = StatsBars::create();
		
		statsBars->setStatsTargetAsTimelineEntry(next);
		
		this->playerPartyStatsBars.push_back(statsBars);
		this->playerPartyStatsNode->addChild(statsBars);
	}

	for (auto next : enemyEntries)
	{
		StatsBars* statsBars = StatsBars::create();
		
		statsBars->setStatsTargetAsTimelineEntry(next);
		
		this->enemyPartyStatsBars.push_back(statsBars);
		this->enemyPartyStatsNode->addChild(statsBars);
	}

	int index = 0;

	for (auto next : this->playerPartyStatsBars)
	{
		next->setPositionY((float)index * -160.0f);

		index++;
	}
	
	index = 0;

	for (auto next : this->enemyPartyStatsBars)
	{
		next->setAnchorPoint(Vec2(1.0f, 0.5f));
		next->setPositionY((float)index * -160.0f);

		index++;
	}
}
