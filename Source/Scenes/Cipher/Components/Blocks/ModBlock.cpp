#include "ModBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

#include "Strings/Cipher/Operations/MOD.h"

using namespace cocos2d;

ModBlock* ModBlock::create(bool isToolBoxItem)
{
	ModBlock* instance = new ModBlock(isToolBoxItem);

	instance->autorelease();

	return instance;
}

ModBlock::ModBlock(bool isToolBoxItem) : super(isToolBoxItem, ClickableNode::create(CipherResources::BlockAscii, CipherResources::BlockAscii), CipherResources::Icons_Modulo, Strings::Cipher_Operations_MOD::create())
{
}

ModBlock::~ModBlock()
{
}

void ModBlock::onEnter()
{
	super::onEnter();
}

void ModBlock::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

BlockBase* ModBlock::spawn()
{
	return ModBlock::create();
}
