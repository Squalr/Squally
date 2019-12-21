#include "ClickableTextNode.h"

#include <typeinfo>

#include "cocos/2d/CCLabel.h"
#include "cocos/2d/CCNode.h"
#include "cocos/2d/CCSprite.h"

using namespace cocos2d;

ClickableTextNode* ClickableTextNode::create(
	Label* label,
	Label* labelSelected,
	std::string spriteResource,
	std::string spriteSelectedResource)
{
	return ClickableTextNode::create(
		label,
		labelSelected,
		Sprite::create(spriteResource),
		Sprite::create(spriteSelectedResource)
	);
}

ClickableTextNode* ClickableTextNode::create(
	Label* label,
	Label* labelSelected,
	Node* spriteResource,
	std::string spriteSelectedResource)
{
	ClickableTextNode* instance = new ClickableTextNode(
		label,
		labelSelected,
		spriteResource, 
		Sprite::create(spriteSelectedResource)
	);

	instance->autorelease();

	return instance;
}

ClickableTextNode* ClickableTextNode::create(
	Label* label,
	Label* labelSelected,
	Node* content, 
	Node* contentSelected)
{
	ClickableTextNode* instance = new ClickableTextNode(
		label,
		labelSelected,
		content,
		contentSelected);

	instance->autorelease();

	return instance;
}

ClickableTextNode::ClickableTextNode(
	Label* label,
	Label* labelSelected,
	Node* content,
	Node* contentSelected) : ClickableNode(content, contentSelected)
{
	this->label = label;
	this->labelSelected = labelSelected;

	Vec2 center = this->getContentSize() / 2.0f;

	this->label->setPosition(center);
	this->labelSelected->setPosition(center);

	this->setCascadeOpacityEnabled(true);

	this->content->addChild(label);
	this->contentSelected->addChild(labelSelected);
}

ClickableTextNode::~ClickableTextNode()
{
}

void ClickableTextNode::setTextVisible(bool isVisible)
{
	this->label->setVisible(isVisible);
	this->labelSelected->setVisible(isVisible);
}

void ClickableTextNode::setTextOffset(Vec2 offset)
{
	Vec2 center = this->getContentSize() / 2.0f;

	this->label->setPosition(center + offset);
	this->labelSelected->setPosition(center + offset);
}