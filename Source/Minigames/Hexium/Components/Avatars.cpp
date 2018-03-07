#include "Avatars.h"

Avatars* Avatars::create()
{
	Avatars* avatars = new Avatars();

	avatars->autorelease();

	return avatars;
}

Avatars::Avatars()
{
	this->playerFrame = Sprite::create(Resources::Minigames_Hexium_AvatarFrame);
	this->enemyFrame = Sprite::create(Resources::Minigames_Hexium_AvatarFrame);

	this->addChild(this->playerFrame);
	this->addChild(this->enemyFrame);
}

Avatars::~Avatars()
{
}

void Avatars::onEnter()
{
	ComponentBase::onEnter();

	this->initializePositions();
	this->initializeListeners();
}

void Avatars::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->playerFrame->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::frameOffsetX, visibleSize.height / 2.0f - Config::frameOffsetY);
	this->enemyFrame->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::frameOffsetX, visibleSize.height / 2.0f + Config::frameOffsetY);
}

void Avatars::initializeListeners()
{
}

void Avatars::onStateChange(GameState* gameState)
{
	switch (gameState->stateType) {
	case GameState::StateType::ControlNeutral:
		break;
	}
}

void Avatars::setAvatars(GameState* gameState)
{
}
