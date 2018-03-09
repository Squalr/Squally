#include "Fight.h"

Fight* Fight::create()
{
	Fight* fight = new Fight();

	fight->autorelease();

	return fight;
}

Fight::Fight()
{
}

Fight::~Fight()
{
}

void Fight::onEnter()
{
	FadeScene::onEnter();

	this->addChild(Mouse::claimInstance());

	this->scheduleUpdate();
	this->initializePositions();
	this->initializeListeners();
}

void Fight::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->hackerModeBackground->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
}

void Fight::initializeListeners()
{
}

void Fight::loadFight(Fight::FightData fightData)
{
	this->addChild(InputManager::claimInstance());

	this->addChild(this->background);
	this->addChild(this->objectLayer);
	this->addChild(this->entityLayer);
}

void Fight::update(float dt)
{
	FadeScene::update(dt);
}
