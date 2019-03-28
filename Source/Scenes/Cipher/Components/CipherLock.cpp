#include "CipherLock.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"
#include "Scenes/Cipher/CipherState.h"

#include "Resources/CipherResources.h"

using namespace cocos2d;

const int CipherLock::PinSpacing = 48.0f;

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
	this->cipherPinsNode = Node::create();
	this->stoppingBlock = Sprite::create(CipherResources::Lock_StoppingBlock);
	this->pinboardFront = Sprite::create(CipherResources::Lock_PinboardFront);
	this->cipherPins = std::vector<cocos2d::Sprite*>();

	this->addChild(this->background);
	this->addChild(this->steelGear);
	this->addChild(this->woodGearTop);
	this->addChild(this->woodGearBottom);
	this->addChild(this->shaft);
	this->addChild(this->pinboardBack);
	this->addChild(this->cipherPinsNode);
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
	this->cipherPinsNode->setPosition(Vec2(visibleSize.width / 2.0f + Config::RightColumnCenter - 66.0f, visibleSize.height / 2.0f + Config::TopPanelCenter));
	this->pinboardBack->setPosition(Vec2(visibleSize.width / 2.0f + Config::RightColumnCenter - 66.0f, visibleSize.height / 2.0f + Config::TopPanelCenter));
	this->stoppingBlock->setPosition(Vec2(visibleSize.width / 2.0f + Config::RightColumnCenter - 16.0f, visibleSize.height / 2.0f + Config::TopPanelCenter + 96.0f));
	this->pinboardFront->setPosition(Vec2(visibleSize.width / 2.0f + Config::RightColumnCenter - 40.0f, visibleSize.height / 2.0f + Config::TopPanelCenter));

	int index = 0;

	for (auto it = cipherPins.begin(); it != cipherPins.end(); it++, index++)
	{
		(*it)->setPosition(Vec2(0.0f, float(index) * -CipherLock::PinSpacing));
	}
}

void CipherLock::initializeListeners()
{
	super::initializeListeners();

	this->addEventListener(EventListenerCustom::create(CipherEvents::EventTryUnlockCurrentCipher, ([=](EventCustom* eventCustom)
	{
		CipherEvents::UnlockArgs* args = static_cast<CipherEvents::UnlockArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			if (args->cipherIndex < cipherPins.size())
			{
				Sprite* pin = this->cipherPins[args->cipherIndex];

				pin->runAction(Sequence::create(
					MoveBy::create(0.5f, Vec2(-32.0f, 0.0f)),
					CallFunc::create([=]()
					{
						this->woodGearTop->runAction(RotateBy::create(0.5f, 180.0f));
						this->steelGear->runAction(RotateBy::create(0.5f, -180.0f));
						this->woodGearBottom->runAction(RotateBy::create(0.5f, 180.0f));

						this->cipherPinsNode->runAction(Sequence::create(
							MoveBy::create(0.5f, Vec2(0.0f, CipherLock::PinSpacing)),
							nullptr
						));
					}),
					DelayTime::create(0.5f),
					CallFunc::create(args->callback),
					nullptr
				));
			}
			else
			{
				if (args->callback != nullptr)
				{
					args->callback();
				}
			}
		}
	})));
}

void CipherLock::onBeforeStateChange(CipherState* cipherState)
{
	super::onBeforeStateChange(cipherState);

	switch(cipherState->stateType)
	{
		case CipherState::StateType::Testing:
		case CipherState::StateType::Unlocking:
		{
			// Reset positions
			this->initializePositions();
			break;
		}
		default:
		{
			break;
		}
	}
}

void CipherLock::onAnyStateChange(CipherState* cipherState)
{
	super::onAnyStateChange(cipherState);

	switch(cipherState->stateType)
	{
		case CipherState::StateType::LoadInitialState:
		{
			this->cipherPins.clear();
			this->cipherPinsNode->removeAllChildren();

			for (auto it = cipherState->inputOutputMap.begin(); it != cipherState->inputOutputMap.end(); it++)
			{
				Sprite* pin = Sprite::create(CipherResources::Lock_Pin);

				this->cipherPins.push_back(pin);
				this->cipherPinsNode->addChild(pin);
			}
			
			this->initializePositions();
			break;
		}
		case CipherState::StateType::Testing:
		case CipherState::StateType::Unlocking:
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
