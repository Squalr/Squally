#include "SmartClippingNode.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCDrawNode.h"

using namespace cocos2d;

const Color4F SmartClippingNode::DebugColor = Color4F(0.0f, 1.0f, 0.0f, 0.5f);

SmartClippingNode* SmartClippingNode::create(cocos2d::Node* contentNode, float radius, Vec2 center, int segments)
{
	DrawNode* stencil = DrawNode::create();

	stencil->drawSolidCircle(center, radius, 0.0f, segments, SmartClippingNode::DebugColor);

	return SmartClippingNode::create(contentNode, stencil);
}

SmartClippingNode* SmartClippingNode::create(cocos2d::Node* contentNode, Rect bounds)
{
	DrawNode* stencil = DrawNode::create();

	stencil->drawSolidRect(bounds.origin, Vec2(bounds.origin + bounds.size), SmartClippingNode::DebugColor);

	return SmartClippingNode::create(contentNode, stencil);
}

SmartClippingNode* SmartClippingNode::create(Node* contentNode, DrawNode* stencil)
{
	SmartClippingNode* instance = new SmartClippingNode(contentNode, stencil);

	instance->autorelease();

	return instance;
}

SmartClippingNode::SmartClippingNode(Node* contentNode, DrawNode* stencil)
{
	this->stencil = stencil;

	this->clip = ClippingNode::create(this->stencil);

	this->stencil->setOpacity(0);

	this->clip->addChild(contentNode);
	this->addChild(this->clip);
	this->addChild(stencil);
}

SmartClippingNode::~SmartClippingNode()
{
}

void SmartClippingNode::onEnter()
{
	super::onEnter();
}

void SmartClippingNode::onDeveloperModeEnable(int debugLevel)
{
	super::onDeveloperModeEnable(debugLevel);

	this->stencil->setOpacity(255);
}

void SmartClippingNode::onDeveloperModeDisable()
{
	this->stencil->setOpacity(0);
}
