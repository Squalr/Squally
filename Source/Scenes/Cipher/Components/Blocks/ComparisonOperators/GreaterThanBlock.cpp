#include "GreaterThanBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

GreaterThanBlock* GreaterThanBlock::create(BlockType blockType)
{
	GreaterThanBlock* instance = new GreaterThanBlock(blockType);

	instance->autorelease();

	return instance;
}

GreaterThanBlock::GreaterThanBlock(BlockType blockType) : super(blockType, CipherResources::Icons_GreaterThan, Strings::Cipher_Operations_SHR::create())
{
}

GreaterThanBlock::~GreaterThanBlock()
{
}

unsigned char GreaterThanBlock::compute()
{
	if (this->currentInputs.size() < 1)
	{
		return (unsigned char)(0);
	}

	return this->currentInputs[0];
}

bool GreaterThanBlock::compare(unsigned char inputA, unsigned char inputB)
{
	return inputA > inputB;
}
