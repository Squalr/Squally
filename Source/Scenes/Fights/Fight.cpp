#include "Fight.h"

Fight* Fight::create()
{
	Fight* instance = new Fight();

	instance->autorelease();

	return instance;
}

Fight::Fight()
{
	this->addChild(Mouse::create());
}

Fight::~Fight()
{
}

void Fight::onEnter()
{
	FadeScene::onEnter();

	this->scheduleUpdate();
}

void Fight::initializePositions()
{
	FadeScene::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void Fight::initializeListeners()
{
	FadeScene::initializeListeners();
}

void Fight::loadFight(Squally* squally, PlatformerEnemy* enemy)
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
