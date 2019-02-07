#include "CombatHud.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Maps/Platformer/Huds/Components/StatsBars.h"

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

	this->addChild(this->playerPartyStatsNode);
	this->addChild(this->enemyPartyStatsNode);
}

CombatHud::~CombatHud()
{
}

void CombatHud::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void CombatHud::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->playerPartyStatsNode->setPosition(32.0f, visibleSize.height - 64.0f);
	this->enemyPartyStatsNode->setPosition(visibleSize.width - 320, visibleSize.height - 64.0f);

	int index = 0;

	for (auto it = this->playerPartyStatsBars.begin(); it != this->playerPartyStatsBars.end(); it++)
	{
		(*it)->setPositionY((float)index * -128.0f);

		index++;
	}
	
	index = 0;

	for (auto it = this->enemyPartyStatsBars.begin(); it != this->enemyPartyStatsBars.end(); it++)
	{
		(*it)->setAnchorPoint(Vec2(1.0f, 0.5f));
		(*it)->setPositionY((float)index * -128.0f);

		index++;
	}
}

void CombatHud::initializeListeners()
{
	super::initializeListeners();
}

void CombatHud::update(float dt)
{
	super::update(dt);
}

void CombatHud::bindStatsBars(std::vector<PlatformerEntity*> playerParty, std::vector<PlatformerEntity*> enemyParty)
{
	this->playerPartyStatsNode->removeAllChildren();
	this->enemyPartyStatsNode->removeAllChildren();
	this->playerPartyStatsBars.clear();
	this->enemyPartyStatsBars.clear();

	for (auto it = playerParty.begin(); it != playerParty.end(); it++)
	{
		StatsBars* statsBars = StatsBars::create();

		statsBars->setStatsTarget(*it);
		this->playerPartyStatsBars.push_back(statsBars);
		this->playerPartyStatsNode->addChild(statsBars);
	}

	for (auto it = enemyParty.begin(); it != enemyParty.end(); it++)
	{
		StatsBars* statsBars = StatsBars::create(false);

		statsBars->setStatsTarget(*it);
		this->enemyPartyStatsBars.push_back(statsBars);
		this->enemyPartyStatsNode->addChild(statsBars);
	}

	this->initializePositions();
}
