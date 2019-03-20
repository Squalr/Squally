#include "ImmediateBlock.h"

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

#include "Strings/Cipher/Operations/Immediate.h"

using namespace cocos2d;

ImmediateBlock* ImmediateBlock::create(BlockType blockType)
{
	ImmediateBlock* instance = new ImmediateBlock(blockType);

	instance->autorelease();

	return instance;
}

ImmediateBlock::ImmediateBlock(BlockType blockType) : super(blockType, ConnectionType::None, ConnectionType::Single, ClickableNode::create(CipherResources::Blocks_BlockAscii, CipherResources::Blocks_BlockAscii), CipherResources::Icons_Immediate, Strings::Cipher_Operations_Immediate::create())
{
	this->displayValue = ConstantString::create();
	this->displayLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, this->displayValue);

	this->displayLabel->enableOutline(Color4B::BLACK, 2);

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

	this->addEventListenerIgnorePause(EventListenerCustom::create(CipherEvents::EventChangeActiveCipher, [=](EventCustom* eventCustom)
	{
		CipherEvents::CipherChangeActiveCipherArgs* args = static_cast<CipherEvents::CipherChangeActiveCipherArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
		}
	}));
}

BlockBase* ImmediateBlock::spawn()
{
	return ImmediateBlock::create(BlockType::Normal);
}
