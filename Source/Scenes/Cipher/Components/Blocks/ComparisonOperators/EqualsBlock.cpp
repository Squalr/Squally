#include "EqualsBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

#include "Strings/Cipher/Operations/SHR.h"

using namespace cocos2d;

EqualsBlock* EqualsBlock::create(BlockType blockType)
{
	EqualsBlock* instance = new EqualsBlock(blockType);

	instance->autorelease();

	return instance;
}

EqualsBlock::EqualsBlock(BlockType blockType) : super(blockType, CipherResources::Icons_Equals, Strings::Cipher_Operations_SHR::create())
{
}

EqualsBlock::~EqualsBlock()
{
}

unsigned char EqualsBlock::compute()
{
	if (this->currentInputs.size() < 1)
	{
		return (unsigned char)(0);
	}

	return this->currentInputs[0];
}

BlockBase* EqualsBlock::spawn()
{
	return EqualsBlock::create();
}

bool EqualsBlock::compare(unsigned char inputA, unsigned char inputB)
{
	return inputA == inputB;
}
