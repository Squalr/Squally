#include "MagePortal.h"

#include "cocos/2d/CCDrawNode.h"
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

void MagePortal::drawEdge(cocos2d::Color4F edgeColor, cocos2d::DrawNode* drawNode, float radius, int thickness)
{
	for (int index = 0; index < thickness; index++)
	{
		drawNode->drawCircle(Vec2::ZERO, radius, 0.0f, 32, false, Color4F::BLACK);
		radius -= 1.0f;
	}
}
