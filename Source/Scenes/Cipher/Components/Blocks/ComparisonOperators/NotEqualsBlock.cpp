#include "NotEqualsBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

NotEqualsBlock* NotEqualsBlock::create(BlockType blockType)
{
	NotEqualsBlock* instance = new NotEqualsBlock(blockType);

	instance->autorelease();

	return instance;
}

NotEqualsBlock::NotEqualsBlock(BlockType blockType) : super(blockType, CipherResources::Icons_NotEquals, Strings::Cipher_Operations_SHR::create())
{
}

NotEqualsBlock::~NotEqualsBlock()
{
}

unsigned char NotEqualsBlock::compute()
{
	return this->inputLeft;
}

bool NotEqualsBlock::compare(unsigned char inputA, unsigned char inputB)
{
	return inputA != inputB;
}
