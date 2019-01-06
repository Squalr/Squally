#include "ClickableTextNode.h"

#include <typeinfo>

#include "cocos/2d/CCLabel.h"
#include "cocos/2d/CCNode.h"
#include "cocos/2d/CCSprite.h"

using namespace cocos2d;

ClickableTextNode* ClickableTextNode::create(
	Label* normalLabel,
	Label* selectedLabel,
	std::string spriteNormal,
	std::string spriteSelectedResource)
{
	return ClickableTextNode::create(
		normalLabel,
		selectedLabel,
		Sprite::create(spriteNormal),
		Sprite::create(spriteSelectedResource)
	);
}

ClickableTextNode* ClickableTextNode::create(
	Label* normalLabel,
	Label* selectedLabel,
	Node* spriteNormal,
	std::string spriteSelectedResource)
{
	ClickableTextNode* instance = new ClickableTextNode(
		normalLabel,
		selectedLabel,
		spriteNormal, 
		Sprite::create(spriteSelectedResource)
	);

	instance->autorelease();

	return instance;
}

ClickableTextNode* ClickableTextNode::create(
	Label* normalLabel,
	Label* selectedLabel,
	Node* nodeNormal, 
	Node* nodeSelected)
{
	ClickableTextNode* instance = new ClickableTextNode(
		normalLabel,
		selectedLabel,
		nodeNormal,
		nodeSelected);

	instance->autorelease();

	return instance;
}

ClickableTextNode::ClickableTextNode(
	Label* normalLabel,
	Label* selectedLabel,
	Node* nodeNormal,
	Node* nodeSelected) : ClickableNode(nodeNormal, nodeSelected)
{
	this->normalContentLabel = normalLabel;
	this->selectedContentLabel = selectedLabel;
	this->normalContent = nodeNormal;
	this->selectedContent = nodeSelected;

	Vec2 center = this->getContentSize() / 2.0f;

	normalLabel->setPosition(center);
	selectedLabel->setPosition(center);

	this->setCascadeOpacityEnabled(true);

	nodeNormal->addChild(normalLabel);
	nodeSelected->addChild(selectedLabel);
}

ClickableTextNode::~ClickableTextNode()
{
}

void ClickableTextNode::setTextOffset(Vec2 offset)
{
	Vec2 center = this->getContentSize() / 2.0f;

	this->normalContentLabel->setPosition(center + offset);
	this->selectedContentLabel->setPosition(center + offset);
}