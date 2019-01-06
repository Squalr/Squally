#include "ClickableIconNode.h"

#include "cocos/2d/CCNode.h"
#include "cocos/2d/CCSprite.h"

using namespace cocos2d;

ClickableIconNode* ClickableIconNode::create(
	std::string normalSprite,
	std::string selectedSprite,
	std::string spriteNormal,
	std::string spriteSelectedResource)
{
	return ClickableIconNode::create(
		Sprite::create(normalSprite),
		Sprite::create(selectedSprite),
		Sprite::create(spriteNormal),
		Sprite::create(spriteSelectedResource)
	);
}

ClickableIconNode* ClickableIconNode::create(
	Sprite* normalSprite,
	Sprite* selectedSprite,
	std::string spriteNormal,
	std::string spriteSelectedResource)
{
	return ClickableIconNode::create(
		normalSprite,
		selectedSprite,
		Sprite::create(spriteNormal),
		Sprite::create(spriteSelectedResource)
	);
}

ClickableIconNode* ClickableIconNode::create(
	Sprite* normalSprite,
	Sprite* selectedSprite,
	Node* nodeNormal,
	Node* nodeSelected)
{
	ClickableIconNode* instance = new ClickableIconNode(
		normalSprite,
		selectedSprite,
		nodeNormal,
		nodeSelected);

	instance->autorelease();

	return instance;
}

ClickableIconNode::ClickableIconNode(
	Sprite* normalSprite,
	Sprite* selectedSprite,
	Node* nodeNormal,
	Node* nodeSelected) : super(nodeNormal, nodeSelected)
{
	this->normalContentSprite = normalSprite;
	this->selectedContentSprite = selectedSprite;

	Vec2 center = this->getContentSize() / 2.0f;

	this->normalContentSprite->setPosition(center);
	this->selectedContentSprite->setPosition(center);

	this->sprite->addChild(this->normalContentSprite);
	this->spriteSelected->addChild(this->selectedContentSprite);
}

ClickableIconNode::~ClickableIconNode()
{
}

void ClickableIconNode::setIconOffset(Vec2 offset)
{
	Vec2 center = this->getContentSize() / 2.0f;

	this->normalContentSprite->setPosition(center + offset);
	this->selectedContentSprite->setPosition(center + offset);
}