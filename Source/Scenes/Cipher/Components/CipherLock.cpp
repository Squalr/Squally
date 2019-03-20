#include "CipherLock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"
#include "Scenes/Cipher/CipherState.h"

#include "Resources/CipherResources.h"

using namespace cocos2d;

CipherLock* CipherLock::create()
{
	CipherLock* instance = new CipherLock();

	instance->autorelease();

	return instance;
}

CipherLock::CipherLock()
{
	this->background = Sprite::create(CipherResources::Lock_Background);
	this->steelGear = Sprite::create(CipherResources::Lock_GearSteel);
	this->woodGearTop = Sprite::create(CipherResources::Lock_GearWood);
	this->woodGearBottom = Sprite::create(CipherResources::Lock_GearWood);
	this->shaft = Sprite::create(CipherResources::Lock_Shaft);
	this->pinboardBack = Sprite::create(CipherResources::Lock_PinboardBack);
	this->stoppingBlock = Sprite::create(CipherResources::Lock_StoppingBlock);
	this->pinboardFront = Sprite::create(CipherResources::Lock_PinboardFront);

	this->addChild(this->background);
	this->addChild(this->steelGear);
	this->addChild(this->woodGearTop);
	this->addChild(this->woodGearBottom);
	this->addChild(this->shaft);
	this->addChild(this->pinboardBack);
	this->addChild(this->stoppingBlock);
	this->addChild(this->pinboardFront);
}

CipherLock::~CipherLock()
{
}

void CipherLock::onEnter()
{
	super::onEnter();
}

void CipherLock::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background->setPosition(Vec2(visibleSize.width / 2.0f + Config::RightColumnCenter, visibleSize.height / 2.0f + Config::TopPanelCenter));
	this->steelGear->setPosition(Vec2(visibleSize.width / 2.0f + Config::RightColumnCenter + 64.0f, visibleSize.height / 2.0f + Config::TopPanelCenter));
	this->woodGearTop->setPosition(Vec2(visibleSize.width / 2.0f + Config::RightColumnCenter + 120.0f, visibleSize.height / 2.0f + Config::TopPanelCenter + 80.0f));
	this->woodGearBottom->setPosition(Vec2(visibleSize.width / 2.0f + Config::RightColumnCenter + 120.0f, visibleSize.height / 2.0f + Config::TopPanelCenter - 80.0f));
	this->shaft->setPosition(Vec2(visibleSize.width / 2.0f + Config::RightColumnCenter + 40.0f, visibleSize.height / 2.0f + Config::TopPanelCenter));
	this->pinboardBack->setPosition(Vec2(visibleSize.width / 2.0f + Config::RightColumnCenter - 66.0f, visibleSize.height / 2.0f + Config::TopPanelCenter));
	this->stoppingBlock->setPosition(Vec2(visibleSize.width / 2.0f + Config::RightColumnCenter - 16.0f, visibleSize.height / 2.0f + Config::TopPanelCenter + 96.0f));
	this->pinboardFront->setPosition(Vec2(visibleSize.width / 2.0f + Config::RightColumnCenter - 40.0f, visibleSize.height / 2.0f + Config::TopPanelCenter));
}

void CipherLock::onBeforeStateChange(CipherState* cipherState)
{
	super::onBeforeStateChange(cipherState);
}

void CipherLock::onAnyStateChange(CipherState* cipherState)
{
	super::onAnyStateChange(cipherState);

	switch(cipherState->stateType)
	{
		case CipherState::StateType::Running:
		{
			this->setVisible(true);
			break;
		}
		default:
		{
			this->setVisible(false);
			break;
		}
	}
}
