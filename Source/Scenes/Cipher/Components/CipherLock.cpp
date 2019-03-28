#include "CipherLock.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCDrawNode.h"
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
const int CipherLock::PinUnlockDistance = 112.0f;

CipherLock* CipherLock::create()
{
	CipherLock* instance = new CipherLock();

	instance->autorelease();

	return instance;
}

CipherLock::CipherLock()
{
	this->hasAnyPinFailed = false;
	
	DrawNode* stencil = DrawNode::create();

	stencil->drawSolidRect(Vec2(-224.0f, -224.0f), Vec2(224.0f, 224.0f), Color4F::GREEN);

	this->contentClip = ClippingNode::create(stencil);
	this->background = Sprite::create(CipherResources::Lock_Background);
	this->steelGear = Sprite::create(CipherResources::Lock_GearSteel);
	this->woodGearTop = Sprite::create(CipherResources::Lock_GearWood);
	this->woodGearBottom = Sprite::create(CipherResources::Lock_GearWood);
	this->shaft = Sprite::create(CipherResources::Lock_Shaft);
	this->pinboardBack = Sprite::create(CipherResources::Lock_PinboardBack);
	this->cipherPinsNode = Node::create();
	this->stoppingBlock = Sprite::create(CipherResources::Lock_StoppingBlock);
	this->pinboardFront = Sprite::create(CipherResources::Lock_PinboardFront);
	this->cipherPinholes = std::vector<cocos2d::Sprite*>();
	this->cipherPins = std::vector<cocos2d::Sprite*>();

	// Enable to debug clipping:
	// this->contentClip->addChild(stencil);

	Texture2D::TexParams params = Texture2D::TexParams();
	params.minFilter = GL_LINEAR;
	params.magFilter = GL_LINEAR;
	params.wrapT = GL_REPEAT;

	this->shaft->getTexture()->setTexParameters(params);
	this->shaft->setTextureRect(Rect(0.0f, 0.0f, this->shaft->getContentSize().width, this->shaft->getContentSize().height * 8.0f));

	this->contentClip->addChild(this->background);
	this->contentClip->addChild(this->steelGear);
	this->contentClip->addChild(this->woodGearTop);
	this->contentClip->addChild(this->woodGearBottom);
	this->contentClip->addChild(this->shaft);
	this->contentClip->addChild(this->pinboardBack);
	this->contentClip->addChild(this->cipherPinsNode);
	this->contentClip->addChild(this->stoppingBlock);
	this->contentClip->addChild(this->pinboardFront);
	this->addChild(this->contentClip);
}

CipherLock::~CipherLock()
{
}

void CipherLock::onEnter()
{
	super::onEnter();

	this->setVisible(false);
}

