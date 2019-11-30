#include "LessThanBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

LessThanBlock* LessThanBlock::create(BlockType blockType)
{
	LessThanBlock* instance = new LessThanBlock(blockType);

	instance->autorelease();

	return instance;
}

LessThanBlock::LessThanBlock(BlockType blockType) : super(blockType, CipherResources::Icons_LessThan, Strings::Cipher_Operations_SHR::create())
{
}

LessThanBlock::~LessThanBlock()
{
}

unsigned char LessThanBlock::compute()
{
	if (this->currentInputs.size() < 1)
	{
		return (unsigned char)(0);
	}

	return this->currentInputs[0];
}

bool LessThanBlock::compare(unsigned char inputA, unsigned char inputB)
{
	return inputA < inputB;
}
