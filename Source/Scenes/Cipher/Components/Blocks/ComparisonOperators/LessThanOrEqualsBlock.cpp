#include "LessThanOrEqualsBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

#include "Strings/Cipher/Operations/SHR.h"

using namespace cocos2d;

LessThanOrEqualsBlock* LessThanOrEqualsBlock::create(BlockType blockType)
{
	LessThanOrEqualsBlock* instance = new LessThanOrEqualsBlock(blockType);

	instance->autorelease();

	return instance;
}

LessThanOrEqualsBlock::LessThanOrEqualsBlock(BlockType blockType) : super(blockType, CipherResources::Icons_LessThanOrEquals, Strings::Cipher_Operations_SHR::create())
{
}

LessThanOrEqualsBlock::~LessThanOrEqualsBlock()
{
}

char LessThanOrEqualsBlock::compute()
{
	if (this->currentInputs.size() < 1)
	{
		return char(0);
	}

	return this->currentInputs[0];
}

BlockBase* LessThanOrEqualsBlock::spawn()
{
	return LessThanOrEqualsBlock::create();
}

bool LessThanOrEqualsBlock::compare(char inputA, char inputB)
{
	return inputA <= inputB;
}
