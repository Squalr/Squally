#include "ImmediateBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/InputText.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/HackUtils.h"
#include "Events/CipherEvents.h"
#include "Scenes/Cipher/Components/Blocks/Connections/InputBolt.h"
#include "Scenes/Cipher/Components/Blocks/Connections/OutputBolt.h"
#include "Scenes/Cipher/Components/Letters/SmartAsciiLabel.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

#include "Strings/Cipher/Operations/Immediate.h"

using namespace cocos2d;

ImmediateBlock* ImmediateBlock::create(BlockType blockType)
{
	ImmediateBlock* instance = new ImmediateBlock(blockType);

	instance->autorelease();

	return instance;
}

ImmediateBlock::ImmediateBlock(BlockType blockType) : super(blockType, ConnectionType::None, ConnectionType::Single, ClickableNode::create(CipherResources::Blocks_BlockDecLong, CipherResources::Blocks_BlockDecLong), CipherResources::Icons_Immediate, Strings::Cipher_Operations_Immediate::create())
{
	this->displayDataType = CipherEvents::DisplayDataType::Ascii;
	this->spriteAscii = Sprite::create(CipherResources::Blocks_BlockAsciiLong);
	this->spriteBin = Sprite::create(CipherResources::Blocks_BlockBinLong);
	this->spriteDec = Sprite::create(CipherResources::Blocks_BlockDecLong);
	this->spriteHex = Sprite::create(CipherResources::Blocks_BlockHexLong);
	this->spriteAsciiSelected = Sprite::create(CipherResources::Blocks_BlockAsciiLong);
	this->spriteBinSelected = Sprite::create(CipherResources::Blocks_BlockBinLong);
	this->spriteDecSelected = Sprite::create(CipherResources::Blocks_BlockDecLong);
	this->spriteHexSelected = Sprite::create(CipherResources::Blocks_BlockHexLong);
	this->displayLabel = SmartAsciiLabel::create();
	this->charValue = (unsigned char)(0);

	this->spriteAscii->setAnchorPoint(Vec2::ZERO);
	this->spriteBin->setAnchorPoint(Vec2::ZERO);
	this->spriteDec->setAnchorPoint(Vec2::ZERO);
	this->spriteHex->setAnchorPoint(Vec2::ZERO);
	this->spriteAsciiSelected->setAnchorPoint(Vec2::ZERO);
	this->spriteBinSelected->setAnchorPoint(Vec2::ZERO);
	this->spriteDecSelected->setAnchorPoint(Vec2::ZERO);
	this->spriteHexSelected->setAnchorPoint(Vec2::ZERO);

	this->block->getSprite()->setOpacity(1);
	this->block->getSprite()->setCascadeOpacityEnabled(false);
	this->block->getSpriteSelected()->setOpacity(1);
	this->block->getSpriteSelected()->setCascadeOpacityEnabled(false);
	
	if (this->blockType == BlockBase::BlockType::Static)
	{
		for (auto it = this->inputBolts.begin(); it != this->inputBolts.end(); it++)
		{
			(*it)->setVisible(false);
		}

		for (auto it = this->outputBolts.begin(); it != this->outputBolts.end(); it++)
		{
			(*it)->setVisible(false);
		}
	}

	if (this->blockType == BlockBase::BlockType::Normal || this->blockType == BlockBase::BlockType::Static)
	{
		this->icon->setVisible(false);
	}

	// Huh? I think we've got a bug where this isn't called on spawned objects, just patch it in
	this->initializePositions();

	this->block->getSprite()->addChild(this->spriteAscii);
	this->block->getSprite()->addChild(this->spriteBin);
	this->block->getSprite()->addChild(this->spriteDec);
	this->block->getSprite()->addChild(this->spriteHex);
	this->block->getSpriteSelected()->addChild(this->spriteAsciiSelected);
	this->block->getSpriteSelected()->addChild(this->spriteBinSelected);
	this->block->getSpriteSelected()->addChild(this->spriteDecSelected);
	this->block->getSpriteSelected()->addChild(this->spriteHexSelected);
	this->addChild(this->displayLabel);
}

ImmediateBlock::~ImmediateBlock()
{
}

void ImmediateBlock::onEnter()
{
	super::onEnter();
}

void ImmediateBlock::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->displayLabel->setPositionY(4.0f);
}

void ImmediateBlock::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(CipherEvents::EventChangeDisplayDataType, [&](EventCustom* eventCustom)
	{
		CipherEvents::CipherChangeDisplayDataTypeArgs* args = static_cast<CipherEvents::CipherChangeDisplayDataTypeArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->displayDataType = args->displayDataType;

			this->loadDisplayValue();
		}
	}));

	if (this->blockType != BlockBase::BlockType::Static)
	{
		this->block->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
		{
			CipherEvents::TriggerOpenAsciiTable(CipherEvents::CipherOpenAsciiTableArgs(this));
		});
	}
}

void ImmediateBlock::setValue(unsigned char value)
{
	this->charValue = value;

	this->loadDisplayValue();
}

unsigned char ImmediateBlock::getValue()
{
	return this->charValue;
}

void ImmediateBlock::loadDisplayValue()
{
	this->spriteAscii->setVisible(false);
	this->spriteBin->setVisible(false);
	this->spriteDec->setVisible(false);
	this->spriteHex->setVisible(false);
	this->spriteAsciiSelected->setVisible(false);
	this->spriteBinSelected->setVisible(false);
	this->spriteDecSelected->setVisible(false);
	this->spriteHexSelected->setVisible(false);

	this->displayLabel->loadDisplayValue(this->charValue, this->displayDataType);
	
	switch(this->displayDataType)
	{
		default:
		case CipherEvents::DisplayDataType::Ascii:
		{
			this->spriteAscii->setVisible(true);
			this->spriteAsciiSelected->setVisible(true);
			break;
		}
		case CipherEvents::DisplayDataType::Bin:
		{
			this->spriteBin->setVisible(true);
			this->spriteBinSelected->setVisible(true);
			break;
		}
		case CipherEvents::DisplayDataType::Dec:
		{
			this->spriteDec->setVisible(true);
			this->spriteDecSelected->setVisible(true);
			break;
		}
		case CipherEvents::DisplayDataType::Hex:
		{
			this->spriteHex->setVisible(true);
			this->spriteHexSelected->setVisible(true);
			break;
		}
	}

	if (this->blockType == BlockBase::BlockType::Toolbox)
	{
		this->displayLabel->setVisible(false);
	}
}

unsigned char ImmediateBlock::compute()
{
	return this->charValue;
}

BlockBase* ImmediateBlock::spawn()
{
	ImmediateBlock* spawn = ImmediateBlock::create(BlockType::Normal);

	spawn->displayDataType = this->displayDataType;
	spawn->loadDisplayValue();

	return spawn;
}
