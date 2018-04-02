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
}

void Fight::initializeListeners()
{
}

void Fight::loadFight(Player* player, Entity* enemy)
{
	this->addChild(InputManager::claimInstance());

	// this->addChild(this->background);
	// this->addChild(this->objectLayer);
	// this->addChild(this->entityLayer);

}

void Fight::update(float dt)
{
	FadeScene::update(dt);
}
