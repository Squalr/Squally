#include "AsciiTable.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"
#include "Scenes/Cipher/CipherState.h"

#include "Resources/CipherResources.h"

using namespace cocos2d;

AsciiTable* AsciiTable::create()
{
	AsciiTable* instance = new AsciiTable();

	instance->autorelease();

	return instance;
}

AsciiTable::AsciiTable()
{
}

AsciiTable::~AsciiTable()
{
}

void AsciiTable::onEnter()
{
	super::onEnter();
}

void AsciiTable::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void AsciiTable::onBeforeStateChange(CipherState* cipherState)
{
	super::onBeforeStateChange(cipherState);
}

void AsciiTable::onAnyStateChange(CipherState* cipherState)
{
	super::onAnyStateChange(cipherState);
}
