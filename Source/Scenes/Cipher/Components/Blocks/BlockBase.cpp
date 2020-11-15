#include "BlockBase.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/InputEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/CipherEvents.h"
#include "Scenes/Cipher/CipherConfig.h"
#include "Scenes/Cipher/CipherState.h"
#include "Scenes/Cipher/Components/Blocks/Connections/InputBolt.h"
#include "Scenes/Cipher/Components/Blocks/Connections/OutputBolt.h"

#include "Resources/CipherResources.h"

using namespace cocos2d;

BlockBase::BlockBase(BlockType blockType, ConnectionType inputType, ConnectionType outputType, ClickableNode* block, std::string iconResource, LocalizedString* label)
{
	this->block = block;
	this->icon = Sprite::create(iconResource);
	this->label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, label);
	this->blockType = blockType;
	this->inputType = inputType;
	this->outputType = outputType;
	this->spawnPosition = Vec2::ZERO;
	this->originalPosition = Vec2::ZERO;
	this->clickDelta = Vec2::ZERO;
	this->inputBoltLeft = nullptr;
	this->inputBoltRight = nullptr;
	this->outputBoltLeft = nullptr;
	this->outputBoltRight = nullptr;
	this->inputLeft = 0;
	this->inputRight = 0;
	this->spawningBlock = nullptr;
	this->receivedInputs = 0;

	this->label->enableOutline(Color4B::BLACK, 2);
	this->label->setOpacity(0);

	if (this->inputType == ConnectionType::Single)
	{
		this->inputBoltLeft = InputBolt::create(this, 0);
	}
	else if (this->inputType == ConnectionType::Double)
	{
		this->inputBoltLeft = InputBolt::create(this, 0);
		this->inputBoltRight = InputBolt::create(this, 1);
	}

	if (this->outputType == ConnectionType::Single)
	{
		this->outputBoltLeft = OutputBolt::create();
	}
	else if (this->outputType == ConnectionType::Double)
	{
		this->outputBoltLeft = OutputBolt::create();
		this->outputBoltRight = OutputBolt::create();
	}

	if (this->inputBoltLeft != nullptr)
	{
		this->addChild(this->inputBoltLeft);
	}

	if (this->inputBoltRight != nullptr)
	{
		this->addChild(this->inputBoltRight);
	}

	this->addChild(this->block);
	this->addChild(this->icon);

	if (this->outputBoltLeft != nullptr)
	{
		this->addChild(this->outputBoltLeft);
	}

	if (this->outputBoltRight != nullptr)
	{
		this->addChild(this->outputBoltRight);
	}

	this->addChild(this->label);
}

BlockBase::~BlockBase()
{
}

void BlockBase::initializePositions()
{
	super::initializePositions();

	if (this->inputType == ConnectionType::Single)
	{
		this->inputBoltLeft->setPosition(Vec2(0.0f, this->getBoltOffsetY()));
	}
	else if (this->inputType == ConnectionType::Double)
	{
		this->inputBoltLeft->setPosition(Vec2(-16.0f, this->getBoltOffsetY()));
		this->inputBoltRight->setPosition(Vec2(16.0f, this->getBoltOffsetY()));
	}

	this->icon->setPosition(Vec2(0.0f, 4.0f));

	if (this->outputType == ConnectionType::Single)
	{
		this->outputBoltLeft->setPosition(Vec2(0.0f, -this->getBoltOffsetY()));
	}
	else if (this->outputType == ConnectionType::Double)
	{
		this->outputBoltLeft->setPosition(Vec2(-16.0f, -this->getBoltOffsetY()));
		this->outputBoltRight->setPosition(Vec2(16.0f, -this->getBoltOffsetY()));
	}
	
	this->label->setPosition(Vec2(0.0f, 48.0f));
}

