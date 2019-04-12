#include "DestinationBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/HackUtils.h"
#include "Events/CipherEvents.h"
#include "Scenes/Cipher/CipherState.h"
#include "Scenes/Cipher/Components/Letters/SmartAsciiLabel.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"
#include "Resources/UIResources.h"

#include "Strings/Cipher/Operations/Immediate.h"

using namespace cocos2d;

DestinationBlock* DestinationBlock::create(int cipherIndex)
{
	DestinationBlock* instance = new DestinationBlock(cipherIndex);

	instance->autorelease();

	return instance;
}

DestinationBlock::DestinationBlock(int cipherIndex) : super(BlockType::Static, ConnectionType::Single, ConnectionType::None, ClickableNode::create(CipherResources::Blocks_BlockDecHuge, CipherResources::Blocks_BlockDecHuge), UIResources::EmptyImage, Strings::Cipher_Operations_Immediate::create())
{
	this->cipherIndex = cipherIndex;
	this->receivedValue = char(0);
	this->charValue = char(0);
	this->displayDataType = CipherEvents::DisplayDataType::Ascii;
	this->displayLabel = SmartAsciiLabel::create();
	this->receivedDisplayLabel = SmartAsciiLabel::create();
	this->spriteAscii = Sprite::create(CipherResources::Blocks_BlockAsciiHuge);
	this->spriteBin = Sprite::create(CipherResources::Blocks_BlockBinHuge);
	this->spriteDec = Sprite::create(CipherResources::Blocks_BlockDecHuge);
	this->spriteHex = Sprite::create(CipherResources::Blocks_BlockHexHuge);

	this->spriteAscii->setAnchorPoint(Vec2::ZERO);
	this->spriteBin->setAnchorPoint(Vec2::ZERO);
	this->spriteDec->setAnchorPoint(Vec2::ZERO);
	this->spriteHex->setAnchorPoint(Vec2::ZERO);

	this->block->getSprite()->setOpacity(1);
	this->block->getSprite()->setCascadeOpacityEnabled(false);
	this->block->getSpriteSelected()->setOpacity(1);
	this->block->getSpriteSelected()->setCascadeOpacityEnabled(false);

	this->block->getSprite()->addChild(this->spriteAscii);
	this->block->getSprite()->addChild(this->spriteBin);
	this->block->getSprite()->addChild(this->spriteDec);
	this->block->getSprite()->addChild(this->spriteHex);
	this->addChild(this->displayLabel);
	this->addChild(this->receivedDisplayLabel);
}

DestinationBlock::~DestinationBlock()
{
}

void DestinationBlock::onEnter()
{
	super::onEnter();
}

void DestinationBlock::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->receivedDisplayLabel->setPositionY(4.0f + 20.0f);
	this->displayLabel->setPositionY(4.0f - 20.0f);
}

void DestinationBlock::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(CipherEvents::EventChangeActiveCipher, [&](EventCustom* eventCustom)
	{
		CipherEvents::CipherChangeActiveCipherArgs* args = static_cast<CipherEvents::CipherChangeActiveCipherArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->charValue = this->cipherIndex < args->output.size() ? args->output[this->cipherIndex] : char(0);
			
			this->loadDisplayValue();
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CipherEvents::EventChangeDisplayDataType, [&](EventCustom* eventCustom)
	{
		CipherEvents::CipherChangeDisplayDataTypeArgs* args = static_cast<CipherEvents::CipherChangeDisplayDataTypeArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->displayDataType = args->displayDataType;

			this->loadDisplayValue();
		}
	}));
}

unsigned char DestinationBlock::getValue()
{
	return this->charValue;
}

bool DestinationBlock::isMatchedValues()
{
	return this->receivedValue == this->charValue;
}

void DestinationBlock::loadDisplayValue()
{
	this->spriteAscii->setVisible(false);
	this->spriteBin->setVisible(false);
	this->spriteDec->setVisible(false);
	this->spriteHex->setVisible(false);

	this->displayLabel->loadDisplayValue(this->charValue, this->displayDataType);
	this->receivedDisplayLabel->loadDisplayValue(this->receivedValue, this->displayDataType, SmartAsciiLabel::Contrast(this->charValue));
	
	switch(this->displayDataType)
	{
		default:
		case CipherEvents::DisplayDataType::Ascii:
		{
			this->spriteAscii->setVisible(true);
			break;
		}
		case CipherEvents::DisplayDataType::Bin:
		{
			this->spriteBin->setVisible(true);
			break;
		}
		case CipherEvents::DisplayDataType::Dec:
		{
			this->spriteDec->setVisible(true);
			break;
		}
		case CipherEvents::DisplayDataType::Hex:
		{
			this->spriteHex->setVisible(true);
			break;
		}
	}
}

float DestinationBlock::getBoltOffsetY()
{
	return 48.0f;
}

void DestinationBlock::onBeforeStateChange(CipherState* cipherState)
{
	super::onBeforeStateChange(cipherState);

	switch(cipherState->stateType)
	{
		case CipherState::StateType::Testing:
		case CipherState::StateType::Unlocking:
		{
			this->receivedValue = (unsigned char)(0);
			this->loadDisplayValue();
			break;
		}
		default:
		{
			break;
		}
	}
}

void DestinationBlock::execute(std::function<void()> onExecuteComplete)
{
	super::execute(onExecuteComplete);

	this->loadDisplayValue();
}

unsigned char DestinationBlock::compute()
{
	if (this->currentInputs.size() < 1)
	{
		return (unsigned char)(0);
	}

	return this->currentInputs[0];
}

BlockBase* DestinationBlock::spawn()
{
	DestinationBlock* spawn = DestinationBlock::create(this->cipherIndex);

	return spawn;
}
