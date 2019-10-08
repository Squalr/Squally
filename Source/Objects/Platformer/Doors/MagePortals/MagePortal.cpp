#include "MagePortal.h"

#include "cocos/base/CCValue.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

MagePortal::MagePortal(ValueMap& properties) : super(properties, Size(128.0f, 256.0f))
{
	this->contentNode = Node::create();
	
	this->contentNode->setScaleX(0.5f);

	this->addChild(this->contentNode);
}

MagePortal::~MagePortal()
{
}

void MagePortal::onEnter()
{
	super::onEnter();
}

void MagePortal::initializePositions()
{
	super::initializePositions();
}

void MagePortal::initializeListeners()
{
	super::initializeListeners();
}
