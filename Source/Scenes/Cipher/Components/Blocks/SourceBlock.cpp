#include "SourceBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
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
	this->displayValue = ConstantString::create();
	this->displayLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, this->displayValue);

	this->displayLabel->setTextColor(Color4B::WHITE);
	this->displayLabel->enableOutline(Color4B::BLACK, 2);

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
}

void SourceBlock::loadDisplayValue(std::string input)
{
	char character = input[this->cipherIndex];
	
	this->displayValue->setString(std::string(1, character));
}

BlockBase* SourceBlock::spawn()
{
	return SourceBlock::create(this->cipherIndex);
}
