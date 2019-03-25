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
	this->displayValue = ConstantString::create();
	this->displayLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, this->displayValue);
	this->spriteAscii = Sprite::create(CipherResources::Blocks_BlockAsciiLong);
	this->spriteBin = Sprite::create(CipherResources::Blocks_BlockBinLong);
	this->spriteDec = Sprite::create(CipherResources::Blocks_BlockDecLong);
	this->spriteHex = Sprite::create(CipherResources::Blocks_BlockHexLong);
	this->spriteAsciiSelected = Sprite::create(CipherResources::Blocks_BlockAsciiLong);
	this->spriteBinSelected = Sprite::create(CipherResources::Blocks_BlockBinLong);
	this->spriteDecSelected = Sprite::create(CipherResources::Blocks_BlockDecLong);
	this->spriteHexSelected = Sprite::create(CipherResources::Blocks_BlockHexLong);

	this->spriteAscii->setAnchorPoint(Vec2::ZERO);
	this->spriteBin->setAnchorPoint(Vec2::ZERO);
	this->spriteDec->setAnchorPoint(Vec2::ZERO);
	this->spriteHex->setAnchorPoint(Vec2::ZERO);
	this->spriteAsciiSelected->setAnchorPoint(Vec2::ZERO);
	this->spriteBinSelected->setAnchorPoint(Vec2::ZERO);
	this->spriteDecSelected->setAnchorPoint(Vec2::ZERO);
	this->spriteHexSelected->setAnchorPoint(Vec2::ZERO);
	this->displayLabel->enableOutline(Color4B::BLACK, 2);

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
		this->block->setClickCallback([=](MouseEvents::MouseEventArgs*)
		{
			CipherEvents::TriggerOpenImmediateEditor(CipherEvents::CipherEditImmediateArgs(this));
		});
	}
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
	
	switch(this->displayDataType)
	{
		default:
		case CipherEvents::DisplayDataType::Ascii:
		{
			this->displayValue->setString(std::string(1, this->charValue));
			this->spriteAscii->setVisible(true);
			this->spriteAsciiSelected->setVisible(true);
			break;
		}
		case CipherEvents::DisplayDataType::Bin:
		{
			this->displayValue->setString(HackUtils::toBinary8(int(this->charValue)));
			this->spriteBin->setVisible(true);
			this->spriteBinSelected->setVisible(true);
			break;
		}
		case CipherEvents::DisplayDataType::Dec:
		{
			this->displayValue->setString(std::to_string(int(this->charValue)));
			this->spriteDec->setVisible(true);
			this->spriteDecSelected->setVisible(true);
			break;
		}
		case CipherEvents::DisplayDataType::Hex:
		{
			this->displayValue->setString(HackUtils::toHex(int(this->charValue)));
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

char ImmediateBlock::compute()
{
	return this->charValue;
}

BlockBase* ImmediateBlock::spawn()
{
	ImmediateBlock* spawm = ImmediateBlock::create(BlockType::Normal);

	spawm->displayDataType = this->displayDataType;
	spawm->loadDisplayValue();

	return spawm;
}
