#include "ToolBox.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Scenes/Cipher/Config.h"
#include "Scenes/Cipher/Components/Blocks/BlockBase.h"
#include "Scenes/Cipher/Components/Blocks/Blocks.h"
#include "Scenes/Cipher/CipherState.h"

#include "Resources/CipherResources.h"
#include "Resources/UIResources.h"

#include "Strings/Cipher/BasicOperators.h"
#include "Strings/Cipher/BinaryOperators.h"
#include "Strings/Cipher/Comparisons.h"
#include "Strings/Cipher/Special.h"
#include "Strings/Cipher/Tools.h"

using namespace cocos2d;

ToolBox* ToolBox::create()
{
	ToolBox* instance = new ToolBox();

	instance->autorelease();

	return instance;
}

ToolBox::ToolBox()
{
	this->cipherToolsLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Cipher_Tools::create());
	this->addBlock = AddBlock::create(BlockBase::BlockType::Toolbox);
	this->andBlock = AndBlock::create(BlockBase::BlockType::Toolbox);
	this->bruteForceBlock = BruteForceBlock::create(BlockBase::BlockType::Toolbox);
	this->cshlBlock = CshlBlock::create(BlockBase::BlockType::Toolbox);
	this->cshrBlock = CshrBlock::create(BlockBase::BlockType::Toolbox);
	this->divBlock = DivBlock::create(BlockBase::BlockType::Toolbox);
	this->equalsBlock = EqualsBlock::create(BlockBase::BlockType::Toolbox);
	this->greaterThanBlock = GreaterThanBlock::create(BlockBase::BlockType::Toolbox);
	this->greaterThanOrEqualsBlock = GreaterThanOrEqualsBlock::create(BlockBase::BlockType::Toolbox);
	this->immediateBlock = ImmediateBlock::create(BlockBase::BlockType::Toolbox);
	this->invBlock = InvBlock::create(BlockBase::BlockType::Toolbox);
	this->lessThanBlock = LessThanBlock::create(BlockBase::BlockType::Toolbox);
	this->lessThanOrEqualsBlock = LessThanOrEqualsBlock::create(BlockBase::BlockType::Toolbox);
	this->modBlock = ModBlock::create(BlockBase::BlockType::Toolbox);
	this->mulBlock = MulBlock::create(BlockBase::BlockType::Toolbox);
	this->notEqualsBlock = NotEqualsBlock::create(BlockBase::BlockType::Toolbox);
	this->orBlock = OrBlock::create(BlockBase::BlockType::Toolbox);
	this->shlBlock = ShlBlock::create(BlockBase::BlockType::Toolbox);
	this->shrBlock = ShrBlock::create(BlockBase::BlockType::Toolbox);
	this->splitterBlock = SplitterBlock::create(BlockBase::BlockType::Toolbox);
	this->subBlock = SubBlock::create(BlockBase::BlockType::Toolbox);
	this->xorBlock = XorBlock::create(BlockBase::BlockType::Toolbox);
	this->scrollPane = ScrollPane::create(Size(312.0f, 316.0f - 12.0f * 2.0f), UIResources::Menus_Buttons_SliderButton, UIResources::Menus_Buttons_SliderButtonSelected, Size(0.0f, 32.0f), Size(12.0f, 12.0f));
	this->specialLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Cipher_Special::create());
	this->binaryOperatorsLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Cipher_BinaryOperators::create());
	this->basicOperatorsLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Cipher_BasicOperators::create());
	this->comparisonLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Cipher_Comparisons::create());
	
	this->specialBlocks = std::vector<BlockBase*>(
	{
		this->immediateBlock,
		this->bruteForceBlock,
		this->splitterBlock,
	});

	this->binaryOperatorBlocks = std::vector<BlockBase*>(
	{
		this->andBlock,
		this->orBlock,
		this->xorBlock,
		this->invBlock,

		this->shlBlock,
		this->shrBlock,
		this->cshlBlock,
		this->cshrBlock,
	});

	this->basicOperatorBlocks = std::vector<BlockBase*>(
	{
		this->addBlock,
		this->subBlock,
		this->divBlock,
		this->mulBlock,
		this->modBlock,
	});

	this->comparisonBlocks = std::vector<BlockBase*>(
	{
		this->equalsBlock,
		this->notEqualsBlock,
		
		this->lessThanOrEqualsBlock,
		this->lessThanBlock,
		this->greaterThanBlock,
		this->greaterThanOrEqualsBlock,
	});

	this->cipherToolsLabel->enableShadow(Color4B::BLACK, Size(2, -2), 2);
	this->specialLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->binaryOperatorsLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->basicOperatorsLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->comparisonLabel->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->scrollPane->addChild(this->specialLabel);
	this->scrollPane->addChild(this->basicOperatorsLabel);
	this->scrollPane->addChild(this->binaryOperatorsLabel);
	this->scrollPane->addChild(this->comparisonLabel);

	for (auto it = this->specialBlocks.begin(); it != this->specialBlocks.end(); it++)
	{
		this->scrollPane->addChild(*it);
	}
	
	for (auto it = this->binaryOperatorBlocks.begin(); it != this->binaryOperatorBlocks.end(); it++)
	{
		this->scrollPane->addChild(*it);
	}
	
	for (auto it = this->basicOperatorBlocks.begin(); it != this->basicOperatorBlocks.end(); it++)
	{
		this->scrollPane->addChild(*it);
	}
	
	for (auto it = this->comparisonBlocks.begin(); it != this->comparisonBlocks.end(); it++)
	{
		this->scrollPane->addChild(*it);
	}

	this->addChild(this->scrollPane);
	this->addChild(this->cipherToolsLabel);
}