void BlockBase::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(CipherEvents::EventExitCipher, [=](EventCustom* eventCustom)
	{
		this->removeConnections();
	}));

	switch (this->blockType)
	{
		default:
		case BlockType::Static:
		{
			this->block->disableInteraction();
			break;
		}
		case BlockType::Normal:
		{
			this->block->setMousePressCallback([=](MouseEventArgs* args)
			{
				this->originalPosition = this->getPosition();
				this->clickDelta = this->originalPosition - args->mouseCoords;
			});

			this->block->setMouseReleaseNoHitTestCallback([=](MouseEventArgs* args)
			{
				if (!this->isInGameArea())
				{
					this->setPosition(this->originalPosition);
				}
			});

			this->block->setMouseDragCallback([=](MouseEventArgs* args)
			{
				this->setPosition(args->mouseCoords + this->clickDelta);
			});
			break;
		}
	}
}

ClickableNode* BlockBase::getBlock()
{
	return this->block;
}

void BlockBase::onAnyStateChange(CipherState* cipherState)
{
	switch(cipherState->stateType)
	{
		case CipherState::StateType::Neutral:
		{
			if (this->blockType == BlockType::Normal)
			{
				this->block->enableInteraction();
			}
			break;
		}
		case CipherState::StateType::Testing:
		case CipherState::StateType::Unlocking:
		{
			this->block->disableInteraction();
			this->inputLeft = 0;
			this->inputRight = 0;
			this->receivedInputs = 0;
			break;
		}
		default:
		{
			this->block->disableInteraction();
			break;
		}
	}
}

bool BlockBase::isInGameArea()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 center = Vec2(visibleSize.width / 2.0f + CipherConfig::LeftColumnCenter, visibleSize.height / 2.0f);
	Vec2 thisPosition = GameUtils::getScreenBounds(this).origin;

	if (thisPosition.x > center.x - CipherConfig::GameAreaWidth / 2.0f &&
		thisPosition.x < center.x + CipherConfig::GameAreaWidth / 2.0f &&
		thisPosition.y > center.y - CipherConfig::GameAreaHeight / 2.0f &&
		thisPosition.y < center.y + CipherConfig::GameAreaHeight / 2.0f)
	{
		return true;
	}

	return false;
}

void BlockBase::setSpawnPosition(cocos2d::Vec2 spawnPosition)
{
	this->spawnPosition = spawnPosition;
}

void BlockBase::setInput(unsigned char input, int inputIndex)
{
	switch(inputIndex)
	{
		default:
		case 0:
		{
			this->inputLeft = input;
			break;
		}
		case 1:
		{
			this->inputRight = input;
			break;
		}
	}

	this->receivedInputs++;
}

void BlockBase::execute(std::function<void()> onExecuteComplete)
{
	this->receivedValue = this->compute();

	// Only perform execution when the total input count has been reached
	if ((this->inputType == BlockBase::ConnectionType::None) || 
		(this->receivedInputs == 1 && this->inputType == BlockBase::ConnectionType::Single) || 
		(this->receivedInputs == 2 && this->inputType == BlockBase::ConnectionType::Double))
	{
		switch(this->outputType)
		{
			case BlockBase::ConnectionType::Single:
			{
				this->outputBoltLeft->execute(this->receivedValue, onExecuteComplete);
				break;
			}
			case BlockBase::ConnectionType::Double:
			{
				this->outputBoltLeft->execute(this->receivedValue, onExecuteComplete);
				this->outputBoltRight->execute(this->receivedValue, onExecuteComplete);
				break;
			}
			default:
			{
				onExecuteComplete();
				break;
			}
		}
	}
	else
	{
		onExecuteComplete();
	}
}

void BlockBase::removeConnections()
{
	if (this->inputBoltLeft != nullptr)
	{
		CipherEvents::TriggerDestroyConnectionToInput(this->inputBoltLeft);
		this->inputBoltLeft->setConnection(nullptr);
	}
	
	if (this->inputBoltRight != nullptr)
	{
		CipherEvents::TriggerDestroyConnectionToInput(this->inputBoltRight);
		this->inputBoltRight->setConnection(nullptr);
	}
	if (this->outputBoltLeft != nullptr)
	{
		this->outputBoltLeft->setConnection(nullptr);
	}
	
	if (this->outputBoltRight != nullptr)
	{
		this->outputBoltRight->setConnection(nullptr);
	}
}

float BlockBase::getBoltOffsetY()
{
	return 32.0f;
}