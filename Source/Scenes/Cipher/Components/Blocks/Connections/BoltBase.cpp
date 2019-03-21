#include "BoltBase.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

BoltBase::BoltBase()
{
	this->connectButton = ClickableNode::create(UIResources::EmptyImage, UIResources::EmptyImage);

	this->connectButton->setContentSize(Size(48.0f, 48.0f));

	this->addChild(this->connectButton);
}

BoltBase::~BoltBase()
{
}

void BoltBase::onEnter()
{
	super::onEnter();
}

void BoltBase::initializePositions()
{
	super::initializePositions();
}