void CipherLock::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->contentClip->setPosition(Vec2(visibleSize.width / 2.0f + Config::RightColumnCenter, visibleSize.height / 2.0f + Config::TopPanelCenter));
	this->background->setPosition(Vec2(0.0f, 0.0f));
	this->steelGear->setPosition(Vec2(0.0f + 64.0f, 0.0f));
	this->woodGearTop->setPosition(Vec2(0.0f + 120.0f, 80.0f));
	this->woodGearBottom->setPosition(Vec2(0.0f + 120.0f, -80.0f));
	this->shaft->setPosition(Vec2(0.0f + 38.0f, 0.0f));
	this->cipherPinsNode->setPosition(Vec2(0.0f + 38.0f, 56.0f));
	this->pinboardBack->setPosition(Vec2(-66.0f, 0.0f));
	this->stoppingBlock->setPosition(Vec2(-16.0f, 96.0f));
	this->pinboardFront->setPosition(Vec2(-40.0f, 0.0f));

	for (int index = 0; (index < this->cipherPins.size() && index < this->cipherPinholes.size()); index++)
	{
		this->cipherPinholes[index]->setPosition(Vec2(0.0f, float(index) * -CipherLock::PinSpacing));
		this->cipherPins[index]->setPosition(Vec2(-24.0f, float(index) * -CipherLock::PinSpacing));
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
			this->hasAnyPinFailed |= !(args->success);
			
			if (args->cipherIndex < cipherPins.size())
			{
				Sprite* pinhole = this->cipherPinholes[args->cipherIndex];
				Sprite* pin = this->cipherPins[args->cipherIndex];

				CallFunc* scrollFunc = CallFunc::create([=]()
				{
					// Normal scroll animation
					if (!this->hasAnyPinFailed)
					{
						this->woodGearTop->runAction(RotateBy::create(0.5f, 180.0f));
						this->steelGear->runAction(RotateBy::create(0.5f, -180.0f));
						this->woodGearBottom->runAction(RotateBy::create(0.5f, 180.0f));
						
						this->shaft->runAction(Sequence::create(
							MoveBy::create(0.5f, Vec2(0.0f, CipherLock::PinSpacing)),
							nullptr
						));

						this->cipherPinsNode->runAction(Sequence::create(
							MoveBy::create(0.5f, Vec2(0.0f, CipherLock::PinSpacing)),
							nullptr
						));
					}
					// Failure stall animation
					else
					{
						this->woodGearTop->runAction(Sequence::create(
							RotateBy::create(0.15f, 10.0f),
							RotateBy::create(0.15f, -10.0f),
							RotateBy::create(0.15f, 10.0f),
							RotateBy::create(0.15f, -10.0f),
							nullptr
						));
						this->steelGear->runAction(Sequence::create(
							RotateBy::create(0.15f, 10.0f),
							RotateBy::create(0.15f, -10.0f),
							RotateBy::create(0.15f, 10.0f),
							RotateBy::create(0.15f, -10.0f),
							nullptr
						));
						this->woodGearBottom->runAction(Sequence::create(
							RotateBy::create(0.15f, 10.0f),
							RotateBy::create(0.15f, -10.0f),
							RotateBy::create(0.15f, 10.0f),
							RotateBy::create(0.15f, -10.0f),
							nullptr
						));
						this->shaft->runAction(Sequence::create(
							MoveBy::create(0.15f, Vec2(0.0f, 10.0f)),
							MoveBy::create(0.15f, Vec2(0.0f, -10.0f)),
							MoveBy::create(0.15f, Vec2(0.0f, 10.0f)),
							MoveBy::create(0.15f, Vec2(0.0f, -10.0f)),
							nullptr
						));
						cipherPinsNode->runAction(Sequence::create(
							MoveBy::create(0.15f, Vec2(0.0f, 10.0f)),
							MoveBy::create(0.15f, Vec2(0.0f, -10.0f)),
							MoveBy::create(0.15f, Vec2(0.0f, 10.0f)),
							MoveBy::create(0.15f, Vec2(0.0f, -10.0f)),
							nullptr
						));
						/*
						pinhole->runAction(Sequence::create(
							MoveBy::create(0.15f, Vec2(0.0f, 10.0f)),
							MoveBy::create(0.15f, Vec2(0.0f, -10.0f)),
							MoveBy::create(0.15f, Vec2(0.0f, 10.0f)),
							MoveBy::create(0.15f, Vec2(0.0f, -10.0f)),
							nullptr
						));*/
					}
				});

				if (args->success)
				{
					pin->runAction(Sequence::create(
						MoveBy::create(0.5f, Vec2(-CipherLock::PinUnlockDistance, 0.0f)),
						scrollFunc,
						DelayTime::create(0.5f),
						CallFunc::create(args->callback),
						nullptr
					));
				}
				else
				{
					pin->runAction(Sequence::create(
						scrollFunc,
						DelayTime::create(0.5f),
						CallFunc::create(args->callback),
						nullptr
					));
				}
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
			this->cipherPinholes.clear();
			this->cipherPins.clear();
			this->cipherPinsNode->removeAllChildren();

			for (auto it = cipherState->inputOutputMap.begin(); it != cipherState->inputOutputMap.end(); it++)
			{
				Sprite* pinhole = Sprite::create(CipherResources::Lock_Pinhole);
				Sprite* pin = Sprite::create(CipherResources::Lock_Pin);

				this->cipherPinholes.push_back(pinhole);
				this->cipherPins.push_back(pin);
				this->cipherPinsNode->addChild(pinhole);
				this->cipherPinsNode->addChild(pin);
			}
			
			this->initializePositions();
			break;
		}
		case CipherState::StateType::Neutral:
		{
			this->hasAnyPinFailed = false;
			break;
		}
		default:
		{
			break;
		}
	}
}