ToolBox::~ToolBox()
{
}

void ToolBox::onEnter()
{
	super::onEnter();
}

void ToolBox::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->cipherToolsLabel->setPosition(Vec2(visibleSize.width / 2.0f + Config::RightColumnCenter, visibleSize.height / 2.0f + 450.0f));
	this->scrollPane->setPosition(Vec2(visibleSize.width / 2.0f + Config::RightColumnCenter, visibleSize.height / 2.0f +  232.0f));

	this->specialLabel->setPosition(Vec2(-this->scrollPane->getPaneSize().width / 2.0f + 16.0f, 0.0f));
	int index = 0;

	for (auto it = this->specialBlocks.begin(); it != this->specialBlocks.end(); it++, index++)
	{
		int x = index % 4;
		int y = index / 4;

		float offset = (index <= 0 ? 0.5f : 1.0f);

		(*it)->setPosition(Vec2(12.0f + (float(x) - 1.5f + offset) * 76.0f, -56.0f - float(y) * 72.0f));
	}

	this->basicOperatorsLabel->setPosition(Vec2(-this->scrollPane->getPaneSize().width / 2.0f + 16.0f, -128.0f));
	index = 0;

	for (auto it = this->basicOperatorBlocks.begin(); it != this->basicOperatorBlocks.end(); it++, index++)
	{
		int x = (index >= 2 ? index + 2 : index) % 4;
		int y = (index >= 2 ? index + 2 : index) / 4;

		(*it)->setPosition(Vec2(12.0f + (float(x) - 1.5f) * 76.0f, -128.0f - 56.0f - float(y) * 72.0f));
	}

	this->binaryOperatorsLabel->setPosition(Vec2(-this->scrollPane->getPaneSize().width / 2.0f + 16.0f, -328.0f));
	index = 0;

	for (auto it = this->binaryOperatorBlocks.begin(); it != this->binaryOperatorBlocks.end(); it++, index++)
	{
		int x = index % 4;
		int y = index / 4;

		(*it)->setPosition(Vec2(12.0f + (float(x) - 1.5f) * 76.0f, -328.0f - 56.0f - float(y) * 72.0f));
	}

	this->comparisonLabel->setPosition(Vec2(-this->scrollPane->getPaneSize().width / 2.0f + 16.0f, -512.0f));
	index = 0;

	for (auto it = this->comparisonBlocks.begin(); it != this->comparisonBlocks.end(); it++, index++)
	{
		int x = (index >= 2 ? index + 2 : index) % 4;
		int y = (index >= 2 ? index + 2 : index) / 4;

		(*it)->setPosition(Vec2(12.0f + (float(x) - 1.5f) * 76.0f, -512.0f - 56.0f - float(y) * 72.0f));
	}
}

void ToolBox::onBeforeStateChange(CipherState* cipherState)
{
	super::onBeforeStateChange(cipherState);
}

void ToolBox::onAnyStateChange(CipherState* cipherState)
{
	super::onAnyStateChange(cipherState);

	switch(cipherState->stateType)
	{
		case CipherState::StateType::Testing:
		case CipherState::StateType::Unlocking:
		{
			this->setVisible(false);
			break;
		}
		default:
		{
			this->setVisible(true);
			break;
		}
	}
}
