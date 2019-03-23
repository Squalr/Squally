#include "SplitterBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

#include "Strings/Cipher/Operations/SHR.h"

using namespace cocos2d;

SplitterBlock* SplitterBlock::create(BlockType blockType)
{
	SplitterBlock* instance = new SplitterBlock(blockType);

	instance->autorelease();

	return instance;
}

SplitterBlock::SplitterBlock(BlockType blockType) : super(blockType, ConnectionType::Single, ConnectionType::Double, ClickableNode::create(CipherResources::Blocks_BlockBin, CipherResources::Blocks_BlockBin), CipherResources::Icons_Splitter, Strings::Cipher_Operations_SHR::create())
{
}

SplitterBlock::~SplitterBlock()
{
}

void SplitterBlock::onEnter()
{
	super::onEnter();
}

void SplitterBlock::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

char SplitterBlock::compute()
{
	if (this->currentInputs.size() < 1)
	{
		return char(0);
	}

	return this->currentInputs[0];
}

BlockBase* SplitterBlock::spawn()
{
	return SplitterBlock::create();
}
