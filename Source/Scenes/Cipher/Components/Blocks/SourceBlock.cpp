#include "SourceBlock.h"

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
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"
#include "Resources/UIResources.h"

#include "Strings/Cipher/Operations/Immediate.h"

using namespace cocos2d;

SourceBlock* SourceBlock::create(int cipherIndex)
{
	SourceBlock* instance = new SourceBlock(cipherIndex);

	instance->autorelease();

	return instance;
}

SourceBlock::SourceBlock(int cipherIndex) : super(BlockType::Static, ConnectionType::None, ConnectionType::Single, ClickableNode::create(CipherResources::Blocks_BlockDecLong, CipherResources::Blocks_BlockDecLong), UIResources::EmptyImage, Strings::Cipher_Operations_Immediate::create())
{
	this->cipherIndex = cipherIndex;
	this->input = "";
	this->displayDataType = CipherEvents::DisplayDataType::Ascii;
	this->displayValue = ConstantString::create();
	this->displayLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, this->displayValue);
	this->spriteAscii = Sprite::create(CipherResources::Blocks_BlockAsciiLong);
	this->spriteBin = Sprite::create(CipherResources::Blocks_BlockBinLong);
	this->spriteDec = Sprite::create(CipherResources::Blocks_BlockDecLong);
	this->spriteHex = Sprite::create(CipherResources::Blocks_BlockHexLong);

	this->spriteAscii->setAnchorPoint(Vec2::ZERO);
	this->spriteBin->setAnchorPoint(Vec2::ZERO);
	this->spriteDec->setAnchorPoint(Vec2::ZERO);
	this->spriteHex->setAnchorPoint(Vec2::ZERO);

	this->displayLabel->setTextColor(Color4B::WHITE);
	this->displayLabel->enableOutline(Color4B::BLACK, 2);
	this->block->getSprite()->setOpacity(1);
	this->block->getSprite()->setCascadeOpacityEnabled(false);
	this->block->getSpriteSelected()->setOpacity(1);
	this->block->getSpriteSelected()->setCascadeOpacityEnabled(false);

	this->block->getSprite()->addChild(this->spriteAscii);
	this->block->getSprite()->addChild(this->spriteBin);
	this->block->getSprite()->addChild(this->spriteDec);
	this->block->getSprite()->addChild(this->spriteHex);
	this->addChild(this->displayLabel);
}

SourceBlock::~SourceBlock()
{
}

void SourceBlock::onEnter()
{
	super::onEnter();
}

void SourceBlock::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->displayLabel->setPositionY(4.0f);
}

void SourceBlock::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(CipherEvents::EventChangeActiveCipher, [=](EventCustom* eventCustom)
	{
		CipherEvents::CipherChangeActiveCipherArgs* args = static_cast<CipherEvents::CipherChangeActiveCipherArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->loadDisplayValue(args->input);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CipherEvents::EventChangeDisplayDataType, [=](EventCustom* eventCustom)
	{
		CipherEvents::CipherChangeDisplayDataTypeArgs* args = static_cast<CipherEvents::CipherChangeDisplayDataTypeArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->displayDataType = args->displayDataType;

			this->loadDisplayValue(this->input);
		}
	}));
}

void SourceBlock::loadDisplayValue(std::string input)
{
	this->input = input;
	char character = this->input[this->cipherIndex];
	this->spriteAscii->setVisible(false);
	this->spriteBin->setVisible(false);
	this->spriteDec->setVisible(false);
	this->spriteHex->setVisible(false);
	
	switch(this->displayDataType)
	{
		default:
		case CipherEvents::DisplayDataType::Ascii:
		{
			this->displayValue->setString(std::string(1, character));
			this->spriteAscii->setVisible(true);
			break;
		}
		case CipherEvents::DisplayDataType::Bin:
		{
			this->displayValue->setString(HackUtils::toBinary8(int(character)));
			this->spriteBin->setVisible(true);
			break;
		}
		case CipherEvents::DisplayDataType::Dec:
		{
			this->displayValue->setString(std::to_string(int(character)));
			this->spriteDec->setVisible(true);
			break;
		}
		case CipherEvents::DisplayDataType::Hex:
		{
			this->displayValue->setString(HackUtils::toHex(int(character)));
			this->spriteHex->setVisible(true);
			break;
		}
	}
}

BlockBase* SourceBlock::spawn()
{
	return SourceBlock::create(this->cipherIndex);
}
