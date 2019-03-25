#include "GreaterThanOrEqualsBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

#include "Strings/Cipher/Operations/SHR.h"

using namespace cocos2d;

GreaterThanOrEqualsBlock* GreaterThanOrEqualsBlock::create(BlockType blockType)
{
	GreaterThanOrEqualsBlock* instance = new GreaterThanOrEqualsBlock(blockType);

	instance->autorelease();

	return instance;
}

GreaterThanOrEqualsBlock::GreaterThanOrEqualsBlock(BlockType blockType) : super(blockType, CipherResources::Icons_GreaterThanOrEquals, Strings::Cipher_Operations_SHR::create())
{
}

GreaterThanOrEqualsBlock::~GreaterThanOrEqualsBlock()
{
}

unsigned char GreaterThanOrEqualsBlock::compute()
{
	if (this->currentInputs.size() < 1)
	{
		return (unsigned char)(0);
	}

	return this->currentInputs[0];
}

BlockBase* GreaterThanOrEqualsBlock::spawn()
{
	return GreaterThanOrEqualsBlock::create();
}

bool GreaterThanOrEqualsBlock::compare(unsigned char inputA, unsigned char inputB)
{
	return inputA >= inputB;
}
