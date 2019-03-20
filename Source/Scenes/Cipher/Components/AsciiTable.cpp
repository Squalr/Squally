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
	this->viewAsciiTableButton = ClickableNode::create(CipherResources::Buttons_AsciiTableButton, CipherResources::Buttons_AsciiTableButtonSelected);

	this->addChild(this->viewAsciiTableButton);
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

	this->viewAsciiTableButton->setPosition(Vec2(visibleSize.width / 2.0f + Config::LeftColumnCenter + 448.0f, visibleSize.height / 2.0f + 420.0f));
}

void AsciiTable::onBeforeStateChange(CipherState* cipherState)
{
	super::onBeforeStateChange(cipherState);
}

void AsciiTable::onAnyStateChange(CipherState* cipherState)
{
	super::onAnyStateChange(cipherState);
}
