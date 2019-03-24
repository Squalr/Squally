#include "Equals.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

#include "Strings/Cipher/Operations/SHR.h"

using namespace cocos2d;

Equals* Equals::create(BlockType blockType)
{
	Equals* instance = new Equals(blockType);

	instance->autorelease();

	return instance;
}

Equals::Equals(BlockType blockType) : super(blockType, ConnectionType::Single, ConnectionType::Double, ClickableNode::create(CipherResources::Blocks_BlockYellow, CipherResources::Blocks_BlockYellow), CipherResources::Icons_Splitter, Strings::Cipher_Operations_SHR::create())
{
}

Equals::~Equals()
{
}

void Equals::onEnter()
{
	super::onEnter();
}

void Equals::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

char Equals::compute()
{
	if (this->currentInputs.size() < 1)
	{
		return char(0);
	}

	return this->currentInputs[0];
}

BlockBase* Equals::spawn()
{
	return Equals::create();
}
