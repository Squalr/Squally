#include "BlockBase.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/MouseEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/CipherEvents.h"
#include "Scenes/Cipher/CipherState.h"
#include "Scenes/Cipher/Components/Blocks/Connections/InputBolt.h"
#include "Scenes/Cipher/Components/Blocks/Connections/OutputBolt.h"
#include "Scenes/Cipher/Config.h"

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
	this->originalPosition = Vec2::ZERO;
	this->clickDelta = Vec2::ZERO;
	this->inputBolts = std::vector<InputBolt*>();
	this->outputBolts = std::vector<OutputBolt*>();
	this->currentInputs = std::vector<char>();

	this->label->enableOutline(Color4B::BLACK, 2);
	this->label->setOpacity(0);

	if (this->blockType != BlockType::Toolbox && this->inputType == ConnectionType::Single)
	{
		this->inputBolts.push_back(InputBolt::create(this));
	}
	else if (this->blockType != BlockType::Toolbox && this->inputType == ConnectionType::Double)
	{
		this->inputBolts.push_back(InputBolt::create(this));
		this->inputBolts.push_back(InputBolt::create(this));
	}

	if (this->blockType != BlockType::Toolbox && this->outputType == ConnectionType::Single)
	{
		this->outputBolts.push_back(OutputBolt::create());
	}
	else if (this->blockType != BlockType::Toolbox && this->outputType == ConnectionType::Double)
	{
		this->outputBolts.push_back(OutputBolt::create());
		this->outputBolts.push_back(OutputBolt::create());
	}

	for (auto it = this->inputBolts.begin(); it != this->inputBolts.end(); it++)
	{
		this->addChild(*it);
	}

	this->addChild(this->block);
	this->addChild(this->icon);

	for (auto it = this->outputBolts.begin(); it != this->outputBolts.end(); it++)
	{
		this->addChild(*it);
	}

	this->addChild(this->label);
}

BlockBase::~BlockBase()
{
}

void BlockBase::initializePositions()
{
	super::initializePositions();

	if (this->blockType != BlockType::Toolbox && this->inputType == ConnectionType::Single)
	{
		this->inputBolts[0]->setPosition(Vec2(0.0f, 32.0f));
	}
	else if (this->blockType != BlockType::Toolbox && this->inputType == ConnectionType::Double)
	{
		this->inputBolts[0]->setPosition(Vec2(-16.0f, 32.0f));
		this->inputBolts[1]->setPosition(Vec2(16.0f, 32.0f));
	}

	this->icon->setPosition(Vec2(0.0f, 4.0f));

	if (this->blockType != BlockType::Toolbox && this->outputType == ConnectionType::Single)
	{
		this->outputBolts[0]->setPosition(Vec2(0.0f, -32.0f));
	}
	else if (this->blockType != BlockType::Toolbox && this->outputType == ConnectionType::Double)
	{
		this->outputBolts[0]->setPosition(Vec2(-16.0f, -32.0f));
		this->outputBolts[1]->setPosition(Vec2(16.0f, -32.0f));
	}
	
	this->label->setPosition(Vec2(0.0f, 48.0f));
}

void BlockBase::initializeListeners()
{
	super::initializeListeners();

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
			this->block->setMouseReleaseCallback([=](MouseEvents::MouseEventArgs* args)
			{
				if (!this->isInGameArea())
				{
					this->removeConnections();

					// Despawn out-of-bounds nodes
					GameUtils::changeParent(this, nullptr, false);
				}
			});
			break;
		}
		case BlockType::Toolbox:
		{
			this->block->setMouseReleaseCallback([=](MouseEvents::MouseEventArgs* args)
			{
				if (this->isInGameArea())
				{
					CipherEvents::TriggerRequestBlockSpawn(CipherEvents::CipherBlockSpawnArgs([=](){ return this->spawn(); }, args->mouseCoords + this->clickDelta));
				}

				this->setOpacity(0);
				this->label->stopAllActions();
				this->label->setOpacity(0);
				this->runAction(FadeTo::create(0.5f, 255));
				this->setPosition(this->originalPosition);

				MouseEvents::TriggerMouseRefresh(*args);
			});

			this->block->setMouseInCallback([=](MouseEvents::MouseEventArgs* args)
			{
				this->label->stopAllActions();
				this->label->runAction(FadeTo::create(0.25f, 255));
			});

			this->block->setMouseOutCallback([=](MouseEvents::MouseEventArgs* args)
			{
				this->label->stopAllActions();
				this->label->runAction(FadeTo::create(0.25f, 0));
			});
			break;
		}
	}

	switch (this->blockType)
	{
		default:
		case BlockType::Static:
		{
			break;
		}
		case BlockType::Normal:
		case BlockType::Toolbox:
		{
			this->block->setMousePressCallback([=](MouseEvents::MouseEventArgs* args)
			{
				this->originalPosition = this->getPosition();
				this->clickDelta = this->originalPosition - args->mouseCoords;
			});

			this->block->setMouseDragCallback([=](MouseEvents::MouseEventArgs* args)
			{
				this->setPosition(args->mouseCoords + this->clickDelta);
			});
			break;
		}
	}
}

void BlockBase::onBeforeStateChange(CipherState* cipherState)
{
	switch(cipherState->stateType)
	{
		case CipherState::StateType::Running:
		{
			this->currentInputs.clear();
			break;
		}
		default:
		{
			break;
		}
	}
}

bool BlockBase::isInGameArea()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 center = Vec2(visibleSize.width / 2.0f + Config::LeftColumnCenter, visibleSize.height / 2.0f);
	Vec2 thisPosition = this->getPosition();

	if (thisPosition.x > center.x - Config::GameAreaWidth / 2.0f &&
		thisPosition.x < center.x + Config::GameAreaWidth / 2.0f &&
		thisPosition.y > center.y - Config::GameAreaHeight / 2.0f &&
		thisPosition.y < center.y + Config::GameAreaHeight / 2.0f)
	{
		return true;
	}

	return false;
}

void BlockBase::pushInput(char input)
{
	this->currentInputs.push_back(input);
}

void BlockBase::execute(std::function<void()> onExecuteComplete)
{
	// Only perform execution when the total input count has been reached
	if (this->outputBolts.size() > 0 && this->currentInputs.size() == this->inputBolts.size())
	{
		char value = this->compute();

		for (auto it = this->outputBolts.begin(); it != this->outputBolts.end(); it++)
		{
			(*it)->execute(value, onExecuteComplete);
		}
	}
	else
	{
		onExecuteComplete();
	}
}

void BlockBase::removeConnections()
{
}
